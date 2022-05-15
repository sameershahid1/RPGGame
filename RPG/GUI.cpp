#include"stdafx.h"
#include"GUI.h"


//Constructor/Distructors
GUIMK47::Button::Button(float posX, float posY, float width, float height, std::string text,unsigned charactersize, sf::Font* F, sf::Color idle, sf::Color Hover, sf::Color Active, sf::Color Tidle, sf::Color THover, sf::Color TActive, sf::Color Outlineidle, sf::Color OutlineHover, sf::Color OutlineActive,short unsigned ID)
{

	this->id = ID;
	this->shape.setPosition(sf::Vector2f(posX,posY));
	this->shape.setSize(sf::Vector2f(width,height));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(Outlineidle);

	this->F=F;
	this->T.setFont(*this->F);
	this->T.setString(text);
	this->T.setFillColor(sf::Color::White);
	this->T.setCharacterSize(charactersize);
	this->T.setPosition(this->shape.getPosition().x+(this->shape.getGlobalBounds().width/2)-T.getGlobalBounds().width/2, this->shape.getPosition().y +(this->shape.getGlobalBounds().height / 2) - T.getGlobalBounds().height / 2);
	this->Butt_stat=Button_idle;
	
	this->idle = idle;
	this->Hover = Hover;
 	this->Active = Active; 

	this->Tidle = Tidle;
	this->THover = THover;
	this->TActive = TActive;


	this->Outlineidle = Outlineidle;
	this->OutlineHover = OutlineHover;
	this->OutlineActive = OutlineActive;

}

GUIMK47::Button::~Button() {}


//Accessors
const std::string GUIMK47::Button::getText() const
{
	return this->T.getString();
}

const bool GUIMK47::Button::isPressed() const
{
	if (this->Butt_stat==Button_Active)
	{
		return true;
	}
	return false;
}

short unsigned GUIMK47::Button::getID()
{
	return this->id;
}


//Modifiers
void GUIMK47::Button::setText(std::string Text)
{
	this->T.setString(Text);

}


//Functions
void GUIMK47::Button::Update(sf::Vector2i & mousePosWindow)
{
	this->Butt_stat = Button_idle;
	if(shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->Butt_stat = Button_Hover;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->Butt_stat = Button_Active;
		}
	}

	if (Butt_stat==Button_idle)
	{
		shape.setFillColor(this->idle);
		this->T.setFillColor(this->Tidle);
		this->shape.setOutlineColor(this->Outlineidle);
	}
	else if (Butt_stat == Button_Hover)
	{
		shape.setFillColor(this->Hover);
		this->T.setFillColor(this->THover);
		this->shape.setOutlineColor(this->OutlineHover);
	}
	else if (Butt_stat == Button_Active)
	{
		shape.setFillColor(this->Active);
		this->T.setFillColor(this->TActive);
		this->shape.setOutlineColor(this->OutlineActive);
	}

}

void GUIMK47::Button::setID(short unsigned id)
{
	this->id = id;
}

void GUIMK47::Button::render(sf::RenderTarget& Target)
{
	Target.draw(shape);
	Target.draw(T);
}



//<**************************************************************************************Drop Down List************************************************************************************************************>



//Constructors
GUIMK47::DropDownList::DropDownList(float x,float y,float width,float height,sf::Font& F,std::vector<std::string> list,int ElementsNO, int defaultIndex) :F{F}
{
	this->showList = false;
	this->keyTime = 1.f;
	this->keyTimeMax = 1.f;
	this->Active = new Button(x, y, width, height,list[defaultIndex], 20, &this->F, sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
		, sf::Color(255, 255, 255, 150), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20, 50)
		, sf::Color(255, 250, 250, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));
	for (int i = 0; i < ElementsNO; i++)
	{
	   this->List.push_back(new Button(x,y+((i+1)*height),width,height,list[i],20,&this->F
	   ,sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	   ,sf::Color(255,255,255,150), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20,50)
	   ,sf::Color(255,250,250,0), sf::Color(255, 255, 255,0), sf::Color(20, 20, 20,0),i));
	}
}

//Distructors
GUIMK47::DropDownList::~DropDownList()
{
	if(this->Active!=nullptr)
	{
		delete Active;
	}

	for (size_t i = 0; i < this->List.size(); i++)
	{
		delete this->List[i];
	}
}


//Accessors
const bool GUIMK47::DropDownList::getKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

short unsigned GUIMK47::DropDownList::getActiceID()
{
	return this->Active->getID();
}



