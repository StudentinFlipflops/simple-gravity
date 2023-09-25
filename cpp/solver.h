#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "ball.h"

class Solver
{
private:

    uint32_t                  m_sub_steps          = 1;
    sf::Vector2f              m_gravity            = {1.0f, 1000.0f};
    sf::Vector2f              m_constraint_center;
    float                     m_constraint_radius  = 100.0f;
    std::vector<Ball>         m_objects;    
    float                     m_time               = 0.0f;
    float                     m_frame_dt           = 0.0f;

    void applyGravitty();
    
    void checkCollisions(float dt);
    
    void applyConstraint();
    
    void updateObjcets(float dt);

public: 

    Solver() = default; 

    Ball& addObject(sf::Vector2f,float);

    void update();

    void setSimulationUpdateRate(uint32_t );

    void setConstraint(sf::Vector2f , float);

    void setSubStepsCount(uint32_t);

    void setObcjetVelocity(Ball* , sf::Vector2f);

    
    const std::vector<Ball>& getObjects()const;

   
    sf::Vector3f getConstraint() const;

   
    uint64_t getObjectsCount() const;

  
    float getTime() const;


    float getStepDt() const;





};