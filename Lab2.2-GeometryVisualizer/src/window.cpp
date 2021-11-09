#include "classes.h"
#include "graphical_interface.h"
#include <iostream>
#include <ctime>

int main()
{
    std::srand(std::time(nullptr));
    auto lambda = [](sf::RenderWindow& window)
    {
        auto act1 = [&window](){window.close();};
        button<decltype(act1)> b1(0,0,800,50,act1,sf::Color::Green,"Curve generation");
        button<decltype(act1)> b2(0,500,400,50,act1,sf::Color::Blue,"Save to svg");
        button<decltype(act1)> b3(400,500,400,50,act1,sf::Color::Blue,"Save to svg");

        sf::RenderTexture pictureLucky, pictureUnlucky;
        pictureLucky.create(400,400);
        pictureUnlucky.create(400,400);

        IPoint* p1 = new Point(50, 50);
        IPoint* p2 = new Point (200, 400);
        IPoint* p3 = new Point (300, 25);
        IPoint* p4 = new Point (500, 115);

        IDrawable* b = new VisualBezier(p1, p2, p3, p4);
        IDrawer* lucky = new DrawerLucky(&pictureLucky);
        IDrawer* unlucky = new DrawerUnlucky(&pictureUnlucky, 1);

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
                        delete p1;
                        delete p2;
                        delete p3;
                        delete p4;
                        p1 = new Point(std::rand()%50+10, std::rand()%100+10);
                        p2 = new Point (std::rand()%100+50, std::rand()%100+100);
                        p3 = new Point (std::rand()%100+150, std::rand()%50+10);
                        p4 = new Point (std::rand()%100+250, std::rand()%150+100);
                        b = new VisualBezier(p1, p2, p3, p4);

                        pictureLucky.clear(sf::Color::White);
                        b->draw(lucky,lucky,lucky);
                        pictureUnlucky.clear(sf::Color::White);
                        b->draw(unlucky,unlucky,unlucky);
                    }
                    else if (b2.check_coordinate(localPosition.x, localPosition.y))
                    {
                        pictureLucky.getTexture().copyToImage().saveToFile("/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build/lucky.png");
                    }
                    else if (b3.check_coordinate(localPosition.x, localPosition.y))
                    {
                        pictureUnlucky.getTexture().copyToImage().saveToFile("/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build/unlucky.png");
                    }
                    
                }
            }
            window.clear(sf::Color::White);
            b1.display(&window);
            b2.display(&window);
            b3.display(&window);
            sf::Sprite sprite1(pictureLucky.getTexture());
            sf::Sprite sprite2(pictureUnlucky.getTexture());
            sprite1.setPosition(0,100);
            sprite2.setPosition(400,100);

            window.draw(sprite1);
            window.draw(sprite2);
            window.display();
        }
    };
    gr_interface<decltype(lambda)> interface(800,600,"start",lambda);
    interface.init();
}