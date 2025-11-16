RAYLIB = $(PWD)/lib/raylib-5.5
TARGET = $(PWD)/bin

lidget: $(TARGET)/main.o $(TARGET)/xbg.o 
	gcc -Wall -Wextra -O2 $^ \
		-L$(RAYLIB)/lib -L/usr/include/X11 -lX11 -lraylib -Wl,-rpath=$(RAYLIB)/lib -o $(TARGET)/lidget

$(TARGET)/main.o: main.c xbg.h | $(TARGET)
	gcc -Wall -Wextra -O2 -I$(RAYLIB)/include -c main.c -o $(TARGET)/main.o


$(TARGET)/xbg.o: xbg.c xbg.h | $(TARGET)
	gcc -Wall -Wextra -O2 -I/usr/include/X11 -c xbg.c -o $(TARGET)/xbg.o

$(TARGET):
	mkdir -p $(TARGET)

clean:
	rm -rf $(TARGET)

run:
	$(TARGET)/lidget $(ARGS)
