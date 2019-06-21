#pragma once

#include "GameStructs.h"


class Game
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	ThreadHead* currentThreadHead;
	std::vector<ThreadHead*> threadHeadList;
	std::vector<Visitable*> visitableList;		//constant list of ALL visitables
	std::vector<Visitable*> visitedList;		//list of visited rings
	std::vector<Visitable*> unvisitedList;		//depletable list of visitables
public:

	Game();
	~Game();

	void handleInput();

	void initializePuzzle();
	bool checkVisitableClicked(sf::CircleShape& circle, sf::RenderWindow& window);
	void physicsStep();
	void update(sf::Vector2i& mousePos);
	void draw(sf::RenderWindow& window);
	void run();
};

