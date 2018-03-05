	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

FirstC64
	jmp block9161
a	dc.b
b	dc.b
c	dc.b
i	dc.b
j	dc.b
k	dc.b
val	dc.b
mainloop	dc.b
idx	dc.b
time	dc.b
c2x	dc.b
c2y	dc.b
ax	dc.b
ay	dc.b
x	dc.b
y	dc.b
scrollx	dc.b
shiftx	dc.b
shifty	dc.b
sprite0data
	incbin "c:/users/leuat/onedrive/documents/github/pmm/pmm///sprite1.bin"
fadeOut
	.byte 0, 13, 11, 5, 2, 10, 9, 15
	.byte 4, 0, 12, 6, 14, 7, 8, 3
	.byte 
fadeRedBlue
	.byte 0, 15, 9, 14, 2, 12, 0, 12
	.byte 9, 0, 2, 0, 11, 5, 6, 12
	.byte 
fade
	.byte 0, 11, 6, 12, 4, 14, 15, 1
	.byte 1, 15, 14, 4, 12, 6, 11, 0
	.byte 
siny	dc.b	 
	org siny+25
	
sinx	dc.b	 
	org sinx+40
	
message	dc.b	 
	org message+255
	
sprite_x	dc.w
sprite_y	dc.w
block9161
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit18636
multiplier	= $02 ; some zeropage adress
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
multiply_eightbit18636
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initjoystick
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initjoystick
initjoystick
joystickvalue .byte 0,0,0,0,4
callJoystick
	lda #0
	sta joystickvalue+1
	sta joystickvalue+2
	sta joystickvalue+3
	sta joystickvalue+4
	lda #%00000001 ; mask joystick up movement
	bit $dc00      ; bitwise AND with address 56320
	bne joystick_down       ; zero flag is not set -> skip to down
	lda #255
	sta joystickvalue+3
joystick_down
	lda #%00000010 ; mask joystick down movement
	bit $dc00      ; bitwise AND with address 56320
	bne joystick_left       ; zero flag is not set -> skip to down
	lda #1
	sta joystickvalue+3
joystick_left
	lda #%00000100 ; mask joystick left movement
	bit $dc00      ; bitwise AND with address 56320
	bne joystick_right       ; zero flag is not set -> skip to down
	lda #1
	sta joystickvalue+1
joystick_right
	lda #%00001000 ; mask joystick up movement
	bit $dc00      ; bitwise AND with address 56320
	bne joystick_button       ; zero flag is not set -> skip to down
	lda #1
	sta joystickvalue+2
joystick_button
	lda #%00010000 ; mask joystick up movement
	bit $dc00      ; bitwise AND with address 56320
	bne callJoystick_end       ; zero flag is not set -> skip to down
	lda #1
	sta joystickvalue+4
callJoystick_end
	rts
	rts
afterProc_initjoystick
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto22355
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
moveto22355
	rts
afterProc_initmoveto
	
	
	; ***********  Defining procedure : initprintstring
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initprintstring
initprintstring
print_text dc "HEISANN",0
	org print_text +#100
printstring
	ldy #0
printstringloop
	lda print_text,x
	cmp #0
	beq printstring_done
	sec
	sbc #64
	sta (screenMemory),y
	iny
	inx
	jmp printstringloop
printstring_done
	rts
afterProc_initprintstring
	
	
	; ***********  Defining procedure : initsinetable
	;    Procedure type : Built-in function
	;    Requires initialization : yes
	
	jmp initsin_continue
sine .byte 0 
	org sine +#255
value .word 0
delta .word 0
initsin_continue
	ldy #$3f
	ldx #$00
initsin_a
	lda value
	clc
	adc delta
	sta value
	lda value+1
	adc delta+1
	sta value+1
	sta sine+$c0,x
	sta sine+$80,y
	eor #$ff
	sta sine+$40,x
	sta sine+$00,y
	lda delta
	adc #$10   ; this value adds up to the proper amplitude
	sta delta
	bcc initsin_b
	inc delta+1
initsin_b
	inx
	dey
	bpl initsin_a
	
	
	; ***********  Defining procedure : Plasma
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Plasma
Plasma
	jmp block24767
block24767

	; Assigning single variable : c2x
	lda ax
	sta c2x
	; Assigning single variable : c2y
	lda ay
	sta c2y
	; Assigning single variable : x
	lda #0
	sta x
for23655
	jmp block15574
block15574

	; Assigning single variable : siny
	; Add/sub right value is variable/expression
	jmp jmprightvar12052
rightvar4031	.byte	0
jmprightvar12052
	lda c2y
	tax
	lda sine,x
	
	sta rightvar4031
	
	lda c2x
	tax
	lda sine,x
	
	clc
	adc rightvar4031
	
	tay
	lda x
	tax
	tya
	sta siny,x
	; Assigning single variable : c2x
	; Add/sub where right value is constant number
	lda c2x
	clc
	adc #4
	 ; end mul var with constant
	
	sta c2x
	; Assigning single variable : c2y
	; Add/sub where right value is constant number
	lda c2y
	clc
	adc #9
	 ; end mul var with constant
	
	sta c2y

	inc x
	lda x
	cmp #25
	bne forLoopFix27350
	jmp forLoopDone1150
