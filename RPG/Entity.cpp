#include"stdafx.h"
#include "Entity.h"

//Constructor/Distructor
//Start
Entity::Entity()
{
	this->MOVE=nullptr;
	this->Animation = nullptr;
	this->HitBox = nullptr;
	this->Attri =nullptr;
}

Entity::~Entity() 
{	
	if (this->MOVE != nullptr)
	{
		delete this->MOVE;
	}	
	if (this->Animation != nullptr)
	{
		delete this->Animation;
	}
	if (this->HitBox != nullptr)
	{
		delete this->HitBox;
	}
	if (this->Attri != nullptr)
	{
		delete this->Attri;
	}

}
//End



//Functions
void Entity::setTexture(sf::Texture& T)
{
	this->sprite.setTexture(T);
}

void Entity::createMovement(const float maxVelocity,const float Acceleration,const float Deceleration)
{
	this->MOVE = new MovementComponent(this->sprite,maxVelocity,Acceleration,Deceleration);
}

void Entity::createAnimnation(sf::Texture& TexSheet)
{
	this->Animation = new AnimationComponent(this->sprite,TexSheet);
}

void Entity::createHitBox(sf::Sprite&sprite,float offsetX, float offsetY, float widht, float height)
{
	this->HitBox = new HitBoxComponent(sprite, offsetX, offsetY, widht, height);
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->HitBox!=nullptr)
	{
		return this->HitBox->getPosition();
	}
	return this->sprite.getPosition();
}

void Entity::createAttribute(const unsigned level)
{
	this->Attri = new AttributeComponent(level);
}




const sf::FloatRect Entity::getGlobelbounds()const
{
	if (this->HitBox!=nullptr)
	{
		return this->HitBox->getGlobalBounds();
	}

	return this->sprite.getGlobalBounds();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->HitBox!=nullptr)
	{
		return sf::Vector2i(static_cast<int>(this->HitBox->getPosition().x / gridSizeI), static_cast<int>(this->HitBox->getPosition().y / gridSizeI));
	}

	return sf::Vector2i(static_cast<int>(this->sprite.getGlobalBounds().width / gridSizeI), static_cast<int>(this->sprite.getGlobalBounds().height / gridSizeI));
}

const sf::FloatRect Entity::getNextGlobelbounds(const float& dt)
{
	
	if (this->MOVE!=nullptr&&this->HitBox!=nullptr)
	{
		return this->HitBox->getNextPosition(this->MOVE->getVelocity()*dt);
	}
	else
	{
		return sf::FloatRect();
	}
}



void Entity::setPostition(const float x, const float y)
{
	if (this->HitBox)
	{
		this->HitBox->setPosition(x,y);
	}
	else
	{
		this->sprite.setPosition(x, y);
	}
}
  
void Entity::StopVelocity()
{
	this->MOVE->StopVelocity();
}

void Entity::StopVelocityX()
{
	this->MOVE->StopVelocityX();
}

void Entity::StopVelocityY()
{
	this->MOVE->StopVelocityY();
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->MOVE != nullptr)
	{
		this->MOVE->move(dir_x,dir_y,dt);
	}
}

void Entity::render(sf::RenderTarget& Target)
{
	Target.draw(this->sprite);
	if(this->HitBox!=nullptr)
	this->HitBox->render(Target);
}
