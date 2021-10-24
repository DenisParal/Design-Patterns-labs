#include "classes.h"
#include "drawing_tool.h"
#include <iostream>

int main()
{
    IPoint* p1 = new Point(1, 2);
    IPoint* p2 = new Point (200, 100);
    IPoint* p3 = new Point (300, 25);
    IPoint* p4 = new Point (500, 115);

    ICurve* l = new Line(p1, p2);
    ICurve* b = new Bezier(p1, p2, p3, p4);

    IPoint* r1 = l->get_point(0.5);
    IPoint* r2 = b->get_point(0.5);

    std::cout << r1->get_x() << " " << r1->get_y() << "\n";
    std::cout << r2->get_x() << " " << r2->get_y() << "\n";

    IDrawable* line = new VisualLine(p1, p2);
    IDrawable* bez = new VisualBezier(p1, p2, p3, p4);

    auto dr = drawing_tool::get();
    line->draw();
    bez->draw();
}