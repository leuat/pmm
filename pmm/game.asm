	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

FirstC64
	jmp block1127
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
	.byte 11, 6, 12, 4, 14, 15, 1, 1
	.byte 15, 14, 4, 12, 6, 11, 0, 0
	.byte 
bar_0	dc.b
colorIndex	dc.b
colorAdd	dc.b
colorSize	dc.b
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
block1127
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit14633
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
multiply_eightbit14633
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
	jmp moveto28240
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
moveto28240
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
	
	
	; ***********  Defining procedure : InitializeSprites
	;    Procedure type : User-defined procedure
	
	jmp afterProc_InitializeSprites
InitializeSprites
	jmp block1862
block1862

	; 
	; ****** Inline assembler section
	ldx #0
	
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
	lda #31
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
memcpy15127
	lda sprite0data,x
	sta $340,x
	inx
	cpx #63
	bne memcpy15127

	rts
afterProc_InitializeSprites
	
	
	; ***********  Defining procedure : SoundTest
	;    Procedure type : User-defined procedure
	
	jmp afterProc_SoundTest
SoundTest
	jmp block27577
wave_type	dc.b
block27577

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
	jmp jmprightvar2340
rightvar23817	.byte	0
jmprightvar2340
	lda wave_type
	sta rightvar23817
	
	lda #1
	clc
	adc rightvar23817
	
	sta 54272 +4
	lda wave_type
	sta 54272 +4

	rts
afterProc_SoundTest
	
	
	; ***********  Defining procedure : PrintText
	;    Procedure type : User-defined procedure
	
	jmp afterProc_PrintText
PrintText
	jmp block10142
block10142

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
	jmp block28400
block28400

	; Setting sprite position
	lda #0
	tay
	lda sprite_x
	sta $D000,y
	lda sprite_x+1
	cmp #0
	beq spritepos6558
	lda $D010
	ora #1
	sta $D010
	jmp spriteposcontinue21476
spritepos6558
	lda $D010
	and #254
	sta $D010
spriteposcontinue21476
	iny
	lda sprite_y
	sta $D000,y
	jsr callJoystick
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger16430
rightvarInteger10935	.byte	0
jmprightvarInteger16430
	; 8 bit mul of power 2
	
	lda joystickvalue+1
	asl
	asl
	
	sta rightvarInteger10935
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	sec
	sbc rightvarInteger10935
	bcs wordAdd3154
	dex
wordAdd3154
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_x
	jmp jmprightvarInteger3537
rightvarInteger21295	.byte	0
jmprightvarInteger3537
	; 8 bit mul of power 2
	
	lda joystickvalue+2
	asl
	asl
	
	sta rightvarInteger21295
	
	clc
	; integer assignment NodeVar
	lda sprite_x+1
	tax
	lda sprite_x
	
	clc
	adc rightvarInteger21295
	bcc wordAdd5831
	inx
wordAdd5831
	
	sta sprite_x
	txa 
	sta sprite_x+1
	; Assigning single variable : sprite_y
	jmp jmprightvarInteger2927
rightvarInteger17922	.byte	0
jmprightvarInteger2927
	; 8 bit mul of power 2
	
	lda joystickvalue+3
	asl
	asl
	
	sta rightvarInteger17922
	
	clc
	; integer assignment NodeVar
	lda sprite_y+1
	tax
	lda sprite_y
	
	clc
	adc rightvarInteger17922
	bcc wordAdd15623
	inx
wordAdd15623
	
	sta sprite_y
	txa 
	sta sprite_y+1
	; Assigning single variable : scroll_x
	lda joystickvalue+1
	
	sta scroll_x
	; Assigning single variable : scroll_x
	; Add/sub right value is variable/expression
	jmp jmprightvar30211
rightvar28029	.byte	0
jmprightvar30211
	lda joystickvalue+2
	
	sta rightvar28029
	
	lda scroll_x
	sec
	sbc rightvar28029
	
	sta scroll_x
	lda joystickvalue+4
	
	cmp #1
	bne branchProblem26880
	jmp branchProblem212253
branchProblem26880
	jmp branch16211
branchProblem212253
	jmp block3293
block3293

	lda #32
	sta wave_type
	jsr SoundTest

branch16211

	rts
afterProc_MoveSprite
	
	
	; ***********  Defining procedure : Clear
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Clear
Clear
	jmp block21321
block21321

	lda #6
	ldx #0
fill20785
	sta $d800,x
	inx
	cpx #0
	bne fill20785
	lda #6
	ldx #0
fill26528
	sta $d900,x
	inx
	cpx #0
	bne fill26528
	lda #6
	ldx #0
fill10443
	sta $da00,x
	inx
	cpx #0
	bne fill10443
	lda #6
	ldx #0
fill31000
	sta $db00,x
	inx
	cpx #0
	bne fill31000
	lda clearval
	ldx #0
