

INCLUDES = -w -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

a1: a1.c wall graphic visible
	gcc a1.c *.o -o a1 $(INCLUDES)
	rm *.o

wall: walls.c walls.h graphic visible
	gcc -c walls.c -o walls.o $(INCLUDES)

graphic: graphics.c graphics.h
	gcc -c graphics.c -o graphics.o $(INCLUDES)

visible:
	gcc -c visible.c -o visible.o $(INCLUDES)
