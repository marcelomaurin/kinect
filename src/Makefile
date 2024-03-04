CC=gcc
CFLAGS=-c -Wall -I/usr/include/libfreenect
LDFLAGS=-L/usr/lib/x86_64-linux-gnu -lfreenect
SOURCES=kinect.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=kinect

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

