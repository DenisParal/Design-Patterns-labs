#pragma once
#include <SFML/Graphics.hpp>
#include <string>

template<typename Func>
class gr_interface
{
private:
    sf::RenderWindow window;
    Func run_function;
    sf::Thread thread;
    std::size_t size_x;
    std::size_t size_y;
    std::string window_name;

    class thread_handler
    {
        Func func;
        std::size_t size_x;
        std::size_t size_y;
        std::string window_name;
    public:
        thread_handler(std::size_t size_x, std::size_t size_y, std::string window_name, Func run_function): size_x(size_x), size_y(size_y), window_name(window_name), func(run_function) {}
        void operator()(sf::RenderWindow* window)
        {
            window->create(sf::VideoMode(size_x, size_y), window_name);
            window->setActive(true);
            func(*window);
        }
    };

public:
    gr_interface(std::size_t size_x, std::size_t size_y, std::string window_name, Func run_function): size_x(size_x), size_y(size_y), window_name(window_name), run_function(run_function), thread(thread_handler{size_x, size_y, window_name, run_function}, &window) {}
    void init()
    {
        if(!window.isOpen())
        {
            thread.launch();
        }
    }
    ~gr_interface()
    {
        thread.wait();
    }
};

template<typename Func>
class button
{
private:
    float x;
    float y;
    float size_x;
    float size_y;
    Func action;
    sf::Color color;
    std::string text;
public:
    button(float x, float y, float size_x, float size_y, Func action, sf::Color color, std::string text): x(x), y(y), size_x(size_x), size_y(size_y), action(action), color(color), text(text) {}
    
    bool check_coordinate(float x, float y)
    {
        return x >= this->x && x <= this->x+this->size_x && y >= this->y && y <= this->y+this->size_y;
    }

    void display(sf::RenderWindow* window)
    {
        sf::Font font;
        font.loadFromFile("/home/dparanic/Study/Design-Patterns-labs/Lab2.2-GeometryVisualizer/src/arial.ttf");

        sf::RectangleShape rectangle(sf::Vector2f(size_x, size_y));
        sf::Text button_text(text, font);
        button_text.setFillColor(sf::Color::Black);
        button_text.setOutlineThickness(1.0f);
        button_text.setCharacterSize(25);
        button_text.setPosition(x+20.0f,y+20.0f);
        rectangle.setFillColor(color);
        rectangle.setOutlineThickness(1.0f);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setPosition(x,y);
        window->draw(rectangle);
        window->draw(button_text);
    }
    void act()
    {
        action();
    }
};