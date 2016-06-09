

all:
	gcc si.c  init_score.o init_invaders.o essential_structs.o essential_defines.o essential_global.o init_player.o init_bullets.o init_saucer.o draw_background.o draw_hud.o draw_title_screen.o draw_saucer.o draw_invaders.o draw_bases.o draw_player.o draw_bullets.o draw_char.o draw_string.o draw_game_over.o set_invaders_speed.o move_bullets.o move_invaders_down.o move_invaders.o move_player.o move_saucer.o collision.o bullet_base_damage.o enemy_base_damage.o enemy_hit_collision.o player_hit_collision.o saucer_hit_collision.o enemy_player_collision.o bullet_base_collision.o game_over_ai.o player_shoot.o calculate_level.o saucer_ai.o enemy_ai.o pause_game.o pause_for.o -lSDL -o invaders
essential_structs: 
	gcc -c essential_structs.c
essential_defines:
	gcc -c essential_defines.c
essential_global:
	gcc -c essential_global.c
init_score:
	gcc -c init_score.c 
init_invaders:
	gcc -c init_invaders.c 
init_player:
	gcc -c init_player.c
init_bullets:
	gcc -c init_bullets.c
init_saucer:
	gcc -c init_saucer.c
draw_background:
	gcc -c draw_background.c
draw_hud:
	gcc -c draw_hud.c
draw_title_screen:
	gcc -c draw_title_screen.c
draw_saucer:
	gcc -c draw_saucer.c
draw_invaders:
	gcc -c draw_invaders.c
draw_bases:
	gcc -c draw_bases.c
draw_player:
	gcc -c draw_player.c
draw_bullets:
	gcc -c draw_bullets.c
draw_char:
	gcc -c draw_char.c
draw_string:
	gcc -c draw_string.c
draw_game_over:
	gcc -c draw_game_over.c
set_invaders_speed:
	gcc -c set_invaders_speed.c
move_bullets:
	gcc -c move_bullets.c
move_invaders_down:
	gcc -c move_invaders_down.c
move_invaders:
	gcc -c move_invaders.c
move_player:
	gcc -c move_player.c
move_saucer:
	gcc -c move_saucer.c
collision:
	gcc -c collision.c
bullet_base_damage:
	gcc -c bullet_base_damage.c
enemy_base_damage:
	gcc -c enemy_base_damage.c
enemy_base_collision:
	gcc -c enemy_base_collision.c
enemy_hit_collision:
	gcc -c enemy_hit_collision.c
player_hit_collision:
	gcc -c player_hit_collision.c
saucer_hit_collision:
	gcc -c saucer_hit_collision.c
enemy_player_collision:
	gcc -c enemy_player_collision.c
bullet_base_collision:
	gcc -c bullet_base_collision.c
game_over_ai:
	gcc -c game_over_ai.c
player_shoot:
	gcc -c player_shoot.c
calculate_level:
	gcc -c calculate_level.c
saucer_ai:
	gcc -c saucer_ai.c
enemy_ai:
	gcc -c enemy_ai.c
pause_game:
	gcc -c pause_game.c
pause_for:
	gcc -c pause_for.c







