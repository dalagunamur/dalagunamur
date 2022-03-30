CC=gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
FLAGGLUT=-lglut -lGL -lGLU
endif
ifeq ($(UNAME_S),Darwin)
FLAGGLUT=-Wno-deprecated-declarations -framework OpenGL -framework GLUT
endif

FLAG=-Wall -std=c99 -IC
SRCS= main.c game.c menu.c drawScreen.c map/map.c game_elements/bonus.c game_elements/missile.c game_elements/obstacle.c game_elements/player.c game_elements/car.c
## OBJET = $(SRCS:.c=.o)
OBJET = main.o game.o menu.o map.o bonus.o missile.o obstacle.o player.o car.o drawScreen.o
EXEC= program



all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) -c $(SRCS) $(FLAG) $(FLAGGLUT)
	$(CC) -o $(EXEC) $(OBJET) $(FLAG) $(FLAGGLUT)
	
clean:
	rm -rf *.o
