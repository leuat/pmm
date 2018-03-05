	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

FirstC64
	jmp block8942
a	dc.b
b	dc.b
c	dc.b
i	dc.b
j	dc.b
k	dc.b
val	dc.b
mainloop	dc.b
time	dc.b
x	dc.b
y	dc.b
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
message	dc.b	 
	org message+255
	
sprite_x	dc.w
sprite_y	dc.w
stars_x	dc.b	 
	org stars_x+100
	
stars_y	dc.b	 
	org stars_y+100
	
stars_dy	dc.b	 
	org stars_dy+100
	
stars_col	dc.b	 
	org stars_col+100
	
clearval	dc.b
scroll_x	dc.b
block8942
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit19264
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
multiply_eightbit19264
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
	jmp moveto22648
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
moveto22648
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
	
	
	; ***********  Defining procedure : initrandom
	;    Procedure type : Built-in function
	;    Requires initialization : yes
	
	; init random
	LDA #$FF
	STA $D40E
	STA $D40F
	LDA #$80
	STA $D412
	jmp continueRandom
upperRandom	dc.b
lowerRandom	dc.b
callRandom
	lda upperRandom
	sbc lowerRandom
	sta upperRandom
RandomLoop
	LDA $D41B ; get random value
	CMP upperRandom  ; compare to
	BCS RandomLoop   ; branch if value >
	ADC lowerRandom
	RTS
continueRandom
	
	
	; ***********  Defining procedure : InitializeSprites
	;    Procedure type : User-defined procedure
	
	jmp afterProc_InitializeSprites
InitializeSprites
	jmp block27446
block27446

	; Assigning single variable : sprite_x
	lda #160
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_y
	lda #180
	sta sprite_y
	txa 
	sta sprite_y+1
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
memcpy23805
	lda sprite0data,x
	sta $340,x
	inx
	cpx #63
	bne memcpy23805

	rts
afterProc_InitializeSprites
	
	
	; ***********  Defining procedure : SoundTest
	;    Procedure type : User-defined procedure
	
	jmp afterProc_SoundTest
SoundTest
	jmp block15890
wave_type	dc.b
block15890

	lda #15
	sta 54272 +24
	lda #10
	sta 54272 +1
	; Binop of two constant values
	lda #0*#16+#0
	sta 54272 +5
	; Binop of two constant values
	lda #15*#16+#6
	sta 54272 +6
	; Add/sub right value is variable/expression
	jmp jmprightvar24370
rightvar6729	.byte	0
jmprightvar24370
	lda wave_type
	sta rightvar6729
	
	lda #1
	clc
	adc rightvar6729
	
	sta 54272 +4
	lda wave_type
	sta 54272 +4

	rts
afterProc_SoundTest
	
	
	; ***********  Defining procedure : PrintText
	;    Procedure type : User-defined procedure
	
	jmp afterProc_PrintText
PrintText
	jmp block15350
block15350

	lda #10
	sta screen_x
	lda #24
	sta screen_y
	lda #4
	jsr SetScreenPosition
	ldx #0
printstring_call15006
	lda message,x
	sta print_text,x
	inx
	cmp #0
	bne printstring_call15006
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
	
	
	; ***********  Defining procedure : MoveSprite
	;    Procedure type : User-defined procedure
	
	jmp afterProc_MoveSprite
MoveSprite
	jmp block24393
block24393

	; Setting sprite position
	lda #0
	tay
	lda sprite_x
	sta $D000,y
	lda sprite_x+1
	cmp #0
	beq spritepos3548
	lda $D010
	ora #1
	sta $D010
	jmp spriteposcontinue19629
spritepos3548
	lda $D010
	and #254
	sta $D010
spriteposcontinue19629
	iny
	lda sprite_y
	sta $D000,y
	jsr callJoystick
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger19954
rightvarInteger24084	.byte	0
jmprightvarInteger19954
	; 8 bit mul of power 2
	
	lda joystickvalue+1
	asl
	asl
	
	sta rightvarInteger24084
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	sec
	sbc rightvarInteger24084
	bcs wordAdd12623
	dex
