#pragma once

class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect NextPosition;
	float offsetX;
	float offsetY;
    
public:
	//Construtor/Distructor
	HitBoxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float widht, float height);
	~HitBoxComponent();
	 

	//Accessor
	const sf::Vector2f& getPosition()const;
	const sf::FloatRect getGlobalBounds()const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Mutators
	void setPosition(const sf::Vector2f& pos);
	void setPosition(const float x,const float y);
     

	//Functions
	bool Intereact(const sf::FloatRect Frect);
	void Update();
	void render(sf::RenderTarget& Target);

};
