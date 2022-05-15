#include"stdafx.h"
#include "EditorState.h"


void EditorState::initFonts()
{
	if (!(this->FM.loadFromFile("Font/FF.ttf")))
	{
		throw("\nERROR:Editor State::Font is not able to load\n");
	}
}

void EditorState::initVariables()
{
	this->layer = 0;
	this->TextureIntRect = sf::IntRect(3, 1, static_cast<int>(this->Statedata->GridSize), static_cast<int>(this->Statedata->GridSize));
	this->collision = false;
	this->type = TileType::DEFAULT;
}

void EditorState::initView()
{
	this->viewSpeed =250.f;
	this->view.setSize(sf::Vector2f(static_cast<float>(this->Statedata->Graphics->Resolution.width),static_cast<float>(this->Statedata->Graphics->Resolution.height)));
	this->view.setCenter(this->Statedata->Graphics->Resolution.width / 2.f, this->Statedata->Graphics->Resolution.height / 2.f);
}

void EditorState::initkeybinds()
{
	std::ifstream ReadConT;
	ReadConT.open("config/EditorStateKeyBinds.ini");
	while (!ReadConT.eof())
	{
		std::string keyName = {}, keyName1 = {};
		ReadConT >> keyName >> keyName1;
		this->keybinds[keyName] = this->supportedKeys[0][keyName1];
	}
	ReadConT.close();
}

void EditorState::initPauseMenu()
{
	this->Pmenu = new PauseMenu(*this->Window, this->FM);
	this->Pmenu->AddButtons("SAVE", 500.f, "SAVE");
	this->Pmenu->AddButtons("LOAD", 600.f, "LOAD");
	this->Pmenu->AddButtons("QUIT", 700.f, "Quit");
}

void EditorState::initButtons()
{

}

void EditorState::initGUI()
{
	//Side Bar
	this->sideBar.setSize(sf::Vector2f(80.f, static_cast<float>(this->Statedata->Graphics->Resolution.height)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineThickness(1.f);
	this->sideBar.setOutlineColor(sf::Color(200, 200, 20, 255));

	//Selector
	this->SelectorRect.setSize(sf::Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
	this->SelectorRect.setOutlineThickness(1.f);
	this->SelectorRect.setFillColor(sf::Color(255, 255, 150));
	this->SelectorRect.setOutlineColor(sf::Color::Green);
	this->SelectorRect.setTexture(this->tileMap->getTileSheet());
	this->SelectorRect.setTextureRect(this->TextureIntRect);

	//Texture Selector
	this->textureSelector = new GUIMK47::TextureSelector(20.f, 20.f,800.f,200.f, this->Statedata->GridSize, this->tileMap->getTileSheet(), this->FM, "TILE");

}

void EditorState::initText()
{
	this->CursorText.setFont(this->FM);
	this->CursorText.setCharacterSize(16);
	this->CursorText.setFillColor(sf::Color::Red);
	this->CursorText.setPosition(this->mouseposView.x + 200, this->mouseposView.y);

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->Statedata->GridSize,20, 20, "Resources/Tiles/tilesheet1.png");
}


EditorState::EditorState(StateData* Statedata) :State(Statedata)
{
	this->initVariables();
	this->initView();
	this->initFonts();
	this->initText();
	this->initkeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGUI();
}


EditorState::~EditorState()
{
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
	if (this->Pmenu != nullptr)
	{
		delete this->Pmenu;
	}
	if (this->tileMap != nullptr)
	{
		delete this->tileMap;
	}
	if (this->textureSelector != nullptr)
	{
		delete this->textureSelector;
	}
}


void EditorState::Update(const float& dt)
{
	this->UpdateMousePosition(&this->view);
	this->UpdatekeyTime(dt);
	this->UpdateInput(dt);
	if (!this->Pause)//Unpause Stae
	{
		this->UpdateButton();
		this->UpdateEditorInput(dt);
		this->UpdateGUI(dt);
	}
	else//Pause Stae
	{
		this->Pmenu->Update(this->mouseposWindow);
		this->UpdatePauseMenuButtons();
	}

}

void EditorState::UpdateEditorInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CAMER_UP"])))
	{
		this->view.move(0.f,-1*this->viewSpeed*dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CAMER_DOWN"])))
	{
		this->view.move(0.f, this->viewSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CAMER_LEFT"])))
	{
		this->view.move(-1*this->viewSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CAMER_RIGHT"])))
	{
		this->view.move(this->viewSpeed * dt, 0.f);
	}

	//Adding Tile on the mad
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())//If user press left than a tile is added 
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mouseposWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->AddTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->TextureIntRect, this->collision, this->type);

			}
			else
			{
				this->TextureIntRect = this->textureSelector->getRect();

			}
		}
	}
	//Removing the tile on the map
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())//If user press right than a tile is Remove
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mouseposWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->RemoveTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
	}

	//TOGGLE Collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["TOGGLE_COLLISION"])) && this->getKeyTime())
	{
		if (this->collision)
		{
			this->collision = false;
		}
		else
		{
			this->collision = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["INC_TYPE"])) && this->getKeyTime())
	{
		if (this->type < TileType::MAXTYPE-1)
			this->type++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["DEC_TYPE"])) && this->getKeyTime())
	{
		if (this->type > 0)
			this->type--;
	}

}


void EditorState::UpdateGUI(const float& dt)
{
	this->textureSelector->Update(this->mouseposWindow, dt);
	if (!this->textureSelector->getActive())
	{
		this->SelectorRect.setPosition(this->mousePosGrid.x * this->Statedata->GridSize, this->mousePosGrid.y * this->Statedata->GridSize);
		this->SelectorRect.setTextureRect(this->TextureIntRect);
	}
	this->CursorText.setPosition(this->mouseposView.x + 70, this->mouseposView.y - 20);
	std::stringstream kin;
	kin << this->mouseposView.x << " " << mouseposView.y << "\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n" << this->TextureIntRect.left << " " << this->TextureIntRect.top << "\n" << "Collision: " << this->collision << "\n" << "Type: " << this->type<<"\n"<<"Tiles: "<<this->tileMap->getLayerSize(this->mousePosGrid.x,this->mousePosGrid.y,this->layer);
	this->CursorText.setString(kin.str());
}


void EditorState::UpdatePauseMenuButtons()
{
	if (this->Pmenu->isbuttonPressed("QUIT"))
	{
		this->Endingstate();
	}

	if (this->Pmenu->isbuttonPressed("SAVE"))
	{
		this->tileMap->SaveToFile("Test.slmp");
	}

	if (this->Pmenu->isbuttonPressed("LOAD"))
	{
		this->tileMap->LoadToFile("Test.slmp");
	}

}


void EditorState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])) && this->getKeyTime())
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

void EditorState::UpdateButton()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mouseposWindow);
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		//Tile selector
		target.draw(this->SelectorRect);
	}

	
	target.setView(this->Window->getDefaultView());
	//Texture Selector
	this->textureSelector->render(target);
	//SideBar 
	target.draw(this->sideBar);


	target.setView(this->view);
	//Cursor 
	target.draw(this->CursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;

	target->setView(this->view);
	//Rendering TileMap
	this->tileMap->render(*target,this->mousePosGrid,false);
	//this->tileMap->renderDeffer(*target);

	target->setView(this->Window->getDefaultView());
	//Rendering Buttons
	for (auto& it : this->buttons)
	{
		it.second->render(*target);
	}

	//Rendering GUI
	this->renderGUI(*target);

	//Rendering Pause Menu
	if (this->Pause)
	{
		target->setView(this->Window->getDefaultView());
		this->Pmenu->render(*target);
	}

}
