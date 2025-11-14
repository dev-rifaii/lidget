RAYLIB = $(PWD)/raylib-5.5_linux_amd64
TARGET = $(PWD)/bin

lidget: $(TARGET)/main.o
	gcc -Wall -Wextra -O2 $(TARGET)/main.o -L$(RAYLIB)/lib -lraylib -Wl,-rpath=$(RAYLIB)/lib -o $(TARGET)/lidget

$(TARGET)/main.o: main.c | $(TARGET)
	gcc -Wall -Wextra -O2 -I$(RAYLIB)/include -c main.c -o $(TARGET)/main.o

$(TARGET):
	mkdir -p $(TARGET)

clean:
	rm -rf $(TARGET)

run:
	$(TARGET)/lidget $(ARGS)
