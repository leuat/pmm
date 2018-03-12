	processor 6502

	ORG $0801
	.byte    $0E, $08, $0A, $00, $9E, $20, $28,  $32, $33
	.byte    $30, $34, $29, $00, $00, $00

	ORG $0900

UnitTest
	jmp block7799
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
block7799
	
	
	; ***********  Defining procedure : initeightbitmul
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initeightbitmul
initeightbitmul
	jmp multiply_eightbit18674
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
multiply_eightbit18674
	rts
afterProc_initeightbitmul
	
	
	; ***********  Defining procedure : initmoveto
	;    Procedure type : Built-in function
	;    Requires initialization : no
	
	jmp afterProc_initmoveto
initmoveto
	jmp moveto21331
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
moveto21331
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
	bcc binaryclausefailed30950
	lda #1; success
	jmp binaryclausefinished3398
binaryclausefailed30950
	lda #0 ; failed state
binaryclausefinished3398
	cmp #1
	beq ConditionalTrueBlock3751
	jmp elsedoneblock32642
ConditionalTrueBlock3751
	; Assigning single variable : screeny
	lda #0
	; VarNode StoreVariable
	sta screeny
elsedoneblock32642
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
	bcs binaryclausefailed1046
	lda #1; success
	jmp binaryclausefinished11723
binaryclausefailed1046
	lda #0 ; failed state
binaryclausefinished11723
	cmp #1
	beq ConditionalTrueBlock24456
	jmp elseblock4973
	jmp elsedoneblock68
ConditionalTrueBlock24456
	jmp printstring_call27137
printstring_text27445	.dc "CONDITIONAL1 = OK",0
printstring_call27137
	clc
	; TEST
	lda #<printstring_text27445
	adc #0
	ldy #>printstring_text27445
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock68
elseblock4973
	jmp printstring_call11644
printstring_text2585	.dc "CONDITIONAL1 = FAILED ****************** ",0
printstring_call11644
	clc
	; TEST
	lda #<printstring_text2585
	adc #0
	ldy #>printstring_text2585
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock68
	jsr incScreen
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed7285
	lda #1; success
	jmp binaryclausefinished23842
binaryclausefailed7285
	lda #0 ; failed state
binaryclausefinished23842
	cmp #1
	beq ConditionalTrueBlock9690
	jmp elseblock5587
	jmp elsedoneblock30908
ConditionalTrueBlock9690
	jmp printstring_call20319
printstring_text15682	.dc "CONDITIONAL2 = OK",0
printstring_call20319
	clc
	; TEST
	lda #<printstring_text15682
	adc #0
	ldy #>printstring_text15682
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock30908
elseblock5587
	jmp printstring_call7930
printstring_text17077	.dc "CONDITIONAL2 = FAILED ****************** ",0
printstring_call7930
	clc
	; TEST
	lda #<printstring_text17077
	adc #0
	ldy #>printstring_text17077
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock30908
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed5845
	lda #1; success
	jmp binaryclausefinished32650
binaryclausefailed5845
	lda #0 ; failed state
binaryclausefinished32650
	cmp #1
	beq ConditionalTrueBlock4149
	jmp elseblock29072
	jmp elsedoneblock6363
ConditionalTrueBlock4149
	jmp printstring_call20435
printstring_text13529	.dc "CONDITIONAL3 = OK",0
printstring_call20435
	clc
	; TEST
	lda #<printstring_text13529
	adc #0
	ldy #>printstring_text13529
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6363
elseblock29072
	jmp printstring_call14450
printstring_text2099	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call14450
	clc
	; TEST
	lda #<printstring_text2099
	adc #0
	ldy #>printstring_text2099
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6363
	jsr incScreen
	; Binary clause: NOTEQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed6449
	lda #1; success
	jmp binaryclausefinished3523
binaryclausefailed6449
	lda #0 ; failed state
binaryclausefinished3523
	cmp #1
	beq ConditionalTrueBlock12529
	jmp elseblock25739
	jmp elsedoneblock2078
ConditionalTrueBlock12529
	jmp printstring_call27252
printstring_text21535	.dc "CONDITIONAL3 = OK",0
printstring_call27252
	clc
	; TEST
	lda #<printstring_text21535
	adc #0
	ldy #>printstring_text21535
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock2078
elseblock25739
	jmp printstring_call17164
printstring_text20038	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call17164
	clc
	; TEST
	lda #<printstring_text20038
	adc #0
	ldy #>printstring_text20038
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock2078
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed15589
	lda #1; success
	jmp binaryclausefinished15207
