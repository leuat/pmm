	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

UnitTest
	jmp block19149
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
block19149
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit3730
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
multiply_eightbit3730
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto2244
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
moveto2244
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
	bcs conditionalfailed19552
	jmp ConditionalTrueBlock14118
conditionalfailed19552
	jmp elsedoneblock26363
ConditionalTrueBlock14118
	; Assigning single variable : screeny
	lda #0
	; VarNode StoreVariable
	sta screeny
elsedoneblock26363
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
	bcc conditionalfailed14398
	jmp ConditionalTrueBlock6747
conditionalfailed14398
	jmp elseblock7511
	jmp elsedoneblock5869
ConditionalTrueBlock6747
	jmp printstring_call7103
printstring_text27352	.dc "CONDITIONAL1 = OK",0
printstring_call7103
	clc
	; TEST
	lda #<printstring_text27352
	adc #0
	ldy #>printstring_text27352
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock5869
elseblock7511
	jmp printstring_call28053
printstring_text13043	.dc "CONDITIONAL1 = FAILED ****************** ",0
printstring_call28053
	clc
	; TEST
	lda #<printstring_text13043
	adc #0
	ldy #>printstring_text13043
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock5869
	jsr incScreen
	lda #0
	cmp x
	bne conditionalfailed9850
	jmp ConditionalTrueBlock31088
conditionalfailed9850
	jmp elseblock1563
	jmp elsedoneblock25834
ConditionalTrueBlock31088
	jmp printstring_call7240
printstring_text21911	.dc "CONDITIONAL2 = OK",0
printstring_call7240
	clc
	; TEST
	lda #<printstring_text21911
	adc #0
	ldy #>printstring_text21911
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock25834
elseblock1563
	jmp printstring_call5651
printstring_text28580	.dc "CONDITIONAL2 = FAILED ****************** ",0
printstring_call5651
	clc
	; TEST
	lda #<printstring_text28580
	adc #0
	ldy #>printstring_text28580
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock25834
	jsr incScreen
	lda #5
	cmp y
	bcs conditionalfailed5220
	jmp ConditionalTrueBlock27616
conditionalfailed5220
	jmp elseblock29876
	jmp elsedoneblock19178
ConditionalTrueBlock27616
	jmp printstring_call22348
printstring_text26798	.dc "CONDITIONAL3 = OK",0
printstring_call22348
	clc
	; TEST
	lda #<printstring_text26798
	adc #0
	ldy #>printstring_text26798
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19178
elseblock29876
	jmp printstring_call31635
printstring_text16857	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call31635
	clc
	; TEST
	lda #<printstring_text16857
	adc #0
	ldy #>printstring_text16857
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19178
	jsr incScreen
	lda #5
	cmp y
	beq conditionalfailed19420
	jmp ConditionalTrueBlock1662
conditionalfailed19420
	jmp elseblock18902
	jmp elsedoneblock28262
ConditionalTrueBlock1662
	jmp printstring_call19022
printstring_text9273	.dc "CONDITIONAL3 = OK",0
printstring_call19022
	clc
	; TEST
	lda #<printstring_text9273
	adc #0
	ldy #>printstring_text9273
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock28262
elseblock18902
	jmp printstring_call12686
printstring_text28888	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call12686
	clc
	; TEST
	lda #<printstring_text28888
	adc #0
	ldy #>printstring_text28888
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock28262
	jsr incScreen
	lda #5
	cmp y
	beq ConditionalTrueBlock31717
	lda #5
	cmp x
	bne ConditionalTrueBlock31717
	jmp conditionalfailed11267
	jmp ConditionalTrueBlock31717
conditionalfailed11267
	jmp elseblock1892
	jmp elsedoneblock13698
ConditionalTrueBlock31717
	jmp printstring_call65
printstring_text10389	.dc "CONDITIONAL4 = OK",0
printstring_call65
	clc
	; TEST
	lda #<printstring_text10389
	adc #0
	ldy #>printstring_text10389
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock13698
elseblock1892
	jmp printstring_call25619
