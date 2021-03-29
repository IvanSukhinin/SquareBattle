#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <sstream>
#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"

using namespace sf;
using namespace std;

void startGame();
void mainLoop(RenderWindow &window, Map &map, int width, int height, Sprite mapSprite, String** mapP, Entity* &p, vector<Entity *> &enemies, Image &enemyImage, int enemiesCount, Font &font, Text &text, int level, Clock &clock);

int main() {

	startGame();

	return 0;
}


void startGame() {
	const int width = 40, height = 25;
	String tileMap[height][width] = {
		"0000000000000000000000000000000000000000",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0    s    s    s    s    s    s    s   0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0000000000000000000000000000000000000000",
	};


	RenderWindow window(VideoMode(900, 600), "Game");
	Map map("map.png", 40, 25);

	// Загружаем картинки 
	Image heroImage;
	heroImage.loadFromFile("images/hero.png");
	Image enemyImage;
	enemyImage.loadFromFile("images/enemy.png");

	// Объекты персонажей
	Entity* p = new Player(heroImage, 32, 729, 32, 39);
	vector<Entity*> enemies;
	int enemiesCount = 1;

	// Создаем карту
	String* mapPointer = (String *)tileMap;
	map.createMap(mapPointer);
	Sprite mapSprite = map.getMapSprite();
	String** mapP = map.getMapPointer();

	// Объект текста
	Font font;
	font.loadFromFile("styles/CyrilicOld.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold | Text::Underlined);

	int level = 1;

	Clock clock;

	mainLoop(window, map, width, height, mapSprite, mapP, p, enemies, enemyImage, enemiesCount, font, text, level, clock);
}


void mainLoop(RenderWindow &window, Map &map, int width, int height, Sprite mapSprite, String** mapP, Entity* &p, vector<Entity *> &enemies, Image &enemyImage, int enemiesCount, Font &font, Text &text, int level, Clock &clock) {
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
 
		clock.restart();
		time /= 800;
		
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();	
			}
		}
		
		map.setPlayerCoordinateForView(p->getX(), p->getY());

		// возрождение врагов
		if (enemies.empty()) {
			for (int i = 0; i < enemiesCount; i++) {
				enemies.push_back(new Enemy(enemyImage, rand() % 1000 + 32 * 3, 729, 39, 39));
			}
			enemiesCount++;
		}

		p->update(map.getMapPointer(), time);
		for (unsigned int i = 0; i < enemies.size(); i++) {
			enemies[i]->update(map.getMapPointer(), time);
		}
		
		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (enemies[i]->getRect().intersects(p->getRect())) {
				if (p->getY() <= (enemies[i]->getY() - 30)) {
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					dynamic_cast<Player *>(p)->jumpAfterWin();
					dynamic_cast<Player *>(p)->addScores();
				} else {
					p->die();
				}
			}
		}
		
		window.setView(map.getView());
		window.clear();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (mapP[i][j] == ' ') {
					mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				}
				if (mapP[i][j] == 's') {
					mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				}
				if ((mapP[i][j] == '0')) {
					mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
				}
				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}
		}

		if (enemies.empty()) {
			level++;
		}

		if (!p->checkLife()) {
			float restartTime = 0;

			ostringstream info;    
			info << "Scores: " << dynamic_cast<Player *>(p)->getScores() << "\nLevel : " << level << "\nGame over\nRestart Soon";
			text.setString(info.str());
			text.setPosition(map.getView().getCenter().x - 50, map.getView().getCenter().y - 200);
			window.draw(text);
			window.display();

			dynamic_cast<Player *>(p)->reborn();

			level = 1;
			for (unsigned int i = 0; i < enemies.size(); i++) {
				delete enemies[i];
			}
			enemiesCount = 1;
			enemies.clear();

			while (restartTime < 3) {
				time = clock.getElapsedTime().asSeconds();
				clock.restart();
				restartTime += time;
			}
		}

		// Вывод очков
		ostringstream info;    
		info << "Scores: " << dynamic_cast<Player *>(p)->getScores() << "\nLevel : " << level;		
		text.setString(info.str());
		text.setPosition(map.getView().getCenter().x - 50, map.getView().getCenter().y - 200);
		window.draw(text);

		window.draw(p->getSprite());
		for (unsigned int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]->getSprite());
		}
		
		window.display();
	}
}

