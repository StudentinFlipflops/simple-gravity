#include "solver.h"
#include "ball.h"

class Renderer
{
private:
    sf::RenderTarget& m_target;
public:

    explicit
    Renderer(sf::RenderTarget& target): m_target{target}{}

    void render(const Solver& );
    


};