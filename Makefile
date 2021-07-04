INCLUDE_PATH	=	include
OBJ_PATH	=	obj
SRC_PATH	=	src
CC	=	g++
EXE	=	maze-game

_OBJS	=	maze.o	scenes.o	var.o	common.o	main.o
OBJS	=	$(patsubst	%,	$(OBJ_PATH)/%,	$(_OBJS))

_DEPS	=	maze.hpp	scenes.hpp	common.hpp	var.hpp
DEPS	=	$(patsubst	%,	$(INCLUDE_PATH)/%,	$(_DEPS))

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.cpp	$(DEPS)
	mkdir -p obj
	$(CC)	-I./$(INCLUDE_PATH)	-c	-o	$@	$<

.PHONY:	game
game:	$(OBJS)
	$(CC)	-I./$(INCLUDE_PATH)	$(OBJS)	-o	$(EXE)	-lGL -lGLU -lglut -no-pie

.PHONY:	fresh
fresh:	clean	game

.PHONY:	clean
clean:
	rm	-f	$(OBJS) $(EXE)
