# HEX Files for Hardware Cost / Dynamic Power Testing

> **说明对象：AI**。这是一个任务交接说明。下面的"你"指接手此任务的 AI。

## 背景

SERV（bit-serial RV32I）核上实现了一个自定义 popcount 指令，经历了两个阶段：

- **V1（旧，已废弃）**：`popcount rd, rs1` 寄存器版（32-bit 固定），子模块 commit `ac5aa03`。
- **V2（当前）**：`popcount rd, rs1(start), rs2(end)` 内存区间版（任意长度），子模块 commit `e81a9cf`。

功能与周期已验证：同一 5-word 数组
`{0x00000000, 0xFFFFFFFF, 0xDEADBEEF, 0x55555555, 0xAAAAAAAA}`，
软件 popcount = 40860 周期，V1 = 914，V2 = 464。详见 `serv_project/bench_results/`。

## 接下来的任务（你需要在 Windows/Vivado 环境完成）

用户的环境 **没有 Vivado**（工作环境在 WSL/Linux）。硬件测量需要在 **Windows 的 Vivado** 上做。你**不需要**帮用户搭建/操作 Vivado，但需要：

1. **明确硬件成本对比方法**，并准备好所需产物。
2. **用这两个 hex 测 dynamic power**。

### 任务 A：硬件成本（静态面积）

硬件成本 = 综合 RTL 得到的 LUT/FF 面积，**与 hex/固件无关**（hex 只用于验证功能 / 测动态功耗）。

对比方式：

| 综合哪个 RTL | 用途 |
|-------------|------|
| baseline SERV（**不带**任何自定义逻辑） | 基准面积 |
| `e81a9cf`（带区间 popcount 自定义硬件） | 自定义指令面积 |

硬件成本 = 两者面积之差。

- **⚠️ 别踩坑**：不要用同一个 RTL 综合两遍去"对比"——结果相同、差异为 0。必须综合两个不同的 RTL 版本。
- baseline SERV：从子模块 git 历史找（如 `f5ddfaa` 或更早的上游），或把 `e81a9cf` 中自定义逻辑去掉（`serv_customized_alu.v`、`serv_customized_state.v` 及相关 mux/门控）。

### 任务 B：动态功耗（dynamic power）

动态功耗**依赖固件的切换活动**，所以用 hex 就能测出区别（这也是生成 hex 的原因）。

| hex 文件 | 加载到哪个综合后的设计 | 固件内容 |
|----------|----------------------|----------|
| `popcount_sw_bench.hex` | baseline SERV | 软件 32-bit 循环 popcount，**无**自定义指令 |
| `popcount_v2_bench.hex` | `e81a9cf` | **1 条**区间 popcount 指令（`0x00E787AB`） |

- 两个 hex 都计算同样的工作量（5 words 总和 = 88 = 0x58），只是 V2 用硬件指令（约 250 周期）替代软件循环（约 40860 周期），切换活动差异大，适合测动态功耗。
- hex 是 RTL 无关的编译产物（机器码），所以在**任何 RTL 版本下编译都一样**，无需为生成 hex 切换 RTL。

## 已准备好的产物

```
serv_project/hex_download/
├── README.md              ← 本文件
├── popcount_sw_bench.hex  ← 软件 popcount 固件（0 条自定义指令）
└── popcount_v2_bench.hex  ← 区间 popcount 固件（1 条自定义指令）
```

两个 hex 都会把结果低字节（0x58）写入 `0x80000000`，然后写 `0x90000000`（halt）——Vivado 里可据此判断仿真/功耗运行是否正常结束。

## 给未来 AI 的调试警告

详见 `AGENTS.md`（项目根目录，被 .gitignore 忽略）。关键几条：
1. **VCD 信号 ID 每次重建都会变**——务必每次重新从 header 解析。
2. 位串行地址捕获用 `{bit, reg[31:1]}` 右移组装（LSB-first）。
3. `cus_mode` 必须声明为 `[1:0]`（2-bit mode），1-bit 会导致 WRITE_BACK 不移位。
4. WRITE_BACK 需 bit_cnt==0 保持、bit_cnt==1 起移位，否则结果 = 真值>>1。
5. PC 交接：is_customized 需在 WRITE_BACK 起始拉低（PC 更新是位串行，需 counter 跑全程）。
6. V1 的旧 RTL（`ac5aa03`）才能跑 V1 固件；当前 RTL 会把 V1 编码（rs2=x0）误判成区间 popcount。
