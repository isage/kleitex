CPP = g++


SOURCES = kleitex.cpp

CFLAGS = -Wall -O0
LDFLAGS = -lsquish -lpng

OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = kleitex

DEPEND = makedepend -Y



all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $@ $(CFLAGS) $(LDFLAGS)

.cpp.o:
	$(CPP) -c $(CFLAGS) $< -o $(<:.cpp=.o) 

depend: $(SOURCES)
	$(DEPEND) $(SOURCES)

clean:
	-rm $(EXECUTABLE) $(SOURCES:.cpp=.o)
