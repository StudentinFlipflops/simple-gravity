#include "solver.h"
#include <iostream>

/*private*/


void Solver::applyGravitty()
{
    for(auto& obj : this->m_objects) obj.accelerate(this->m_gravity);

}

void Solver::checkCollisions(float dt)
{
    const float     response_coef = 0.75f;
    const uint64_t  objects_count = m_objects.size();

    for(uint64_t i{0} ; i < objects_count ; ++i)
    {
        Ball& object_1 = m_objects[i];
        
        for(uint64_t k{i+1} ; k < objects_count ; ++k)
        {
            Ball&               object_2   = m_objects[k]; 
            const sf::Vector2f  v           = object_1.position_current - object_2.position_current; 
            const float         dist2       = v.x*v.x + v.y *v.y;
            const float         min_dist    = object_1.radius + object_2.radius;
                if (dist2 < min_dist * min_dist) {
                const float        dist  = sqrt(dist2);
                const sf::Vector2f n     = v / dist;
                const float mass_ratio_1 = object_1.radius / (object_1.radius + object_2.radius);
                const float mass_ratio_2 = object_2.radius / (object_1.radius + object_2.radius);
                const float delta        = 0.5f * response_coef * (dist - min_dist);
                object_1.position_current -= n * (mass_ratio_2 * delta);
                object_2.position_current += n * (mass_ratio_1 * delta); 
            }
        }
    }
}

void Solver::applyConstraint()
{
    for(auto& obj : m_objects)
    {
        const sf::Vector2f  v       = m_constraint_center - obj.position_current;
        const float         dist    = sqrt(v.x*v.x + v.y*v.y);

        if(dist > (m_constraint_radius - obj.radius))
        {
            const sf::Vector2f n = v/dist;
            obj.position_current = m_constraint_center - n*(m_constraint_radius  - obj.radius);

        }
    }
}

void Solver::updateObjcets(float dt)
{
    for(auto& obj: m_objects)
    {
        obj.update(dt);
    }
}



/*public*/



Ball &Solver::addObject(sf::Vector2f position,   float radius)
{
    return m_objects.emplace_back(position, radius);
}

void Solver::update()
{
    m_time += m_frame_dt;
    const float step_dt = getStepDt();
    for(uint32_t i{m_sub_steps} ; i--;  )
    {
        applyGravitty();
        checkCollisions(step_dt);
        applyConstraint();
        updateObjcets(step_dt);
    }
}







void Solver::setSimulationUpdateRate(uint32_t rate)
{
    m_frame_dt = 1.0f/static_cast<float>(rate);
}

void Solver::setConstraint(sf::Vector2f position, float radius)
{
    m_constraint_center = position;
    m_constraint_radius = radius;
}

void Solver::setSubStepsCount(uint32_t sub_steps)
{
    m_sub_steps = sub_steps;
}

void Solver::setObcjetVelocity(Ball *object, sf::Vector2f v )
{
    object->setVelocity(v , getStepDt());
}

const std::vector<Ball> &Solver::getObjects() const
{
    return m_objects;
}

sf::Vector3f Solver::getConstraint() const
{
    return {m_constraint_center.x , m_constraint_center.y, m_constraint_radius } ;
}

uint64_t Solver::getObjectsCount() const
{
    return m_objects.size();
}

float Solver::getTime() const
{
    return m_time;
}

float Solver::getStepDt() const
{   
    return  m_frame_dt/static_cast<float>(m_sub_steps);
}


