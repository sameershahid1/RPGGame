#include"stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridsize, int widht, int height, std::string TextureName)
{

	this->TexturName = TextureName;
	this->gridsizeF = gridsize;
	this->maxsizeF.x = static_cast<float>(widht) * this->gridsizeF;
	this->maxsizeF.y = static_cast<float>(height) * this->gridsizeF;
	this->gridsizeI = static_cast<int>(this->gridsizeF);
	this->maxsize.x = widht;
	this->maxsize.y = height;
	this->layers = 1;

	
	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	this->layer = 0;

	
	this->map.resize(this->maxsize.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->maxsize.x; x++)
	{
		for (int y = 0; y < this->maxsize.y; y++)
		{
			this->map[x].resize(this->maxsize.y, std::vector<std::vector<Tile*>>());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	
	if (!this->TileSheet.loadFromFile(this->TexturName))
	{
		std::cout << "ERROR:TILE MAP: TEXTURE IS NOT ABLE TO LOAD SUCCESSFULLY" << this->TexturName << std::endl;
	}


	this->CollisionBox.setSize(sf::Vector2f(this->gridsizeF, this->gridsizeF));
	this->CollisionBox.setFillColor(sf::Color(255, 0, 0, 50));
}

TileMap::~TileMap()
{
	this->clear();
}


//Accessor
sf::Texture* TileMap::getTileSheet()
{
	return &this->TileSheet;
}

const int TileMap::getLayerSize(int x, int y, int z)
{
	int count = 0;
	if (x>=0&&x<this->map.size())
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (z >= 0 && z< this->map[x][y].size())
			{
				return static_cast<const int>(this->map[x][y][z].size());
			}
		}
	}	
	return -1;
}

//Mutators


//Functions
void TileMap::AddTile(const int x, const int y, const int z, const sf::IntRect& TextureRect, const bool COL, const short Type)//Adding Tile 
{
	if ((x < this->maxsize.x && x >= 0) && (y < this->maxsize.y && y >= 0) && (z < this->layers && z >= 0))//checking the boundaries of the grid
	{
		this->map[x][y][z].push_back(new Tile(x, y, this->gridsizeF, this->TileSheet, TextureRect, COL, Type));
	}
}

void TileMap::RemoveTile(const int x, const int y, const int z)//Removing the Tile
{

	if ((x < this->maxsize.x && x >= 0) && (y < this->maxsize.y && y >= 0) && (z < this->layers && z >= 0))//checking the boundaries of the grid
	{
		if (!this->map[x][y][z].empty())//It will only adds when the Tile is empty/or equal to nullptr
		{
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
		}
	}

}

void TileMap::SaveToFile(std::string path)
{
	/*
		Saving the Entire the Tile map in the File
		1. Grid Size
		2. size x,y
		3. Basic
		4. Grid Positions
		5. Texture Rect
		6. Layers
		7. Texture File
	*/

	std::ofstream write;
	write.open(path);
	if (write.is_open())
	{
		write << this->maxsize.x << " " << this->maxsize.y << std::endl;
		write << this->gridsizeF << std::endl;
		write << this->layers << std::endl;
		write << this->TexturName << std::endl;
		for (int x = 0; x < this->maxsize.x; x++)
		{
			for (int y = 0; y < this->maxsize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (int k = 0; k < this->map[x][y][z].size(); k++)
						{
							write << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getTileDetals() << " ";//Needs to change it
						}
					}
				}
			}
		}

	}
	else
	{
		throw("\nERROW:TILE-MAP: COULD NOT ABLE TO STORE THE TILES ON THE FILES\n");
	}
	write.close();
}


