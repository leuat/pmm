	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

UnitTest
	jmp block29617
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
block29617
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit9099
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
multiply_eightbit9099
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto25023
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
moveto25023
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
	; Binary clause: GREATER
	; Compare with pure num / var optimization
	cmp #23
	bcc binaryclausefailed8636
	lda #1; success
	jmp binaryclausefinished9458
binaryclausefailed8636
	lda #0 ; failed state
binaryclausefinished9458
	cmp #1
	beq ConditionalTrueBlock30048
	jmp elsedoneblock1570
ConditionalTrueBlock30048
	; Assigning single variable : screeny
	lda #0
	; VarNode StoreVariable
	sta screeny
elsedoneblock1570
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
	; Binary clause: LESS
	lda y
	; Compare with pure num / var optimization
	cmp #20
	bcs binaryclausefailed7975
	lda #1; success
	jmp binaryclausefinished10556
binaryclausefailed7975
	lda #0 ; failed state
binaryclausefinished10556
	cmp #1
	beq ConditionalTrueBlock11531
	jmp elseblock29962
	jmp elsedoneblock26819
ConditionalTrueBlock11531
	jmp printstring_call31495
printstring_text8044	.dc "CONDITIONAL1 = OK",0
printstring_call31495
	clc
	; TEST
	lda #<printstring_text8044
	adc #0
	ldy #>printstring_text8044
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock26819
elseblock29962
	jmp printstring_call26803
printstring_text3388	.dc "CONDITIONAL1 = FAILED ****************** ",0
printstring_call26803
	clc
	; TEST
	lda #<printstring_text3388
	adc #0
	ldy #>printstring_text3388
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock26819
	jsr incScreen
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed25791
	lda #1; success
	jmp binaryclausefinished29383
binaryclausefailed25791
	lda #0 ; failed state
binaryclausefinished29383
	cmp #1
	beq ConditionalTrueBlock7450
	jmp elseblock12319
	jmp elsedoneblock6272
ConditionalTrueBlock7450
	jmp printstring_call1775
printstring_text24642	.dc "CONDITIONAL2 = OK",0
printstring_call1775
	clc
	; TEST
	lda #<printstring_text24642
	adc #0
	ldy #>printstring_text24642
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6272
elseblock12319
	jmp printstring_call18300
printstring_text17954	.dc "CONDITIONAL2 = FAILED ****************** ",0
printstring_call18300
	clc
	; TEST
	lda #<printstring_text17954
	adc #0
	ldy #>printstring_text17954
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6272
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed893
	lda #1; success
	jmp binaryclausefinished10490
binaryclausefailed893
	lda #0 ; failed state
binaryclausefinished10490
	cmp #1
	beq ConditionalTrueBlock3585
	jmp elseblock2257
	jmp elsedoneblock25333
ConditionalTrueBlock3585
	jmp printstring_call4750
printstring_text17233	.dc "CONDITIONAL3 = OK",0
printstring_call4750
	clc
	; TEST
	lda #<printstring_text17233
	adc #0
	ldy #>printstring_text17233
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock25333
elseblock2257
	jmp printstring_call24271
printstring_text19611	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call24271
	clc
	; TEST
	lda #<printstring_text19611
	adc #0
	ldy #>printstring_text19611
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock25333
	jsr incScreen
	; Binary clause: NOTEQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed19047
	lda #1; success
	jmp binaryclausefinished2352
binaryclausefailed19047
	lda #0 ; failed state
binaryclausefinished2352
	cmp #1
	beq ConditionalTrueBlock30338
	jmp elseblock21641
	jmp elsedoneblock23258
ConditionalTrueBlock30338
	jmp printstring_call479
printstring_text25302	.dc "CONDITIONAL3 = OK",0
printstring_call479
	clc
	; TEST
	lda #<printstring_text25302
	adc #0
	ldy #>printstring_text25302
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock23258
elseblock21641
	jmp printstring_call18990
printstring_text10002	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call18990
	clc
	; TEST
	lda #<printstring_text10002
	adc #0
	ldy #>printstring_text10002
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock23258
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed18008
	lda #1; success
	jmp binaryclausefinished12361
binaryclausefailed18008
	lda #0 ; failed state
binaryclausefinished12361
	jmp logical_class_temp_label22194
