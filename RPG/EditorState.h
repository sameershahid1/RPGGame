#pragma once
#include"State.h"
#include"GUI.h"
#include"PauseMenu.h"
#include"TileMap.h"


class State;
class GUI;
class TileMap;
class PauseMenu;

class EditorState :public State
{
	//Variables
	sf::Font FM;
	PauseMenu* Pmenu;
	sf::Text CursorText;

	//Tile Maps
	TileMap * tileMap;
	sf::IntRect TextureIntRect;
	sf::RectangleShape SelectorRect;

    //SideBar for the Texture Selector
	sf::RectangleShape sideBar;

	//Texture Selector
	GUIMK47::TextureSelector* textureSelector;
       
	//Buttons
	std::map<std::string, GUIMK47::Button*> buttons;

	//View for moving the Camera 
	sf::View view;
	float viewSpeed;

	int layer;

	//Collision and Time of tiles
	bool collision;
	short type;

	//Functions
	void initVariables();
	void initView();
	void initFonts();
	void initkeybinds();
	void initPauseMenu();
	void initButtons();
	void initGUI();
	void initText();
	void initTileMap();
public:
	//Constructor/Distructor
	EditorState(StateData* Statedate);
	virtual ~EditorState();






	//Funcions
	//Updating
	void Update(const float& dt);
	void UpdateEditorInput(const float& dt);
	void UpdateGUI(const float &dt);
	void UpdatePauseMenuButtons();
	void UpdateInput(const float& dt);
	void UpdateButton();
	//Rendering
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target);
};

