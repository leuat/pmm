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
	; Binary clause: GREATER
	; Compare with pure num / var optimization
	cmp #23
	bcc binaryclausefailed26962
	lda #1; success
	jmp binaryclausefinished24464
binaryclausefailed26962
	lda #0 ; failed state
binaryclausefinished24464
	cmp #1
	beq ConditionalTrueBlock15724
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
	; Binary clause: LESS
	lda y
	; Compare with pure num / var optimization
	cmp #20
	bcs binaryclausefailed2995
	lda #1; success
	jmp binaryclausefinished11942
binaryclausefailed2995
	lda #0 ; failed state
binaryclausefinished11942
	cmp #1
	beq ConditionalTrueBlock16827
	jmp elseblock9961
	jmp elsedoneblock491
ConditionalTrueBlock16827
	jmp printstring_call5436
printstring_text32391	.dc "CONDITIONAL1 = OK",0
printstring_call5436
	clc
	; TEST
	lda #<printstring_text32391
	adc #0
	ldy #>printstring_text32391
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock491
elseblock9961
	jmp printstring_call3902
printstring_text153	.dc "CONDITIONAL1 = FAILED ****************** ",0
printstring_call3902
	clc
	; TEST
	lda #<printstring_text153
	adc #0
	ldy #>printstring_text153
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock491
	jsr incScreen
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed19718
	lda #1; success
	jmp binaryclausefinished19895
binaryclausefailed19718
	lda #0 ; failed state
binaryclausefinished19895
	cmp #1
	beq ConditionalTrueBlock12382
	jmp elseblock17421
	jmp elsedoneblock18716
ConditionalTrueBlock12382
	jmp printstring_call21726
printstring_text14771	.dc "CONDITIONAL2 = OK",0
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
	jmp elsedoneblock18716
elseblock17421
	jmp printstring_call1869
printstring_text19912	.dc "CONDITIONAL2 = FAILED ****************** ",0
printstring_call1869
	clc
	; TEST
	lda #<printstring_text19912
	adc #0
	ldy #>printstring_text19912
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock18716
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed28703
	lda #1; success
	jmp binaryclausefinished23811
binaryclausefailed28703
	lda #0 ; failed state
binaryclausefinished23811
	cmp #1
	beq ConditionalTrueBlock26299
	jmp elseblock17035
	jmp elsedoneblock9894
ConditionalTrueBlock26299
	jmp printstring_call30333
printstring_text17673	.dc "CONDITIONAL3 = OK",0
printstring_call30333
	clc
	; TEST
	lda #<printstring_text17673
	adc #0
	ldy #>printstring_text17673
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock9894
elseblock17035
	jmp printstring_call15141
printstring_text7711	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call15141
	clc
	; TEST
	lda #<printstring_text7711
	adc #0
	ldy #>printstring_text7711
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock9894
	jsr incScreen
	; Binary clause: NOTEQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed32662
	lda #1; success
	jmp binaryclausefinished32757
binaryclausefailed32662
	lda #0 ; failed state
binaryclausefinished32757
	cmp #1
	beq ConditionalTrueBlock6868
	jmp elseblock25547
	jmp elsedoneblock27644
ConditionalTrueBlock6868
	jmp printstring_call12859
printstring_text8723	.dc "CONDITIONAL3 = OK",0
printstring_call12859
	clc
	; TEST
	lda #<printstring_text8723
	adc #0
	ldy #>printstring_text8723
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock27644
elseblock25547
	jmp printstring_call27529
printstring_text778	.dc "CONDITIONAL3 = FAILED ****************** ",0
printstring_call27529
	clc
	; TEST
	lda #<printstring_text778
	adc #0
	ldy #>printstring_text778
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock27644
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed288
	lda #1; success
	jmp binaryclausefinished30106
binaryclausefailed288
	lda #0 ; failed state
binaryclausefinished30106
	jmp logical_class_temp_label8942
logical_class_temp_var9040	.byte	0
logical_class_temp_label8942
	sta logical_class_temp_var9040
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	beq binaryclausefailed19264
	lda #1; success
	jmp binaryclausefinished22648
binaryclausefailed19264
	lda #0 ; failed state
binaryclausefinished22648
	ora logical_class_temp_var9040
	cmp #1
	beq ConditionalTrueBlock3035
	jmp elseblock22190
	jmp elsedoneblock1842
ConditionalTrueBlock3035
	jmp printstring_call23805
