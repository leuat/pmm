	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

UnitTest
	jmp block41
x	dc.b
y	dc.b
z	dc.b
i	dc.b
val	dc.b
ok	dc.b
screeny	dc.b
arr	dc.b	 
	org arr+255
iarr	dc.w	 
	org iarr+255
str	dc.b
block41
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit18467
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
multiply_eightbit18467
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto6334
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
moveto6334
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
	
	
	; ***********  Defining procedure : incScreen
	;    Procedure type : User-defined procedure
	
	jmp afterProc_incScreen
incScreen

	; Assigning single variable : screeny
	; Add/sub where right value is constant number
	lda screeny
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta screeny
	lda #23
	cmp screeny
	bcs conditionalfailed26962
	jmp ConditionalTrueBlock15724
conditionalfailed26962
	jmp elsedoneblock29358
ConditionalTrueBlock15724
	; Assigning single variable : screeny
	lda #0
	; VarNode StoreVariable
	sta screeny
elsedoneblock29358
	lda #0
	sta screen_x
	lda screeny
	sta screen_y
	lda #4
	jsr SetScreenPosition

	rts
afterProc_incScreen
	
	
	; ***********  Defining procedure : TestConditionals
	;    Procedure type : User-defined procedure
	
	jmp afterProc_TestConditionals
TestConditionals

	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
	; Assigning single variable : y
	lda #10
	; VarNode StoreVariable
	sta y
	; Assigning single variable : z
	lda #20
	; VarNode StoreVariable
	sta z
	lda #20
	cmp y
	bcc conditionalfailed491
	jmp ConditionalTrueBlock23281
conditionalfailed491
	jmp elseblock16827
	jmp elsedoneblock9961
ConditionalTrueBlock23281
	jmp printstring_call11942
printstring_text4827	.dc "CONDITIONAL1 = OK",0
printstring_call11942
	clc
	; TEST
	lda #<printstring_text4827
	adc #0
	ldy #>printstring_text4827
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock9961
elseblock16827
	jmp printstring_call32391
printstring_text14604	.dc "CONDITIONAL1 = FAILED ****************** ",0
printstring_call32391
	clc
	; TEST
	lda #<printstring_text14604
	adc #0
	ldy #>printstring_text14604
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock9961
	jsr incScreen
	lda #0
	cmp x
	bne conditionalfailed17421
	jmp ConditionalTrueBlock153
conditionalfailed17421
	jmp elseblock292
	jmp elsedoneblock12382
ConditionalTrueBlock153
	jmp printstring_call19718
printstring_text19895	.dc "CONDITIONAL2 = OK",0
printstring_call19718
	clc
	; TEST
	lda #<printstring_text19895
	adc #0
	ldy #>printstring_text19895
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock12382
elseblock292
	jmp printstring_call21726
printstring_text14771	.dc "CONDITIONAL2 = FAILED ****************** ",0
printstring_call21726
	clc
	; TEST
	lda #<printstring_text14771
	adc #0
	ldy #>printstring_text14771
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock12382
	jsr incScreen
	lda #5
	cmp y
	bcs conditionalfailed26299
	jmp ConditionalTrueBlock1869
conditionalfailed26299
	jmp elseblock19912
	jmp elsedoneblock25667
ConditionalTrueBlock1869
	jmp printstring_call9894
printstring_text28703	.dc "CONDITIONAL3 = OK",0
printstring_call9894
	clc
	; TEST
	lda #<printstring_text28703
	adc #0
	ldy #>printstring_text28703
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock25667
elseblock19912
	jmp printstring_call31322
printstring_text30333	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call31322
	clc
	; TEST
	lda #<printstring_text30333
	adc #0
	ldy #>printstring_text30333
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock25667
	jsr incScreen
	lda #5
	cmp y
	beq conditionalfailed28253
	jmp ConditionalTrueBlock4664
conditionalfailed28253
	jmp elseblock15141
	jmp elsedoneblock7711
ConditionalTrueBlock4664
	jmp printstring_call25547
printstring_text27644	.dc "CONDITIONAL3 = OK",0
printstring_call25547
	clc
	; TEST
	lda #<printstring_text27644
	adc #0
	ldy #>printstring_text27644
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock7711
elseblock15141
	jmp printstring_call32757