forLoopFix27350
	jmp for23655
forLoopDone1150
	; Assigning single variable : ax
	; Add/sub where right value is constant number
	lda ax
	clc
	adc #3
	 ; end mul var with constant
	
	sta ax
	; Assigning single variable : ay
	; Add/sub where right value is constant number
	lda ay
	sec
	sbc #5
	 ; end mul var with constant
	
	sta ay
	; Assigning single variable : x
	lda #0
	sta x
for16941
	jmp block21724
block21724

	; Assigning single variable : sinx
	; Add/sub right value is variable/expression
	jmp jmprightvar3430
rightvar13966	.byte	0
jmprightvar3430
	lda c2y
	tax
	lda sine,x
	
	sta rightvar13966
	
	lda c2x
	tax
	lda sine,x
	
	clc
	adc rightvar13966
	
	tay
	lda x
	tax
	tya
	sta sinx,x
	; Assigning single variable : c2x
	; Add/sub where right value is constant number
	lda c2x
	clc
	adc #6
	 ; end mul var with constant
	
	sta c2x
	; Assigning single variable : c2y
	; Add/sub where right value is constant number
	lda c2y
	clc
	adc #14
	 ; end mul var with constant
	
	sta c2y

	inc x
	lda x
	cmp #40
	bne forLoopFix31107
	jmp forLoopDone30191
forLoopFix31107
	jmp for16941
forLoopDone30191
	; Assigning single variable : y
	lda #9
	sta y
for18007
	jmp block11337
block11337

	lda #1
	sta screen_x
	lda y
	sta screen_y
	lda #4
	jsr SetScreenPosition
	; Assigning single variable : val
	lda y
	tax
	lda siny,x
	
	sta val
	; Assigning single variable : x
	lda #1
	sta x
for15457
	jmp block12287
block12287

	; Assigning single variable : k
	; Add/sub right value is variable/expression
	jmp jmprightvar10383
rightvar27753	.byte	0
jmprightvar10383
	lda val
	sta rightvar27753
	
	lda x
	tax
	lda sinx,x
	
	clc
	adc rightvar27753
	
	sta k
	; Assigning single variable : k
	; 8 bit mul of power 2
	
	lda k
	lsr
	lsr
	lsr
	
	sta k
	; Assigning single variable : c
	; 8 bit mul of power 2
	
	lda k
	lsr
	
	tax
	lda fade,x
	
	sta c
	; Assigning single variable : k
	; Add/sub where right value is constant number
	lda k
	clc
	adc #64
	 ; end mul var with constant
	
	sta k
	ldy #0
	sta (screenMemory),y
	iny
	sta (screenMemory),y
	lda screenMemory+1
	tax
	adc #$D4
	sta screenMemory+1
	lda c
	sta (screenMemory),y
	dey
	sta (screenMemory),y
	txa
	sta screenMemory+1
	lda #2
	sta screen_x
	lda screenMemory
	cpx #0
	beq incscreenx14945
	clc
	adc screen_x
	bcc incscreenx14945
	inc screenMemory+1
incscreenx14945
	sta screenMemory

	inc x
	lda x
	cmp #10
	bne forLoopFix8909
	jmp forLoopDone32209
forLoopFix8909
	jmp for15457
forLoopDone32209

	inc y
	lda y
	cmp #23
	bne forLoopFix9758
	jmp forLoopDone24221
forLoopFix9758
	jmp for18007
forLoopDone24221

	rts
afterProc_Plasma
	
	
	; ***********  Defining procedure : InitializeSprites
	;    Procedure type : User-defined procedure
	
	jmp afterProc_InitializeSprites
InitializeSprites
	jmp block18588
block18588

	lda #0
	tax
	lda #13
	sta $7f8,x
	lda #1
	tax
	lda #13
	sta $7f8,x
	lda #0
	tax
	lda #7
	sta $d015,x
	lda #0
	tax
	lda #1
	sta $d027,x
	lda #1
	tax
	lda #7
	sta $d027,x
	ldx #0
memcpy6422
	lda sprite0data,x
	sta $340,x
	inx
	cpx #63
	bne memcpy6422

	rts
afterProc_InitializeSprites
	
	
	; ***********  Defining procedure : MoveSprite
	;    Procedure type : User-defined procedure
	
	jmp afterProc_MoveSprite
MoveSprite
	jmp block24946
block24946

	; Setting sprite position
	lda #0
	tay
	lda sprite_x
	sta $D000,y
	lda sprite_x+1
	cmp #0
	beq spritepos27506
	lda $D010
	ora #1
	sta $D010
	jmp spriteposcontinue13030
spritepos27506
	lda $D010
	and #254
	sta $D010
spriteposcontinue13030
	iny
	lda sprite_y
	sta $D000,y
	jsr callJoystick
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger900
rightvarInteger29168	.byte	0
jmprightvarInteger900
	; 8 bit mul of power 2
	
	lda joystickvalue+1
	asl
	asl
	
	sta rightvarInteger29168
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	sec
	sbc rightvarInteger29168
	bcs wordAdd16413
	dex