printstring_text15890	.dc "CONDITIONAL4 = OK",0
printstring_call23805
	clc
	; TEST
	lda #<printstring_text15890
	adc #0
	ldy #>printstring_text15890
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock1842
elseblock22190
	jmp printstring_call24370
printstring_text15350	.dc "CONDITIONAL4 = FAILED ****************** ",0
printstring_call24370
	clc
	; TEST
	lda #<printstring_text15350
	adc #0
	ldy #>printstring_text15350
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock1842
	jsr incScreen
	; Binary clause: GREATER
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bcc binaryclausefailed19629
	lda #1; success
	jmp binaryclausefinished12623
binaryclausefailed19629
	lda #0 ; failed state
binaryclausefinished12623
	jmp logical_class_temp_label19954
logical_class_temp_var24084	.byte	0
logical_class_temp_label19954
	sta logical_class_temp_var24084
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed18756
	lda #1; success
	jmp binaryclausefinished11840
binaryclausefailed18756
	lda #0 ; failed state
binaryclausefinished11840
	and logical_class_temp_var24084
	cmp #1
	beq ConditionalTrueBlock31101
	jmp elseblock24393
	jmp elsedoneblock3548
ConditionalTrueBlock31101
	jmp printstring_call7376
printstring_text13931	.dc "CONDITIONAL5 = OK",0
printstring_call7376
	clc
	; TEST
	lda #<printstring_text13931
	adc #0
	ldy #>printstring_text13931
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock3548
elseblock24393
	jmp printstring_call16944
printstring_text32439	.dc "CONDITIONAL5 = FAILED ****************** ",0
printstring_call16944
	clc
	; TEST
	lda #<printstring_text32439
	adc #0
	ldy #>printstring_text32439
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock3548
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed16118
	lda #1; success
	jmp binaryclausefinished2082
binaryclausefailed16118
	lda #0 ; failed state
binaryclausefinished2082
	jmp logical_class_temp_label16541
logical_class_temp_var22929	.byte	0
logical_class_temp_label16541
	sta logical_class_temp_var22929
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #0
	bne binaryclausefailed4833
	lda #1; success
	jmp binaryclausefinished31115
binaryclausefailed4833
	lda #0 ; failed state
binaryclausefinished31115
	jmp logical_class_temp_label29658
logical_class_temp_var4639	.byte	0
logical_class_temp_label29658
	sta logical_class_temp_var4639
	; Binary clause: EQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #20
	bne binaryclausefailed22704
	lda #1; success
	jmp binaryclausefinished9930
binaryclausefailed22704
	lda #0 ; failed state
binaryclausefinished9930
	and logical_class_temp_var4639
	and logical_class_temp_var22929
	cmp #1
	beq ConditionalTrueBlock11323
	jmp elseblock5537
	jmp elsedoneblock21538
ConditionalTrueBlock11323
	jmp printstring_call2306
printstring_text31673	.dc "CONDITIONAL6 = OK",0
printstring_call2306
	clc
	; TEST
	lda #<printstring_text31673
	adc #0
	ldy #>printstring_text31673
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock21538
elseblock5537
	jmp printstring_call5021
printstring_text28745	.dc "CONDITIONAL6 = FAILED ****************** ",0
printstring_call5021
	clc
	; TEST
	lda #<printstring_text28745
	adc #0
	ldy #>printstring_text28745
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock21538
	jsr incScreen
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed26777
	lda #1; success
	jmp binaryclausefinished15573
binaryclausefailed26777
	lda #0 ; failed state
binaryclausefinished15573
	jmp logical_class_temp_label16512
logical_class_temp_var5097	.byte	0
logical_class_temp_label16512
	sta logical_class_temp_var5097
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #23
	bne binaryclausefailed23986
	lda #1; success
	jmp binaryclausefinished13290
binaryclausefailed23986
	lda #0 ; failed state
binaryclausefinished13290
	jmp logical_class_temp_label18636
logical_class_temp_var9161	.byte	0
logical_class_temp_label18636
	sta logical_class_temp_var9161
	; Binary clause: NOTEQUALS
	lda z
	; Compare with pure num / var optimization
	cmp #10
	beq binaryclausefailed22355
	lda #1; success
	jmp binaryclausefinished24767
binaryclausefailed22355
	lda #0 ; failed state
binaryclausefinished24767
	ora logical_class_temp_var9161
	ora logical_class_temp_var5097
	cmp #1
	beq ConditionalTrueBlock19072
	jmp elseblock6270
	jmp elsedoneblock5829
ConditionalTrueBlock19072
	jmp printstring_call15574
