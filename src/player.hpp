#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;

class Player: public Entity { 
// Игрок
private:
	enum {left, right, jump, stay} state;
	int scores;
	void control();
public:
	Player(Image &image, float _x, float _y, int _w, int _h);
	bool checkOnGround();
	void jumpAfterWin();
	void addScores();
	int getScores();
	void reborn();
	void update(String** tileMap, float time) override;
	void checkCollisionWithMap(String** tileMap, float _dx, float _dy) override;
};

#endif