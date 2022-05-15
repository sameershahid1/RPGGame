#include"stdafx.h"
#include "Player.h"

AttributeComponent* Player::getAttributes()
{
	return this->Attri;
}

void Player::initVariables()
{
	this->Attacking = false;
}

void Player::initCompoent()
{
 
}

Player::Player(float x,float y,sf::Texture &TexSheet)
{
	//InitFunctions
	this->initVariables();
	this->initCompoent();
	this->setPostition(x,y);
	
	//Creation Funcitons
	this->createHitBox(this->sprite, 86,64,86,116);
	this->createMovement(350.f, 1500.f, 500.f);
	this->createAnimnation(TexSheet);
	this->createAttribute(1);

	//Putting the Animaition of the character
	this->Animation->AddAnimation("IDLE",11.f,0,0,13,0,192,192);
	this->Animation->AddAnimation("WALK",6.f, 0, 1,11,1,192, 192);
	this->Animation->AddAnimation("ATTACK",5.f,0,2,13,2,192*2,192);
}


Player::~Player()
{

}


//Functions

void Player::UpdateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
	{
		this->Attacking = true;
	}
}

void Player::UpdateAnimations(const float& dt)
{
	if (this->Attacking)
	{	
	
		if (this->sprite.getScale().x > 0)
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		else if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(354.f, 0.f);
		}


		//Animate and check animation end of Attack
		if (this->Animation->Play("ATTACK", dt, true))
		{
			this->Attacking = false;
			if (this->sprite.getScale().x > 0)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}

	if (!this->Attacking)
	{
		this->MOVE->Update(dt);
		if (this->MOVE->getState(IDLE))
		{
			this->Animation->Play("IDLE", dt, false);

		}
		else if (this->MOVE->getState(Move_Left))
		{
			this->Attacking = false;
			if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(0, 0.f);
				this->sprite.setScale(1.f, 1.f);
			}
			this->Animation->Play("WALK", dt, this->MOVE->getVelocity().x, this->MOVE->getMaxVelocity(), false);
		}
		else if (this->MOVE->getState(Move_Right))
		{
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(258.f, 0.f);
				this->sprite.setScale(-1.f, 1.f);
			}
			this->Animation->Play("WALK", dt, this->MOVE->getVelocity().x, this->MOVE->getMaxVelocity(), false);
		}
		else if (this->MOVE->getState(Move_Up) && !this->Attacking)
		{
			this->Animation->Play("WALK", dt, this->MOVE->getVelocity().y, this->MOVE->getMaxVelocity(), false);
		}
		else if (this->MOVE->getState(Move_Down))
		{
			this->Animation->Play("WALK", dt, this->MOVE->getVelocity().y, this->MOVE->getMaxVelocity(), false);
		}
	}
}


void Player::Update(const float &dt)
{

	this->Attri->Update();

	this->UpdateAttack();
	
	
	this->UpdateAnimations(dt);
	


	if (this->HitBox != nullptr)
	{
		this->HitBox->Update();
	}
}

void Player::render(sf::RenderTarget& Target)
{
	Target.draw(this->sprite);
	if (this->HitBox != nullptr)
		this->HitBox->render(Target);
}