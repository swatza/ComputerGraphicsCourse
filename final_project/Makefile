#hw1make: main.c lorenz.c rendering.c keyboard.c
#	gcc -O3 -Wall -o hw1 main.c lorenz.c rendering.c keyboard.c -lglut -lGLU -lGL -lm

#clean:
#	rm -f hw1 *.o *.ad
#HW3
EXE=cow_tool
SOURCES=cow_animation.c keyboard.c rendering.c util.c primitives.c cow.c helper.c loadtexbmp.c windmill.c scene_1.c materials.c fence.c
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXE)

# MinGW
ifeq "$(OS)" "Windows_NT"
CLFG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del*.exe *.o *.a
else
# OSX
ifeq "$(shell uname)" "Darwin"
CLFG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#Linux/Unix/Solaris
else
CLFG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

#Link
$(EXE): $(OBJECTS)
	gcc $(CLFG) $(SOURCES) $(LIBS) -o $@

clean:
	$(CLEAN)