//Functions
void GUIMK47::DropDownList::Update(sf::Vector2i& mousePOs,const float& dt)
{

	this->UpdateKeyTime(dt);

	//Updating the Buttons
	this->Active->Update(mousePOs);
	
	if (this->Active->isPressed()&&this->getKeyTime())
	{
		if(this->showList)
		{
			this->showList = false;
		}
		else
		{
			this->showList = true;
		}
	}
	if (this->showList)
	{
		for (auto& it : this->List)
		{
			it->Update(mousePOs);
			if (it->isPressed()&&this->getKeyTime())
			{
				this->showList = false;
				this->Active->setText(it->getText());
				this->Active->setID(it->getID());
			}
		}
	}

}

void GUIMK47::DropDownList::UpdateKeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10*dt;
	}
}

//used for Rendering the Drop Down List
void GUIMK47::DropDownList::render(sf::RenderTarget& Target)
{
	this->Active->render(Target); 
	
	if (this->showList)
	{
		for (auto& it : this->List)
		{
			it->render(Target);
		}
	}
}


//<******************************************************************************Texture Selector******************************************************************************>

//Constructor
GUIMK47::TextureSelector::TextureSelector(float x, float y, float width, float height,float gridsize, sf::Texture* TextureSheet,sf::Font &FM,std::string Text)
{
	this->keyTime = 0.f;
	this->keyTimeMax = 1.f;

	this->gridsize = gridsize;
	this->hidden = false;
	this->Active = false;

	float offerSet = 100.f;

	//Setting the Box which will contains all the tils set
	this->bounds.setSize(sf::Vector2f(width,height));
	this->bounds.setPosition(x+offerSet,y);
	this->bounds.setFillColor(sf::Color(50,50,50,100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255,255,255,200));
	

	this->sheet.setTexture(*TextureSheet);
	this->sheet.setPosition(x+offerSet,y);
	
	
	//Making sure that the sheet does not get out Of the Box boundary
	//if(this->sheet.getGlobalBounds().width>this->bounds.getGlobalBounds().width)//Checking with respect to Width
	//{
	//	this->sheet.setTextureRect(sf::IntRect(0,0,static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	//}
	//if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)//Checking with respect to Height
	//{
	//	this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>( this->sheet.getGlobalBounds().width), static_cast<int>( this->bounds.getGlobalBounds().height)));
	//}

	//Setting the Selector
	this->Selector.setPosition(x+offerSet,y);
	this->Selector.setSize(sf::Vector2f(this->gridsize,this->gridsize));
	this->Selector.setFillColor(sf::Color::Transparent);
	this->Selector.setOutlineThickness(1.f);
	this->Selector.setOutlineColor(sf::Color::Red);


	this->TexureRect.width = static_cast<int>(this->gridsize);
	this->TexureRect.height = static_cast<int>(this->gridsize);

    //Buttons Creations
	this->Hide= new Button(x,y,50,50,Text,24,&FM, sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 50), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50));
}

//Distructor
GUIMK47::TextureSelector::~TextureSelector()
{
	if (this->Hide != nullptr)
	{
		delete this->Hide;
	}
}


//Accessors
const bool& GUIMK47::TextureSelector::getActive()const
{
	return this->Active;
}

const sf::IntRect& GUIMK47::TextureSelector::getRect()const
{
	return this->TexureRect;
}

const bool GUIMK47::TextureSelector::getKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//Mutators


//Functions
void GUIMK47::TextureSelector::Update(sf::Vector2i& mousePosWindow,const float &dt)
{

	this->UpdateKeyTime(dt);
	this->Hide->Update( mousePosWindow);
	
	if(this->Hide->isPressed()&&this->getKeyTime())
	{
		if(this->hidden)
		{
			this->hidden = false;
		}
		else
		{
			this->hidden = true;
		}
	}
	
	if(!this->hidden)
	{

		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->Active = true;
		}
		else
		{
			this->Active = false;
		}
		

		if (this->Active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridsize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridsize);
			this->Selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridsize, this->bounds.getPosition().y + this->mousePosGrid.y * this->gridsize);

			//updating the Texture Rect
			this->TexureRect.left = static_cast<int>(this->Selector.getPosition().x - this->bounds.getPosition().x);
			this->TexureRect.top = static_cast<int>(this->Selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}


void GUIMK47::TextureSelector::UpdateKeyTime(const float dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10 * dt;
	}
}


void GUIMK47::TextureSelector::render(sf::RenderTarget& Target)
{

	if (!this->hidden)
	{
		Target.draw(this->bounds);
		Target.draw(this->sheet);
		if (this->Active)
		{
			Target.draw(this->Selector);
		}
	}

	this->Hide->render(Target);
}


