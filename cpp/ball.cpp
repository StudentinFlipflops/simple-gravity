#include "ball.h"
#include <iostream>


void Ball::accelerate(sf::Vector2f acc)
{
    this->acceleration += acc;
}



void Ball::update(float dt)
{
    const sf::Vector2f displacment = this->position_current - this->position_old;
    this->position_old      = this->position_current ;
    
    this->position_current  = this->position_current + displacment + this->acceleration*(dt*dt); 
    this->acceleration  = {};

}


void Ball::setVelocity(sf::Vector2f v, float dt)
{
    this->position_old = this->position_current - (v*dt);
}

void Ball::addVelocity(sf::Vector2f v, float dt)
{
    this->position_old -= v*dt;
}



