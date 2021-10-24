#include "drawing_tool.h"

drawing_tool* drawing_tool::entity=nullptr;
// void renderingThread(sf::RenderWindow* window)
// {
//     window->setActive(true);

//     while (window->isOpen())
//     {
//         sf::Event event;
//         while (window->pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window->close();
//         }
//         window->display();
//     }
// }

drawing_tool* drawing_tool::get()
{
    if(entity == nullptr)
    {
        entity = new drawing_tool();
    }
    return entity;
}

drawing_tool::drawing_tool()
{
    
}

drawing_tool::~drawing_tool()
{
    if(window.isOpen())
    {
        window.close();
    }
    entity=nullptr;
}

void drawing_tool::init()
{
    window.close();
    window.create(sf::VideoMode(800, 600), "OpenGL");
    window.setActive(true);
}

void drawing_tool::draw_line(float x1, float y1, float x2, float y2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(line, 2, sf::Lines);
}

void drawing_tool::wait()
{
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }
}