printstring_text4031	.dc "CONDITIONAL7 = OK",0
printstring_call15574
	clc
	; TEST
	lda #<printstring_text4031
	adc #0
	ldy #>printstring_text4031
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock5829
elseblock6270
	jmp printstring_call27350
printstring_text1150	.dc "CONDITIONAL7 = FAILED ****************** ",0
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
elsedoneblock5829
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	bne binaryclausefailed31107
	lda #1; success
	jmp binaryclausefinished30191
binaryclausefailed31107
	lda #0 ; failed state
binaryclausefinished30191
	jmp logical_class_temp_label11337
logical_class_temp_var18007	.byte	0
logical_class_temp_label11337
	sta logical_class_temp_var18007
	; Binary clause: EQUALS
	lda y
	; Compare with pure num / var optimization
	cmp #10
	bne binaryclausefailed15457
	lda #1; success
	jmp binaryclausefinished12287
binaryclausefailed15457
	lda #0 ; failed state
binaryclausefinished12287
	ora logical_class_temp_var18007
	cmp #1
	beq ConditionalTrueBlock21724
	jmp elseblock13966
	jmp elsedoneblock3430
ConditionalTrueBlock21724
	jmp printstring_call10383
printstring_text14945	.dc "CONDITIONAL8 = OK",0
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
	jmp elsedoneblock3430
elseblock13966
	jmp printstring_call32209
printstring_text9758	.dc "CONDITIONAL8 = FAILED ****************** ",0
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
elsedoneblock3430
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
	bne binaryclausefailed13030
	lda #1; success
	jmp binaryclausefinished16413
binaryclausefailed13030
	lda #0 ; failed state
binaryclausefinished16413
	cmp #1
	beq ConditionalTrueBlock6422
	jmp elseblock24946
	jmp elsedoneblock27506
ConditionalTrueBlock6422
	jmp printstring_call900
printstring_text32591	.dc "ASSIGN1 OK ",0
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
	jmp elsedoneblock27506
elseblock24946
	jmp printstring_call1655
printstring_text17410	.dc "ASSING 1 FAILED ****************",0
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
elsedoneblock27506
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
	bne binaryclausefailed4041
	lda #1; success
	jmp binaryclausefinished3602
binaryclausefailed4041
	lda #0 ; failed state
binaryclausefinished3602
	cmp #1
	beq ConditionalTrueBlock21548
	jmp elseblock6483
	jmp elsedoneblock27595
ConditionalTrueBlock21548
	jmp printstring_call10291
printstring_text30836	.dc "ASSIGN2 OK ",0
printstring_call10291
	clc
	; TEST
	lda #<printstring_text30836
	adc #0
	ldy #>printstring_text30836
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock27595
elseblock6483
	jmp printstring_call11020
printstring_text4596	.dc "ASSING 2 FAILED ****************",0
printstring_call11020
	clc
	; TEST
	lda #<printstring_text4596
	adc #0
	ldy #>printstring_text4596
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock27595
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
	bne binaryclausefailed4734
	lda #1; success
	jmp binaryclausefinished53
binaryclausefailed4734
	lda #0 ; failed state
binaryclausefinished53
	cmp #1
	beq ConditionalTrueBlock19668
	jmp elseblock24484
	jmp elsedoneblock8281
ConditionalTrueBlock19668
	jmp printstring_call26418
printstring_text27938	.dc "ASSIGN3 OK ",0
printstring_call26418
	clc
	; TEST
	lda #<printstring_text27938
	adc #0
	ldy #>printstring_text27938
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock8281
elseblock24484
	jmp printstring_call3788
printstring_text18127	.dc "ASSING 3 FAILED ****************",0
printstring_call3788
	clc
	; TEST
	lda #<printstring_text18127
	adc #0
	ldy #>printstring_text18127
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock8281
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
	bne binaryclausefailed2421
	lda #1; success
	jmp binaryclausefinished14310
binaryclausefailed2421
	lda #0 ; failed state
binaryclausefinished14310
	cmp #1
	beq ConditionalTrueBlock24648
	jmp elseblock22483
	jmp elsedoneblock17807
ConditionalTrueBlock24648
	jmp printstring_call22813
printstring_text9514	.dc "ASSIGN4 OK ",0
printstring_call22813
	clc
	; TEST
	lda #<printstring_text9514
	adc #0
	ldy #>printstring_text9514
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock17807
elseblock22483
	jmp printstring_call7616
