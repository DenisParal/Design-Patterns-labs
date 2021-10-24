#include "classes.h"
#include "drawing_tool.h"
#include <iostream>

int main()
{
    IPoint* p1 = new Point(1, 2);
    IPoint* p2 = new Point (15, 25);
    IPoint* p3 = new Point (5, 5);
    IPoint* p4 = new Point (5, 5);

    ICurve* l = new Line(p1, p2);
    ICurve* b = new Bezier(p1, p2, p1, p2);

    IPoint* r1 = l->get_point(0.5);
    IPoint* r2 = b->get_point(0.5);

    std::cout << r1->get_x() << " " << r1->get_y() << "\n";
    std::cout << r2->get_x() << " " << r2->get_y() << "\n";

    IDrawable* line = new VisualLine(p1, p2);

    auto dr = drawing_tool::get();
    line->draw();
    dr->wait();
}