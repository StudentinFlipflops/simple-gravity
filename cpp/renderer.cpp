#include "renderer.h"

 void Renderer::render(const Solver& solver) 
    {
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraint_bacground{constraint.z};
        constraint_bacground.setOrigin(constraint.z , constraint.z);
        constraint_bacground.setFillColor(sf::Color::White);
        constraint_bacground.setPosition(constraint.x , constraint.y);
        constraint_bacground.setPointCount(128);
        m_target.draw(constraint_bacground);
        


        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f , 1.0f);
        const auto& objects = solver.getObjects();
        for(const auto& obj : objects)
        {
            circle.setPosition(obj.position_current);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.color);
            m_target.draw(circle);
        }
    }

