#pragma once

enum Button_states{Button_idle = 0,Button_Hover,Button_Active};

namespace GUIMK47
{
//<**************************************************************************************Buttons************************************************************************************************************>
	class Button
	{
	private:
		short unsigned  Butt_stat;
		short unsigned id;
		sf::RectangleShape shape;
		sf::Font* F;
		sf::Text T;

		//ShapeColor
		sf::Color idle;
		sf::Color Hover;
		sf::Color Active;

		//Text Color
		sf::Color Tidle;
		sf::Color THover;
		sf::Color TActive;

		//Outline Color
		sf::Color Outlineidle;
		sf::Color OutlineHover;
		sf::Color OutlineActive;

	public:
		Button(float posX, float posY, float width, float height, std::string text, unsigned charactersize, sf::Font* F, sf::Color idle, sf::Color Hover, sf::Color Active, sf::Color Tidle, sf::Color THover, sf::Color TActive, sf::Color Outlineidle = sf::Color::Transparent, sf::Color OutlineHover = sf::Color::Transparent, sf::Color OutlineActive = sf::Color::Transparent, short unsigned ID = 0);
		~Button();

		//Accessor
		const std::string getText()const;
		const bool isPressed()const;
		short unsigned getID();

		//Modifiers
		void setText(std::string Text);
		void setID(short unsigned id);
		void Update(sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& Target);
	};


//<**************************************************************************************Drop Down List************************************************************************************************************>

	class DropDownList
	{
	private:
		//Variable
		sf::Font& F;
		GUIMK47::Button* Active;
		std::vector<GUIMK47::Button*> List;
		bool showList;
		float keyTime;
		float keyTimeMax;

	public:
		//Constructors/Distructors
		DropDownList(float x, float y, float width, float height, sf::Font& F, std::vector<std::string> li, int ElementsNO,int defaultIndex);
		~DropDownList();

		//Accessors
		const bool getKeyTime();
		short unsigned getActiceID();

		//Functions
		void Update(sf::Vector2i& mousePOs, const float& dt);
		void UpdateKeyTime(const float dt);
		void render(sf::RenderTarget& Target);
	};


//<******************************************************************************Texture Selector******************************************************************************>

	/* 
	      Texture Selector will contains all the Texture of the game, in this GUI we can create a box which will contains the Textures
	*/

	class TextureSelector
	{
	private:
		//Variables
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape Selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect TexureRect;
		Button* Hide;
		float gridsize;
		bool Active;
		bool hidden;
		float keyTime;
		float keyTimeMax;



	public:
		//Construtors/Distructors
		TextureSelector(float x,float y,float width,float height,float gridsize,sf::Texture *TextureSheet,sf::Font& FM,std::string Text);
		~TextureSelector();


		//Accessors
		const bool& getActive()const;
		const sf::IntRect& getRect()const;
		const bool getKeyTime();
		//Mutators

		//Functions
		void Update(sf::Vector2i& mousePosWindow,const float &dt);
		void UpdateKeyTime(const float dt);
		void render(sf::RenderTarget& Target);

	};
}