printstring_text20037	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call32757
	clc
	; TEST
	lda #<printstring_text20037
	adc #0
	ldy #>printstring_text20037
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock7711
	jsr incScreen
	lda #5
	cmp y
	beq ConditionalTrueBlock8723
	lda #5
	cmp x
	bne ConditionalTrueBlock8723
	jmp conditionalfailed778
	jmp ConditionalTrueBlock8723
conditionalfailed778
	jmp elseblock9741
	jmp elsedoneblock27529
ConditionalTrueBlock8723
	jmp printstring_call3035
printstring_text22190	.dc "CONDITIONAL4 = OK",0
printstring_call3035
	clc
	; TEST
	lda #<printstring_text22190
	adc #0
	ldy #>printstring_text22190
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock27529
elseblock9741
	jmp printstring_call288
printstring_text30106	.dc "CONDITIONAL4 = FAILED ****************** ",0
printstring_call288
	clc
	; TEST
	lda #<printstring_text30106
	adc #0
	ldy #>printstring_text30106
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock27529
	jsr incScreen
	lda #5
	cmp y
	bcs conditionalfailed27446
	lda #0
	cmp x
	bne conditionalfailed27446
	jmp ConditionalTrueBlock8942
conditionalfailed27446
	jmp elseblock19264
	jmp elsedoneblock22648
ConditionalTrueBlock8942
	jmp printstring_call15890
printstring_text6729	.dc "CONDITIONAL5 = OK",0
printstring_call15890
	clc
	; TEST
	lda #<printstring_text6729
	adc #0
	ldy #>printstring_text6729
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock22648
elseblock19264
	jmp printstring_call15350
printstring_text15006	.dc "CONDITIONAL5 = FAILED ****************** ",0
printstring_call15350
	clc
	; TEST
	lda #<printstring_text15006
	adc #0
	ldy #>printstring_text15006
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock22648
	jsr incScreen
	lda #10
	cmp y
	bne conditionalfailed12623
	lda #0
	cmp x
	bne conditionalfailed12623
	lda #0
	cmp x
	bne conditionalfailed12623
	lda #20
	cmp z
	bne conditionalfailed12623
	jmp ConditionalTrueBlock24393
conditionalfailed12623
	jmp elseblock3548
	jmp elsedoneblock19629
ConditionalTrueBlock24393
	jmp printstring_call19954
printstring_text18756	.dc "CONDITIONAL6 = OK",0
printstring_call19954
	clc
	; TEST
	lda #<printstring_text18756
	adc #0
	ldy #>printstring_text18756
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19629
elseblock3548
	jmp printstring_call4966
printstring_text7376	.dc "CONDITIONAL6 = FAILED ****************** ",0
printstring_call4966
	clc
	; TEST
	lda #<printstring_text7376
	adc #0
	ldy #>printstring_text7376
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19629
	jsr incScreen
	lda #5
	cmp y
	beq ConditionalTrueBlock26308
	lda #23
	cmp x
	beq ConditionalTrueBlock26308
	lda #23
	cmp x
	beq ConditionalTrueBlock26308
	lda #10
	cmp z
	bne ConditionalTrueBlock26308
	jmp conditionalfailed24626
	jmp ConditionalTrueBlock26308
conditionalfailed24626
	jmp elseblock16944
	jmp elsedoneblock32439
ConditionalTrueBlock26308
	jmp printstring_call5537
printstring_text21538	.dc "CONDITIONAL7 = OK",0
printstring_call5537
	clc
	; TEST
	lda #<printstring_text21538
	adc #0
	ldy #>printstring_text21538
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock32439
elseblock16944
	jmp printstring_call2082
printstring_text22929	.dc "CONDITIONAL7 = FAILED ****************** ",0
printstring_call2082
	clc
	; TEST
	lda #<printstring_text22929
	adc #0
	ldy #>printstring_text22929
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock32439
	lda #1
	cmp x
	beq ConditionalTrueBlock4833
	lda #10
	cmp y
	beq ConditionalTrueBlock4833
	jmp conditionalfailed29658
	jmp ConditionalTrueBlock4833
conditionalfailed29658
	jmp elseblock31115
	jmp elsedoneblock4639
ConditionalTrueBlock4833
	jmp printstring_call9930