logical_class_temp_var16742	.byte	0
logical_class_temp_label22194
	sta logical_class_temp_var16742
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed23699
	lda #1; success
	jmp binaryclausefinished23188
binaryclausefailed23699
	lda #0 ; failed state
binaryclausefinished23188
	ora logical_class_temp_var16742
	cmp #1
	beq ConditionalTrueBlock4422
	jmp elseblock16895
	jmp elsedoneblock6135
ConditionalTrueBlock4422
	jmp printstring_call4042
printstring_text31357	.dc "CONDITIONAL4 = OK",0
printstring_call4042
	clc
	; TEST
	lda #<printstring_text31357
	adc #0
	ldy #>printstring_text31357
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6135
elseblock16895
	jmp printstring_call1847
printstring_text7469	.dc "CONDITIONAL4 = FAILED ****************** ",0
printstring_call1847
	clc
	; TEST
	lda #<printstring_text7469
	adc #0
	ldy #>printstring_text7469
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6135
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed25710
	lda #1; success
	jmp binaryclausefinished20061
binaryclausefailed25710
	lda #0 ; failed state
binaryclausefinished20061
	jmp logical_class_temp_label20073
logical_class_temp_var25385	.byte	0
logical_class_temp_label20073
	sta logical_class_temp_var25385
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed27504
	lda #1; success
	jmp binaryclausefinished9462
binaryclausefailed27504
	lda #0 ; failed state
binaryclausefinished9462
	and logical_class_temp_var25385
	cmp #1
	beq ConditionalTrueBlock4380
	jmp elseblock31913
	jmp elsedoneblock14964
ConditionalTrueBlock4380
	jmp printstring_call28102
printstring_text11069	.dc "CONDITIONAL5 = OK",0
printstring_call28102
	clc
	; TEST
	lda #<printstring_text11069
	adc #0
	ldy #>printstring_text11069
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock14964
elseblock31913
	jmp printstring_call3529
printstring_text31552	.dc "CONDITIONAL5 = FAILED ****************** ",0
printstring_call3529
	clc
	; TEST
	lda #<printstring_text31552
	adc #0
	ldy #>printstring_text31552
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock14964
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed10844
	lda #1; success
	jmp binaryclausefinished13049
binaryclausefailed10844
	lda #0 ; failed state
binaryclausefinished13049
	jmp logical_class_temp_label24065
logical_class_temp_var14118	.byte	0
logical_class_temp_label24065
	sta logical_class_temp_var14118
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed26363
	lda #1; success
	jmp binaryclausefinished19552
binaryclausefailed26363
	lda #0 ; failed state
binaryclausefinished19552
	jmp logical_class_temp_label18470
logical_class_temp_var28773	.byte	0
logical_class_temp_label18470
	sta logical_class_temp_var28773
	; Binary clause: EQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #20
	bne binaryclausefailed29731
	lda #1; success
	jmp binaryclausefinished6747
binaryclausefailed29731
	lda #0 ; failed state
binaryclausefinished6747
	and logical_class_temp_var28773
	and logical_class_temp_var14118
	cmp #1
	beq ConditionalTrueBlock19149
	jmp elseblock3730
	jmp elsedoneblock2244
ConditionalTrueBlock19149
	jmp printstring_call5869
printstring_text14398	.dc "CONDITIONAL6 = OK",0
printstring_call5869
	clc
	; TEST
	lda #<printstring_text14398
	adc #0
	ldy #>printstring_text14398
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock2244
elseblock3730
	jmp printstring_call7103
printstring_text27352	.dc "CONDITIONAL6 = FAILED ****************** ",0
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
elsedoneblock2244
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed31088
	lda #1; success
	jmp binaryclausefinished1563
binaryclausefailed31088
	lda #0 ; failed state
binaryclausefinished1563
	jmp logical_class_temp_label9850
logical_class_temp_var25834	.byte	0
logical_class_temp_label9850
	sta logical_class_temp_var25834
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #23
	bne binaryclausefailed17022
	lda #1; success
	jmp binaryclausefinished7240
binaryclausefailed17022
	lda #0 ; failed state
binaryclausefinished7240
	jmp logical_class_temp_label9492
logical_class_temp_var21911	.byte	0
logical_class_temp_label9492
	sta logical_class_temp_var21911
	; Binary clause: NOTEQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #10
	beq binaryclausefailed5651
	lda #1; success
	jmp binaryclausefinished28580