void TileMap::LoadToFile(std::string path)
{
	std::ifstream read;
	read.open(path);
	if (read.is_open())
	{
		sf::Vector2f size = {};
		int gridsizeI = {}, layer = {}, x = {}, y = {}, z = {};
		short type = {};
		std::string TN = {};
		sf::IntRect react = {};
		bool col = {};


		//Basic information
		read >> size.x >> size.y;
		read >> gridsizeI;
		read >> layer;
		read >> TN;

		this->TexturName = TN;
		this->gridsizeF = static_cast<float>(gridsizeI);
		this->gridsizeI = gridsizeI;
		this->maxsize.x = static_cast<unsigned>(size.x);
		this->maxsize.y = static_cast<unsigned>(size.y);
		this->layers = layer;
		this->clear();

		this->map.resize(this->maxsize.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < this->maxsize.x; x++)
		{
			for (int y = 0; y < this->maxsize.y; y++)
			{
				this->map[x].resize(this->maxsize.y, std::vector<std::vector<Tile*>>());
				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->TileSheet.loadFromFile(this->TexturName))
		{
			std::cout << "ERROR:TILE MAP: TEXTURE IS NOT ABLE TO LOAD SUCCESSFULLY" << this->TexturName << std::endl;
		}


		//Load all tiles from the files
		this->TileSheet.loadFromFile(TN);
		while (!read.eof())
		{
			read >> x >> y >> z >> react.left >> react.top >> col >> type;

			this->map[x][y][z].push_back(new Tile(x, y, this->gridsizeF, this->TileSheet, sf::IntRect(react.left, react.top, this->gridsizeI, this->gridsizeI), col, type));
		}

	}
	else
	{
		throw("\nERROW:TILE-MAP: COULD NOT ABLE TO LOAD FROM TILES ON THE FILES\n");
	}
	read.close();

}

void TileMap::clear()
{
	for (int x = 0; x < this->maxsize.x; x++)
	{
		for (int y = 0; y < this->maxsize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (int k = 0; k < this->map[x][y][z].size(); k++)
				{
					if (map[x][y][z][k] != nullptr)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = nullptr;
					}
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

void TileMap::Update()
{

}

//Updating the Collision
void TileMap::UpdateCollision(Entity* EN, const float& dt)
{

	//World Bounds
	if (EN->getPosition().x < 0.f)
	{
		EN->setPostition(0.f, EN->getPosition().y);
		EN->StopVelocityX();
	}
	else if (EN->getPosition().x + EN->getGlobelbounds().width > this->maxsizeF.x)
	{
		EN->setPostition(this->maxsizeF.x - EN->getGlobelbounds().width, EN->getPosition().y);
		EN->StopVelocityX();
	}
	else if (EN->getPosition().y < 0.f)
	{
		EN->setPostition(EN->getPosition().x, 0.f);
		EN->StopVelocityY();
	}
	else if (EN->getPosition().y + EN->getGlobelbounds().height > this->maxsizeF.y)
	{
		EN->setPostition(EN->getPosition().x, this->maxsizeF.y - EN->getGlobelbounds().height);
		EN->StopVelocityY();
	}



	//Tiles
	this->layer = 0;
	this->fromX = EN->getGridPosition(this->gridsizeI).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxsize.x)
	{
		this->fromX = this->maxsize.x;
	}


	this->toX = EN->getGridPosition(this->gridsizeI).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxsize.x)
	{
		this->toX = this->maxsize.x;
	}

	this->fromY = EN->getGridPosition(this->gridsizeI).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxsize.y)
	{
		this->fromY = this->maxsize.y;
	}

	this->toY = EN->getGridPosition(this->gridsizeI).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxsize.y)
	{
		this->toY = this->maxsize.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect Playerbounds = EN->getGlobelbounds();
				sf::FloatRect Wallbounds = this->map[x][y][this->layer][k]->getGlobelbounds();
				sf::FloatRect NextPosBounds = EN->getNextGlobelbounds(dt);
				if (this->map[x][y][this->layer][k]->getCollision() && this->map[x][y][this->layer][k]->intersects(NextPosBounds))
				{

					//Bottom collision
					if (Playerbounds.top < Wallbounds.top && Playerbounds.top + Playerbounds.height < Wallbounds.top + Wallbounds.height && Playerbounds.left< Wallbounds.left + Wallbounds.width && Playerbounds.left + Playerbounds.width>Wallbounds.left)
					{
						EN->StopVelocityY();
						EN->setPostition(Playerbounds.left, Wallbounds.top - Playerbounds.height);

					}//Top Collision
					else if (Playerbounds.top > Wallbounds.top && Playerbounds.top + Playerbounds.height > Wallbounds.top + Wallbounds.height && Playerbounds.left< Wallbounds.left + Wallbounds.width && Playerbounds.left + Playerbounds.width>Wallbounds.left)
					{
						EN->StopVelocityY();
						EN->setPostition(Playerbounds.left, Wallbounds.top + Wallbounds.height);
					}

					//Right Collion
					if (Playerbounds.left < Wallbounds.left && Playerbounds.left + Playerbounds.width < Wallbounds.left + Wallbounds.width && Playerbounds.top<Wallbounds.top + Wallbounds.height && Playerbounds.top + Playerbounds.height>Wallbounds.top)
					{
						EN->StopVelocityX();
						EN->setPostition(Wallbounds.left - Playerbounds.width, Playerbounds.top);
					}//Left Collion
					else if (Playerbounds.left > Wallbounds.left && Playerbounds.left + Playerbounds.width > Wallbounds.left + Wallbounds.width && Playerbounds.top<Wallbounds.top + Wallbounds.height && Playerbounds.top + Playerbounds.height>Wallbounds.top)
					{
						EN->StopVelocityX();
						EN->setPostition(Wallbounds.left + Wallbounds.width, Playerbounds.top);
					}

				}
			}

		}
	}
}


void TileMap::render(sf::RenderTarget& Target, const sf::Vector2i& gridPosition,const bool Active)
{
	this->layer = 0;
	this->fromX=gridPosition.x-4;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxsize.x)
	{
		this->fromX = this->maxsize.x;
	}


	this->toX = gridPosition.x + 5;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxsize.x)
	{
		this->toX = this->maxsize.x;
	}


	this->fromY=gridPosition.y-3;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY>this->maxsize.y)
	{
		this->fromY = this->maxsize.y;
	}


	this->toY = gridPosition.y + 5;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxsize.y)
	{
		this->toY = this->maxsize.y;
	}
    

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if ((this->map[x][y][this->layer][k]->getType() == TileType::DOODAD)&&Active)
				{
					this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					this->map[x][y][this->layer][k]->render(Target);
				}
				if (this->map[x][y][this->layer][k]->getCollision())
				{
					this->CollisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
					Target.draw(this->CollisionBox);
				}
			}
		}
	}
}



void TileMap::renderDeffer(sf::RenderTarget& Target)
{
	while (!this->defferedRenderStack.empty())
	{
		this->defferedRenderStack.top()->render(Target);
		this->defferedRenderStack.pop();
	}
}