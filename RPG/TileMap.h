#pragma once
#include"Tile.h"
#include"Entity.h"


class Tile;
class Entity;

class TileMap
{
private:
	//Variables
	//Grid Size/World size
	float gridsizeF;
	int gridsizeI;
	sf::Vector2i maxsize;
	sf::Vector2f maxsizeF;

	//Tile limit for having Layers
	int layers;
	
	//Collection of Tiles
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	
	std::stack<Tile*> defferedRenderStack;

	//Texture Sheet
	sf::Texture TileSheet;
	
	//Destination of the Texture File
	std::string TexturName;
	
	//CollisionBox
	sf::RectangleShape CollisionBox;
    
	//Culling
	int fromX;
	int fromY;
	int toX;
	int toY;
	int layer;

public:
	//Constructors/Distructors
	TileMap(float gridsize,int widht, int height,std::string TextureName);
    ~TileMap();


	//Accessors
	sf::Texture* getTileSheet();
	const int getLayerSize(int x, int y, int z);


	//Modifiers



	//Functions	
	//Adding and Removing Tiles
	void AddTile(const int x, const int y, const int z, const sf::IntRect& TextureRect,const bool COL,const short Type);
	void RemoveTile(const int x, const int y, const int z);
	
	//Clearing the memory
	void clear();

    //A checker That check the collision between the player and the Tiles
	void UpdateCollision(Entity* EN, const float& dt);

	//Saving and loading the Tiles
	void SaveToFile(std::string path);
	void LoadToFile(std::string path);
	
	//Updating And Rendering the Tiles 
	void Update();
	void renderDeffer(sf::RenderTarget& Target);
	void render(sf::RenderTarget& Target,const sf::Vector2i& gridPosition,const bool Active);
};