binaryclausefailed5651
	lda #0 ; failed state
binaryclausefinished28580
	ora logical_class_temp_var21911
	ora logical_class_temp_var25834
	cmp #1
	beq ConditionalTrueBlock28053
	jmp elseblock13043
	jmp elsedoneblock14522
ConditionalTrueBlock28053
	jmp printstring_call27616
printstring_text29876	.dc "CONDITIONAL7 = OK",0
printstring_call27616
	clc
	; TEST
	lda #<printstring_text29876
	adc #0
	ldy #>printstring_text29876
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock14522
elseblock13043
	jmp printstring_call5220
printstring_text14615	.dc "CONDITIONAL7 = FAILED ****************** ",0
printstring_call5220
	clc
	; TEST
	lda #<printstring_text14615
	adc #0
	ldy #>printstring_text14615
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock14522
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	bne binaryclausefailed16857
	lda #1; success
	jmp binaryclausefinished2883
binaryclausefailed16857
	lda #0 ; failed state
binaryclausefinished2883
	jmp logical_class_temp_label18902
logical_class_temp_var1662	.byte	0
logical_class_temp_label18902
	sta logical_class_temp_var1662
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed28262
	lda #1; success
	jmp binaryclausefinished19420
binaryclausefailed28262
	lda #0 ; failed state
binaryclausefinished19420
	ora logical_class_temp_var1662
	cmp #1
	beq ConditionalTrueBlock26798
	jmp elseblock32179
	jmp elsedoneblock31635
ConditionalTrueBlock26798
	jmp printstring_call19022
printstring_text9273	.dc "CONDITIONAL8 = OK",0
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
	jmp elsedoneblock31635
elseblock32179
	jmp printstring_call12686
printstring_text28888	.dc "CONDITIONAL8 = FAILED ****************** ",0
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
elsedoneblock31635
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
	; Binary clause: EQUALS
	; Compare with pure num / var optimization
	cmp #2
	bne binaryclausefailed11749
	lda #1; success
	jmp binaryclausefinished65
binaryclausefailed11749
	lda #0 ; failed state
binaryclausefinished65
	cmp #1
	beq ConditionalTrueBlock1892
	jmp elseblock13698
	jmp elsedoneblock11267
ConditionalTrueBlock1892
	jmp printstring_call6932
printstring_text25619	.dc "ASSIGN1 OK ",0
printstring_call6932
	clc
	; TEST
	lda #<printstring_text25619
	adc #0
	ldy #>printstring_text25619
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock11267
elseblock13698
	jmp printstring_call2003
printstring_text29130	.dc "ASSING 1 FAILED ****************",0
printstring_call2003
	clc
	; TEST
	lda #<printstring_text29130
	adc #0
	ldy #>printstring_text29130
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock11267
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
	; Binary clause: EQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #4
	bne binaryclausefailed19864
	lda #1; success
	jmp binaryclausefinished6407
binaryclausefailed19864
	lda #0 ; failed state
binaryclausefinished6407
	cmp #1
	beq ConditionalTrueBlock23152
	jmp elseblock18630
	jmp elsedoneblock19172
ConditionalTrueBlock23152
	jmp printstring_call25428
printstring_text29681	.dc "ASSIGN2 OK ",0
printstring_call25428
	clc
	; TEST
	lda #<printstring_text29681
	adc #0
	ldy #>printstring_text29681
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19172
elseblock18630
	jmp printstring_call26610
printstring_text26177	.dc "ASSING 2 FAILED ****************",0
printstring_call26610
	clc
	; TEST
	lda #<printstring_text26177
	adc #0
	ldy #>printstring_text26177
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19172
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
	; Binary clause: EQUALS
	; Compare with pure num / var optimization
	cmp #6
	bne binaryclausefailed27037
	lda #1; success
	jmp binaryclausefinished23893
binaryclausefailed27037
	lda #0 ; failed state
binaryclausefinished23893
	cmp #1
	beq ConditionalTrueBlock20643
	jmp elseblock16840
	jmp elsedoneblock27633
ConditionalTrueBlock20643
	jmp printstring_call20274
printstring_text12993	.dc "ASSIGN3 OK ",0
printstring_call20274
	clc
	; TEST
	lda #<printstring_text12993
	adc #0
	ldy #>printstring_text12993
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock27633
elseblock16840
	jmp printstring_call32203
