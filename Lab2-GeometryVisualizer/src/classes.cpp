#include "classes.h"
#include "drawing_tool.h"
#include <cmath>

// class Point realization

double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

void Point::set_x(double value)
{
    x = value;
}

void Point::set_y(double value)
{
    y = value;
}

Point::Point(double x_value, double y_value) : x(x_value), y(y_value) {}

// class ACurve realization

ACurve::ACurve(IPoint* a_ptr, IPoint* b_ptr) : a(a_ptr), b(b_ptr) {}

// class Line realization

Line::Line(IPoint* a_ptr, IPoint* b_ptr) : ACurve(a_ptr, b_ptr) {}

IPoint* Line::get_point(double t)
{
    return new Point((1 - t) * a->get_x() + t * b->get_x(), (1 - t) * a->get_y() + t * b->get_y());
}

// class Bezier realization

Bezier::Bezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr) : ACurve(a_ptr, b_ptr), c(c_ptr), d(d_ptr) {}

IPoint* Bezier::get_point(double t)
{
    return new Point(std::pow((1 - t), 3) * a->get_x() + 3 * t * std::pow((1 - t), 2) * c->get_x() + 3 * std::pow(t, 2) * (1 - t) * d->get_x() + std::pow(t, 3) * b->get_x(),
                     std::pow((1 - t), 3) * a->get_y() + 3 * t * std::pow((1 - t), 2) * c->get_y() + 3 * std::pow(t, 2) * (1 - t) * d->get_y() + std::pow(t, 3) * b->get_y());
}

//class VisualLine

VisualLine::VisualLine(IPoint* a_ptr, IPoint* b_ptr): Line(a_ptr, b_ptr) {}
void VisualLine::draw()
{
    auto drawer = drawing_tool::get();
    for(float t=0.1f; t<1.0f;t+=0.1f)
    {
        drawer->draw_line(get_point(t-0.1f)->get_x(), get_point(t-0.1f)->get_y(), get_point(t)->get_x(), get_point(t)->get_y());
    }
}

IPoint* VisualLine::get_point(double t)
{
    return Line::get_point(t);
}

//class VisualBezier

VisualBezier::VisualBezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr): Bezier(a_ptr, c_ptr, d_ptr, b_ptr) {}

IPoint* VisualBezier::get_point(double t)
{
    return Bezier::get_point(t);
}

void VisualBezier::draw()
{
    auto drawer = drawing_tool::get();
    for(float t=0.0f; t<1.0f;t+=0.1f)
    {
        drawer->draw_line(get_point(t-0.1f)->get_x(), get_point(t-0.1f)->get_y(), get_point(t)->get_x(), get_point(t)->get_y());
    }
}