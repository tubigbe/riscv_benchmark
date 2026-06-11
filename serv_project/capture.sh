# =================================================================
# 自动化抓取反汇编门牌号
# =================================================================
ELF_FILE="/home/chenyoo/riscv_benchmark/serv_project/firmware.elf"

# 【自动抓起点】：找到 <main> 标志行的下一行，并提取第一列的十六进制地址
START_PC=$(arm-none-eabi-objdump -d $ELF_FILE | awk '/<main>:/ {getline; print $1}' | tr -d ':')

# 【自动抓终点】：找到 <main> 后面第一个出现 ret（或者流出循环的 nop）的地址
# 这里以 ret 为例，`-O2` 拍平代码后，通常直接冲向 ret 结束
STOP_PC=$(arm-none-eabi-objdump -d $ELF_FILE | awk '/<main>:/, /ret/ {if($0 ~ /ret/) print $1}' | head -n 1 | tr -d ':')

# 打印一下，看看脚本有没有偷懒，是不是精准抓到了
echo "🤖 自动化雷达扫描成功！"
echo "📍 计时起点 (Start PC): 0000${START_PC}"
echo "📍 计时终点 (Stop PC) : 0000${STOP_PC}"