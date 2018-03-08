	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

UnitTest
	jmp block2505
x	dc.b
y	dc.b
i	dc.b
val	dc.b
ok	dc.b
arr	dc.b	 
	org arr+255
	
iarr	dc.w	 
	org iarr+255
	
str	dc.b
block2505
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit13337
multiplier .byte 0
multiply_eightbit
	cpx #$00
	beq mul_end
	dex
	stx mul_mod+1
	lsr
	sta multiplier
	lda #$00
	ldx #$08
mul_loop
	bcc mul_skip
mul_mod
	adc #$00
mul_skip
	ror
	ror multiplier
	dex
	bne mul_loop
	ldx multiplier
	rts
mul_end
	txa
	rts
multiply_eightbit13337
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto10004
screenMemory = $fb 
screen_x .byte 0 
screen_y .byte 0 
SetScreenPosition
	sta screenMemory+1
	lda #0
	sta screenMemory
	ldy screen_y
	cpy #0
	beq sydone
syloop
	clc
	adc #40
	bcc sskip
	inc screenMemory+1
sskip
	dey
	cpy #$00
	bne syloop
sydone
	ldx screen_x
	cpx #0
	beq sxdone
	clc
	adc screen_x
	bcc sxdone
	inc screenMemory+1
sxdone
	sta screenMemory
	rts
moveto10004
	rts
afterProc_initmoveto
	
	
	; ***********  Defining procedure : initprintstring
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initprintstring
initprintstring
print_text = $fd
print_number_text .dc "    ",0
printstring
	ldy #0
printstringloop
	lda (print_text),y
	cmp #0
	beq printstring_done
	cmp #64
	bcc printstring_skip
	sec
	sbc #64
printstring_skip
	sta (screenMemory),y
	iny
	dex
	cpx #0
	beq printstring_done
	jmp printstringloop
printstring_done
	rts
afterProc_initprintstring
	
	
	; ***********  Defining procedure : Test1
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Test1
Test1
	jmp block16337
block16337

	; Assigning single variable : ok
	lda #1
	; VarNode StoreVariable
	sta ok
	; Assigning single variable : x
	lda #2
	; VarNode StoreVariable
	sta x
	; Assigning single variable : val
	; 8 bit mul
	lda x
	; 8 bit mul of power 2
	
	lda x
	asl
	ldx 
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	lda #12
	cmp val
	beq branchProblem9970
	jmp branch2623
branchProblem9970
	jmp block30568
block30568

	jmp printstring_call19281
printstring_text7085	.dc "ASSIGN X OK IS 2",0
printstring_call19281
	clc
	; TEST
	lda #<printstring_text7085
	adc #0
	ldy #>printstring_text7085
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring

branch2623

	rts
afterProc_Test1

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop9152
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop9152
	lda #0
	sta screen_x
	lda #0
	sta screen_y
	lda #4
	jsr SetScreenPosition
	jsr Test1
	jmp * ; loop like (¤/%

	rts