printstring_text13977	.dc "CONDITIONAL8 = OK",0
printstring_call9930
	clc
	; TEST
	lda #<printstring_text13977
	adc #0
	ldy #>printstring_text13977
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock4639
elseblock31115
	jmp printstring_call31673
printstring_text22386	.dc "CONDITIONAL8 = FAILED ****************** ",0
printstring_call31673
	clc
	; TEST
	lda #<printstring_text22386
	adc #0
	ldy #>printstring_text22386
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock4639
	jsr incScreen

	rts
afterProc_TestConditionals
	
	
	; ***********  Defining procedure : TestMul
	;    Procedure type : User-defined procedure
	
	jmp afterProc_TestMul
TestMul

	; Assigning single variable : ok
	lda #1
	; VarNode StoreVariable
	sta ok
	; Assigning single variable : x
	lda #2
	; VarNode StoreVariable
	sta x
	; Assigning single variable : y
	lda #3
	; VarNode StoreVariable
	sta y
	; Assigning single variable : z
	lda #2
	; VarNode StoreVariable
	sta z
	; Assigning single variable : val
	lda x
	; VarNode StoreVariable
	sta val
	lda #2
	cmp val
	bne conditionalfailed5829
	jmp ConditionalTrueBlock26924
conditionalfailed5829
	jmp elseblock19072
	jmp elsedoneblock6270
ConditionalTrueBlock26924
	jmp printstring_call15573
printstring_text5097	.dc "ASSIGN1 OK ",0
printstring_call15573
	clc
	; TEST
	lda #<printstring_text5097
	adc #0
	ldy #>printstring_text5097
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6270
elseblock19072
	jmp printstring_call23986
printstring_text13290	.dc "ASSING 1 FAILED ****************",0
printstring_call23986
	clc
	; TEST
	lda #<printstring_text13290
	adc #0
	ldy #>printstring_text13290
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6270
	; Assigning single variable : val
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	tax
	pla
	lda x
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	jsr incScreen
	lda #4
	cmp val
	bne conditionalfailed4031
	jmp ConditionalTrueBlock24767
conditionalfailed4031
	jmp elseblock23655
	jmp elsedoneblock15574
ConditionalTrueBlock24767
	jmp printstring_call27350
printstring_text1150	.dc "ASSIGN2 OK ",0
printstring_call27350
	clc
	; TEST
	lda #<printstring_text1150
	adc #0
	ldy #>printstring_text1150
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock15574
elseblock23655
	jmp printstring_call21724
printstring_text13966	.dc "ASSING 2 FAILED ****************",0
printstring_call21724
	clc
	; TEST
	lda #<printstring_text13966
	adc #0
	ldy #>printstring_text13966
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock15574
	jsr incScreen
	; Assigning single variable : val
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	; Add/sub where right value is constant number
	lda x
	clc
	adc #1
	 ; end add / sub var with constant
	tax
	pla
	
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	lda #6
	cmp val
	bne conditionalfailed12287
	jmp ConditionalTrueBlock18007
conditionalfailed12287
	jmp elseblock11337
	jmp elsedoneblock15457
ConditionalTrueBlock18007
	jmp printstring_call10383
printstring_text14945	.dc "ASSIGN3 OK ",0
printstring_call10383
	clc
	; TEST
	lda #<printstring_text14945
	adc #0
	ldy #>printstring_text14945
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock15457
elseblock11337
	jmp printstring_call32209
printstring_text9758	.dc "ASSING 3 FAILED ****************",0
printstring_call32209
	clc
	; TEST
	lda #<printstring_text9758
	adc #0
	ldy #>printstring_text9758
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock15457
	jsr incScreen
	; Assigning single variable : val
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	; Add/sub where right value is constant number
	; 8 bit mul of power 2
	
	lda x
	asl
	
	clc
	adc #1
	 ; end add / sub var with constant
	tax
	pla
	
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	lda #10
	cmp val
	bne conditionalfailed16413
	jmp ConditionalTrueBlock24946
conditionalfailed16413
	jmp elseblock27506
	jmp elsedoneblock13030
ConditionalTrueBlock24946
	jmp printstring_call900
printstring_text32591	.dc "ASSIGN4 OK ",0
printstring_call900
	clc
	; TEST
	lda #<printstring_text32591
	adc #0
	ldy #>printstring_text32591
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock13030
elseblock27506
	jmp printstring_call1655