wordAdd16413
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger1655
rightvarInteger18762	.byte	0
jmprightvarInteger1655
	; 8 bit mul of power 2
	
	lda joystickvalue+2
	asl
	asl
	
	sta rightvarInteger18762
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	clc
	adc rightvarInteger18762
	bcc wordAdd32591
	inx
wordAdd32591
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_y
	jmp jmprightvarInteger27624
rightvarInteger6359	.byte	0
jmprightvarInteger27624
	; 8 bit mul of power 2
	
	lda joystickvalue+3
	asl
	asl
	
	sta rightvarInteger6359
	
	clc
	; integer assignment NodeVar
	lda sprite_y+1
	tax
	lda sprite_y
	
	clc
	adc rightvarInteger6359
	bcc wordAdd17410
	inx
wordAdd17410
	
	sta sprite_y
	txa 
	sta sprite_y+1
	lda joystickvalue+3
	
	cmp #1
	bne branchProblem6483
	jmp branchProblem227595
branchProblem6483
	jmp branch20537
branchProblem227595
	jmp block4041
block4041

	lda #3
	sta screen_x
	lda #3
	sta screen_y
	lda #4
	jsr SetScreenPosition

branch20537

	rts
afterProc_MoveSprite
	
	
	; ***********  Defining procedure : PrintText
	;    Procedure type : User-defined procedure
	
	jmp afterProc_PrintText
PrintText
	jmp block3602
block3602

	lda #10
	sta screen_x
	lda #24
	sta screen_y
	lda #4
	jsr SetScreenPosition
	ldx #0
printstring_call24350
	lda message,x
	sta print_text,x
	inx
	cmp #0
	bne printstring_call24350
	lda #0
	tax
	jsr printstring
	lda #17
	sta screen_x
	lda #24
	sta screen_y
	lda #4
	jsr SetScreenPosition
	ldx #0
	lda time
	tay
	and #$0F
	cmp #$0A
	bcc printnumber_l1
	sec
	sbc #$39
printnumber_l1
	adc #$30 + #64
	sta print_text,x
	inx
	tya
	and #$F0
	lsr
	lsr 
	lsr 
	lsr 
	cmp #$0A
	bcc printnumber_l2
	sec
	sbc #$39
printnumber_l2
	adc #$30 + #64
	sta print_text,x
	inx
	lda #0
	sta print_text,x
	ldx #0
	jsr printstring

	rts
afterProc_PrintText

	lda #0
	sta screen_x
	lda #0
	sta screen_y
	lda #4
	jsr SetScreenPosition
	; Assigning single variable : message
	jmp stringassign30836
stringassignstr9374	.dc "TIME",0
stringassign30836
	ldx #0
stringassigncpy11020
	lda stringassignstr9374,x
	sta message,x
	inx
	cmp #0
	bne stringassigncpy11020
	; Assigning single variable : i
	lda #0
	sta i
	; Assigning single variable : a
	lda #4
	sta a
	; Assigning single variable : b
	lda #4
	sta b
	; Assigning single variable : a
	; 8 bit mul
	lda b
	ldx #3
	jsr multiply_eightbit
	txa
	
	sta a
	lda #0
	tax
	lda a
	sta $d020,x
	lda #1
	tax
	lda #0
	sta $d020,x
	lda #0
	tax
	lda #0
	sta $d020,x
	lda #0
	tax
	lda #24
	sta $d018,x
	lda #0
	tax
	lda #13
	sta $c202,x
	; Assigning single variable : mainloop
	lda #1
	sta mainloop
	; Assigning single variable : time
	lda #0
	sta time
	; Assigning single variable : ax
	lda #1
	sta ax
	; Assigning single variable : ay
	lda #5
	sta ay
	lda #5
	ldx #0
fill4596
	sta $d800,x
	inx
	cpx #0
	bne fill4596
	lda #5
	ldx #0
fill24021
	sta $d900,x
	inx
	cpx #0
	bne fill24021
	lda #5
	ldx #0
fill27348
	sta $da00,x
	inx
	cpx #0
	bne fill27348
	lda #5
	ldx #0
fill23199
	sta $db00,x
	inx
	cpx #0
	bne fill23199
	; 
	; ****** Inline assembler section

	cli
	
	
	jsr InitializeSprites
while24484
	lda mainloop
	cmp #10
	bcs branchProblem8281
	jmp branchProblem24734
branchProblem8281
	jmp branch19668
branchProblem24734
	jmp block53
block53

	; Assigning single variable : time
	; Add/sub where right value is constant number
	lda time
	clc
	adc #1
	 ; end mul var with constant
	
	sta time
	; Assigning single variable : shiftx
	; Add/sub where right value is constant number
	lda shiftx
	clc
	adc #1
	 ; end mul var with constant
	
	sta shiftx
	; Assigning single variable : shifty
	; Add/sub where right value is constant number
	lda shifty
	clc
	adc #3
	 ; end mul var with constant
	
	sta shifty
	jsr Plasma
	jsr PrintText
	jsr MoveSprite

	jmp while24484
branch19668

	rts
	org $1fff
charset
	incbin "test.bin"
