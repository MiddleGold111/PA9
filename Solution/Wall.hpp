#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include <vector>
#include <iostream>

class WallBlock : public GameObject
{
public:
	WallBlock(const sf::Texture& _texture, const sf::Vector2f & _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
		/*float height = _position.y;
		int num = 1;*/
		
		/*while (height > 0)
		{
			this->blocks[num] = new Wall(_texture, _position, size);
			this->blocks[num].setPosition({ _position.x, height + 50 });
			height += 50;
		}*/
		//was also breakingthings
		//said it didn't like the way i was treating height
		
	}
	void update() override;


private:
	


};

void WallBlock::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		//this->move({0,1});
	}

	//if player reaches a certain height, move walls down
	//platforms need to move with the walls as well
	//track player position so either need to pass in player or?


}

class Wall 
{
public:
	Wall(int newNumBlocks, const sf::Texture& newTexture, const sf::Vector2f& _windowPosition, const float sizeW) : numBlocks(newNumBlocks), textRef(newTexture), winpos(_windowPosition), size(sizeW)
	{
		numBlocks = newNumBlocks;
		sf::Vector2f pos = winpos = _windowPosition;
		sf::Texture testtext;
		if (!testtext.loadFromFile("goldblock.png")) { std::cout << "Failed to load goldblock.png" << std::endl; }
	
		 
		
		for (int i = 0; i < numBlocks; i++)
		{
			WallBlock block(testtext, { 0, pos.y }, { size,size });
			WallBlock block2(testtext, { winpos.x - size, pos.y }, { size,size });
			//wall[i].setPosition({ 0,(pos.y) - (wall[i].getSize().y) });
			wall.push_back(block);
			wall2.push_back(block2);
			pos.y -= size;
		}

		


	}

	void update(Player& p, sf::RenderWindow& theWindow);
	void draw (sf::RenderWindow& theWindow);



private:
	std::vector<WallBlock> wall;
	std::vector<WallBlock> wall2;
	int numBlocks;
	sf::Vector2f winpos;
	float size;
	const sf::Texture& textRef;
	

};

void Wall::update(Player& p, sf::RenderWindow& theWindow)
{
	if (wall[0].getPosition().y < winpos.y)
	{
		//then we have the block being too far down
		//need to remove block and add one on the top
		
		for (int i = 0; i < numBlocks-1; i++) //loop through number of blocks adjusting vector
		{
			wall[i] = wall[i + 1];
			wall2[i] = wall2[i + 1];
		}
		float newY = wall[numBlocks - 2].getPosition().y - size;
		wall[numBlocks - 1] = WallBlock(textRef, {0, newY}, {size,size});


		float newX = winpos.x - size;
		wall2[numBlocks - 1] = WallBlock(textRef, { newX, newY }, { size,size });

	}

	
	
	draw(theWindow);


}


void Wall::draw(sf::RenderWindow& theWindow) //draw because not derived from drawable class
{
	for (int i = 0; i < numBlocks; i++)
	{
		theWindow.draw(wall[i]);
		theWindow.draw(wall2[i]);
	}
}