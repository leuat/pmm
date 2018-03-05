procedure InitializeSprites();

begin
	sprite_x:=#160;
	sprite_y:=#180;
    poke(SPRITE_DATA_LOC,#0, #$0D); 
	poke(SPRITE_DATA_LOC,#1, #$0D);
    poke(SPRITE_BITMASK,#0, #%00000111);
	poke(SPRITE_COLOR,#0, WHITE);
    poke(SPRITE_COLOR,#1, YELLOW);
    memcpy(sprite0data, $0340, #63);

end;