#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::handleInput()
{
}


void Game::initializePuzzle()
{
	Colorizer* cc0 = new Colorizer(RingColor::yellow, { 100.f,100.f });
	Colorizer* cc1 = new Colorizer(RingColor::yellow, { 200.f,200.f });
	Colorizer* cc2 = new Colorizer(RingColor::yellow, { 100.f,300.f });
	Ring* cc3 = new Ring(RingColor::yellow, { 300.f,400.f });
	Colorizer* cc4 = new Colorizer(RingColor::blue, { 500.f,300.f });
	Inverter* cc5 = new Inverter({ 600.f,200.f });
	AllInverter* cc6 = new AllInverter({ 500.f,200.f });
	Splitter* cc7 = new Splitter({ 200.f, 500.f });
	visitableList.push_back(cc0);
	visitableList.push_back(cc1);
	visitableList.push_back(cc2);
	visitableList.push_back(cc3);
	visitableList.push_back(cc4);
	visitableList.push_back(cc5);
	visitableList.push_back(cc6);
	visitableList.push_back(cc7);

	//should be the correct way to copy our vector in this case
	unvisitedList = visitableList;

	ThreadHead* th = new ThreadHead();
	threadHeadList.push_back(th);
	currentThreadHead = threadHeadList[0];
}

bool Game::checkVisitableClicked(sf::CircleShape& circle, sf::RenderWindow& window)
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
	float distance = (mousePosition.x - circle.getPosition().x) * (mousePosition.x - circle.getPosition().x) + (mousePosition.y - circle.getPosition().y) * (mousePosition.y - circle.getPosition().y);
	if (distance < circle.getRadius() * circle.getRadius())
		return true;
	return false;
}

void Game::physicsStep()
{
	//do stuff...
}

void Game::update(sf::Vector2i& mousePos)
{
	//update thread head positions	-later check for active thread heads?
	for (int i = 0; i < threadHeadList.size(); i++)
	{
		threadHeadList[i]->update(mousePos);
	}

	//...
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);

	//draw Rings
	for (int i = 0; i < visitableList.size(); i++)
	{
		visitableList[i]->draw(window);
	}
	//draw lines between Rings
	for (int j = 0; j < threadHeadList.size(); j++)
	{
		if (threadHeadList[j]->visitableStack.size() > 0)
		{
			sf::Vertex line1[] =
			{
				sf::Vertex(sf::Vector2f(0.f, 0.f)),
				sf::Vertex(sf::Vector2f(threadHeadList[j]->visitableStack[0]->circle.getPosition().x, threadHeadList[j]->visitableStack[0]->circle.getPosition().y)),
			};
			window.draw(line1, 2, sf::Lines);
			for (int i = 1; i < threadHeadList[j]->visitableStack.size(); i++)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(threadHeadList[j]->visitableStack[i - 1]->circle.getPosition().x, threadHeadList[j]->visitableStack[i - 1]->circle.getPosition().y)),
					sf::Vertex(sf::Vector2f(threadHeadList[j]->visitableStack[i]->circle.getPosition().x, threadHeadList[j]->visitableStack[i]->circle.getPosition().y)),
				};
				window.draw(line, 2, sf::Lines);
			}

			sf::Vertex line2[] =
			{
				sf::Vertex(threadHeadList[j]->visitableStack.back()->circle.getPosition()),
				sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window)),
			};
			window.draw(line2, 2, sf::Lines);

		}
	}


	//draw thread heads
	for (int i = 0; i < threadHeadList.size(); i++)
	{
		threadHeadList[i]->draw(window);
	}
	window.display();
}

void Game::run()
{
	initializePuzzle();

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	backgroundTexture.loadFromFile("images/background1.png");
	backgroundSprite.setTexture(backgroundTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//if (event.type == sf::Event::KeyPressed)
			//{
			//	if (currentThreadHead->visitableStack.size() > 0)
			//		{
			//			currentThreadHead->visitableStack.back()->unvisit(visitedList, unvisitedList, currentThreadHead);
			//			currentThreadHead->visitableStack.pop_back();
			//		}
			//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			//	{
			//		int th_count = threadHeadList.size();
			//		//get the next active thread head...
			//	}
			//}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (currentThreadHead->visitableStack.size() > 0)
				{
					printf("popped Ring!\n");
					std::vector<int> ca = currentThreadHead->visitableStack.back()->getColorArr();

						//apply invert
					if (currentThreadHead->visitableStack.back()->color_id != none)
					{
						ca = currentThreadHead->visitableStack.back()->getColorArr();
						currentThreadHead->redCount -= ca[0];
						currentThreadHead->yellowCount -= ca[1];
						currentThreadHead->blueCount -= ca[2];
					}

					currentThreadHead->visitableStack.back()->unvisit(visitedList, unvisitedList, currentThreadHead);
					currentThreadHead->visitableStack.pop_back();
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					//check every visitable to see if clicked...
					int foundIndex = -1;
					for (int i = 0; i < visitableList.size(); i++)
					{
						if (!visitableList[i]->isVisited && checkVisitableClicked(visitableList[i]->circle, window))
						{
							printf("visited!");
							foundIndex = i;
							visitableList[i]->visit(visitedList, unvisitedList, currentThreadHead, threadHeadList);
							currentThreadHead->visitableStack.push_back(visitableList[i]);

							std::vector<int> ca = visitableList[i]->getColorArr();

							//apply invert
							if (visitableList[i]->color_id != none)
							{
								if (visitableList[i]->invertCount % 2 == 1)
									ca = visitableList[i]->getColorArr();

								currentThreadHead->redCount += ca[0];
								currentThreadHead->yellowCount += ca[1];
								currentThreadHead->blueCount += ca[2];
							}
							printf("\n\n%i, %i, %i\n", currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount);
							break;
						}
					}
					if (foundIndex != -1)
					{
						//printf("do some action with %i!", foundIndex);
					}
				}
			}
		}

		// UPDATE
		physicsStep();
		update(sf::Mouse::getPosition(window));

		// DRAW
		draw(window);
	}
}