printstring_text17461	.dc "ASSING 3 FAILED ****************",0
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
elsedoneblock27633
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
	; Binary clause: EQUALS
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed8890
	lda #1; success
	jmp binaryclausefinished16717
binaryclausefailed8890
	lda #0 ; failed state
binaryclausefinished16717
	cmp #1
	beq ConditionalTrueBlock20997
	jmp elseblock31151
	jmp elsedoneblock18423
ConditionalTrueBlock20997
	jmp printstring_call28703
printstring_text5566	.dc "ASSIGN4 OK ",0
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
	jmp elsedoneblock18423
elseblock31151
	jmp printstring_call23661
printstring_text22659	.dc "ASSING 4 FAILED ****************",0
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
elsedoneblock18423
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
	; Binary clause: EQUALS
	; Compare with pure num / var optimization
	cmp #12
	bne binaryclausefailed27283
	lda #1; success
	jmp binaryclausefinished29250
binaryclausefailed27283
	lda #0 ; failed state
binaryclausefinished29250
	cmp #1
	beq ConditionalTrueBlock16840
	jmp elseblock17209
	jmp elsedoneblock1497
ConditionalTrueBlock16840
	jmp printstring_call8421
printstring_text175	.dc "ASSIGN5 OK ",0
printstring_call8421
	clc
	; TEST
	lda #<printstring_text175
	adc #0
	ldy #>printstring_text175
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1497
elseblock17209
	jmp printstring_call26787
printstring_text3271	.dc "ASSING 5 FAILED ****************",0
printstring_call26787
	clc
	; TEST
	lda #<printstring_text3271
	adc #0
	ldy #>printstring_text3271
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1497
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
	; Binary clause: EQUALS
	; Compare with pure num / var optimization
	cmp #30
	bne binaryclausefailed12118
	lda #1; success
	jmp binaryclausefinished205
binaryclausefailed12118
	lda #0 ; failed state
binaryclausefinished205
	cmp #1
	beq ConditionalTrueBlock10700
	jmp elseblock530
	jmp elsedoneblock2461
ConditionalTrueBlock10700
	jmp printstring_call18828
printstring_text24459	.dc "ASSIGN6 OK ",0
printstring_call18828
	clc
	; TEST
	lda #<printstring_text24459
	adc #0
	ldy #>printstring_text24459
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock2461
elseblock530
	jmp printstring_call14398
printstring_text3760	.dc "ASSING 6 FAILED ****************",0
printstring_call14398
	clc
	; TEST
	lda #<printstring_text3760
	adc #0
	ldy #>printstring_text3760
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock2461
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
while12935
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	beq binaryclausefailed18493
	lda #1; success
	jmp binaryclausefinished28596
binaryclausefailed18493
	lda #0 ; failed state
binaryclausefinished28596
	cmp #1
	beq ConditionalTrueBlock10481
	jmp elsedoneblock19567
ConditionalTrueBlock10481

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

	jmp while12935
elsedoneblock19567
	; Binary clause: EQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #9
	bne binaryclausefailed21476
	lda #1; success
	jmp binaryclausefinished21555
binaryclausefailed21476
	lda #0 ; failed state
binaryclausefinished21555
	cmp #1
	beq ConditionalTrueBlock10538
	jmp elseblock7670
	jmp elsedoneblock20538
ConditionalTrueBlock10538
	jmp printstring_call16371
printstring_text16760	.dc "WHILE1 OK ",0
printstring_call16371
	clc
	; TEST
	lda #<printstring_text16760
	adc #0
	ldy #>printstring_text16760
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock20538
elseblock7670
	jmp printstring_call13758
printstring_text15433	.dc "WHILE1 FAILED ******************** ",0
printstring_call13758
	clc
	; TEST
	lda #<printstring_text15433
	adc #0
	ldy #>printstring_text15433
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock20538
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
while32255
	; Binary clause: LESS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bcs binaryclausefailed3034
	lda #1; success
	jmp binaryclausefinished12759
binaryclausefailed3034
	lda #0 ; failed state
binaryclausefinished12759
	cmp #1
	beq ConditionalTrueBlock29065
	jmp elsedoneblock2401
ConditionalTrueBlock29065

	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta x

	jmp while32255
elsedoneblock2401
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed12933
	lda #1; success
	jmp binaryclausefinished30137
binaryclausefailed12933
	lda #0 ; failed state
