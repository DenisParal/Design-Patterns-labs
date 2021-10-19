#include <SFML/Graphics.hpp>

class drawing_tool
{
private:
    sf::RenderWindow window;
    sf::Thread* render_thread;
    static drawing_tool* entity;
    drawing_tool();
    drawing_tool(const drawing_tool&)=delete;
public:
    static drawing_tool* get();
    ~drawing_tool();
};