fill10555
	sta $400,x
	inx
	cpx #0
	bne fill10555
	lda clearval
	ldx #0
fill24671
	sta $500,x
	inx
	cpx #0
	bne fill24671
	lda clearval
	ldx #0
fill9270
	sta $600,x
	inx
	cpx #0
	bne fill9270
	lda clearval
	ldx #0
fill7452
	sta $700,x
	inx
	cpx #0
	bne fill7452

	rts
afterProc_Clear
	
	
	; ***********  Defining procedure : WaitRaster
	;    Procedure type : User-defined procedure
	
	jmp afterProc_WaitRaster
WaitRaster
	jmp block9375
block9375

	; 
	; ****** Inline assembler section

	lda $d012
	clc       ;make sure carry is clear
	adc #199  ;add lines to wait
	cmp $d012
	bne *-3   ;check *until* we're at the target raster line

	

	rts
afterProc_WaitRaster
	
	
	; ***********  Defining procedure : InitStars
	;    Procedure type : User-defined procedure
	
	jmp afterProc_InitStars
InitStars
	jmp block14631
block14631

	; Assigning single variable : i
	lda #0
	sta i
for13640
	jmp block8934
block8934

	lda #0
	sta lowerRandom
	lda #40
	sta upperRandom
	jsr callRandom
	sta x
	lda #1
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
	bne forLoopFix18040
	jmp forLoopDone7986
forLoopFix18040
	jmp for13640
forLoopDone7986

	rts
afterProc_InitStars
	
	
	; ***********  Defining procedure : UpdateStars
	;    Procedure type : User-defined procedure
	
	jmp afterProc_UpdateStars
UpdateStars
	jmp block28834
block28834

	; Assigning single variable : i
	lda #0
	sta i
for14248
	jmp block1539
block1539

	; Assigning single variable : stars_y
	; Add/sub right value is variable/expression
	jmp jmprightvar12796
rightvar28765	.byte	0
jmprightvar12796
	lda i
	tax
	lda stars_dy,x
	
	sta rightvar28765
	
	lda i
	tax
	lda stars_y,x
	
	clc
	adc rightvar28765
	
	tay
	lda i
	tax
	tya
	sta stars_y,x
	lda i
	tax
	lda stars_y,x
	
	; Binop of two constant values
	cmp #18*$8
	bcc branchProblem25052
	jmp branchProblem230731
branchProblem25052
	jmp branch10312
branchProblem230731
	jmp block23987
block23987

	; Assigning single variable : stars_y
	lda #1
	tay
	lda i
	tax
	tya
	sta stars_y,x

branch10312
	; Assigning single variable : y
	lda i
	tax
	lda stars_y,x
	
	sta y
	; Assigning single variable : x
	lda y
	sta x
	; Assigning single variable : y
	; 8 bit mul of power 2
	
	lda y
	lsr
	lsr
	lsr
	
	sta y
	lda x
	and #7
	sta x
	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	clc
	adc #34
	 ; end mul var with constant
	
	sta x
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
	lda #40
	sta screen_x
	lda screenMemory
	cpx #0
	beq incscreenx24464
	clc
	adc screen_x
	bcc incscreenx24464
	inc screenMemory+1
incscreenx24464
	sta screenMemory
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
	cmp #10
	bne forLoopFix32557
	jmp forLoopDone14248
forLoopFix32557
	jmp for14248
forLoopDone14248
	lda clearval
	ldx #0
fill29556
	sta $6d0,x
	inx
	cpx #39
	bne fill29556

	rts
afterProc_UpdateStars
	
	
	; ***********  Defining procedure : Update
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Update
Update
	jmp block20170
block20170

	lda #0
	tax
	lda #0
	sta $d020,x
	lda #0
	tax
	lda #0
	sta $d021,x
	jsr UpdateStars
	jsr PrintText
	jsr MoveSprite
	jsr $1806

	rts
afterProc_Update
	
	
	; ***********  Defining procedure : UpdateRaster
	;    Procedure type : User-defined procedure
	
	jmp afterProc_UpdateRaster
UpdateRaster
	dec $d019        ; acknowledge IRQ
	jmp block5450
block5450

	jsr Update
	; Assigning single variable : time
	; Add/sub where right value is constant number
	lda time
	clc
	adc #1
	 ; end mul var with constant
	
	sta time
	; Assigning single variable : colorSize
	lda #4
	sta colorSize
	; Assigning single variable : bar_0
	; Add/sub where right value is constant number
	; 8 bit mul of power 2
	
	; 8 bit mul of power 2
	
	lda time
	asl
	
	tax
	lda sine,x
	lsr
	lsr
	
	clc
	adc #70
	 ; end mul var with constant
	
	sta bar_0
	; Assigning single variable : colorAdd
	; 8 bit mul of power 2
	
	lda time
	lsr
	lsr
	
	sta colorAdd
	and #15
	sta colorAdd
	; Assigning single variable : colorIndex
	lda #0
	sta colorIndex
	; Set raster interrupt pointing to : RasterSprite
	lda #$01    ; Set Interrupt Request Mask...
	sta $d01a   ; ...we want IRQ by Rasterbeam
	lda #<RasterSprite
	ldx #>RasterSprite
	sta $314    ; store in $314/$315
	stx $315
	lda bar_0
	sta $d012
	jmp $ea81        ; return to kernel interrupt routine

	rts
