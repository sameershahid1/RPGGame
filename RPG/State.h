#pragma once
#include"Player.h"
#include"GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;


//State Data
//Used for Storing all the common data between the states class 
class StateData
{
public:
    //Variables
    float GridSize;
    sf::RenderWindow* Window;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
    GraphicsSettings* Graphics;


    //Constructors
    StateData() 
    {
        GridSize=0;
        Window=nullptr;
        supportedKeys=nullptr;
        states=nullptr;
        Graphics=nullptr;
    }
    ~StateData() {}
  
};


class State
{
protected:
    StateData* Statedata;
    sf::RenderWindow* Window;
    std::map<std::string, int>*supportedKeys;
    std::map<std::string, int> keybinds;
    std::stack<State*>* states;
    bool Quit;
    bool Pause;
    float keyTime;
    float keyTimeMax;
    float GridSize;

    //Mouse Position
    sf::Vector2i mouseposScreen;
    sf::Vector2i mouseposWindow;
    sf::Vector2f mouseposView;
    sf::Vector2i mousePosGrid;


    //Resources
    std::map<std::string,sf::Texture> Tex;
    
    //Functions
    virtual void initkeybinds() = 0;
    
public:
  

   State(StateData* Statedate);
   virtual ~State();
   
   //Accessors
   const bool& getQuit()const;
   const bool getKeyTime();
   
   //Ending State
   virtual void Endingstate();

   //Pausing the game State
   void PauseState();
   void UnPauseState();


   //Updating
   virtual void Update(const float& dt) = 0;
   virtual void UpdatekeyTime(const float dt);
   virtual void UpdateInput(const float& dt) = 0;
   virtual void UpdateMousePosition(sf::View* view = nullptr);
   
   //Drawing
   virtual void render(sf::RenderTarget *target)=0;

};