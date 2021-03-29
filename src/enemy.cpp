#include <SFML/Graphics.hpp>
#include "enemy.hpp"
#include <vector>

using namespace sf;

Enemy::Enemy(Image &image, float _x, float _y, int _w, int _h) : Entity(image, _x, _y, _w, _h){
	dx = fRand(0.15, 0.4);
}

void Enemy::update(String** tileMap, float time) 
{
	x += dx * time; 
	checkCollisionWithMap(tileMap, dx, 0);
	sprite.setPosition(x + w / 2, y + h / 2);

	if (health <= 0) {
		life = false;
	}
}

void Enemy::checkCollisionWithMap(String** tileMap, float Dx, float Dy)
{
	// Коллизии с картой
	for (int i = y / 32; i < (y + h) / 32; i++) {
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (tileMap[i][j] == '0') {
				if (Dy > 0){y = i * 32 - h;}
				if (Dy < 0){y = i * 32 + 32;}
				if (Dx > 0){x = j * 32 - w; dx *= -1;}
				if (Dx < 0){x = j * 32 + 32; dx *= -1;}
			}
		}
	}
}

double Enemy::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
