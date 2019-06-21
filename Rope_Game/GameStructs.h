#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <algorithm>

enum RingColor { white, brown, red, yellow, blue, green, purple, orange, black, none };

namespace fun
{
	static int getInverseColorId(int color_id)
	{
		switch (color_id)
		{
		case white:
			return white;
		case black:
			return black;
		case brown:
			return brown;
		case red:
			return green;
		case yellow:
			return purple;
		case blue:
			return orange;
		case green:
			return red;
		case purple:
			return yellow;
		case orange:
			return blue;
		case none:
			return none;
		}
		return none;
	}

	static std::vector<int> getColorArr(int color_id)
	{
		if (color_id == none)
			return{};
		std::vector<int> ca = { 0,0,0 };
		switch (color_id)
		{
		case white:
		case black:
			break;
		case brown:
			ca[0] = 1; ca[1] = 1; ca[2] = 1; break;
		case red:
			ca[0] = 1; break;
		case yellow:
			ca[1] = 1; break;
		case blue:
			ca[2] = 1; break;
		case green:
			ca[1] = 1; ca[2] = 1; break;
		case purple:
			ca[0] = 1; ca[2] = 1; break;
		case orange:
			ca[0] = 1; ca[1] = 1; break;
		}
		return ca;
	}

	static std::string getColorString(int color_id)
	{
		switch (color_id)
		{
		case white:
			return "white";
		case brown:
			return "brown";
		case red:
			return "red";
		case yellow:
			return "yellow";
		case blue:
			return "blue";
		case green:
			return "green";
		case purple:
			return "purple";
		case orange:
			return "orange";
		case black:
			return "black";
		case none:
			return "NONE";
		}
		return "NONE";
	}

	static std::vector<int> getInvertedColorArr(int color_id)
	{
		if (color_id == none)
			exit(1); //this is bad
			//return {};
		std::vector<int> ca = { 1,1,1 };
		switch (color_id)
		{
		case white:
		case black:
			ca[0] = 0; ca[1] = 0; ca[2] = 0; break;
			break;
		case brown:
			break;
		case red:
			ca[0] = 0; break;
		case yellow:
			ca[1] = 0; break;
		case blue:
			ca[2] = 0; break;
		case green:
			ca[1] = 0; ca[2] = 0; break;
		case purple:
			ca[0] = 0; ca[2] = 0; break;
		case orange:
			ca[0] = 0; ca[1] = 0; break;
		}
		return ca;
	}

	static int getColorId(std::vector<int> ca)
	{
		if (ca[0] > 0 && ca[1] > 0 && ca[2] > 0)
			return brown;
		else if (ca[0] == 0 && ca[1] == 0 && ca[2] == 0)
			return white;
		else if (ca[0] > 0 && ca[1] == 0 && ca[2] == 0)
			return red;
		else if (ca[0] == 0 && ca[1] > 0 && ca[2] == 0)
			return yellow;
		else if (ca[0] == 0 && ca[1] == 0 && ca[2] > 0)
			return blue;
		else if (ca[0] == 0 && ca[1] > 0 && ca[2] > 0)
			return green;
		else if (ca[0] > 0 && ca[1] == 0 && ca[2] > 0)
			return purple;
		else if (ca[0] > 0 && ca[1] > 0 && ca[2] == 0)
			return orange;
	}
}


//begin structs
struct ThreadHead;
struct Visitable;
struct Colorizer;
struct Ring;
struct Inverter;
struct AllInverter;


struct ThreadHead {
	bool isActive;
	sf::CircleShape circle;
	sf::Font font;
	sf::Text redText;
	sf::Text yellowText;
	sf::Text blueText;

	int redCount;
	int yellowCount;
	int blueCount;

	std::vector<Visitable*> visitableStack;

	ThreadHead* lth;
	ThreadHead* rth;

	//initial thread head constructor
	ThreadHead()
	{
		isActive = true;

		redCount = 0;
		yellowCount = 0;
		blueCount = 0;

		font.loadFromFile("fonts/BELLB.TTF");
		redText.setFont(font);
		yellowText.setFont(font);
		blueText.setFont(font);

		redText.setFillColor(sf::Color::Red);
		yellowText.setFillColor(sf::Color::Yellow);
		blueText.setFillColor(sf::Color::Blue);
		
		redText.setOutlineColor(sf::Color::Black);
		yellowText.setOutlineColor(sf::Color::Black);
		blueText.setOutlineColor(sf::Color::White);

		redText.setOutlineThickness(2.f);
		yellowText.setOutlineThickness(2.f);
		blueText.setOutlineThickness(2.f);

		redText.setString("RED");
		yellowText.setString("YELLOW");
		blueText.setString("BLUE");

		lth = nullptr;
		rth = nullptr;
	}
	ThreadHead(int r, int y, int b, sf::Vector2f position)
	{
		isActive = false;

		redCount = r;
		yellowCount = y;
		blueCount = b;

		font.loadFromFile("fonts/BELLB.TTF");
		redText.setFont(font);
		yellowText.setFont(font);
		blueText.setFont(font);

		redText.setFillColor(sf::Color::Red);
		yellowText.setFillColor(sf::Color::Yellow);
		blueText.setFillColor(sf::Color::Blue);
		
		redText.setOutlineColor(sf::Color::Black);
		yellowText.setOutlineColor(sf::Color::Black);
		blueText.setOutlineColor(sf::Color::White);

		redText.setOutlineThickness(2.f);
		yellowText.setOutlineThickness(2.f);
		blueText.setOutlineThickness(2.f);

		redText.setString("RED");
		yellowText.setString("YELLOW");
		blueText.setString("BLUE");

		lth = nullptr;
		rth = nullptr;
	}

