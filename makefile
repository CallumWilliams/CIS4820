INCLUDES = -w -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

a4: a1.c utils.h item mob wall graphic visible
	gcc a1.c *.o -o a4 $(INCLUDES)
	rm *.o

item: item.c item.h graphics.h
	gcc -c item.c -o item.o $(INCLUDES)

mob: mob.c mob.h graphics.h
	gcc -c mob.c -o mob.o $(INCLUDES)

wall: walls.c walls.h graphics.h
	gcc -c walls.c -o walls.o $(INCLUDES)

graphic: graphics.c graphics.h
	gcc -c graphics.c -o graphics.o $(INCLUDES)

visible: visible.c graphics.h
	gcc -c visible.c -o visible.o $(INCLUDES)

clean:
	rm a4
