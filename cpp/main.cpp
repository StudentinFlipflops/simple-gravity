#include "ball.h"
#include "solver.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

int main()
{
    srand (static_cast <unsigned> (time(0)));

    constexpr int32_t window_width  = 1000;
    constexpr int32_t window_height = 1000;
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(window_width,window_height,32), "Window" , sf::Style::Default , settings)  ; 
    
    const int32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    Solver solver; 
    Renderer renderer(window);
    
    
    solver.setConstraint({static_cast<float>(window_width)*0.5f,static_cast<float>(window_height)*0.5f } , 450.0f);
    solver.setSubStepsCount(8);
    solver.setSimulationUpdateRate(frame_rate);
   


    const float        object_spawn_delay    = 0.10f;
    const float        object_spawn_speed    = 1000.0f;
    const sf::Vector2f object_spawn_position = {501.0f, 200.0f};
    const float        object_min_radius     = 5.0f;
    const float        object_max_radius     = 40.0f;
    const uint32_t     max_objects_count     = 150;
    const float        max_angle             = 1.0f;


    sf::Clock clock; 


    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            } 
        }

        if(solver.getObjectsCount()< max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay)
        {   

            clock.restart();
            float randomRadius= object_min_radius + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(object_max_radius-object_min_radius)));
            auto&           object  = solver.addObject(object_spawn_position, randomRadius);
            const float     t       = solver.getTime();
            const float     angle   = max_angle*sin(t) + 3.1415f*0.5f;

            solver.setObcjetVelocity(&object , object_spawn_speed * sf::Vector2f{static_cast<float>(cos(angle)), static_cast<float>(sin(angle))});
        }    
        
        solver.update();
        window.clear();
        renderer.render(solver);
        window.display();
    }

    return 0 ;
}