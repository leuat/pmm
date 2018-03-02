# pmm
Rascal-- 

A pascal-like low-level compiler to MOS6502 processors.

Write sexy Rascal programs directly for your c64. Compiles to dasm assembler. 

Example program: 


	
  ```Pascal
  PROGRAM FirstC64;
VAR
   a, b, c, i, j,k,val : byte;
   x,y,scrollx : byte;
   sprite0data: IncBin("sprite1.bin");
   charset: IncBin("scrap.bin","$1ffe");
   colorVals : array [8] of byte = (0, 11, 6, 12, 14, 13, 15, 17,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,17, 15, 13 ,14 ,12, 6, 11 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   charVals : array[8] of byte = (166, 161, 162, 191, 187, 169);
BEGIN
	InitRandom();
  
	i:=#0;
	a:=#0;
	b:=#0;
	poke(SCREEN_BACKGROUND_COLOR, #1, BLACK);
 	poke(SCREEN_BACKGROUND_COLOR, #0, BLACK);
	{poke($d018, #0, #$18);
    	poke($C202, #0,#13);}

	j:=#1;
	c:=#0;
	scrollx:=#7;
	while i<#10 do begin
 		{rand(#0,#40,x);
		rand(#0,#25,y);
		moveto(x,y,#$04);
	
		moveto(x,y,#$D8);}
		c:=c+#1;
		if c=#40 then begin
			c:=#0;
		end;
		{pokescreen(val);}
		{k:=colorVals + c;}
		peek(colorVals, c, k);

			rand(#0,#5,val);
			peek(charVals, val, j);
			fill($0400,j,#$FF);
			fill($D800,k,#$FF);
			fill($0400+1*#$FF,j,#$FF);
			fill($D800+1*#$FF,k,#$FF);
			fill($0400+2*#$FF,j,#$FF);
			fill($0400+3*#$FF,j,#$FF);
			{fill($D800+2*#$FF,k,#$FF);}

		while a<>#0 do begin
			peek(RASTERLINE_POS, #0,a);
		end;
		while a<>#199 do begin
			peek(RASTERLINE_POS, #0,a);
		end;
		scroll(scrollx);
		scrollx:=scrollx+#1;	
		if scrollx=#0 then begin
			scrollx:=#7;
		end;
	

       end;



END.

```


To do:
  - Sine wave table
  - 16 bit operands
  - memory direct access like
     a:=vals[b]; // aka peek
     vals[b]:=5; // aka poke
     
  - print text at x,y
  - print number at x,y
  - sid music
  - IRQs
