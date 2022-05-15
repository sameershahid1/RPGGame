#include "stdafx.h"
#include "PlayerGUI.h"


//init Funcitons
void PlayerGUI::initFont()
{
	if (!(this->FM.loadFromFile("Font/FF.ttf")))
	{
		throw("\nERROR: Font is not able to load\n");
	}
}

void PlayerGUI::initHPBAR()
{
	float width = 300.f, height = 50.f,x=20.f,y=50.f;

	this->HPBarBack.setSize(sf::Vector2f(width,height));
	this->HPBarBack.setFillColor(sf::Color(50,50,50,200));
	this->HPBarBack.setPosition(x, y);

	this->HPBarFront.setSize(sf::Vector2f(width, height));
	this->HPBarFront.setFillColor(sf::Color(250,20,20,200));
	this->HPBarFront.setPosition(this->HPBarBack.getPosition());
}

//Construtor/Distructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;
	this->initFont();
	this->initHPBAR();
}

PlayerGUI::~PlayerGUI() 
{

}

//Functions
void PlayerGUI::Update(const float& dt)
{

}

void PlayerGUI::UpdateHPBAR()
{

}

void PlayerGUI::render(sf::RenderTarget& Target)
{
	//Rendering the HPBar
	Target.draw(this->HPBarBack);
	Target.draw(this->HPBarFront);

}
