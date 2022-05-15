#pragma once
class AttributeComponent
{
public:
	//Leveling 
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned StatusPoint;
	unsigned Attributepoints;

	//Attributes
	int Vitality;
	int strength;
    int Dexterity;
	int agility;
	int Intelligence;

	//Stats
	int HP;
	int HPMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;




	//Constructors/Distructors
	AttributeComponent(unsigned level);
	~AttributeComponent();


	//Functions
	void UpdateStats(const bool reset);
	void gainExp(const unsigned exp);
	void UpdateLevelUp();
	void Update();
};
