#include "drawing_tool.h"

drawing_tool* drawing_tool::entity=nullptr;
void renderingThread(sf::RenderWindow* window)
{
    window->setActive(true);

    while (window->isOpen())
    {
        window->display();
    }
}

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
    window.create(sf::VideoMode(800, 600), "My window");
    window.setActive(false);

    render_thread = new sf::Thread(&renderingThread, &window);
    render_thread->launch();
}

drawing_tool::~drawing_tool()
{
    window.close();
    render_thread->wait();
    entity=nullptr;
    delete render_thread;
}