binaryclausefailed15589
	lda #0 ; failed state
binaryclausefinished15207
	jmp logical_class_temp_label10779
logical_class_temp_var22191	.byte	0
logical_class_temp_label10779
	sta logical_class_temp_var22191
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed17148
	lda #1; success
	jmp binaryclausefinished30236
binaryclausefailed17148
	lda #0 ; failed state
binaryclausefinished30236
	ora logical_class_temp_var22191
	cmp #1
	beq ConditionalTrueBlock27311
	jmp elseblock11473
	jmp elsedoneblock6797
ConditionalTrueBlock27311
	jmp printstring_call29649
printstring_text22572	.dc "CONDITIONAL4 = OK",0
printstring_call29649
	clc
	; TEST
	lda #<printstring_text22572
	adc #0
	ldy #>printstring_text22572
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6797
elseblock11473
	jmp printstring_call23843
printstring_text787	.dc "CONDITIONAL4 = FAILED ****************** ",0
printstring_call23843
	clc
	; TEST
	lda #<printstring_text787
	adc #0
	ldy #>printstring_text787
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6797
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed12749
	lda #1; success
	jmp binaryclausefinished14758
binaryclausefailed12749
	lda #0 ; failed state
binaryclausefinished14758
	jmp logical_class_temp_label27335
logical_class_temp_var30217	.byte	0
logical_class_temp_label27335
	sta logical_class_temp_var30217
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed24008
	lda #1; success
	jmp binaryclausefinished25669
binaryclausefailed24008
	lda #0 ; failed state
binaryclausefinished25669
	and logical_class_temp_var30217
	cmp #1
	beq ConditionalTrueBlock7211
	jmp elseblock26735
	jmp elsedoneblock21625
ConditionalTrueBlock7211
	jmp printstring_call12320
printstring_text9590	.dc "CONDITIONAL5 = OK",0
printstring_call12320
	clc
	; TEST
	lda #<printstring_text9590
	adc #0
	ldy #>printstring_text9590
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock21625
elseblock26735
	jmp printstring_call12152
printstring_text30582	.dc "CONDITIONAL5 = FAILED ****************** ",0
printstring_call12152
	clc
	; TEST
	lda #<printstring_text30582
	adc #0
	ldy #>printstring_text30582
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock21625
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed30502
	lda #1; success
	jmp binaryclausefinished21091
binaryclausefailed30502
	lda #0 ; failed state
binaryclausefinished21091
	jmp logical_class_temp_label11905
logical_class_temp_var25209	.byte	0
logical_class_temp_label11905
	sta logical_class_temp_var25209
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed28797
	lda #1; success
	jmp binaryclausefinished10115
binaryclausefailed28797
	lda #0 ; failed state
binaryclausefinished10115
	jmp logical_class_temp_label28877
logical_class_temp_var32243	.byte	0
logical_class_temp_label28877
	sta logical_class_temp_var32243
	; Binary clause: EQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #20
	bne binaryclausefailed15285
	lda #1; success
	jmp binaryclausefinished7883
binaryclausefailed15285
	lda #0 ; failed state
binaryclausefinished7883
	and logical_class_temp_var32243
	and logical_class_temp_var25209
	cmp #1
	beq ConditionalTrueBlock8082
	jmp elseblock28125
	jmp elsedoneblock12869
ConditionalTrueBlock8082
	jmp printstring_call32493
printstring_text23759	.dc "CONDITIONAL6 = OK",0
printstring_call32493
	clc
	; TEST
	lda #<printstring_text23759
	adc #0
	ldy #>printstring_text23759
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock12869
elseblock28125
	jmp printstring_call27372
printstring_text11902	.dc "CONDITIONAL6 = FAILED ****************** ",0
printstring_call27372
	clc
	; TEST
	lda #<printstring_text11902
	adc #0
	ldy #>printstring_text11902
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock12869
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed11075
	lda #1; success
	jmp binaryclausefinished4955
binaryclausefailed11075
	lda #0 ; failed state
binaryclausefinished4955
	jmp logical_class_temp_label11653
logical_class_temp_var26341	.byte	0
logical_class_temp_label11653
	sta logical_class_temp_var26341
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #23
	bne binaryclausefailed10210
	lda #1; success
	jmp binaryclausefinished22596
binaryclausefailed10210
	lda #0 ; failed state
binaryclausefinished22596
	jmp logical_class_temp_label1845
