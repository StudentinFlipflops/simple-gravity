#pragma once 
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>


class Ball
{
public:
    sf::Vector2f    position_current; 
    sf::Vector2f    position_old;
    sf::Vector2f    acceleration; 
    float           radius              = 10.f;
    sf::Color       color               = sf::Color::Red;


    
    Ball() = default;
    Ball(sf::Vector2f position , float radius_ )
        :position_current{position}
        ,position_old{position}
        ,acceleration{ 0.0f , 0.0f}
        ,radius{radius_}
    {}

    void accelerate(sf::Vector2f );
    
    void update(float);

    void setVelocity(sf::Vector2f , float );

    void addVelocity(sf::Vector2f , float );

    
    sf::Vector2f getVelocity(float dt) const
    {
        return (this->position_current - this->position_old)/dt; 
    }
};

