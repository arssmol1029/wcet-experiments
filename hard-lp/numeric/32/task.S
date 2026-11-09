.syntax unified
.arm
.text
.balign 4
.global benchmark_entry
.type benchmark_entry,%function
benchmark_entry:
 ldr r0, 1f
 b 2f
1: .word prepared_packet
2:
 .inst 0xe92d4bf0
 .incbin "image.bin",4
.size benchmark_entry,.-benchmark_entry
.bss
.balign 4
.global prepared_packet
.type prepared_packet,%object
prepared_packet: .space 128
.size prepared_packet,.-prepared_packet
.section .note.GNU-stack,"",%progbits
