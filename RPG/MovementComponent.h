#pragma once
enum MovementStates {IDLE=0,Moving,Move_Left,Move_Right,Move_Up, Move_Down};

class MovementComponent
{
private: 
	//Variables
	sf::Sprite& sprite;
	sf::Vector2f Velocity;
	float maxVelocity;
	float Acceleration;
	float Deceleration;

	//InitFuncitons

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float Acceleration, float Decelerataion);
	~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity()const;
	const float& getMaxVelocity()const;
	const bool getState(const short unsigned state)const;


	//Mutators


	//Funcitons
	//Reseting the Velocity
	void StopVelocity();	
	void StopVelocityX();	
	void StopVelocityY();	
	
	void move(const float dir_x, const float dir_y, const float& dt);
	void Update(const float &dt);
};