wordAdd12623
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger4966
rightvarInteger11840	.byte	0
jmprightvarInteger4966
	; 8 bit mul of power 2
	
	lda joystickvalue+2
	asl
	asl
	
	sta rightvarInteger11840
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	clc
	adc rightvarInteger11840
	bcc wordAdd18756
	inx
wordAdd18756
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_y
	jmp jmprightvarInteger26308
rightvarInteger13931	.byte	0
jmprightvarInteger26308
	; 8 bit mul of power 2
	
	lda joystickvalue+3
	asl
	asl
	
	sta rightvarInteger13931
	
	clc
	; integer assignment NodeVar
	lda sprite_y+1
	tax
	lda sprite_y
	
	clc
	adc rightvarInteger13931
	bcc wordAdd7376
	inx
wordAdd7376
	
	sta sprite_y
	txa 
	sta sprite_y+1
	; Assigning single variable : scroll_x
	lda joystickvalue+1
	
	sta scroll_x
	; Assigning single variable : scroll_x
	; Add/sub right value is variable/expression
	jmp jmprightvar32439
rightvar16944	.byte	0
jmprightvar32439
	lda joystickvalue+2
	
	sta rightvar16944
	
	lda scroll_x
	sec
	sbc rightvar16944
	
	sta scroll_x
	lda joystickvalue+4
	
	cmp #1
	bne branchProblem5537
	jmp branchProblem221538
branchProblem5537
	jmp branch24626
branchProblem221538
	jmp block16118
block16118

	lda #32
	sta wave_type
	jsr SoundTest

branch24626

	rts
afterProc_MoveSprite
	
	
	; ***********  Defining procedure : Clear
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Clear
Clear
	jmp block2082
block2082

	lda #6
	ldx #0
fill22929
	sta $d800,x
	inx
	cpx #0
	bne fill22929
	lda #6
	ldx #0
fill16541
	sta $d900,x
	inx
	cpx #0
	bne fill16541
	lda #6
	ldx #0
fill4833
	sta $da00,x
	inx
	cpx #0
	bne fill4833
	lda #6
	ldx #0
fill31115
	sta $db00,x
	inx
	cpx #0
	bne fill31115
	lda clearval
	ldx #0
fill4639
	sta $400,x
	inx
	cpx #0
	bne fill4639
	lda clearval
	ldx #0
fill29658
	sta $500,x
	inx
	cpx #0
	bne fill29658
	lda clearval
	ldx #0
fill22704
	sta $600,x
	inx
	cpx #0
	bne fill22704
	lda clearval
	ldx #0
fill9930
	sta $700,x
	inx
	cpx #0
	bne fill9930

	rts
afterProc_Clear
	
	
	; ***********  Defining procedure : WaitRaster
	;    Procedure type : User-defined procedure
	
	jmp afterProc_WaitRaster
WaitRaster
	jmp block13977
block13977

while31673
	lda val
	cmp #199
	beq branchProblem22386
	jmp branchProblem25021
branchProblem22386
	jmp branch2306
branchProblem25021
	jmp block28745
block28745

	lda #0
	tax
	lda $d012,x
	sta val

	jmp while31673
branch2306

	rts
afterProc_WaitRaster
	
	
	; ***********  Defining procedure : InitStars
	;    Procedure type : User-defined procedure
	
	jmp afterProc_InitStars
InitStars
	jmp block26924
block26924

	; Assigning single variable : i
	lda #0
	sta i
for19072
	jmp block6270
block6270

	lda #0
	sta lowerRandom
	lda #40
	sta upperRandom
	jsr callRandom
	sta x
	lda #0
	sta lowerRandom
	lda #200
	sta upperRandom
	jsr callRandom
	sta y
	lda #0
	sta lowerRandom
	lda #4
	sta upperRandom
	jsr callRandom
	sta val
	lda #1
	sta lowerRandom
	lda #4
	sta upperRandom
	jsr callRandom
	sta c
	; Assigning single variable : stars_x
	lda x
	tay
	lda i
	tax
	tya
	sta stars_x,x
	; Assigning single variable : stars_y
	lda y
	tay
	lda i
	tax
	tya
	sta stars_y,x
	; Assigning single variable : stars_col
	lda val
	tay
	lda i
	tax
	tya
	sta stars_col,x
	; Assigning single variable : stars_dy
	lda c
	tay
	lda i
	tax
	tya
	sta stars_dy,x

	inc i
	lda i
	cmp #100
	bne forLoopFix5829
	jmp forLoopDone26777
