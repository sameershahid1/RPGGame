#include"stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->Type = 0;
}

Tile::Tile(int x, int y,float gridsize,const sf::Texture &Tex,const sf::IntRect &Texturerect,bool collision,short type)
{
	this->collision = collision;
	this->Type = type;
	this->shape.setSize(sf::Vector2f(gridsize,gridsize));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(x)*gridsize, static_cast<float>(y)*static_cast<unsigned>(gridsize));
	this->shape.setTexture(&Tex);
	this->shape.setTextureRect(Texturerect);
}

Tile::~Tile()
{

}

//Accessors
const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobelbounds() const
{
 	return this->shape.getGlobalBounds();
}

const int Tile::getType() const
{
	return this->Type;
}


//Functions
const std::string Tile::getTileDetals()const
{
	std::stringstream king;
	king << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->Type<<" ";
	return king.str();
}

void Tile::Update()
{

}

void Tile::render(sf::RenderTarget& Target)
{
	Target.draw(this->shape);
}
