#HW1
EXE=hw1
SOURCES=main.c lorenz.c keyboard.c rendering.c
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

#Compile rules
.c.o:
	gcc -c $(CLFG) $< -o $@
	
#Link
$(EXE): $(OBJECTS)
	gcc -O3 $(LIBS) $(OBJECTS) -o $@