forLoopFix5829
	jmp for19072
forLoopDone26777

	rts
afterProc_InitStars
	
	
	; ***********  Defining procedure : UpdateStars
	;    Procedure type : User-defined procedure
	
	jmp afterProc_UpdateStars
UpdateStars
	jmp block15573
block15573

	; Assigning single variable : i
	lda #0
	sta i
for5097
	jmp block16512
block16512

	; Assigning single variable : y
	lda i
	tax
	lda stars_y,x
	
	sta y
	; Assigning single variable : y
	; 8 bit mul of power 2
	
	lda y
	lsr
	lsr
	lsr
	
	sta y
	lda i
	tax
	lda stars_x,x
	
	sta screen_x
	lda y
	sta screen_y
	lda #4
	jsr SetScreenPosition
	lda clearval
	ldy #0
	sta (screenMemory),y
	; Assigning single variable : stars_y
	; Add/sub right value is variable/expression
	jmp jmprightvar13290
rightvar23986	.byte	0
jmprightvar13290
	lda i
	tax
	lda stars_dy,x
	
	sta rightvar23986
	
	lda i
	tax
	lda stars_y,x
	
	clc
	adc rightvar23986
	
	tay
	lda i
	tax
	tya
	sta stars_y,x
	lda i
	tax
	lda stars_y,x
	
	cmp #150
	bcc branchProblem22355
	jmp branchProblem224767
branchProblem22355
	jmp branch9161
branchProblem224767
	jmp block23655
block23655

	; Assigning single variable : stars_y
	lda #0
	tay
	lda i
	tax
	tya
	sta stars_y,x
	lda #0
	sta lowerRandom
	lda #40
	sta upperRandom
	jsr callRandom
	sta val
	; Assigning single variable : stars_x
	lda val
	tay
	lda i
	tax
	tya
	sta stars_x,x

branch9161
	; Assigning single variable : y
	lda i
	tax
	lda stars_y,x
	
	sta y
	; Assigning single variable : x
	lda y
	sta x
	and #7
	sta x
	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	clc
	adc #34
	 ; end mul var with constant
	
	sta x
	; Assigning single variable : y
	; 8 bit mul of power 2
	
	lda y
	lsr
	lsr
	lsr
	
	sta y
	lda i
	tax
	lda stars_x,x
	
	sta screen_x
	lda y
	sta screen_y
	lda #4
	jsr SetScreenPosition
	lda x
	ldy #0
	sta (screenMemory),y
	lda screenMemory+1
	tax
	adc #$D4
	sta screenMemory+1
	lda i
	tax
	lda stars_col,x
	
	sta (screenMemory),y
	txa
	sta screenMemory+1

	inc i
	lda i
	cmp #50
	bne forLoopFix15574
	jmp forLoopDone4031
forLoopFix15574
	jmp for5097
forLoopDone4031

	rts
afterProc_UpdateStars

	lda #0
	tax
	lda #0
	sta $d020,x
	lda #1
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
	; Assigning single variable : clearval
	lda #32
	sta clearval
	jsr Clear
	; Assigning single variable : mainloop
	lda #1
	sta mainloop
	; Assigning single variable : time
	lda #0
	sta time
	; 
	; ****** Inline assembler section

	cli
	
	
	; Assigning single variable : scroll_x
	lda #0
	sta scroll_x
	jsr InitializeSprites
	jsr InitStars
while27350
	lda mainloop
	cmp #10
	bcs branchProblem1150
	jmp branchProblem216941
branchProblem1150
	jmp branch12052
branchProblem216941
	jmp block21724
block21724

	; Assigning single variable : time
	; Add/sub where right value is constant number
	lda time
	clc
	adc #1
	 ; end mul var with constant
	
	sta time
	jsr UpdateStars
	jsr PrintText
	jsr MoveSprite
	jsr WaitRaster

	jmp while27350
branch12052

	rts
	org $1fff
charset
	incbin "test.bin"
