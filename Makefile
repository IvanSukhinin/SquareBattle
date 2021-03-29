.PHONY: all clean install uninstall

CC := g++
CFLAGS := -Wall -Werror
GAME := ./bin/game
BUILD_DIR := ./build
INSTALL_PATH := /usr/local/bin

all: $(GAME)

$(GAME): $(BUILD_DIR)/main.o $(BUILD_DIR)/map.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/player.o $(BUILD_DIR)/enemy.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/map.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/player.o -o $(GAME) $(BUILD_DIR)/enemy.o -lsfml-graphics -lsfml-window -lsfml-system

$(BUILD_DIR)/main.o: src/main.cpp src/map.cpp src/map.hpp src/entity.cpp src/entity.hpp src/player.cpp src/player.hpp src/enemy.cpp src/enemy.hpp
	$(CC) $(CFLAGS) -c src/main.cpp -o $(BUILD_DIR)/main.o 

$(BUILD_DIR)/map.o: src/main.cpp src/map.cpp src/map.hpp 
	$(CC) $(CFLAGS) -c src/map.cpp -o $(BUILD_DIR)/map.o

$(BUILD_DIR)/entity.o: src/entity.cpp src/entity.hpp
	$(CC) $(CFLAGS) -c src/entity.cpp -o $(BUILD_DIR)/entity.o 

$(BUILD_DIR)/player.o: src/main.cpp src/map.cpp src/map.hpp src/entity.cpp src/entity.hpp src/player.cpp src/player.hpp
	$(CC) $(CFLAGS) -c src/player.cpp -o $(BUILD_DIR)/player.o 

$(BUILD_DIR)/enemy.o: src/main.cpp src/map.cpp src/map.hpp src/entity.cpp src/entity.hpp src/enemy.cpp src/enemy.hpp
	$(CC) $(CFLAGS) -c src/enemy.cpp -o $(BUILD_DIR)/enemy.o 

clean:
	rm -rf $(BUILD_DIR)/*.o $(GAME)

install: 
	install bin/game $(INSTALL_PATH)

uninstall:
	rm -rf $(INSTALL_PATH)/game
