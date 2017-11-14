
.section .text
.code 16
.thumb_func

.long _initial_stack
.long _start
.long default_handler
.long default_handler
.long default_handler
.long default_handler
.long default_handler
.long 0
.long 0
.long 0
.long 0
.long default_handler
.long default_handler
.long 0
.long default_handler
.long default_handler


_start:
	ldr r0, =_initial_stack
	mov sp, r0
	ldr r0, =main
	bx r0
default_handler:
	b	default_handler

