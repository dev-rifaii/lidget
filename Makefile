RAYLIB = $(PWD)/lib/raylib/src
TARGET = $(PWD)/bin

lidget: $(TARGET)/main.o $(TARGET)/xbg.o 
	gcc -Wall -Wextra -O2 $^ \
		-L$(RAYLIB) -L/usr/include/X11 -L/usr/include/GLFW -lX11 -lraylib -lm -lglfw -Wl,-rpath=$(RAYLIB)/lib -o $(TARGET)/lidget

$(TARGET)/main.o: main.c xbg.h | $(TARGET)
	gcc -Wall -Wextra -O2 -I$(RAYLIB) -c main.c -o $(TARGET)/main.o


$(TARGET)/xbg.o: xbg.c xbg.h | $(TARGET)
	gcc -Wall -Wextra -O2 -I/usr/include/X11 -I/usr/include/GLFW -c xbg.c -o $(TARGET)/xbg.o

$(TARGET):
	mkdir -p $(TARGET)

clean:
	rm -rf $(TARGET)

run:
	$(TARGET)/lidget $(ARGS)
