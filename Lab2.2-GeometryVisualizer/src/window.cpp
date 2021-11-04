#include "classes.h"
#include "drawing_tool.h"
#include "graphical_interface.h"
#include <iostream>

int main()
{
    auto lambda = [](sf::RenderWindow& window)
    {
        auto act1 = [&window](){window.close();};
        button<decltype(act1)> b1(0,0,200,200,act1,sf::Color::Blue,"1");
        while(window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    if (b1.check_coordinate(localPosition.x, localPosition.y))
                    {
                        window.close();
                    }
                }
            }
            window.clear();
            b1.display(&window);
            window.display();
        }
    };
    gr_interface<decltype(lambda)> interface(200,400,"start",lambda);
    interface.init();
}