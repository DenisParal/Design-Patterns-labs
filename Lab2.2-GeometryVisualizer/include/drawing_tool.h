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
        sf::RectangleShape rectangle(sf::Vector2f(size_x, size_x));
        rectangle.setFillColor(color);
        rectangle.setPosition(x,y);
        window->draw(rectangle);
    }
    void act()
    {
        action();
    }
};