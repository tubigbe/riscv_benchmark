/* startup.S — SERV bare-metal entry point
 * Same as ../startup.S but _start is placed in .text.start
 * so the linker script puts it at address 0x00000000.
 */
#define GPIO_ADDR 0x40000000
#define HALT_ADDR 0x90000000

.section .text.start, "ax"
.globl _start
_start:
    /* 1. GPIO → high */
    li	a0, GPIO_ADDR
    addi	t0, zero, 1
    sb	t0, 0(a0)

    /* 2. Jump to C main */
    jal main

    /* 3. Halt if main returns */
halt:
    li	t0, HALT_ADDR
    sw	zero, 0(t0)
1:	j	1b


/*
 * asm_uart_putchar — bit-banged UART via GPIO
 * C calling convention: character arrives in a0
 */
.globl asm_uart_putchar
asm_uart_putchar:
    mv      t0, a0
    li      a0, GPIO_ADDR
    ori	t0, t0, 0x100
    slli	t0, t0, 1
2:	sb	t0, 0(a0)
    srli	t0, t0, 1
    nop
    nop
    bnez	t0, 2b
    ret