	void update(sf::Vector2i& mousePos)
	{
		float x_offset = 10.f;
		float y_offset = 20.f;
		if (isActive)
		{
			redText.setPosition({ mousePos.x + x_offset, mousePos.y + y_offset * 0.f });
			yellowText.setPosition({ mousePos.x + x_offset, mousePos.y + y_offset * 1.f });
			blueText.setPosition({ mousePos.x + x_offset, mousePos.y + y_offset * 2.f });
		}
		redText.setString("red: " + std::to_string(redCount));
		yellowText.setString("yellow: " + std::to_string(yellowCount));
		blueText.setString("blue: " + std::to_string(blueCount));
	}

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(redText);
		window.draw(yellowText);
		window.draw(blueText);
	}
};

struct Visitable {
	bool isVisited = false;
	int invertCount = 0;			//keeps count of the amount of times this ring has been hit with an AllInverter color swap
	int color_id = none;
	sf::Sprite sprite;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	sf::Vector2f position;

	virtual void visit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead, std::vector<ThreadHead*>& th_list)
	{
		isVisited = true;
		vl.push_back(this);
		unvl.erase(std::remove(unvl.begin(), unvl.end(), this), unvl.end());
	}
	virtual void unvisit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead)
	{
		isVisited = false;
		vl.erase(std::remove(vl.begin(), vl.end(), this), vl.end());
		unvl.push_back(this);
	}	

	//child classes that don't have this function default to this definition
	virtual std::vector<int> getColorArr()
	{
		return { 0,0,0 };
	}

	virtual void invertSpriteColor() { }

	// DRAW
	virtual void draw(sf::RenderWindow& window) = 0;
};

struct Splitter : Visitable {
	//needs color and position (change pos to be grid/tile based later?)
	Splitter(sf::Vector2f position)
	{
		this->color_id = RingColor::none;
		this->position = position;
		circle.setOrigin(32, 32);
		circle.setPosition(position);
		circle.setRadius(32);

		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_splitter.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
		sprite.setOrigin(32, 32);
		sprite.setPosition(position);
	}

	void visit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead, std::vector<ThreadHead*>& th_list)
	{
		std::vector<int> in = { currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount };
		std::vector<int> ca = fun::getInvertedColorArr(fun::getColorId(in));

		ThreadHead* lth = new ThreadHead(currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount, this->circle.getPosition());
		ThreadHead* rth = new ThreadHead(currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount, this->circle.getPosition());

		lth->circle.setPosition(this->circle.getPosition().x - 200.f, this->circle.getPosition().y);
		rth->circle.setPosition(this->circle.getPosition().x + 200.f, this->circle.getPosition().y);

		currentThreadHead->isActive = false;
		rth->isActive = true;

		th_list.push_back(lth);
		th_list.push_back(rth);

		currentThreadHead->lth = lth;
		currentThreadHead->rth = rth;

		currentThreadHead = th_list.back();
		isVisited = true;

		vl.push_back(this);
		unvl.erase(std::remove(unvl.begin(), unvl.end(), this), unvl.end());
	}
	void unvisit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead)
	{
		std::vector<int> in = { currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount };
		std::vector<int> ca = fun::getInvertedColorArr(fun::getColorId(in));
		currentThreadHead->redCount = ca[0];
		currentThreadHead->yellowCount = ca[1];
		currentThreadHead->blueCount = ca[2];
		isVisited = false;

		vl.erase(std::remove(vl.begin(), vl.end(), this), vl.end());
		unvl.push_back(this);
	}

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(sprite);
	}
};


struct Colorizer : Visitable {
	//needs color and position (change pos to be grid/tile based later?)
	Colorizer(int color_id, sf::Vector2f position)
	{
		this->color_id = color_id;
		this->position = position;
		circle.setOrigin(32, 32);
		circle.setPosition(position);
		circle.setRadius(32);

		std::string color_str = fun::getColorString(color_id);
		
		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_colorizer_" + color_str + "_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
		sprite.setOrigin(32, 32);
		sprite.setPosition(position);
	}

