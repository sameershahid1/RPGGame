#pragma once
class GraphicsSettings
{
public:
	//Constructors
	GraphicsSettings();

	//Variables
	std::string Title;
	sf::VideoMode Resolution;
	bool fullscreen;
	bool VerticalSync;
	unsigned FrameLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> Videomodes;


	//Distructors
	~GraphicsSettings();

	//Functions
	void SaveToFile(std::string path);

	void loadFromFile(std::string path);
};
