#pragma once
#include"GUI.h"

class GUI;

class PauseMenu
{
private:
	//Variable
	sf::RectangleShape background;
	sf::RectangleShape containers;
	std::map<std::string, GUIMK47::Button*> buttons;
    
	sf::Font& F;
	sf::Text menuText;

    
	//Private Functions



public:
	PauseMenu(sf::RenderWindow& Target,sf::Font& F);
	~PauseMenu();


	//Accessors
	std::map<std::string, GUIMK47::Button*>& getbuttons();


    //Functions
	const bool isbuttonPressed(std::string key);
	void AddButtons(const std::string key,float y,const std::string Text);
	void Update(sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