	std::vector<int> getColorArr()
	{
		std::vector<int> ca;
		if (invertCount % 2 == 1)
			ca = fun::getInvertedColorArr(color_id);
		else
			ca = fun::getColorArr(color_id); //idk if this calls the parent one...
		return ca;
	}

	void invertSpriteColor()
	{
		std::string color_str;
		if(invertCount % 2 == 0)
			color_str = fun::getColorString(color_id);
		else
			color_str = fun::getColorString(fun::getInverseColorId(color_id));
		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_colorizer_" + color_str + "_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
	}

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(sprite);
	}
};

struct Ring : Visitable {
	//needs color and position (change pos to be grid/tile based later?)
	Ring(int color_id, sf::Vector2f position)
	{
		this->color_id = color_id;
		this->position = position;
		circle.setOrigin(32, 32);
		circle.setPosition(position);
		circle.setRadius(32);

		std::string color_str = fun::getColorString(color_id);
		
		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_ring_" + color_str + "_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
		sprite.setOrigin(32, 32);
		sprite.setPosition(position);
	}

	std::vector<int> getColorArr()
	{
		std::vector<int> ca;
		if (invertCount % 2 == 1)
			ca = fun::getInvertedColorArr(color_id);
		else
			ca = fun::getColorArr(color_id);
		ca[0] *= -1;
		ca[1] *= -1;
		ca[2] *= -1;
		return ca;
	}

	void invertSpriteColor()
	{
		std::string color_str;
		if(invertCount % 2 == 0)
			color_str = fun::getColorString(color_id);
		else
			color_str = fun::getColorString(fun::getInverseColorId(color_id));
		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_ring_" + color_str + "_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
	}

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(sprite);
	}
};

struct Inverter : Visitable {
	Inverter(sf::Vector2f position)
	{
		//this->color_id = color_id;
		this->position = position;
		circle.setOrigin(32, 32);
		circle.setPosition(position);
		circle.setRadius(32);

		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_ring_black_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
		sprite.setOrigin(32, 32);
		sprite.setPosition(position);
	}

	void visit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead, std::vector<ThreadHead*>& th_list)
	{
		std::vector<int> in = { currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount };
		std::vector<int> ca = fun::getInvertedColorArr(fun::getColorId(in));
		currentThreadHead->redCount = ca[0];
		currentThreadHead->yellowCount = ca[1];
		currentThreadHead->blueCount = ca[2];
		isVisited = true;

		vl.push_back(this);
		unvl.erase(std::remove(unvl.begin(), unvl.end(), this), unvl.end());
	}
	void unvisit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead)
	{
		std::vector<int> in = { currentThreadHead->redCount, currentThreadHead->yellowCount, currentThreadHead->blueCount };
		std::vector<int> ca = fun::getInvertedColorArr(fun::getColorId(in));
		currentThreadHead->redCount = ca[0];
		currentThreadHead->yellowCount = ca[1];
		currentThreadHead->blueCount = ca[2];
		isVisited = false;

		vl.erase(std::remove(vl.begin(), vl.end(), this), vl.end());
		unvl.push_back(this);
	}

	// UPDATE

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(sprite);
	}
};

struct AllInverter : Visitable {
	AllInverter(sf::Vector2f position)
	{
		//this->color_id = color_id;
		this->position = position;
		circle.setOrigin(32, 32);
		circle.setPosition(position);
		circle.setRadius(32);

		sf::Texture* texture = new sf::Texture();
		std::string filename = "images/spr_ring_white_0.png";
		texture->loadFromFile(filename);
		sprite.setTexture(*texture);
		sprite.setOrigin(32, 32);
		sprite.setPosition(position);
	}

	void visit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead, std::vector<ThreadHead*>& th_list)
	{
		isVisited = true;

		vl.push_back(this);
		unvl.erase(std::remove(unvl.begin(), unvl.end(), this), unvl.end());
		for (int i = 0; i < unvl.size(); i++)
		{
			unvl[i]->invertCount++;
			unvl[i]->invertSpriteColor();
		}
	}
	void unvisit(std::vector<Visitable*>& vl, std::vector<Visitable*>& unvl, ThreadHead* currentThreadHead)
	{
		isVisited = false;

		//this needs some thought
		//we must require all threads to be placed back at a certain point before undo-ing


		//for now just do it. (CHANGE WITH ADDITION OF SPLITTER!!)
		for (int i = 0; i < unvl.size(); i++)
		{
			unvl[i]->invertCount--;
			unvl[i]->invertSpriteColor();
		}

		vl.erase(std::remove(vl.begin(), vl.end(), this), vl.end());
		unvl.push_back(this);
	}

	// UPDATE

	// DRAW
	void draw(sf::RenderWindow& window)
	{
		window.draw(circle);
		window.draw(sprite);
	}
};

//end structs
