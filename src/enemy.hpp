#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include <vector>

using namespace sf;

class Enemy : public Entity {
private:
	double fRand(double fMin, double fMax);
public:
	Enemy(Image &image, float _x, float _y, int _w, int _h);
	void update(String** tileMap, float time) override;
	void checkCollisionWithMap(String** tileMap, float Dx, float Dy) override;
};


#endif