printstring_text17410	.dc "ASSING 4 FAILED ****************",0
printstring_call1655
	clc
	; TEST
	lda #<printstring_text17410
	adc #0
	ldy #>printstring_text17410
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock13030
	jsr incScreen
	; Assigning single variable : val
	; 8 bit mul
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	tax
	pla
	lda y
	jsr multiply_eightbit
	txa
	
	pha
	; Load right hand side
	tax
	pla
	lda z
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	lda #12
	cmp val
	bne conditionalfailed24350
	jmp ConditionalTrueBlock27595
conditionalfailed24350
	jmp elseblock4041
	jmp elsedoneblock3602
ConditionalTrueBlock27595
	jmp printstring_call30836
printstring_text9374	.dc "ASSIGN5 OK ",0
printstring_call30836
	clc
	; TEST
	lda #<printstring_text9374
	adc #0
	ldy #>printstring_text9374
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock3602
elseblock4041
	jmp printstring_call4596
printstring_text24021	.dc "ASSING 5 FAILED ****************",0
printstring_call4596
	clc
	; TEST
	lda #<printstring_text24021
	adc #0
	ldy #>printstring_text24021
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock3602
	jsr incScreen
	; Assigning single variable : val
	; 8 bit mul
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	; Add/sub where right value is constant number
	lda y
	clc
	adc #2
	 ; end add / sub var with constant
	tax
	pla
	
	jsr multiply_eightbit
	txa
	
	pha
	; Load right hand side
	; Add/sub where right value is constant number
	; 8 bit mul of power 2
	
	lda z
	asl
	
	sec
	sbc #1
	 ; end add / sub var with constant
	tax
	pla
	
	jsr multiply_eightbit
	txa
	
	; VarNode StoreVariable
	sta val
	lda #30
	cmp val
	bne conditionalfailed26418
	jmp ConditionalTrueBlock4734
conditionalfailed26418
	jmp elseblock53
	jmp elsedoneblock1999
ConditionalTrueBlock4734
	jmp printstring_call6900
printstring_text3788	.dc "ASSIGN6 OK ",0
printstring_call6900
	clc
	; TEST
	lda #<printstring_text3788
	adc #0
	ldy #>printstring_text3788
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1999
elseblock53
	jmp printstring_call467
printstring_text3728	.dc "ASSING 6 FAILED ****************",0
printstring_call467
	clc
	; TEST
	lda #<printstring_text3728
	adc #0
	ldy #>printstring_text3728
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1999
	jsr incScreen

	rts
afterProc_TestMul
	
	
	; ***********  Defining procedure : TestWhile
	;    Procedure type : User-defined procedure
	
	jmp afterProc_TestWhile
TestWhile

	; Assigning single variable : x
	lda #10
	; VarNode StoreVariable
	sta x
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
while24648
	lda #1
	cmp x
	beq conditionalfailed14310
	jmp ConditionalTrueBlock22483
conditionalfailed14310
	jmp elsedoneblock2421
ConditionalTrueBlock22483

	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	sec
	sbc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta x
	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	jmp while24648
elsedoneblock2421
	lda #9
	cmp val
	bne conditionalfailed18935
	jmp ConditionalTrueBlock9514
conditionalfailed18935
	jmp elseblock14309
	jmp elsedoneblock7616
ConditionalTrueBlock9514
	jmp printstring_call20600
printstring_text5249	.dc "WHILE1 OK ",0
printstring_call20600
	clc
	; TEST
	lda #<printstring_text5249
	adc #0
	ldy #>printstring_text5249
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock7616
elseblock14309
	jmp printstring_call31556
printstring_text22798	.dc "WHILE1 FAILED ******************** ",0
printstring_call31556
	clc
	; TEST
	lda #<printstring_text22798
	adc #0
	ldy #>printstring_text22798
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock7616
	jsr incScreen

	rts
afterProc_TestWhile
	
	
	; ***********  Defining procedure : TestFor
	;    Procedure type : User-defined procedure
	
	jmp afterProc_TestFor
TestFor

	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for6224

	; Assigning single variable : arr
	lda x
	; VarNode StoreVariable
	pha
	lda x
	tax
	pla
	sta arr,x

	inc x
	lda #10
	cmp x
	bne forLoopFix5844
	jmp forLoopDone32609
