#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Map {
private:
	Image mapImage;
	Sprite mapSprite;
	Texture mapTexture;
	View view;
	int width;
	int height;
	String** map;
	void copyMap(String* tempMap);

public:
	Map(String filename, int width, int height);
	~Map();
	Sprite getMapSprite();
	void setPlayerCoordinateForView(float x, float y);
	View getView();
	void createMap(String* tempMap);
	void printMap(RenderWindow window);
	String** getMapPointer();
};


#endif