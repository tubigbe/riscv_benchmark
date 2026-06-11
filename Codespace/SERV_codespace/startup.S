#define GPIO_ADDR 0x40000000
#define HALT_ADDR 0x90000000

.section .text.start
.globl _start
_start:
    /* 1. 初始化栈指针 sp。
     * 你的 python3 makehex.py 参数写的是 4096 (4KB RAM)，
     * 栈是向下生长的，所以把 sp 设在 RAM 的最顶端 4096 字节处
     */
    li      sp, 4096

    /* 2. 初始化：将 GPIO 拉高 */
    li	a0, GPIO_ADDR
    addi	t0, zero, 1
    sb	t0, 0(a0)

    /* 3. 稳稳地召唤 C 语言的 main 函数 */
    jal main

    /* 4. 当 main 正常 return 0 退出后，会精准来到这里 */
halt:
    li	t0, HALT_ADDR
    sw	zero, 0(t0)
    j	halt       /* 恢复原作者的大招：死循环轰炸停机地址，逼仿真器立刻退出 */