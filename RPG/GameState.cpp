#include"stdafx.h"
#include "GameState.h"

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(static_cast<float>(this->Statedata->Graphics->Resolution.width),static_cast<float>(this->Statedata->Graphics->Resolution.height)));
	this->view.setCenter(this->Statedata->Graphics->Resolution.width /2.f, this->Statedata->Graphics->Resolution.height /2.f);
}

void GameState::initDefferRender()
{
	this->renderTextures.create(this->Statedata->Graphics->Resolution.width,this->Statedata->Graphics->Resolution.height);
	this->renderSprite.setTexture(this->renderTextures.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0,0,this->Statedata->Graphics->Resolution.width,this->Statedata->Graphics->Resolution.height));
}

void GameState::initkeybinds()
{
	std::ifstream ReadConT;
	ReadConT.open("config/GameStateKeyBinds.ini");
	while (!ReadConT.eof())
	{
		std::string keyName = {},keyName1 = {};
		ReadConT >> keyName >>keyName1;
		this->keybinds[keyName]=this->supportedKeys[0][keyName1];
	}
	ReadConT.close();
}

void GameState::initPlayerGUI()
{
	this->PGUI = new PlayerGUI(this->player);
}

void GameState::initTextures()
{
	if (!this->Tex["PlayerSheet"].loadFromFile("Resources/sprites/Player/PLAYER_SHEET.png"))
	{
		throw("ERROR: Game State::Player Texture is not able to load");
	}
}

void GameState::initPlayer()
{
	this->player = new Player(this->view.getCenter().x/2,this->view.getCenter().y, this->Tex["PlayerSheet"]);
}

void GameState::initPauseMen()
{
	this->Pmenu = new PauseMenu(*this->Window,this->FM);
	this->Pmenu->AddButtons("RESUME", 500.f, "RESUME");
	this->Pmenu->AddButtons("QUIT", 600.f, "Quit");
}

void GameState::initFont()
{
	if (!(this->FM.loadFromFile("Font/FF.ttf")))
	{
		throw("\nERROR: Font is not able to load\n");
	}
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->Statedata->GridSize, 20, 20,"Resources/Tiles/tilesheet1.png");
	this->tileMap->LoadToFile("Test.slmp");
}



GameState::GameState(StateData* Statedata) :State{Statedata}
{
	this->initDefferRender();
    this->initFont();
	this->initkeybinds();
	this->initTextures();
	this->initPauseMen();
	this->initPlayer();
	this->initPlayerGUI();
	this->initTileMap();
}

GameState::~GameState()
{
	if (this->player != nullptr)
	{
		delete this->player;
	}
    
	if (this->Pmenu != nullptr)
	{
		delete this->Pmenu;
	}
	if (this->tileMap != nullptr)
	{
		delete this->tileMap;
	}

	if (this->PGUI != nullptr)
	{
		delete this->PGUI;
	}

}

void GameState::Update(const float& dt)
{
	this->UpdateMousePosition(&this->view);
	this->UpdateInput(dt);
	this->UpdatekeyTime(dt);
	if (!this->Pause)//Unpause Stae
	{
		this->UpdateView(dt);
		this->PlayerInput(dt);
		this->UpdateTileMap(dt);
		this->player->Update(dt);
		this->PGUI->Update(dt);
	}
	else//Pause Stae
	{
		this->Pmenu->Update(this->mouseposWindow);
		this->UpdatePauseMenuButtons();
	}
}

void GameState::UpdateTileMap(const float& dt)
{
	this->tileMap->Update();
	this->tileMap->UpdateCollision(this->player,dt);

}

void GameState::UpdateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x),std::floor(this->player->getPosition().y));
}

void GameState::UpdatePlayerGUI(const float& dt)
{
	this->PGUI->Update(dt);
}

void GameState::UpdatePauseMenuButtons()
{
	if(this->Pmenu->isbuttonPressed("QUIT"))
	{
		this->Endingstate();
	}	
	if (this->Pmenu->isbuttonPressed("RESUME"))
	{
		this->UnPauseState();
	}
	
	
}
void GameState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"]))&&this->getKeyTime())
	{
		if (!this->Pause)
		{
			this->PauseState();
		}
		else
		{
			this->UnPauseState();
		}
	}
}

void GameState::PlayerInput(const float& dt)
{
	//Update player input 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_LEFT"])))
	{
		this->player->move(-1, 0,dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_RIGHT"])))
	{
		this->player->move( 1,0,dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_UP"])))
	{
		this->player->move(0, -1, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_DOWN"])))
	{
		this->player->move(0, 1,dt);
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if(!target)
	{
	   target = this->Window;
	}
	
	this->renderTextures.clear();

	renderTextures.setView(this->view);
	
	this->tileMap->render(renderTextures,this->player->getGridPosition(static_cast<int>(this->GridSize)),true);

	this->player->render(renderTextures);

	//Rendering the TileMap
	this->tileMap->renderDeffer(this->renderTextures);
	
	//Rendering the GUI
	renderTextures.setView(this->renderTextures.getDefaultView());
	this->PGUI->render(renderTextures);
	
	if (this->Pause)
	{
		this->Pmenu->render(renderTextures);
    }

	//Rendering as a single Image
	//Final Render
	this->renderTextures.display();
	this->renderSprite.setTexture(this->renderTextures.getTexture());
	target->draw(this->renderSprite);

}