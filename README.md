# pmm
Rascal-- 

A pascal-like low-level compiler to MOS6502 processors.

Write sexy Rascal programs directly for your c64. Compiles to dasm assembler. 

Example program: 


	
  ```Pascal
 PROGRAM FirstC64;

VAR
   a, b, c, i, j,k,val,mainloop, idx, time,c2x, c2y,ax, ay : byte;
   x,y,scrollx,shiftx, shifty : byte;
   sprite0data: IncBin("sprite1.bin");
   charset: IncBin("test.bin","$1fff");
   fadeOut : array [8] of byte = ($00,$0d,$0b,$05,$02,$0a,$09,$0f,$04,$00,$0c,$06,$0e,$07,$08,$03 );
	fadeRedBlue : array [8] of byte = (00,$0f,$09,$0e,$02,$0c,$00,$0c,$09,$00,$02,$00,$0b,$05,$06,$0c); 

   siny : array[25] of byte; 
   sinx : array[40] of byte; 

   message: array[255] of byte;
  
   sprite_x : array[8] of byte;
   sprite_y : array[8] of byte;


	
procedure Plasma();
begin

	c2x:=ax;
	c2y:=ay;

	for x:=#0 to #25 do begin 
		siny[x]:=  sine[c2x] + sine[c2y];

		c2x:=c2x+#4;
		c2y:=c2y+#9;
	end;

	ax:=ax+#3;
	ay:=ay-#5;

		

	for x:=#0 to #40 do begin 
		sinx[x] := sine[c2x] + sine[c2y];
		c2x:=c2x+#6;
		c2y:=c2y+#14;

	end;

	for y:=#9 to #23 do begin
		moveto(#1,y, #$04);
		peek(siny, y, val);
		for x:=#1 to #19 do begin
			k:=sinx[x] +val;

		 	k:=k/#8;
			c:=fadeRedBlue[k/#4];
			k:=k+#64;

			pokescreencolor(k,c,#0,#2);
/*			pokescreencolor(k,c,#1);*/
			incscreenx(#2);

		end;
	end;
		
	

end;



procedure InitializeSprites();

begin
    poke(SPRITE_DATA_LOC,#0, #$0D); 
	poke(SPRITE_DATA_LOC,#1, #$0D);
    poke(SPRITE_BITMASK,#0, #%00000111);
	poke(SPRITE_COLOR,#0, WHITE);
    poke(SPRITE_COLOR,#1, YELLOW);
    memcpy(sprite0data, $0340, #63);

end;


procedure MoveSprite();
begin
	b:=time;
	poke(SPRITE_POS,#0, b);
    	poke(SPRITE_POS,#1, b);

end;


procedure PrintText(); 
begin
	MoveTo(#10, #24, #$04);
	printstring(message, #0);
	MoveTo(#17, #24, #$04);
	printnumber(time);

end;


begin
	moveto(#0,#0, #$04);
	message:="TIME";
	i:=#0;
	a:=#4;
	b:=#4;
	a:=b*#3;
	poke(SCREEN_BACKGROUND_COLOR, #0, a);

	poke(SCREEN_BACKGROUND_COLOR, #1, BLACK);
 	poke(SCREEN_BACKGROUND_COLOR, #0, BLACK);
	poke($d018, #0, #$18);
    poke($C202, #0,#13);

	mainloop:=#1;
	time:=#0;


	ax:=#1;
	ay:=#5;
	fill($D800, GREEN,#0);
	fill($D900, GREEN,#0);
	fill($DA00, GREEN,#0);
	fill($DB00, GREEN,#0);
	asm("
	cli
	");


	InitializeSprites();

	while mainloop<#10 do begin
		time:=time+#1;
		shiftx:=shiftx+#1;
		shifty:=shifty+#3;

		Plasma();
		PrintText();
		MoveSprite();
	end;

END.
```


To do:
  - 16 bit operands
  - 16 bit poke sprite location
  - sid music
  - IRQs
  - user input
  - create small shooter game
