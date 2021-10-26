#include <SFML/Graphics.hpp>
class drawing_tool
{
private:
    sf::RenderWindow window;
    static drawing_tool* entity;
    drawing_tool();
    drawing_tool(const drawing_tool&)=delete;
public:
    static drawing_tool* get();
    void wait();
    void init();
    void draw_line(float, float, float, float);
    ~drawing_tool();
};