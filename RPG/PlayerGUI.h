#pragma once
#include"Player.h"

class Player;

class PlayerGUI
{
private:
	//Variables
	Player* player;

	sf::Font FM;

	//HP
	sf::RectangleShape HPBarBack;
	sf::RectangleShape HPBarFront;


	//init Funcitons
	void initFont();
	void initHPBAR();
public:
	//Construtor/Distructor
	PlayerGUI(Player* player);
	~PlayerGUI();


	//Functions
	void Update(const float& dt);
	void UpdateHPBAR();
	void render(sf::RenderTarget& Target);
};

