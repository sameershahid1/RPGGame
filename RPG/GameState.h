#pragma once
#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"PlayerGUI.h"
//Telling the campiler that their objects is already created in this class
class PauseMenu;
class TileMap;
class State;
class Player;
class PlayerGUI;

/*
     The Game state is the place where the player will play it's game, the player can move the character how ever he wants to in the game.
*/

class GameState :public State
{
private:
	//Variables
	Player* player;
	PlayerGUI* PGUI;
	PauseMenu* Pmenu;
	sf::Font FM;

	//view For the Game
	sf::View view;

	//used for rendering the textures on the screen 
	sf::RenderTexture renderTextures;
	
	//The sprite that will contains the collections of tiles
	sf::Sprite renderSprite;

	//Game Maps
	TileMap* tileMap;

	//InitialFunctions
	void initView();
	void initDefferRender();
	void initkeybinds();
	void initPlayerGUI();
	void initTextures();
	void initPlayer();
	void initPauseMen();
	void initFont();
	void initTileMap();
public:
	//Consturctor/ Distructors
	GameState(StateData *Statedata);
	virtual ~GameState();

	//Funcions
    void Update(const float &dt);
	void UpdateTileMap(const float& dt);
	void UpdateView(const float& dt);
	void UpdatePlayerGUI(const float& dt);
	void UpdatePauseMenuButtons();
	void UpdateInput(const float& dt);
	virtual void PlayerInput(const float& dt);
	void render(sf::RenderTarget* target);
};