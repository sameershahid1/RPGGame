#include"stdafx.h"
#include "State.h"

State::State(StateData* Statedata)
{
	this->Statedata = Statedata;
	this->Window = Statedata->Window;
	this->states = Statedata->states;
	this->supportedKeys = Statedata->supportedKeys;
	this->GridSize = Statedata->GridSize;
	this->Quit = false;
	this->Pause = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State() {}

const bool& State::getQuit()const
{
	return this->Quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void State::Endingstate()
{
	this->Quit = true;
}

void State::PauseState()
{
	this->Pause = true;
}

void State::UnPauseState()
{
	this->Pause = false;
}

void State::UpdatekeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		keyTime += 100.f * dt;
	}
}

void State::UpdateMousePosition(sf::View* view)
{
	this->mouseposScreen = sf::Mouse::getPosition();
	this->mouseposWindow = sf::Mouse::getPosition(*this->Window);
	if (view != nullptr)
	{
		this->Window->setView(*view);
	}
	this->mouseposView = this->Window->mapPixelToCoords(sf::Mouse::getPosition(*this->Window));
	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mouseposView.x)/static_cast<int>( this->Statedata->GridSize)
		,static_cast<int>(this->mouseposView.y) / static_cast<int>(this->Statedata->GridSize));
	this->Window->setView(this->Window->getDefaultView());
}