printstring_text16081	.dc "CONDITIONAL4 = FAILED ****************** ",0
printstring_call25619
	clc
	; TEST
	lda #<printstring_text16081
	adc #0
	ldy #>printstring_text16081
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock13698
	jsr incScreen
	lda #5
	cmp y
	bcs conditionalfailed14589
	lda #0
	cmp x
	bne conditionalfailed14589
	jmp ConditionalTrueBlock29130
conditionalfailed14589
	jmp elseblock13028
	jmp elsedoneblock18631
ConditionalTrueBlock29130
	jmp printstring_call18630
printstring_text19172	.dc "CONDITIONAL5 = OK",0
printstring_call18630
	clc
	; TEST
	lda #<printstring_text19172
	adc #0
	ldy #>printstring_text19172
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock18631
elseblock13028
	jmp printstring_call6407
printstring_text12295	.dc "CONDITIONAL5 = FAILED ****************** ",0
printstring_call6407
	clc
	; TEST
	lda #<printstring_text12295
	adc #0
	ldy #>printstring_text12295
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock18631
	jsr incScreen
	lda #10
	cmp y
	bne conditionalfailed26177
	lda #0
	cmp x
	bne conditionalfailed26177
	lda #0
	cmp x
	bne conditionalfailed26177
	lda #20
	cmp z
	bne conditionalfailed26177
	jmp ConditionalTrueBlock29681
conditionalfailed26177
	jmp elseblock18490
	jmp elsedoneblock26610
ConditionalTrueBlock29681
	jmp printstring_call25236
printstring_text6459	.dc "CONDITIONAL6 = OK",0
printstring_call25236
	clc
	; TEST
	lda #<printstring_text6459
	adc #0
	ldy #>printstring_text6459
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock26610
elseblock18490
	jmp printstring_call16840
printstring_text27633	.dc "CONDITIONAL6 = FAILED ****************** ",0
printstring_call16840
	clc
	; TEST
	lda #<printstring_text27633
	adc #0
	ldy #>printstring_text27633
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock26610
	jsr incScreen
	lda #5
	cmp y
	beq ConditionalTrueBlock23893
	lda #23
	cmp x
	beq ConditionalTrueBlock23893
	lda #23
	cmp x
	beq ConditionalTrueBlock23893
	lda #10
	cmp z
	bne ConditionalTrueBlock23893
	jmp conditionalfailed12993
	jmp ConditionalTrueBlock23893
conditionalfailed12993
	jmp elseblock22630
	jmp elsedoneblock20274
ConditionalTrueBlock23893
	jmp printstring_call32203
printstring_text17461	.dc "CONDITIONAL7 = OK",0
printstring_call32203
	clc
	; TEST
	lda #<printstring_text17461
	adc #0
	ldy #>printstring_text17461
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock20274
elseblock22630
	jmp printstring_call19662
printstring_text22307	.dc "CONDITIONAL7 = FAILED ****************** ",0
printstring_call19662
	clc
	; TEST
	lda #<printstring_text22307
	adc #0
	ldy #>printstring_text22307
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock20274
	lda #1
	cmp x
	beq ConditionalTrueBlock31151
	lda #10
	cmp y
	beq ConditionalTrueBlock31151
	jmp conditionalfailed16717
	jmp ConditionalTrueBlock31151
conditionalfailed16717
	jmp elseblock18423
	jmp elsedoneblock8890
ConditionalTrueBlock31151
	jmp printstring_call28703
printstring_text5566	.dc "CONDITIONAL8 = OK",0
printstring_call28703
	clc
	; TEST
	lda #<printstring_text5566
	adc #0
	ldy #>printstring_text5566
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock8890
elseblock18423
	jmp printstring_call23661
printstring_text22659	.dc "CONDITIONAL8 = FAILED ****************** ",0
printstring_call23661
	clc
	; TEST
	lda #<printstring_text22659
	adc #0
	ldy #>printstring_text22659
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock8890
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
	bne conditionalfailed16840
	jmp ConditionalTrueBlock32651
conditionalfailed16840
	jmp elseblock32765
	jmp elsedoneblock19601
ConditionalTrueBlock32651
	jmp printstring_call1497