logical_class_temp_var2591	.byte	0
logical_class_temp_label1845
	sta logical_class_temp_var2591
	; Binary clause: NOTEQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #10
	beq binaryclausefailed1266
	lda #1; success
	jmp binaryclausefinished26100
binaryclausefailed1266
	lda #0 ; failed state
binaryclausefinished26100
	ora logical_class_temp_var2591
	ora logical_class_temp_var26341
	cmp #1
	beq ConditionalTrueBlock7315
	jmp elseblock27425
	jmp elsedoneblock19428
ConditionalTrueBlock7315
	jmp printstring_call4592
printstring_text6607	.dc "CONDITIONAL7 = OK",0
printstring_call4592
	clc
	; TEST
	lda #<printstring_text6607
	adc #0
	ldy #>printstring_text6607
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19428
elseblock27425
	jmp printstring_call7777
printstring_text23503	.dc "CONDITIONAL7 = FAILED ****************** ",0
printstring_call7777
	clc
	; TEST
	lda #<printstring_text23503
	adc #0
	ldy #>printstring_text23503
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19428
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	bne binaryclausefailed5174
	lda #1; success
	jmp binaryclausefinished5912
binaryclausefailed5174
	lda #0 ; failed state
binaryclausefinished5912
	jmp logical_class_temp_label26697
logical_class_temp_var21300	.byte	0
logical_class_temp_label26697
	sta logical_class_temp_var21300
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed17852
	lda #1; success
	jmp binaryclausefinished11385
binaryclausefailed17852
	lda #0 ; failed state
binaryclausefinished11385
	ora logical_class_temp_var21300
	cmp #1
	beq ConditionalTrueBlock20371
	jmp elseblock4169
	jmp elsedoneblock21557
ConditionalTrueBlock20371
	jmp printstring_call17322
printstring_text20368	.dc "CONDITIONAL8 = OK",0
printstring_call17322
	clc
	; TEST
	lda #<printstring_text20368
	adc #0
	ldy #>printstring_text20368
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock21557
elseblock4169
	jmp printstring_call23002
printstring_text2398	.dc "CONDITIONAL8 = FAILED ****************** ",0
printstring_call23002
	clc
	; TEST
	lda #<printstring_text2398
	adc #0
	ldy #>printstring_text2398
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock21557
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
	bne binaryclausefailed30939
	lda #1; success
	jmp binaryclausefinished30218
binaryclausefailed30939
	lda #0 ; failed state
binaryclausefinished30218
	cmp #1
	beq ConditionalTrueBlock27154
	jmp elseblock6411
	jmp elsedoneblock22570
ConditionalTrueBlock27154
	jmp printstring_call7287
printstring_text27645	.dc "ASSIGN1 OK ",0
printstring_call7287
	clc
	; TEST
	lda #<printstring_text27645
	adc #0
	ldy #>printstring_text27645
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock22570
elseblock6411
	jmp printstring_call6391
printstring_text9894	.dc "ASSING 1 FAILED ****************",0
printstring_call6391
	clc
	; TEST
	lda #<printstring_text9894
	adc #0
	ldy #>printstring_text9894
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock22570
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
	bne binaryclausefailed18034
	lda #1; success
	jmp binaryclausefinished2168
binaryclausefailed18034
	lda #0 ; failed state
binaryclausefinished2168
	cmp #1
	beq ConditionalTrueBlock26717
	jmp elseblock23923
	jmp elsedoneblock1902
ConditionalTrueBlock26717
	jmp printstring_call21795
printstring_text2064	.dc "ASSIGN2 OK ",0
printstring_call21795
	clc
	; TEST
	lda #<printstring_text2064
	adc #0
	ldy #>printstring_text2064
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1902
elseblock23923
	jmp printstring_call27876
printstring_text2439	.dc "ASSING 2 FAILED ****************",0
printstring_call27876
	clc
	; TEST
	lda #<printstring_text2439
	adc #0
	ldy #>printstring_text2439
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1902
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
	bne binaryclausefailed29670
	lda #1; success
	jmp binaryclausefinished11985
binaryclausefailed29670
	lda #0 ; failed state
binaryclausefinished11985
	cmp #1
	beq ConditionalTrueBlock19517
	jmp elseblock9499
	jmp elsedoneblock3589
ConditionalTrueBlock19517
	jmp printstring_call1816
printstring_text21699	.dc "ASSIGN3 OK ",0
printstring_call1816
	clc
	; TEST
	lda #<printstring_text21699
	adc #0
	ldy #>printstring_text21699
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock3589
elseblock9499
	jmp printstring_call23035