printstring_text18935	.dc "ASSING 4 FAILED ****************",0
printstring_call7616
	clc
	; TEST
	lda #<printstring_text18935
	adc #0
	ldy #>printstring_text18935
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock17807
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
	bne binaryclausefailed11008
	lda #1; success
	jmp binaryclausefinished5844
binaryclausefailed11008
	lda #0 ; failed state
binaryclausefinished5844
	cmp #1
	beq ConditionalTrueBlock22798
	jmp elseblock30303
	jmp elsedoneblock6224
ConditionalTrueBlock22798
	jmp printstring_call14989
printstring_text32702	.dc "ASSIGN5 OK ",0
printstring_call14989
	clc
	; TEST
	lda #<printstring_text32702
	adc #0
	ldy #>printstring_text32702
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock6224
elseblock30303
	jmp printstring_call20485
printstring_text3093	.dc "ASSING 5 FAILED ****************",0
printstring_call20485
	clc
	; TEST
	lda #<printstring_text3093
	adc #0
	ldy #>printstring_text3093
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock6224
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
	bne binaryclausefailed6618
	lda #1; success
	jmp binaryclausefinished20580
binaryclausefailed6618
	lda #0 ; failed state
binaryclausefinished20580
	cmp #1
	beq ConditionalTrueBlock7448
	jmp elseblock25200
	jmp elsedoneblock13458
ConditionalTrueBlock7448
	jmp printstring_call14798
printstring_text15281	.dc "ASSIGN6 OK ",0
printstring_call14798
	clc
	; TEST
	lda #<printstring_text15281
	adc #0
	ldy #>printstring_text15281
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock13458
elseblock25200
	jmp printstring_call20798
printstring_text28009	.dc "ASSING 6 FAILED ****************",0
printstring_call20798
	clc
	; TEST
	lda #<printstring_text28009
	adc #0
	ldy #>printstring_text28009
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock13458
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
while20472
	; Binary clause: NOTEQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #1
	beq binaryclausefailed6038
	lda #1; success
	jmp binaryclausefinished24179
binaryclausefailed6038
	lda #0 ; failed state
binaryclausefinished24179
	cmp #1
	beq ConditionalTrueBlock23622
	jmp elsedoneblock12292
ConditionalTrueBlock23622

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

	jmp while20472
elsedoneblock12292
	; Binary clause: EQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #9
	bne binaryclausefailed22888
	lda #1; success
	jmp binaryclausefinished19156
binaryclausefailed22888
	lda #0 ; failed state
binaryclausefinished19156
	cmp #1
	beq ConditionalTrueBlock7958
	jmp elseblock6191
	jmp elsedoneblock19815
ConditionalTrueBlock7958
	jmp printstring_call16202
printstring_text2634	.dc "WHILE1 OK ",0
printstring_call16202
	clc
	; TEST
	lda #<printstring_text2634
	adc #0
	ldy #>printstring_text2634
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock19815
elseblock6191
	jmp printstring_call20055
printstring_text20328	.dc "WHILE1 FAILED ******************** ",0
printstring_call20055
	clc
	; TEST
	lda #<printstring_text20328
	adc #0
	ldy #>printstring_text20328
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock19815
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
while22646
	; Binary clause: LESS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bcs binaryclausefailed28433
	lda #1; success
	jmp binaryclausefinished29869
binaryclausefailed28433
	lda #0 ; failed state
binaryclausefinished29869
	cmp #1
	beq ConditionalTrueBlock26362
	jmp elsedoneblock18875
ConditionalTrueBlock26362

	; Assigning single variable : x
	; Add/sub where right value is constant number
	lda x
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta x

	jmp while22646
elsedoneblock18875
	; Binary clause: EQUALS
	lda x
	; Compare with pure num / var optimization
	cmp #5
	bne binaryclausefailed10322
	lda #1; success
	jmp binaryclausefinished18651
binaryclausefailed10322
	lda #0 ; failed state
binaryclausefinished18651
	cmp #1
	beq ConditionalTrueBlock1416
	jmp elseblock21881
	jmp elsedoneblock31998
ConditionalTrueBlock1416
	jmp printstring_call5699
printstring_text3557	.dc "WHILE2 OK ",0
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
	jmp elsedoneblock31998
elseblock21881
	jmp printstring_call27892
printstring_text24389	.dc "WHILE2 FAILED ******************** ",0
printstring_call27892
	clc
	; TEST
	lda #<printstring_text24389
	adc #0
	ldy #>printstring_text24389
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock31998
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
for10712
	lda #10
	cmp x
	bne forLoopFix2600
	jmp forLoopDone2510
