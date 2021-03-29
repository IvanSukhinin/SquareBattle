#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Entity {
protected:
	float dx, dy, x, y, speed;
	int health, w, h;
	bool life, isMove, onGround;
	String name;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Entity(Image &image, float _x, float _y, int _w, int _h);
	virtual ~Entity() {};
	virtual FloatRect getRect();
	virtual void die();
	virtual bool checkLife();
	virtual Sprite getSprite();
	virtual float getX();
	virtual float getY();
	virtual void checkCollisionWithMap(String** tileMap, float _dx, float _dy) = 0;
	virtual void update(String** tileMap, float time) = 0;
};

#endif