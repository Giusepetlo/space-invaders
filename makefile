
invaders:
	gcc si.c init.o move.o collision.o diverses.o load.o maxpont.o -lSDL -lSDL_mixer -o invaders
all:
	gcc -c essential.c essential_defines.c essential_structs.c essential_global.c init.c move.c collision.c diverses.c load.c maxpont.c
essential:
	gcc -c essential.c
essential_defines:
	gcc -c essential_defines.c
essential_structs:
	gcc -c essential_structs.c
essential_global:
	gcc -c essential_global.c
init:
	gcc -c init.c
move:
	gcc -c move.c
collision:
	gcc -c collision.c
diverses:
	gcc -c diverses.c
load:
	gcc -c load.c
maxpont:
	cc -c maxpont.c








