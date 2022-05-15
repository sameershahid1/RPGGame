#pragma
#include "State.h"
#include"GUI.h"

class GUI;
class State;

class SettingState :public State
{
private:
	//Variables

	sf::RectangleShape Background;
	sf::Texture TexBackGround;
	sf::Font FM;
	sf::Text Toption;
	std::vector<sf::VideoMode> modes;
	std::vector<std::string> choice;

	//GUI
	std::map<std::string, GUIMK47::Button*> buttons;
	std::map<std::string, GUIMK47::DropDownList*> dropdownL;

	//InitFunctions
	void initFonts();
	void initkeybinds();
	void initBackground();
	void initGUI();
	void initTextOption();
   
public:
	//Constrctors/Distructor
	SettingState(StateData* Statedate);
	~SettingState();


	//Accessors



	//Funcitons

	void Update(const float& dt);
	void UpdateInput(const float& dt);
	void UpdateGUI(const float& dt);
	void render(sf::RenderTarget* target);
};