afterProc_UpdateRaster
	
	
	; ***********  Defining procedure : RasterSprite
	;    Procedure type : User-defined procedure
	
	jmp afterProc_RasterSprite
RasterSprite
	jmp block27182
block27182

	lda #2
	tax
	lda $d012
	sta $d000,x
	lda #3
	tax
	lda $d012
	sta $d000,x
	; Set raster interrupt pointing to : UpdateRaster
	lda #$01    ; Set Interrupt Request Mask...
	sta $d01a   ; ...we want IRQ by Rasterbeam
	lda #<UpdateRaster
	ldx #>UpdateRaster
	sta $314    ; store in $314/$315
	stx $315
	lda #0
	sta $d012
	jmp $ea81        ; return to kernel interrupt routine

	rts
afterProc_RasterSprite
	
	
	; ***********  Defining procedure : Bars
	;    Procedure type : User-defined procedure
	
	jmp afterProc_Bars
Bars
	jmp block7301
block7301

	; Assigning single variable : val
	lda colorIndex
	tax
	lda fade,x
	
	sta val
	; Assigning single variable : bar_0
	; Add/sub right value is variable/expression
	jmp jmprightvar24099
rightvar13293	.byte	0
jmprightvar24099
	lda colorSize
	sta rightvar13293
	
	lda bar_0
	clc
	adc rightvar13293
	
	sta bar_0
	lda #0
	tax
	lda val
	sta $d020,x
	lda #0
	tax
	lda val
	sta $d021,x
	; Assigning single variable : colorIndex
	; Add/sub where right value is constant number
	lda colorIndex
	clc
	adc #1
	 ; end mul var with constant
	
	sta colorIndex
	cmp #15
	bcs branchProblem32331
	jmp branchProblem275
branchProblem32331
	jmp branch23332
branchProblem275
	jmp block31004
block31004

	; Set raster interrupt pointing to : Bars
	lda #$01    ; Set Interrupt Request Mask...
	sta $d01a   ; ...we want IRQ by Rasterbeam
	lda #<Bars
	ldx #>Bars
	sta $314    ; store in $314/$315
	stx $315
	lda bar_0
	sta $d012

branch23332
	lda colorIndex
	cmp #14
	bcc branchProblem14066
	jmp branchProblem211738
branchProblem14066
	jmp branch19050
branchProblem211738
	jmp block19801
block19801

	; Set raster interrupt pointing to : UpdateRaster
	lda #$01    ; Set Interrupt Request Mask...
	sta $d01a   ; ...we want IRQ by Rasterbeam
	lda #<UpdateRaster
	ldx #>UpdateRaster
	sta $314    ; store in $314/$315
	stx $315
	lda #0
	sta $d012
	lda #0
	tax
	lda #0
	sta $d020,x
	lda #0
	tax
	lda #0
	sta $d021,x

branch19050
	jmp $ea81        ; return to kernel interrupt routine

	rts
afterProc_Bars

	; initsid
	lda #0
	tax
	tay
	jsr $1903
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
	lda #26
	sta $d018,x
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
	; Assigning single variable : scroll_x
	lda #0
	sta scroll_x
	jsr InitializeSprites
	jsr InitStars
	; Disable interrupts
	sei 
	ldy #$7f    ; $7f = %01111111
	sty $dc0d   ; Turn off CIAs Timer interrupts
	sty $dd0d   ; Turn off CIAs Timer interrupts
	lda $dc0d   ; cancel all CIA-IRQs in queue/unprocessed
	lda $dd0d   ; cancel all CIA-IRQs in queue/unprocessed
	
	; Set raster interrupt pointing to : UpdateRaster
	lda #$01    ; Set Interrupt Request Mask...
	sta $d01a   ; ...we want IRQ by Rasterbeam
	lda #<UpdateRaster
	ldx #>UpdateRaster
	sta $314    ; store in $314/$315
	stx $315
	lda #0
	sta $d012
	lda $d011   ; Bit#0 of $d011 is basically...
	and #$7f    ; ...the 9th Bit for $d012
	sta $d011   ; we need to make sure it is set to zero 
	cli
	jmp * ; loop like (¤/%

	rts
	org $1806
sidmusic1
	incbin "c:/users/leuat/onedrive/documents/github/pmm/pmm//_music2.dat"
	org $27FF
charset
	incbin "c:/users/leuat/onedrive/documents/github/pmm/pmm///test.bin"
