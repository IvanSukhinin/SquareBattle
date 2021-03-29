#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Player::Player(Image &image, float _x, float _y, int _w, int _h) : Entity(image, _x, _y, _w, _h){
	scores = 0;
	state = stay;
}

void Player::control(){
	// Управление персонажем
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		state = left;
		speed = .2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		state = right;
		speed = .2;
	}
 	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
		state = jump; dy = -0.6; onGround = false;
	}
}

void Player::update(String** tileMap, float time) 
{
	control();
	switch (state) {
		case right: dx = speed;break;
		case left: dx = -speed;break;
		case jump: break;
		case stay: break;
	}
	x += dx * time; 
	checkCollisionWithMap(tileMap, dx, 0);
	y += dy * time; 
	checkCollisionWithMap(tileMap, 0, dy);

	if (!isMove) { 
		speed = 0;
	}
	sprite.setPosition(x + w / 2, y + h / 2);

	if (health <= 0) {
		life = false;
	}

	dy = dy + 0.0015 * time;
}

void Player::checkCollisionWithMap(String** tileMap, float Dx, float Dy)
{
	// Коллизии с картой
	for (int i = y / 32; i < (y + h) / 32; i++) {
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (tileMap[i][j] == '0') {
				if (Dy > 0){y = i * 32 - h;  dy = 0; onGround = true;}
				if (Dy < 0){y = i * 32 + 32;  dy = 0;}
				if (Dx > 0){x = j * 32 - w;}
				if (Dx < 0){x = j * 32 + 32;}
			}
		}
	}
}

bool Player::checkOnGround() {
	return onGround;
}	

void Player::jumpAfterWin() {
	dy = -0.2;
}

void Player::reborn() {
	x = 32;
	health = 100;
	life = true;
	scores = 0;
}

void Player::addScores() {
	scores += 50;
}

int Player::getScores() {
	return scores;
}
