#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#define DEFAULT_COLOR 150, 50, 250
class drawing_tool
{
private:
    sf::RenderWindow window;
    static drawing_tool* entity;
    drawing_tool();
    drawing_tool(const drawing_tool&)=delete;
public:
    bool state = false;
    static drawing_tool* get();
    void wait();
    void init();
    void draw_line(float, float, float, float);
    ~drawing_tool();
};

