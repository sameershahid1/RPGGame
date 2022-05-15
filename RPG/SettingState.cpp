#include"stdafx.h"
#include "SettingState.h"


//InitFunctions
void SettingState::initFonts()
{
	if (!(this->FM.loadFromFile("Font/FF.ttf")))
	{
		throw("\nERROR: Font is not able to load\n");
	}
}

void SettingState::initkeybinds()
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

void SettingState::initBackground()
{
	if (!this->TexBackGround.loadFromFile("Resources/Background/bg1.png"))
	{
		throw("ERROR:Background image is not able to laod");
	}
	this->Background.setTexture(&TexBackGround);
	this->Background.setSize(sf::Vector2f(static_cast<float>(this->Window->getSize().x), static_cast<float>(this->Window->getSize().y)));
}

void SettingState::initGUI()
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->buttons["BACK"] = new GUIMK47::Button(540, 900, 150, 50, "Back", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
	this->buttons["APPLY"] = new GUIMK47::Button(740, 900, 150, 50, "Apply", 30, &this->FM, sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 200));
	
	choice.push_back("YES");
	choice.push_back("NO");


	std::vector<std::string> modes_str;
	for (auto& it : this->modes)
	{
		modes_str.push_back(std::to_string(it.width)+'x'+std::to_string(it.height));
	}
	int Msize = static_cast<int>(modes_str.size()), Ssize = static_cast<int>(choice.size());

	this->dropdownL["RESOLUTION"] = new GUIMK47::DropDownList(750,500,200,50,this->FM,modes_str,Msize,0);
	this->dropdownL["VSYNC"] = new GUIMK47::DropDownList(750,600,200,50,this->FM,choice, Ssize,1);
	this->dropdownL["ANTIALIASING"] = new GUIMK47::DropDownList(750,700,200,50,this->FM,choice, Ssize,1);
}

void SettingState::initTextOption()
{
	this->Toption.setFont(this->FM);
	this->Toption.setCharacterSize(40);
	this->Toption.setPosition(540.f,500.f);
	this->Toption.setFillColor(sf::Color(255,255,255,200));
	this->Toption.setString("Resolution\n\nVsync\n\nAntialiasing\n\n");
}


//Constructor/Distructor
SettingState::SettingState(StateData* Statedate):State(Statedate)
{
	this->initkeybinds();
	this->initFonts();
	this->initBackground();
	this->initGUI();
	this->initTextOption();
}

SettingState::~SettingState()
{
	for(auto& it : this->buttons)
	{
		delete it.second;
	}
   
	for (auto& it:this->dropdownL) 
	{
		delete it.second;
	}

}
  
void SettingState::Update(const float& dt)
{
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateGUI(dt);
	this->UpdatekeyTime(dt);
}


void SettingState::UpdateInput(const float& dt)
{

}

void SettingState::UpdateGUI(const float &dt)
{
	//Update All GUI Buttons
	for (auto& it : this->buttons)
	{
		it.second->Update(mouseposWindow);
	}

	//Buttons Functionality
	if (this->buttons["BACK"]->isPressed() && this->getKeyTime())
	{
		this->Quit = true;
	}


	if (this->buttons["APPLY"]->isPressed() && this->getKeyTime())
	{
		this->Statedata->Graphics->Resolution= this->modes[this->dropdownL["RESOLUTION"]->getActiceID()];
		
		if (this->choice[this->dropdownL["VSYNC"]->getActiceID()]=="YES")
		{
			this->Statedata->Graphics->VerticalSync = 1;
		}
		else
		{
			this->Statedata->Graphics->VerticalSync = 0;
		}

		if (this->choice[this->dropdownL["ANTIALIASING"]->getActiceID()] == "YES")
		{
			this->Statedata->Graphics->contextSettings.antialiasingLevel= 1;
		}
		else
		{
			this->Statedata->Graphics->contextSettings.antialiasingLevel =0;
		}
		this->Window->create(this->Statedata->Graphics->Resolution, this->Statedata->Graphics->Title, sf::Style::Titlebar | sf::Style::Close , this->Statedata->Graphics->contextSettings);
		this->Window->setVerticalSyncEnabled(this->Statedata->Graphics->VerticalSync);
		this->Statedata->Graphics->SaveToFile("config/Graphics.ini");
	}

    
	//DropDown lists
	for (auto& it : this->dropdownL)
	{
		it.second->Update(this->mouseposWindow, dt);
	}


	//DropDown List Funt
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;
	this->Window->draw(this->Background);
	
	target->draw(this->Toption);
	
	for (auto& it:this->buttons)
	{
		it.second->render(*target);
	}

	for (auto& it : this->dropdownL)
	{
		it.second->render(*target);
	}

}
