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
        button<decltype(act1)> b4(400,550,400,50,act1,sf::Color::Blue,"Find center");

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

        IDrawer* drawer_lucky = new DrawCollection(lucky, lucky, lucky);
        IDrawer* drawer_unlucky = new DrawCollection(unlucky, unlucky, unlucky);

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
                        ICurve* bez = new Bezier(p1, p2, p3, p4);
                        ICurve* bez1 = new Fragment(bez,1,0);
                        ICurve* bez2 = new MoveTo(bez1,p4);
                        DrawableCurve reversed_curve{bez2};
                        pictureLucky.clear(sf::Color::White);
                        
                        b->draw(drawer_lucky);
                        reversed_curve.draw(drawer_lucky);
                        pictureUnlucky.clear(sf::Color::White);
                        b->draw(drawer_unlucky);
                        reversed_curve.draw(drawer_unlucky);
                        delete bez;
                        delete bez1;
                        delete bez2;
                    }
                    else if (b2.check_coordinate(localPosition.x, localPosition.y))
                    {
                        pictureLucky.getTexture().copyToImage().saveToFile("/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build/lucky.png");
                    }
                    else if (b3.check_coordinate(localPosition.x, localPosition.y))
                    {
                        pictureUnlucky.getTexture().copyToImage().saveToFile("/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/build/unlucky.png");
                    }
                    else if (b4.check_coordinate(localPosition.x, localPosition.y))
                    {
                        IStrategy* runner1 = new getCurveLength();
                        IStrategy* runner2 = new getCoeff();
                        ICurve* curve = new Bezier(p1, p2, p3, p4);
                        float middle_length = runner1->operator()(curve,0.5f,0.05f);
                        std::cout << "Middle length is " << middle_length <<"\n";
                        float middle_coef = runner2->operator()(curve, middle_length, 0.05f);
                        std::cout << "Middle coeff is " << middle_coef <<"\n";
                        IPoint* p = curve->get_point(middle_coef);

                        sf::CircleShape circle(4,30);
                        circle.setFillColor(sf::Color::Red);
                        circle.setPosition(p->get_x()-4, p->get_y()-4);
                        pictureLucky.draw(circle);
                        pictureUnlucky.draw(circle);
                    }
                    
                }
            }

            window.clear(sf::Color::White);
            b1.display(&window);
            b2.display(&window);
            b3.display(&window);
            b4.display(&window);
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