binaryclausefinished30137
	cmp #1
	beq ConditionalTrueBlock27273
	jmp elseblock18792
	jmp elsedoneblock16193
ConditionalTrueBlock27273
	jmp printstring_call3690
printstring_text28211	.dc "WHILE2 OK ",0
printstring_call3690
	clc
	; TEST
	lda #<printstring_text28211
	adc #0
	ldy #>printstring_text28211
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock16193
elseblock18792
	jmp printstring_call24668
printstring_text32627	.dc "WHILE2 FAILED ******************** ",0
printstring_call24668
	clc
	; TEST
	lda #<printstring_text32627
	adc #0
	ldy #>printstring_text32627
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock16193
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
for989

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
	bne forLoopFix3879
	jmp forLoopDone11647
forLoopFix3879
	jmp for989
forLoopDone11647
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for11149

	; Assigning single variable : val
	; Add/sub right value is variable/expression
	jmp jmprightvar30875
rightvar669	.byte	0
jmprightvar30875
	lda x
	sta rightvar669
	
	lda val
	clc
	adc rightvar669
	
	; VarNode StoreVariable
	sta val

	inc x
	lda #3
	cmp x
	bne forLoopFix25598
	jmp forLoopDone25449
forLoopFix25598
	jmp for11149
forLoopDone25449
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #6
	beq binaryclausefailed1731
	lda #1; success
	jmp binaryclausefinished18154
binaryclausefailed1731
	lda #0 ; failed state
binaryclausefinished18154
	cmp #1
	beq ConditionalTrueBlock24599
	jmp elseblock20123
	jmp elsedoneblock1443
ConditionalTrueBlock24599
	jmp printstring_call4434
printstring_text9385	.dc "FOR1 OK ",0
printstring_call4434
	clc
	; TEST
	lda #<printstring_text9385
	adc #0
	ldy #>printstring_text9385
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1443
elseblock20123
	jmp printstring_call10816
printstring_text11393	.dc "FOR1 FAILED ******************** ",0
printstring_call10816
	clc
	; TEST
	lda #<printstring_text11393
	adc #0
	ldy #>printstring_text11393
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1443
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
for16704

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
	bne forLoopFix30953
	jmp forLoopDone30308
forLoopFix30953
	jmp for16704
forLoopDone30308
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #25
	beq binaryclausefailed13930
	lda #1; success
	jmp binaryclausefinished30811
binaryclausefailed13930
	lda #0 ; failed state
binaryclausefinished30811
	cmp #1
	beq ConditionalTrueBlock22667
	jmp elseblock10048
	jmp elsedoneblock32469
ConditionalTrueBlock22667
	jmp printstring_call16090
printstring_text5427	.dc "FOR2 OK ",0
printstring_call16090
	clc
	; TEST
	lda #<printstring_text5427
	adc #0
	ldy #>printstring_text5427
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock32469
elseblock10048
	jmp printstring_call1604
printstring_text10599	.dc "FOR2 FAILED ******************** ",0
printstring_call1604
	clc
	; TEST
	lda #<printstring_text10599
	adc #0
	ldy #>printstring_text10599
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock32469
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for16474

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
	bne forLoopFix506
	jmp forLoopDone5158
forLoopFix506
	jmp for16474
forLoopDone5158
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
for27809

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
	bne forLoopFix11447
	jmp forLoopDone40
forLoopFix11447
	jmp for27809
forLoopDone40
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #8
	beq binaryclausefailed30066
	lda #1; success
	jmp binaryclausefinished26412
binaryclausefailed30066
	lda #0 ; failed state
binaryclausefinished26412
	cmp #1
	beq ConditionalTrueBlock26
	jmp elseblock25089
	jmp elsedoneblock2503
ConditionalTrueBlock26
	jmp printstring_call12570
printstring_text14676	.dc "FOR3 OK ",0
printstring_call12570
	clc
	; TEST
	lda #<printstring_text14676
	adc #0
	ldy #>printstring_text14676
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock2503
elseblock25089
	jmp printstring_call28641
printstring_text29986	.dc "FOR3 FAILED ******************** ",0
printstring_call28641
	clc
	; TEST
	lda #<printstring_text29986
	adc #0
	ldy #>printstring_text29986
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock2503
	jsr incScreen

	rts
afterProc_TestFor

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop17651
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop17651
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
