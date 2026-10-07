__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
main:
.L__stack_usage = 0
        in r24,0x4
        ori r24,lo8(33)
        out 0x4,r24
        cbi 0xa,2
        sbi 0xb,2
        ldi r25,lo8(1)
        rjmp .L4
.L2:
        sbi 0x5,5
.L3:
        in r24,0x5
        eor r24,r25
        out 0x5,r24
.L4:
        sbis 0x9,2
        rjmp .L2
        cbi 0x5,5
        rjmp .L3