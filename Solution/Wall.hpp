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
		
		
	}
	void update() override;


private:
	


};

void WallBlock::update()
{
	//currently a set constant move, should be based on position of player
		this->move({0,0.1});
	

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

	//needed to call draw function for each block because not a derived class
	void draw (sf::RenderWindow& theWindow);



private:
	std::vector<WallBlock> wall; //left wall
	std::vector<WallBlock> wall2; //right wall
	int numBlocks; //should be based on window position
	sf::Vector2f winpos;
	float size;
	const sf::Texture& textRef;
	

};

void Wall::update(Player& p, sf::RenderWindow& theWindow)
{
	for (int i = 0; i < numBlocks - 1; i++)
	{
		wall[i].update();
		wall2[i].update();
	}

	if (wall[0].getPosition().y > winpos.y)
	{
				
		for (int i = 0; i < numBlocks-1; i++) //loop through number of blocks adjusting vector
		{
			wall[i] = wall[i + 1];
			wall2[i] = wall2[i + 1];
		}

		//set new y position for top block
		float newY = wall[numBlocks - 2].getPosition().y;// -size;
		wall[numBlocks - 1] = WallBlock(textRef, {0, newY}, {size,size});


		float newX = winpos.x - size;
		wall2[numBlocks - 1] = WallBlock(textRef, { newX, newY }, { size,size });

	}

	
	//draw all the blocks 
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