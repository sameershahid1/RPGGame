#pragma 
#include"MainMenuState.h"
/*
    This is the place where our all the shapes and gui are created for the game
	We can also say that this is out Game Engine.
*/
class Game
{
private:
	//Variables
	StateData Statedata;
	GraphicsSettings Graphics;
	sf::RenderWindow *Window;
	sf::Event evt;
	float GridSize;


	//delta time
	sf::Clock dtclock;
	float dt;
	

	//States
	std::stack<State*> states;
	

	//Suppprting Keys
	std::map<std::string,int> supportedKeys;


	//Initiliazation
	void initWindow();
	void initGraphicsSetting();
	void initkeys();
	void initStates();
	void initStateData();
public:
	//Constructor/Distructor
	Game();
	~Game();

	//Funcitons
	void endApplication();

	//Update
	void UpdateEvent();
	void UpdateDT();
	void Update();
	
	//Render
	void render();
	
	//Core
	void run();

};

