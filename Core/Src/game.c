#include "game.h"
#include "lcd.h"

char game_level_data[16];
int game_score = 0;
#define GAME_START_LIVES 3
int game_current_lives = GAME_START_LIVES;
char game_n_generated_in_row = 0;
// Max frames player can hold a jump
#define GAME_JUMP_LEN 3

char game_random_tile()
{
	//TODO: seed random
	if (game_n_generated_in_row >= GAME_JUMP_LEN){
		game_n_generated_in_row = 0;
		return '_';
	} else {
		uint8_t res = rand() % 4 == 0 ? 'n' : '_';
		if (res == 'n'){
			game_n_generated_in_row ++;
		}
		return res;
	}
}

void game_shift_left()
{
//	LCD_command(0x18);//entire screen to the right
//	LCD_data(game_random_tile());

	LCD_home2();
	char cur[16];
	memcpy(cur, game_level_data, 16);
	memcpy(game_level_data, cur+1, 15);
	game_level_data[15] = game_random_tile();
}

void game_player()
{
	// TODO: when moving cursor to right here it will display wrong tiles behind player.
	// Should solve this, but for now just put player at left most tile

	if (game_jump >= GAME_JUMP_LEN){
		game_jump = 0;
	}

	if (!game_jump){
		// Erase player at jump pos
		LCD_home();
		LCD_data(' ');

		LCD_home2();
		LCD_data('|');

		// Check if player hit something
		uint8_t collision = game_level_data[0];
		if (collision == 'n'){
			game_current_lives -= 1;
			if (!game_current_lives){
				game_over = 1;
			}
		}
	} else {
		LCD_home();
		LCD_data('|');
		LCD_home2();
		game_jump ++;
	}
}

void game_over_state()
{
	LCD_home();
	LCD_text("game over");

	game_shift_left();
	LCD_text(game_level_data);
}

void game_render_lives()
{
	LCD_home();
	for (int i = 0; i < 3; i++){
		LCD_command(0x14);
	}
	for (int i = 0; i < GAME_START_LIVES; i++){
		if (i < game_current_lives){
			LCD_data('.');
		} else {
			LCD_data(' ');
		}
	}
}

void game_render_score()
{
	char snum[5];
	sprintf(snum, "%d", game_score);

	LCD_home();
	for (int i = 0; i < 15 - strlen(snum) + 1; i++){
		LCD_command(0x14);
	}

	LCD_text(snum);
}

void game_init()
{
	LCD_init();

	game_over = 0;
	game_current_lives = GAME_START_LIVES;
	game_score = 0;

	LCD_home2();
	memcpy(game_level_data, "________________", 16);
	//memcpy(game_level_data, "nnnn____________", 16);
	LCD_text(game_level_data);
}

void game_render()
{
	if (!game_over){
		game_shift_left();
		game_player();
		LCD_text(game_level_data);
		game_render_lives();
		game_score++;
	} else {
		game_over_state();
	}
	game_render_score();
}
