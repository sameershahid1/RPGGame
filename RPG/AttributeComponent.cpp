#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level+1, 3) - 6 * (pow(this->level+1, 2) + ((this->level+1) * 17 - 12))));
	this->Attributepoints =5;

	this->Vitality = 1;
	this->strength = 1;
	this->Dexterity = 1;
	this->agility = 1;
	this->Intelligence = 1;
	this->UpdateLevelUp();
	this->UpdateStats(true);}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::UpdateStats(const bool reset)
{
	this->HPMax = this->Vitality *4 + this->Vitality + this->strength +this->Intelligence/5;
	this->damageMax = this->strength * 3 + this->strength / 4 + this->Intelligence/5;
	this->damageMin = this->strength * 2 + this->strength / 5 + this->Intelligence/5;
	this->accuracy = this->Dexterity * 3 + this->Dexterity /2 + this->Intelligence/5;
	this->defence = this->agility * 3 + this->agility/4+ this->Intelligence/5;
	this->luck = this->Intelligence * 2 + this->Intelligence/5;
	
	if (reset)
	{
		this->HP = HPMax;
	}
}

void AttributeComponent::gainExp(const unsigned exp)
{
	this->exp += exp;

	this->UpdateLevelUp();
}



void AttributeComponent::UpdateLevelUp()
{
	while(this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext =static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * (pow(this->level, 2) + (this->level * 17 - 12))));
		++this->Attributepoints;
	}
}

void AttributeComponent::Update()
{
	this->UpdateLevelUp();
}
