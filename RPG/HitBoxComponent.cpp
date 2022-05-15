#include"stdafx.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float widht, float height) :sprite{ sprite }, offsetX{ offsetX }, offsetY{ offsetY }
{
	//Next Positions
	this->NextPosition.left = 0.f;
	this->NextPosition.top = 0.f;
	this->NextPosition.width = widht;
	this->NextPosition.height = height;
	
	//HitBox
	this->hitbox.setPosition(this->sprite.getPosition().x+offsetX, this->sprite.getPosition().y+offsetY);
	this->hitbox.setSize(sf::Vector2f(widht,height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitBoxComponent::~HitBoxComponent() {}

//Accessor/Getters
const sf::Vector2f& HitBoxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitBoxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitBoxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	this->NextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->NextPosition.top= this->hitbox.getPosition().y+ velocity.y;
	
	return this->NextPosition;
}


//Modifiers/Setters
void HitBoxComponent::setPosition(const sf::Vector2f& pos)
{
	this->hitbox.setPosition(pos);
	this->sprite.setPosition(pos.x-offsetX, pos.y-offsetY);
}

void HitBoxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x,y);
	this->sprite.setPosition(x-offsetX,y-offsetY);
}

bool HitBoxComponent::Intereact(const sf::FloatRect Frect)
{
	return  this->hitbox.getLocalBounds().intersects(Frect);
}

void HitBoxComponent::Update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
}

void HitBoxComponent::render(sf::RenderTarget& Target)
{
	Target.draw(this->hitbox);
}
