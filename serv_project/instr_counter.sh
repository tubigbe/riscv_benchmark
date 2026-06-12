# =================================================================
# Static instruction counter for a given function in firmware.elf
# Parses objdump disassembly, counts each unique mnemonic.
# Usage: ./instr_counter.sh
# Edit the awk pattern below to target a different function name.
# =================================================================
riscv64-unknown-elf-objdump -d ~/riscv_benchmark/serv_project/firmware.elf | awk '
/<popcount>:/ { flag = 1; next }
flag {
    # Only count lines with hex address + valid instruction
    if ($1 ~ /^[0-9a-f]+:/) {
        if ($3 != "") inst_count[$3]++
    }
    # Stop at ret — popcount function ends here
    if ($0 ~ /ret/) flag = 0
}
END {
    print "[Static] popcount instruction breakdown:"
    print "========================================="
    for (ins in inst_count) {
        printf "%-10s : %d\n", ins, inst_count[ins]
    }
}
'