#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.hpp"

using namespace sf;

Map::Map(String filename, int w, int h) {
	width = w;
	height = h;
	mapImage.loadFromFile("images/" + filename);
	mapTexture.loadFromImage(mapImage);
	mapSprite.setTexture(mapTexture);
	view.reset(FloatRect(0, 0, 640, 480));
}

Map::~Map() {
    for(int i = 0; i < height; i++)
        delete[] map[i];
    delete[] map;
}

String** Map::getMapPointer() {
	return map;
}

void Map::printMap(RenderWindow window) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == ' ')  mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
			if (map[i][j] == 's')  mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
			if ((map[i][j] == '0')) mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
			mapSprite.setPosition(j * 32, i * 32);
			
			window.draw(mapSprite);
		}
	}
}

void Map::createMap(String* tempMap) {
    map = new String*[height];
    for(int i = 0; i < height; ++ i) {
        map[i] = new String[width];
    }
    copyMap(tempMap);
}

void Map::copyMap(String* tempMap) {
    for (int index_1 = 0; index_1 < height; index_1++) {
        for (int index_2 = 0; index_2 < width; index_2++) {
        	map[index_1][index_2] = tempMap[index_1][index_2];
        }
    }
}

Sprite Map::getMapSprite() {
	return mapSprite;
}

void Map::setPlayerCoordinateForView(float x, float y) { 
	// Функция для считывания координат игрока
	float tempX = x; float tempY = y;
 
	if (x < 320) tempX = 320;
	if (x > 960) tempX = 960; 
	if (y < 240) tempY = 240;
	if (y > 554) tempY = 554;
 
	view.setCenter(tempX, tempY);
}

View Map::getView() {
	return view;
}
