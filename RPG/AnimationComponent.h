#pragma once
class AnimationComponent
{
private:
	//Animaiton Class
	//Also it does not matter whather we create animation class in AnimationComponent.
	class Animation
	{
	public:
		//Variables 
		sf::Sprite& sprite;
		sf::Texture& TexSheet;
		float AnimationTimer;
		float timer;
		bool done;

		int width;
		int height;
		sf::IntRect startR;
		sf::IntRect Current;
		sf::IntRect endR;
		Animation(sf::Sprite& sprite, sf::Texture& TexSheet, float AnimationTimer, int startFramex, int startFramey, int Framex, int Framey, int width, int height) :sprite{sprite}, TexSheet{ TexSheet }, AnimationTimer{ AnimationTimer }, width{ width }, height{ height }
		{
			//Giving values to the Attributes
			this->startR = sf::IntRect(startFramex*width,startFramey*height,this->width,this->height);
			this->endR = sf::IntRect(Framex* width, Framey * height,this->width,this->height);
			this->sprite.setTexture(this->TexSheet,true);
			this->Current = this->startR;
			this->timer = 0.f;
			this->done=false;
			this->sprite.setTextureRect(this->Current);
		}

		//Accessors
		const bool& getdone()const
		{
			return this->done;
		}

		//Functions
		const bool &Play(const float& dt)
		{
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->AnimationTimer)
			{
				//Reset Timer
				this->timer = 0.f;
				
				//Animate it
				if(this->Current!=this->endR)
				{
					this->Current.left += this->width;
				}
				else//Reset
				{
					this->Current.left =this->startR.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->Current);
			}
			return this->done;
		}

		const bool& Play(const float& dt,float percentage)
		{
			this->done = false;
			if (percentage < 0.5f)
			{
				percentage = 0.5f;
			}
			this->timer +=percentage*100* dt;
			if (this->timer >= this->AnimationTimer)
			{
				//Reset Timer
				this->timer = 0.f;

				//Animate it
				if (this->Current != this->endR)
				{   
					this->Current.left += this->width;
				}
				else//Reset
				{
					this->Current.left = this->startR.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->Current);
			}
			return this->done;
		}

		void reset() 
		{
			this->timer =this->AnimationTimer;
			this->Current = this->startR;
		}
	};


	//Attributes
	sf::Sprite& sprite;
	sf::Texture& TexSheet;
	std::map<std::string, Animation*> animation;
	
	//Animation objects
	Animation* LastAnimation;
	Animation* PriorityAnimation;
public:
	//Constructor/Distructor
	AnimationComponent(sf::Sprite &sprite,sf::Texture &TexSheet);
    ~AnimationComponent();

	//Accessors
	const bool& isDone(std::string key);

	//Functions
	void AddAnimation(const std::string Key,float AnimationTimer, int startFramex, int startFramey, int Framex, int Framey, int width, int height);
	const bool& Play(const std::string key,const float &dt, const bool pripority);
	const bool& Play(const std::string key,const float &dt,const float &modifier,const float &moaxModifier, const bool pripority);
};