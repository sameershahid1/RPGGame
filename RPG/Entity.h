#pragma once
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"HitBoxComponent.h"
#include"AttributeComponent.h"

class HitBoxComponent;
class AnimationComponent;
class MovementComponent;
class AttributeComponent;

class Entity
{
private:
	sf::Vector2i mouseposScreen;
	sf::Vector2u mouseposWindow;
	sf::Vector2i mouseposView;
protected:
	//This will contains the Texture of the Entity
	sf::Sprite sprite;
	
	//This Component will control the handle the movement of the entity
	MovementComponent* MOVE;
	
	//This component will deals with the animation of the Entity
	AnimationComponent* Animation;
	
	//This component will deals with the Hit box of the Player
	HitBoxComponent* HitBox;

    //Attributes of the Entity
	AttributeComponent* Attri;

public:
	Entity();
	virtual ~Entity();

	//component Functions
	void setTexture(sf::Texture&T);
	void createMovement(const float maxVelocity, const float Acceleration, const float Deceleration);
	void createAnimnation(sf::Texture& TexSheet);
	void createHitBox(sf::Sprite& sprite,float offsetX, float offsetY, float widht, float height);
	void createAttribute(const unsigned level);



	//Accessor
	virtual const sf::Vector2f& getPosition()const;
	virtual const sf::FloatRect getGlobelbounds()const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI)const;
	virtual const sf::FloatRect getNextGlobelbounds(const float& dt);
	
	
	//Mutators
	virtual void setPostition(const float x, const float y);

	//Funcions
	//Reseting the velocity
	void StopVelocity();
	void StopVelocityX();
	void StopVelocityY();
	
	//Moving the Entity
	virtual void move(const float dir_x,const float dir_y, const float& dt);
	
	//Updating the Entity
	virtual void Update(const float& dt)=0;
	
	//Rendering the Entity
	virtual void render(sf::RenderTarget& Target)=0;
};