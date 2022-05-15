#pragma once
#include"GameState.h"
#include"GUI.h"
#include"EditorState.h"
#include"SettingState.h"


class GUI;
class GameState;
class EditorState;
class SettingState;

class MainMenuState :public State
{
private:
	//Variables
	sf::RectangleShape Background;
	sf::Texture TexBackGround;
	sf::Font FM;
	
	
	//GUI
	std::map<std::string, GUIMK47::Button*> buttons;

	//Functions
	void initFonts();
	void initkeybinds();
	void initBackground();
	void initButtons();
public:
	//Constructors
	MainMenuState(StateData* Statedate);
	virtual ~MainMenuState();

	//Funcions
	void Update(const float& dt);
	void UpdateInput(const float& dt);
	void UpdateButton();
	void render(sf::RenderTarget* target);
};