printstring_text27283	.dc "ASSIGN1 OK ",0
printstring_call1497
	clc
	; TEST
	lda #<printstring_text27283
	adc #0
	ldy #>printstring_text27283
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19601
elseblock32765
	jmp printstring_call18058
printstring_text8421	.dc "ASSING 1 FAILED ****************",0
printstring_call18058
	clc
	; TEST
	lda #<printstring_text8421
	adc #0
	ldy #>printstring_text8421
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19601
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
	bne conditionalfailed12504
	jmp ConditionalTrueBlock3271
conditionalfailed12504
	jmp elseblock4287
	jmp elsedoneblock27999
ConditionalTrueBlock3271
	jmp printstring_call2138
printstring_text10700	.dc "ASSIGN2 OK ",0
printstring_call2138
	clc
	; TEST
	lda #<printstring_text10700
	adc #0
	ldy #>printstring_text10700
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock27999
elseblock4287
	jmp printstring_call2461
printstring_text12118	.dc "ASSING 2 FAILED ****************",0
printstring_call2461
	clc
	; TEST
	lda #<printstring_text12118
	adc #0
	ldy #>printstring_text12118
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock27999
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
	bne conditionalfailed3760
	jmp ConditionalTrueBlock24459
conditionalfailed3760
	jmp elseblock11622
	jmp elsedoneblock14398
ConditionalTrueBlock24459
	jmp printstring_call12935
printstring_text10481	.dc "ASSIGN3 OK ",0
printstring_call12935
	clc
	; TEST
	lda #<printstring_text10481
	adc #0
	ldy #>printstring_text10481
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock14398
elseblock11622
	jmp printstring_call19567
printstring_text18493	.dc "ASSING 3 FAILED ****************",0
printstring_call19567
	clc
	; TEST
	lda #<printstring_text18493
	adc #0
	ldy #>printstring_text18493
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock14398
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
	bne conditionalfailed21476
	jmp ConditionalTrueBlock10538
conditionalfailed21476
	jmp elseblock7670
	jmp elsedoneblock20538
ConditionalTrueBlock10538
	jmp printstring_call24917
printstring_text16371	.dc "ASSIGN4 OK ",0
printstring_call24917
	clc
	; TEST
	lda #<printstring_text16371
	adc #0
	ldy #>printstring_text16371
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock20538
elseblock7670
	jmp printstring_call5752
printstring_text13758	.dc "ASSING 4 FAILED ****************",0
printstring_call5752
	clc
	; TEST
	lda #<printstring_text13758
	adc #0
	ldy #>printstring_text13758
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock20538
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
	bne conditionalfailed30548
	jmp ConditionalTrueBlock3034
conditionalfailed30548
	jmp elseblock12759
	jmp elsedoneblock10393
ConditionalTrueBlock3034
	jmp printstring_call18792
printstring_text16193	.dc "ASSIGN5 OK ",0
printstring_call18792
	clc
	; TEST
	lda #<printstring_text16193
	adc #0
	ldy #>printstring_text16193
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock10393
elseblock12759
	jmp printstring_call30137
printstring_text17103	.dc "ASSING 5 FAILED ****************",0
printstring_call30137
	clc
	; TEST
	lda #<printstring_text17103
	adc #0
	ldy #>printstring_text17103
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock10393
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
	bne conditionalfailed3879
	jmp ConditionalTrueBlock7498
conditionalfailed3879
	jmp elseblock989
	jmp elsedoneblock15248
ConditionalTrueBlock7498
	jmp printstring_call11149
printstring_text30931	.dc "ASSIGN6 OK ",0
printstring_call11149
	clc
	; TEST
	lda #<printstring_text30931
	adc #0
	ldy #>printstring_text30931
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock15248
elseblock989
	jmp printstring_call30875
printstring_text25598	.dc "ASSING 6 FAILED ****************",0
printstring_call30875
	clc
	; TEST
	lda #<printstring_text25598
	adc #0
	ldy #>printstring_text25598
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock15248
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
while25436
	lda #1
	cmp x
	beq conditionalfailed1731
	jmp ConditionalTrueBlock24599
conditionalfailed1731
	jmp elsedoneblock1443
