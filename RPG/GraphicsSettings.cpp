#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->Title = "SKILET: THE UNKNOWN DANGER";
	this->Resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->VerticalSync = false;
	this->FrameLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->Videomodes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings() {}

void GraphicsSettings::SaveToFile(std::string path)
{
	std::ofstream WINWrite(path);
	if (WINWrite.is_open())
	{
		WINWrite << this->Title<<std::endl;
		WINWrite << this->Resolution.width<<" "<< Resolution.height << std::endl;
		WINWrite << this->fullscreen << std::endl;
		WINWrite << this->contextSettings.antialiasingLevel << std::endl;
		WINWrite << this->FrameLimit << std::endl;
		WINWrite << this->VerticalSync;
	}
	WINWrite.close();
}

void GraphicsSettings::loadFromFile(std::string path)
{
	std::ifstream WINread(path);
	if (WINread.is_open())
	{
		std::getline(WINread, this->Title);
		WINread >> this->Resolution.width>> Resolution.height;
		WINread >> this->fullscreen;
		WINread >> this->contextSettings.antialiasingLevel;
		WINread >> this->FrameLimit;
		WINread >> this->VerticalSync;
	}
	WINread.close();
}
