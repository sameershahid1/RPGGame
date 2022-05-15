#include"stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& TexSheet) :sprite{ sprite }, TexSheet{ TexSheet }, LastAnimation{ nullptr },PriorityAnimation{nullptr} {}

AnimationComponent::~AnimationComponent()
{
	for(auto& it: this->animation)
	{
		delete it.second;
	}
}

const bool& AnimationComponent::isDone(std::string key)
{
	return this->animation[key]->getdone();
}


//Functions
void AnimationComponent::AddAnimation(const std::string Key, float AnimationTimer, int startFrameX, int startFrameY, int FrameX, int FrameY, int width, int height)
{
	this->animation[Key] =new Animation(this->sprite, this->TexSheet, AnimationTimer,startFrameX, startFrameY, FrameX, FrameY, width, height);
}

const bool& AnimationComponent::Play(const std::string key, const float& dt,const bool pripority)
{
	if (this->PriorityAnimation)
	{
		if (this->PriorityAnimation==this->animation[key])//If Priority Animation is active 
		{
			if (this->LastAnimation!=this->animation[key])
			{
				if (this->LastAnimation == nullptr)
				{
					this->LastAnimation = this->animation[key];
				}
				else
				{
					this->LastAnimation->reset();
					this->LastAnimation = this->animation[key];
				}
			}
			//If Animation is ended than it will remove it
			if (this->animation[key]->Play(dt))
			{
				this->PriorityAnimation = nullptr;
			}
		}
	}
	else//if Priority Animation not Active 
	{
		if (pripority)
		{
			this->PriorityAnimation = this->animation[key];
		}

		if (this->LastAnimation != this->animation[key])
		{
			if (this->LastAnimation == nullptr)
			{
				this->LastAnimation = this->animation[key];
			}
			else
			{
				this->LastAnimation->reset();
				this->LastAnimation = this->animation[key];
			}
		}
		this->animation[key]->Play(dt);
	}
	return this->animation[key]->getdone();
}

const bool& AnimationComponent::Play(const std::string key, const float& dt, const float& modifier, const float& maxModifier,const bool pripority)
{
	if (this->PriorityAnimation)
	{
		if (this->PriorityAnimation == this->animation[key])
		{
			if (this->LastAnimation != this->animation[key])
			{
				if (this->LastAnimation == nullptr)
				{
					this->LastAnimation = this->animation[key];
				}
				else
				{
					this->LastAnimation->reset();
					this->LastAnimation = this->animation[key];
				}
			}
			if(this->animation[key]->Play(dt,abs(modifier / maxModifier)))
			{
				this->PriorityAnimation = nullptr;
			}
		}
	}
	else//Play no Priority
	{
		if (this->LastAnimation != this->animation[key])
		{
			if (this->LastAnimation == nullptr)
			{
				this->LastAnimation = this->animation[key];
			}
			else
			{
				this->LastAnimation->reset();
				this->LastAnimation = this->animation[key];
			}
		}
		this->animation[key]->Play(dt, abs(modifier / maxModifier));
	}
	return this->animation[key]->getdone();
}