forLoopFix2600

	; Assigning single variable : arr
	lda x
	; VarNode StoreVariable
	pha
	lda x
	tax
	pla
	sta arr,x

	inc x
	jmp for10712
forLoopDone2510
	; Assigning single variable : val
	lda #0
	; VarNode StoreVariable
	sta val
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for26869
	lda #3
	cmp x
	bne forLoopFix17861
	jmp forLoopDone14688
forLoopFix17861

	; Assigning single variable : val
	; Add/sub right value is variable/expression
	jmp jmprightvar15255
rightvar9789	.byte	0
jmprightvar15255
	lda x
	sta rightvar9789
	
	lda val
	clc
	adc rightvar9789
	
	; VarNode StoreVariable
	sta val

	inc x
	jmp for26869
forLoopDone14688
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #6
	beq binaryclausefailed10285
	lda #1; success
	jmp binaryclausefinished27088
binaryclausefailed10285
	lda #0 ; failed state
binaryclausefinished27088
	cmp #1
	beq ConditionalTrueBlock5002
	jmp elseblock10585
	jmp elsedoneblock24182
ConditionalTrueBlock5002
	jmp printstring_call28617
printstring_text23757	.dc "FOR1 OK ",0
printstring_call28617
	clc
	; TEST
	lda #<printstring_text23757
	adc #0
	ldy #>printstring_text23757
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock24182
elseblock10585
	jmp printstring_call30932
printstring_text4169	.dc "FOR1 FAILED ******************** ",0
printstring_call30932
	clc
	; TEST
	lda #<printstring_text4169
	adc #0
	ldy #>printstring_text4169
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock24182
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
for2154
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
	bne forLoopFix25721
	jmp forLoopDone17189
forLoopFix25721

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	jmp for2154
forLoopDone17189
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #25
	beq binaryclausefailed16549
	lda #1; success
	jmp binaryclausefinished7441
binaryclausefailed16549
	lda #0 ; failed state
binaryclausefinished7441
	cmp #1
	beq ConditionalTrueBlock21425
	jmp elseblock10555
	jmp elsedoneblock3434
ConditionalTrueBlock21425
	jmp printstring_call30145
printstring_text18060	.dc "FOR2 OK ",0
printstring_call30145
	clc
	; TEST
	lda #<printstring_text18060
	adc #0
	ldy #>printstring_text18060
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock3434
elseblock10555
	jmp printstring_call3753
printstring_text16139	.dc "FOR2 FAILED ******************** ",0
printstring_call3753
	clc
	; TEST
	lda #<printstring_text16139
	adc #0
	ldy #>printstring_text16139
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock3434
	jsr incScreen
	; Assigning single variable : x
	lda #0
	; VarNode StoreVariable
	sta x
for12423
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
	bne forLoopFix16279
	jmp forLoopDone25996
forLoopFix16279

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	jmp for12423
forLoopDone25996
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
for17437
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
	bne forLoopFix19866
	jmp forLoopDone12949
forLoopFix19866

	; Assigning single variable : val
	; Add/sub where right value is constant number
	lda val
	clc
	adc #1
	 ; end add / sub var with constant
	
	; VarNode StoreVariable
	sta val

	inc x
	jmp for17437
forLoopDone12949
	; Binary clause: NOTEQUALS
	lda val
	; Compare with pure num / var optimization
	cmp #8
	beq binaryclausefailed16282
	lda #1; success
	jmp binaryclausefinished12455
binaryclausefailed16282
	lda #0 ; failed state
binaryclausefinished12455
	cmp #1
	beq ConditionalTrueBlock28286
	jmp elseblock16105
	jmp elsedoneblock24488
ConditionalTrueBlock28286
	jmp printstring_call18114
printstring_text11701	.dc "FOR3 OK ",0
printstring_call18114
	clc
	; TEST
	lda #<printstring_text11701
	adc #0
	ldy #>printstring_text11701
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
	jmp elsedoneblock24488
elseblock16105
	jmp printstring_call20671
printstring_text5786	.dc "FOR3 FAILED ******************** ",0
printstring_call20671
	clc
	; TEST
	lda #<printstring_text5786
	adc #0
	ldy #>printstring_text5786
	sta print_text+0
	sty print_text+1
	lda #40
	tax
	jsr printstring
elsedoneblock24488
	jsr incScreen

	rts
afterProc_TestFor

	; Clear screen with offset
	lda #$00
	tax
	lda #32
clearloop12263
	sta $0000+$400,x
	sta $0100+$400,x
	sta $0200+$400,x
	sta $0300+$400,x
	dex
	bne clearloop12263
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
