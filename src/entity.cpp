#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;

Entity::Entity(Image &image, float _x, float _y, int _w, int _h) {
	speed = 0; health = 100; dx = 0; dy = 0;
	life = true; isMove = false; onGround = false;
	w = _w; h = _h;
	x = _x; y = _y;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

FloatRect Entity::getRect() {
	return FloatRect(x, y, w, h);
}

void Entity::die() {
	health = 0;
}

Sprite Entity::getSprite() {
	return sprite;
}

bool Entity::checkLife() {
	return life;
}

float Entity::getX() {	
	return x;
}

float Entity::getY(){
	return y;
}
