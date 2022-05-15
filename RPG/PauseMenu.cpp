#include"stdafx.h"
#include "PauseMenu.h"

//Constructors/Distructors
PauseMenu::PauseMenu(sf::RenderWindow& Window, sf::Font& F) : F{F}
{
	//Background information
	this->background.setSize(sf::Vector2f(static_cast<float>(Window.getSize().x),static_cast<float>(Window.getSize().y)));
	this->background.setFillColor(sf::Color(20,20,20,100));
	
	//Contaiers informaiton
	this->containers.setSize(sf::Vector2f(static_cast<float>(Window.getSize().x)/3.f, static_cast<float>(Window.getSize().y)-300.f));
	this->containers.setFillColor(sf::Color(20,20,20,200));
	this->containers.setPosition(static_cast<float>(Window.getSize().x)/2.f - this->containers.getSize().x/2.f,100.f);

	//Init Text
	this->menuText.setFont(this->F);
	this->menuText.setFillColor(sf::Color(255,255,255,200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->containers.getPosition().x+this->containers.getSize().x/2.f-this->menuText.getGlobalBounds().width/2.f, this->containers.getPosition().y + 20);
}

PauseMenu::~PauseMenu()
{

	//De-alloacting the buttons object map
	for (auto& it : this->buttons)
	{
		delete it.second;
	}

}

std::map<std::string, GUIMK47::Button*>& PauseMenu::getbuttons()
{
	return this->buttons;
}


//Functions
const bool PauseMenu::isbuttonPressed(std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::AddButtons(const std::string key, float y, const std::string Text)
{
	float width = 250, heigth = 50.f;
	float x = this->containers.getPosition().x + this->containers.getSize().x / 2.f - width / 2;

	this->buttons[key] = new GUIMK47::Button(x, y, width, heigth, Text, 50, &this->F, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));

}

void PauseMenu::Update(sf::Vector2i& mousePosWindow)
{
 
	for (auto &it:this->buttons )
	{
		it.second->Update(mousePosWindow);
	}

}

void PauseMenu::render(sf::RenderTarget& Target)
{
	Target.draw(this->background);
	Target.draw(this->containers);
	for (auto& it : this->buttons)
	{
		it.second->render(Target);
	}
	Target.draw(this->menuText);
}

