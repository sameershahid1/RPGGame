#include"stdafx.h"
#include "Game.h"

//INI Funcitons

void Game::initWindow()
{
	if (this->Graphics.fullscreen)
	{
		this->Window = new sf::RenderWindow(this->Graphics.Resolution, this->Graphics.Title,sf::Style::Fullscreen, this->Graphics.contextSettings);
	}
	else
	{
		this->Window = new sf::RenderWindow(this->Graphics.Resolution,this->Graphics.Title, sf::Style::Titlebar | sf::Style::Close, this->Graphics.contextSettings);
	}
	this->Window->setFramerateLimit(this->Graphics.FrameLimit);
	this->Window->setVerticalSyncEnabled(this->Graphics.VerticalSync);
}

void Game::initGraphicsSetting()
{
	this->Graphics.loadFromFile("config/Graphics.ini");
}

void Game::initkeys()
{
	std::ifstream ReadConT;
	ReadConT.open("config/Controls.ini");
	while(!ReadConT.eof())
	{
		std::string keyName = {};
		int keyValue = {};
		ReadConT >> keyName >> keyValue;
		this->supportedKeys[keyName]=keyValue;
	}
	ReadConT.close();
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->Statedata));
}

void Game::initStateData()
{
	
	this->Statedata.Window=this->Window;
	this->Statedata.Graphics=&this->Graphics;
	this->Statedata.states=&this->states;
	this->Statedata.supportedKeys=&this->supportedKeys;
	this->Statedata.GridSize=GridSize;
}

//Constructior/Distructor
Game::Game()
{
	this->GridSize = 100.f;
	this->initGraphicsSetting();
	this->initWindow();
	this->initkeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	if(this->Window!=nullptr)
	{
		delete this->Window;
    }

	while(!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


//Functions
void Game::endApplication()
{
	std::cout << "Ending the Application"<<std::endl;
}

void Game::UpdateEvent()
{
	while (this->Window->pollEvent(this->evt))
	{
		if (this->evt.type == sf::Event::Closed)
		{
			this->Window->close();
		}
	}
}

void Game::UpdateDT()
{
	/*Update the dt(deltaTime) variable with the time it takes to update and render*/
	this->dt = this->dtclock.restart().asSeconds();
}

void Game::Update()
{
	this->UpdateEvent();
	if (!this->states.empty())
	{
		if (this->Window->hasFocus())
		{
			this->states.top()->Update(this->dt);
			if (this->states.top()->getQuit())
			{
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		this->endApplication();
		this->Window->close();
	}
}


void Game::render()
{
	this->Window->clear();
	if (!(this->states.empty()))
	{
		this->states.top()->render(this->Window);
	}
	this->Window->display();
}

void Game::run()
{
	while (this->Window->isOpen())
	{
		this->UpdateDT();
		this->Update();
		this->render();
	}
}