forLoopFix5844
	jmp for6224
forLoopDone32609
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for14989

	; Assigning single variable : val
	; Add/sub right value is variable/expression
	jmp jmprightvar20485
rightvar3195	.byte	0
jmprightvar20485
	lda x
	sta rightvar3195
	
	lda val
	clc
	adc rightvar3195
	
	; VarNode StoreVariable
	sta val

	inc x
	lda #3
	cmp x
	bne forLoopFix3093
	jmp forLoopDone14343
forLoopFix3093
	jmp for14989
forLoopDone14343
	lda #6
	cmp val
	beq conditionalfailed7448
	jmp ConditionalTrueBlock1587
conditionalfailed7448
	jmp elseblock29314
	jmp elsedoneblock9503
ConditionalTrueBlock1587
	jmp printstring_call13458
printstring_text6618	.dc "FOR1 OK ",0
printstring_call13458
	clc
	; TEST
	lda #<printstring_text6618
	adc #0
	ldy #>printstring_text6618
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock9503
elseblock29314
	jmp printstring_call19796
printstring_text14798	.dc "FOR1 FAILED ******************** ",0
printstring_call19796
	clc
	; TEST
	lda #<printstring_text14798
	adc #0
	ldy #>printstring_text14798
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock9503
	; Assigning single variable : x
	lda #5
	; VarNode StoreVariable
	sta x
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for15281

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	tax
	pla
	lda x
	jsr multiply_eightbit
	txa
	
	cmp x
	bne forLoopFix20798
	jmp forLoopDone28009
forLoopFix20798
	jmp for15281
forLoopDone28009
	lda #25
	cmp val
	beq conditionalfailed24179
	jmp ConditionalTrueBlock18538
conditionalfailed24179
	jmp elseblock12292
	jmp elsedoneblock6038
ConditionalTrueBlock18538
	jmp printstring_call29657
printstring_text7958	.dc "FOR2 OK ",0
printstring_call29657
	clc
	; TEST
	lda #<printstring_text7958
	adc #0
	ldy #>printstring_text7958
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6038
elseblock12292
	jmp printstring_call19815
printstring_text22888	.dc "FOR2 FAILED ******************** ",0
printstring_call19815
	clc
	; TEST
	lda #<printstring_text22888
	adc #0
	ldy #>printstring_text22888
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6038
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for19156

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	tax
	pla
	lda x
	jsr multiply_eightbit
	txa
	
	cmp x
	bne forLoopFix16202
	jmp forLoopDone2634
forLoopFix16202
	jmp for19156
forLoopDone2634
	; Assigning single variable : arr
	lda #3
	; VarNode StoreVariable
	sta arr+4
	; Assigning single variable : x
	lda #2
	; VarNode StoreVariable
	sta x
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #5
	; VarNode StoreVariable
	sta x
for20328

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	; Load Byte array
	pha
	; 8 bit mul
	lda x
	pha
	; Load right hand side
	tax
	pla
	lda #3
	jsr multiply_eightbit
	txa
	
	tax
	pla
	lda arr,x
	
	cmp x
	bne forLoopFix26362
	jmp forLoopDone4886
forLoopFix26362
	jmp for20328
forLoopDone4886
	lda #8
	cmp val
	beq conditionalfailed21881
	jmp ConditionalTrueBlock20142
conditionalfailed21881
	jmp elseblock23844
	jmp elsedoneblock1416
ConditionalTrueBlock20142
	jmp printstring_call10322
printstring_text18651	.dc "FOR3 OK ",0
printstring_call10322
	clc
	; TEST
	lda #<printstring_text18651
	adc #0
	ldy #>printstring_text18651
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1416
elseblock23844
	jmp printstring_call5699
printstring_text3557	.dc "FOR3 FAILED ******************** ",0
printstring_call5699
	clc
	; TEST
	lda #<printstring_text3557
	adc #0
	ldy #>printstring_text3557
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1416
	jsr incScreen

	rts
afterProc_TestFor

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop28476
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop28476
	lda #0
	sta screen_x
	lda #0
	sta screen_y
	lda #4
	jsr SetScreenPosition
	jsr TestConditionals
	jsr TestWhile
	jsr TestMul
	jsr TestFor
	jmp * ; loop like (¤/%

	rts
