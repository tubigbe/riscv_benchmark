riscv64-unknown-elf-objdump -d /home/chenyoo/riscv_benchmark/serv_project/firmware.elf | awk '
/<main>:/ { flag = 1; next }
flag {
    # 确保是带有十六进制冒号的有效指令行
    if ($1 ~ /^[0-9a-f]+:/) {
        if ($3 != "") inst_count[$3]++
    }
    # 踩到 ret 标志说明 main 函数结束，拉闸退出
    if ($0 ~ /ret/) flag = 0
}
END {
    print "📊 [静态分析] main 函数指令构成及出现次数："
    print "========================================="
    for (ins in inst_count) {
        printf "%-10s : %d 次\n", ins, inst_count[ins]
    }
}
'