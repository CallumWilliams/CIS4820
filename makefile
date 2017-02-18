

INCLUDES = -w -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

a1: a1.c graphics.c visible.c graphics.h walls.c
	gcc a1.c graphics.c visible.c walls.c -o a1 $(INCLUDES)
