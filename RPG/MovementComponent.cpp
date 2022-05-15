#include"stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Deceleration) :sprite{ sprite }, maxVelocity{ maxVelocity }, Acceleration{ Acceleration }, Deceleration{ Deceleration }{}

MovementComponent::~MovementComponent() {}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->Velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

void MovementComponent::StopVelocity()
{
	/*Reset the velocity*/
	this->Velocity.x= 0.f;
	this->Velocity.y= 0.f;

}

void MovementComponent::StopVelocityX()
{
	this->Velocity.x = 0.f;
}

void MovementComponent::StopVelocityY()
{
	this->Velocity.y = .0f;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	if(IDLE==state)
	{
		if (this->Velocity.x == 0.f && this->Velocity.y == 0.f)
		{
			return true;
		}
	}
	else if (Moving==state)
	{
		if (this->Velocity.x != 0 || this->Velocity.y != 0)
		{
			return true;
		}
	}
	else if (Move_Left==state)
	{
		if (this->Velocity.x < 0)
		{
			return true;
		}
	}
	else if(Move_Right==state)
	{
		if (this->Velocity.x > 0)
		{
			return true;
		}
	}
	else if (Move_Up==state)
	{
		if (this->Velocity.y < 0)
		{
			return true;
		}
	}
	else if (Move_Down==state)
	{
		if (this->Velocity.y >0)
		{
			return true;
		}
	}
	return false;
}


void MovementComponent::move(const float dir_x, const float dir_y,const float& dt)
{
	//Acceleration
	this->Velocity.x+=this->Acceleration*dir_x*dt;
	this->Velocity.y += this->Acceleration * dir_y*dt;
}

void MovementComponent::Update(const float& dt)
{
	//Deceleration
	if (Velocity.x > 0.f)//For Right side of X
	{
		//Max Velocity for X
		if (this->Velocity.x > maxVelocity)
		{
			this->Velocity.x = this->maxVelocity;
		}
		
		//Deceleration of X
		this->Velocity.x -=this->Deceleration*dt;
		if(this->Velocity.x<0.f)
		this->Velocity.x =0.f;

	}
	else if(Velocity.x<.0f)//For Left side of X
	{
		//Max Velocity for X
		if (this->Velocity.x < -maxVelocity)
		{
			this->Velocity.x = -maxVelocity;
		}

		//Deceleration of X
		this->Velocity.x +=this->Deceleration*dt;
		if (this->Velocity.x > 0.f)
			this->Velocity.x = 0.f;
	}

	if (Velocity.y > 0.f)//For Right side of Y
	{
		//Max Velocity for Y
		if (this->Velocity.y > maxVelocity)
		{
			this->Velocity.y = this->maxVelocity;
		}

		//Deceleration of Y
		this->Velocity.y -= this->Deceleration*dt;
		if (this->Velocity.y < 0.f)
			this->Velocity.y = 0.f;
	}
	else if (Velocity.y < .0f)//For Left side of Y
	{
		//Max Velocity for Y
		if (this->Velocity.y < -maxVelocity)
		{
			this->Velocity.y = -maxVelocity;
		}
		//Deceleration of Y
		this->Velocity.y += this->Deceleration*dt;
		if (this->Velocity.y > 0.f)
			this->Velocity.y = 0.f;
	}

	//Final Movement
	this->sprite.move(this->Velocity*dt);
}