printstring_text30498	.dc "ASSING 3 FAILED ****************",0
printstring_call23035
	clc
	; TEST
	lda #<printstring_text30498
	adc #0
	ldy #>printstring_text30498
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock3589
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
	bne binaryclausefailed5315
	lda #1; success
	jmp binaryclausefinished26445
binaryclausefailed5315
	lda #0 ; failed state
binaryclausefinished26445
	cmp #1
	beq ConditionalTrueBlock29556
	jmp elseblock10813
	jmp elsedoneblock23208
ConditionalTrueBlock29556
	jmp printstring_call27114
printstring_text21485	.dc "ASSIGN4 OK ",0
printstring_call27114
	clc
	; TEST
	lda #<printstring_text21485
	adc #0
	ldy #>printstring_text21485
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock23208
elseblock10813
	jmp printstring_call13138
printstring_text30306	.dc "ASSING 4 FAILED ****************",0
printstring_call13138
	clc
	; TEST
	lda #<printstring_text30306
	adc #0
	ldy #>printstring_text30306
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock23208
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
	bne binaryclausefailed17668
	lda #1; success
	jmp binaryclausefinished27612
binaryclausefailed17668
	lda #0 ; failed state
binaryclausefinished27612
	cmp #1
	beq ConditionalTrueBlock27550
	jmp elseblock27959
	jmp elsedoneblock16464
ConditionalTrueBlock27550
	jmp printstring_call5546
printstring_text2074	.dc "ASSIGN5 OK ",0
printstring_call5546
	clc
	; TEST
	lda #<printstring_text2074
	adc #0
	ldy #>printstring_text2074
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock16464
elseblock27959
	jmp printstring_call7589
printstring_text20937	.dc "ASSING 5 FAILED ****************",0
printstring_call7589
	clc
	; TEST
	lda #<printstring_text20937
	adc #0
	ldy #>printstring_text20937
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock16464
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
	bne binaryclausefailed27706
	lda #1; success
	jmp binaryclausefinished11420
binaryclausefailed27706
	lda #0 ; failed state
binaryclausefinished11420
	cmp #1
	beq ConditionalTrueBlock10752
	jmp elseblock2391
	jmp elsedoneblock22295
ConditionalTrueBlock10752
	jmp printstring_call29251
printstring_text27917	.dc "ASSIGN6 OK ",0
printstring_call29251
	clc
	; TEST
	lda #<printstring_text27917
	adc #0
	ldy #>printstring_text27917
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock22295
elseblock2391
	jmp printstring_call14992
printstring_text15352	.dc "ASSING 6 FAILED ****************",0
printstring_call14992
	clc
	; TEST
	lda #<printstring_text15352
	adc #0
	ldy #>printstring_text15352
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock22295
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
while20399
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	beq binaryclausefailed7413
	lda #1; success
	jmp binaryclausefinished22418
binaryclausefailed7413
	lda #0 ; failed state
binaryclausefinished22418
	cmp #1
	beq ConditionalTrueBlock17162
	jmp elsedoneblock2088
ConditionalTrueBlock17162

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

	jmp while20399
elsedoneblock2088
	; Binary clause: EQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #9
	bne binaryclausefailed27763
	lda #1; success
	jmp binaryclausefinished18433
binaryclausefailed27763
	lda #0 ; failed state
binaryclausefinished18433
	cmp #1
	beq ConditionalTrueBlock25527
	jmp elseblock18596
	jmp elsedoneblock13094
ConditionalTrueBlock25527
	jmp printstring_call19374
printstring_text11738	.dc "WHILE1 OK ",0
printstring_call19374
	clc
	; TEST
	lda #<printstring_text11738
	adc #0
	ldy #>printstring_text11738
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock13094
elseblock18596
	jmp printstring_call17806
printstring_text28730	.dc "WHILE1 FAILED ******************** ",0
printstring_call17806
	clc
	; TEST
	lda #<printstring_text28730
	adc #0
	ldy #>printstring_text28730
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock13094
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
while12349
	; Binary clause: LESS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bcs binaryclausefailed1080
	lda #1; success
	jmp binaryclausefinished1172
binaryclausefailed1080
	lda #0 ; failed state
binaryclausefinished1172
	cmp #1
	beq ConditionalTrueBlock18452
	jmp elsedoneblock31684
ConditionalTrueBlock18452

	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta x

	jmp while12349