ConditionalTrueBlock24599

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

	jmp while25436
elsedoneblock1443
	lda #9
	cmp val
	bne conditionalfailed10816
	jmp ConditionalTrueBlock4434
conditionalfailed10816
	jmp elseblock9385
	jmp elsedoneblock23967
ConditionalTrueBlock4434
	jmp printstring_call16704
printstring_text29866	.dc "WHILE1 OK ",0
printstring_call16704
	clc
	; TEST
	lda #<printstring_text29866
	adc #0
	ldy #>printstring_text29866
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock23967
elseblock9385
	jmp printstring_call30308
printstring_text28223	.dc "WHILE1 FAILED ******************** ",0
printstring_call30308
	clc
	; TEST
	lda #<printstring_text28223
	adc #0
	ldy #>printstring_text28223
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock23967
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
for30792

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
	bne forLoopFix10048
	jmp forLoopDone32469
forLoopFix10048
	jmp for30792
forLoopDone32469
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for13930

	; Assigning single variable : val
	; Add/sub right value is variable/expression
	jmp jmprightvar16090
rightvar19814	.byte	0
jmprightvar16090
	lda x
	sta rightvar19814
	
	lda val
	clc
	adc rightvar19814
	
	; VarNode StoreVariable
	sta val

	inc x
	lda #3
	cmp x
	bne forLoopFix5427
	jmp forLoopDone23743
forLoopFix5427
	jmp for13930
forLoopDone23743
	lda #6
	cmp val
	beq conditionalfailed506
	jmp ConditionalTrueBlock10599
conditionalfailed506
	jmp elseblock16474
	jmp elsedoneblock7195
ConditionalTrueBlock10599
	jmp printstring_call17589
printstring_text9858	.dc "FOR1 OK ",0
printstring_call17589
	clc
	; TEST
	lda #<printstring_text9858
	adc #0
	ldy #>printstring_text9858
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock7195
elseblock16474
	jmp printstring_call17889
printstring_text11447	.dc "FOR1 FAILED ******************** ",0
printstring_call17889
	clc
	; TEST
	lda #<printstring_text11447
	adc #0
	ldy #>printstring_text11447
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock7195
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
for40

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
	bne forLoopFix9364
	jmp forLoopDone17975
forLoopFix9364
	jmp for40
forLoopDone17975
	lda #25
	cmp val
	beq conditionalfailed12570
	jmp ConditionalTrueBlock30066
conditionalfailed12570
	jmp elseblock26412
	jmp elsedoneblock6840
ConditionalTrueBlock30066
	jmp printstring_call25395
printstring_text28641	.dc "FOR2 OK ",0
printstring_call25395
	clc
	; TEST
	lda #<printstring_text28641
	adc #0
	ldy #>printstring_text28641
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6840
elseblock26412
	jmp printstring_call17651
printstring_text21109	.dc "FOR2 FAILED ******************** ",0
printstring_call17651
	clc
	; TEST
	lda #<printstring_text21109
	adc #0
	ldy #>printstring_text21109
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6840
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for8187

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
	bne forLoopFix21085
	jmp forLoopDone23390
forLoopFix21085
	jmp for8187
forLoopDone23390
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
for4755

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
	bne forLoopFix28128
	jmp forLoopDone25502
forLoopFix28128
	jmp for4755
forLoopDone25502
	lda #8
	cmp val
	beq conditionalfailed30885
	jmp ConditionalTrueBlock3565
conditionalfailed30885
	jmp elseblock3872
	jmp elsedoneblock832
ConditionalTrueBlock3565
	jmp printstring_call6646
printstring_text20889	.dc "FOR3 OK ",0
printstring_call6646
	clc
	; TEST
	lda #<printstring_text20889
	adc #0
	ldy #>printstring_text20889
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock832
elseblock3872
	jmp printstring_call10883
printstring_text24925	.dc "FOR3 FAILED ******************** ",0
printstring_call10883
	clc
	; TEST
	lda #<printstring_text24925
	adc #0
	ldy #>printstring_text24925
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock832
	jsr incScreen

	rts
afterProc_TestFor

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop21265
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop21265
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
