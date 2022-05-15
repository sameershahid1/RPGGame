#pragma once
#include "Entity.h"

class Entity;

class Player :public Entity
{
private:
	//Variables
	bool Attacking;
	AttributeComponent* getAttributes();

	//Attributes


	//Iniallization
	void initVariables();
	void initCompoent();
public:
	Player(float x,float y,	sf::Texture &T);
	~Player();

	//Functions
	void UpdateAttack();
	void UpdateAnimations(const float &dt);
	virtual void Update(const float& dt);
	virtual void render(sf::RenderTarget& Target);

};