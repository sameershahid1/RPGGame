#include"stdafx.h"
#include"MainMenuState.h"


void MainMenuState::initFonts()
{
	if (!(this->FM.loadFromFile("Font/FF.ttf")))
	{
		throw("\nERROR: Font is not able to load\n");
	}
}

void MainMenuState::initkeybinds()
{
	std::ifstream ReadConT;
	ReadConT.open("config/MainMenuStateKeyBinds.ini");
	while (!ReadConT.eof())
	{
		std::string keyName = {}, keyName1 = {};
		ReadConT >> keyName >> keyName1;
		this->keybinds[keyName] = this->supportedKeys[0][keyName1];
	}
	ReadConT.close();
}

void MainMenuState::initBackground()
{
	if (!this->TexBackGround.loadFromFile("Resources/Background/bg1.png"))
	{
		throw("ERROR:Background image is not able to laod");
	}	
	this->Background.setTexture(&TexBackGround);
	this->Background.setSize(sf::Vector2f(static_cast<float >(this->Window->getSize().x),static_cast<float>( this->Window->getSize().y)));
}

void MainMenuState::initButtons()
{
	this->buttons["NewGameState"] = new GUIMK47::Button(540, 500, 150, 50, "New Game", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
	this->buttons["SettingState"] = new GUIMK47::Button(540, 600, 150, 50, "Settings", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
	this->buttons["EditorState"] = new GUIMK47::Button(540, 700, 150, 50, "Editor", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
	this->buttons["QuitFromState"] = new GUIMK47::Button(540, 800, 150, 50, "Quit", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
 }


MainMenuState::MainMenuState(StateData *Statedata) :State(Statedata)
{ 	
	this->initkeybinds(); 
	this->initFonts();
	this->initBackground();
	this->initButtons();
}


MainMenuState::~MainMenuState() 
{
	for(auto &it: this->buttons)
	{
		delete it.second;
	}
}


void MainMenuState::Update(const float& dt)
{
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButton();
	this->UpdatekeyTime(dt);
}


void MainMenuState::UpdateInput(const float& dt)
{
   
}

void MainMenuState::UpdateButton()
{
	for (auto &it : this->buttons)
	{ 
		it.second->Update(this->mouseposWindow);
	}


	if(this->buttons["NewGameState"]->isPressed()&&this->getKeyTime())
	{
		this->states->push(new GameState(this->Statedata));
	}
	else if (this->buttons["SettingState"]->isPressed() && this->getKeyTime())
	{
		this->states->push(new SettingState(this->Statedata));
	}
	else if (this->buttons["EditorState"]->isPressed() && this->getKeyTime())
	{
		this->states->push(new EditorState(this->Statedata));
	}
	else if (this->buttons["QuitFromState"]->isPressed()&&this->getKeyTime())
	{
		this->Quit = true;
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;
	this->Window->draw(this->Background);
	for(auto &it:this->buttons)
	{
		it.second->render(*target);
	}
}