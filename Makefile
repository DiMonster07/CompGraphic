CC = g++

SOURCES = mainFPS.cpp camera.cpp
EXECUTABLE = main
OBJECTS = $(SOURCES: .cpp = .o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lSOIL -lGL -lGLEW -lglut
del:
	rm -f &(EXECUTABLE) *.o