elsedoneblock31684
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed7917
	lda #1; success
	jmp binaryclausefinished8944
binaryclausefailed7917
	lda #0 ; failed state
binaryclausefinished8944
	cmp #1
	beq ConditionalTrueBlock26169
	jmp elseblock31635
	jmp elsedoneblock12483
ConditionalTrueBlock26169
	jmp printstring_call19732
printstring_text19579	.dc "WHILE2 OK ",0
printstring_call19732
	clc
	; TEST
	lda #<printstring_text19579
	adc #0
	ldy #>printstring_text19579
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock12483
elseblock31635
	jmp printstring_call21559
printstring_text32621	.dc "WHILE2 FAILED ******************** ",0
printstring_call21559
	clc
	; TEST
	lda #<printstring_text32621
	adc #0
	ldy #>printstring_text32621
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock12483
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
for23803

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
	bne forLoopFix18425
	jmp forLoopDone20428
forLoopFix18425
	jmp for23803
forLoopDone20428
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for141

	; Assigning single variable : val
	; Add/sub right value is variable/expression
	jmp jmprightvar27382
rightvar20725	.byte	0
jmprightvar27382
	lda x
	sta rightvar20725
	
	lda val
	clc
	adc rightvar20725
	
	; VarNode StoreVariable
	sta val

	inc x
	lda #3
	cmp x
	bne forLoopFix17911
	jmp forLoopDone24278
forLoopFix17911
	jmp for141
forLoopDone24278
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #6
	beq binaryclausefailed3127
	lda #1; success
	jmp binaryclausefinished26806
binaryclausefailed3127
	lda #0 ; failed state
binaryclausefinished26806
	cmp #1
	beq ConditionalTrueBlock7896
	jmp elseblock24255
	jmp elsedoneblock8054
ConditionalTrueBlock7896
	jmp printstring_call20347
printstring_text2619	.dc "FOR1 OK ",0
printstring_call20347
	clc
	; TEST
	lda #<printstring_text2619
	adc #0
	ldy #>printstring_text2619
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock8054
elseblock24255
	jmp printstring_call30683
printstring_text29352	.dc "FOR1 FAILED ******************** ",0
printstring_call30683
	clc
	; TEST
	lda #<printstring_text29352
	adc #0
	ldy #>printstring_text29352
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock8054
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
for20883

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
	bne forLoopFix17774
	jmp forLoopDone20250
forLoopFix17774
	jmp for20883
forLoopDone20250
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #25
	beq binaryclausefailed21720
	lda #1; success
	jmp binaryclausefinished3735
binaryclausefailed21720
	lda #0 ; failed state
binaryclausefinished3735
	cmp #1
	beq ConditionalTrueBlock19756
	jmp elseblock20847
	jmp elsedoneblock24323
ConditionalTrueBlock19756
	jmp printstring_call26660
printstring_text28368	.dc "FOR2 OK ",0
printstring_call26660
	clc
	; TEST
	lda #<printstring_text28368
	adc #0
	ldy #>printstring_text28368
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock24323
elseblock20847
	jmp printstring_call12979
printstring_text5801	.dc "FOR2 FAILED ******************** ",0
printstring_call12979
	clc
	; TEST
	lda #<printstring_text5801
	adc #0
	ldy #>printstring_text5801
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock24323
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for10770

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
	bne forLoopFix11363
	jmp forLoopDone29802
forLoopFix11363
	jmp for10770
forLoopDone29802
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
for2380

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
	bne forLoopFix6509
	jmp forLoopDone410
forLoopFix6509
	jmp for2380
forLoopDone410
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #8
	beq binaryclausefailed9951
	lda #1; success
	jmp binaryclausefinished22859
binaryclausefailed9951
	lda #0 ; failed state
binaryclausefinished22859
	cmp #1
	beq ConditionalTrueBlock13158
	jmp elseblock23722
	jmp elsedoneblock25878
ConditionalTrueBlock13158
	jmp printstring_call8961
printstring_text17318	.dc "FOR3 OK ",0
printstring_call8961
	clc
	; TEST
	lda #<printstring_text17318
	adc #0
	ldy #>printstring_text17318
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock25878
elseblock23722
	jmp printstring_call15937
printstring_text22060	.dc "FOR3 FAILED ******************** ",0
printstring_call15937
	clc
	; TEST
	lda #<printstring_text22060
	adc #0
	ldy #>printstring_text22060
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock25878
	jsr incScreen

	rts
afterProc_TestFor

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop20610
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop20610
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
