.syntax unified
.arm
.section .text.startup,"ax",%progbits
.global _start
.type _start,%function
_start:
    ldr sp,=__study_stack_top
    bl main
    ldr r1,=study_main_return_code
    str r0,[r1]
1:  b 1b
.size _start,.-_start
.section .bss.study_stack,"aw",%nobits
.balign 8
.global __study_stack_bottom
__study_stack_bottom:
.space 65536
.global __study_stack_top
__study_stack_top:
.section .note.GNU-stack,"",%progbits
