#pragma once

enum TileType{DEFAULT=0,DAMAGING,DOODAD,MAXTYPE};

class Tile
{
protected:
//Variables
	sf::RectangleShape shape;
	bool collision;
	short Type;

private:
//InitFuncitons



public:
	//Constructors/Distructors
	Tile();
	Tile(int x, int y, float gridsize,const sf::Texture &Tex, const sf::IntRect& rect,bool collision=false,short type=TileType::DEFAULT);
	~Tile();


	//Accessors
	const sf::Vector2f& getPosition()const;
	const bool& getCollision()const;
	const bool intersects(const sf::FloatRect bounds)const;
	const sf::FloatRect getGlobelbounds()const;
	const int getType()const;

	//Modifiers


	//Functions
	const std::string getTileDetals()const;
	void Update();
	void render(sf::RenderTarget& Target);
};

