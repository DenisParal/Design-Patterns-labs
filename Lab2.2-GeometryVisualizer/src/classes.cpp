#include "classes.h"
#include <cmath>
#include <iostream>

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

IPoint* VisualLine::get_point(double t)
{
    return Line::get_point(t);
}

//class VisualCurve
void VisualCurve::draw(IDrawer* drawer) 
{
    IPoint* fp = get_point(0.0f);
    drawer->draw_beginning(fp);
    for(float t=0.05f; t<1.0f;t+=0.05f)
    {
        IPoint* p1 = get_point(t-0.05f);
        IPoint* p2 = get_point(t);
        drawer->draw_segment(p1,p2);
        delete p1;
        delete p2;
    }
    IPoint* lp1 = get_point(0.9f);
    IPoint* lp2 = get_point(1.0f);
    drawer->draw_ending(lp1, lp2);
    delete fp;
    delete lp1;
    delete lp2;
}

//class VisualBezier

VisualBezier::VisualBezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr): Bezier(a_ptr, c_ptr, d_ptr, b_ptr) {}

IPoint* VisualBezier::get_point(double t)
{
    return Bezier::get_point(t);
}

//class IDrawer

IDrawer::IDrawer(sf::RenderTexture* picture): picture(picture) {}

//class DrawerLucky
DrawerLucky::DrawerLucky(sf::RenderTexture* picture):IDrawer(picture){}
void DrawerLucky::draw_beginning(IPoint* fp)
{
    sf::CircleShape circle(10,15);
    circle.setPosition(sf::Vector2f(fp->get_x()-10, fp->get_y()-10));
    circle.setOutlineColor(sf::Color::Yellow);
    circle.setFillColor(sf::Color::Green);
    picture->draw(circle);
}
void DrawerLucky::draw_segment(IPoint* p1, IPoint* p2)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(p1->get_x(), p1->get_y());
    line[1].position = sf::Vector2f(p2->get_x(), p2->get_y());
    line[0].color = sf::Color::Green;
    line[1].color = sf::Color::Green;
    picture->draw(line);
}
void DrawerLucky::draw_ending(IPoint* p1, IPoint* p2)
{
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(p2->get_x(), p2->get_y());
    triangle[0].color = sf::Color::Green;
    sf::Vector2f vec(p2->get_x()-p1->get_x(), p2->get_y()-p1->get_y());

    sf::Vector2f v1((vec.y * (-1))/2.0f, vec.x/2.0f); //wrong calculations
    sf::Vector2f v2(vec.y/2.0f, (vec.x * (-1))/2.0f);
    
    Point p3(p1->get_x()+v1.x, p1->get_y()+v1.y);
    Point p4(p1->get_x()+v2.x, p1->get_y()+v2.y);

    triangle[1].position = sf::Vector2f(p3.get_x(), p3.get_y());
    triangle[1].color = sf::Color::Green;

    triangle[2].position = sf::Vector2f(p4.get_x(), p4.get_y());
    triangle[2].color = sf::Color::Green;

    picture->draw(triangle);
}

// class DrawerUnlucky

DrawerUnlucky::DrawerUnlucky(sf::RenderTexture* picture, std::size_t periodicity):IDrawer(picture), periodicity(periodicity), current_per(0){}
void DrawerUnlucky::draw_beginning(IPoint* fp)
{
    sf::RectangleShape rect(sf::Vector2f(10.f, 10.f));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(fp->get_x()-5, fp->get_y()-5);
    picture->draw(rect);
}
void DrawerUnlucky::draw_segment(IPoint* p1, IPoint* p2)
{
    if(current_per!= periodicity)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(p1->get_x(), p1->get_y());
        line[1].position = sf::Vector2f(p2->get_x(), p2->get_y());
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        picture->draw(line);
        current_per++;
    }
    else
    {
        current_per=0;
    }
    
}
void DrawerUnlucky::draw_ending(IPoint* p1, IPoint* p2)
{
    sf::RectangleShape rect(sf::Vector2f(10.f, 10.f));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(p2->get_x()-5, p2->get_y()-5);
    picture->draw(rect);
}


//DrawerCollection

DrawCollection::DrawCollection(IDrawer* drawer_begin, IDrawer* drawer_segment, IDrawer* drawer_end) : IDrawer(drawer_begin->picture), drawer_begin(drawer_begin), drawer_segment(drawer_segment), drawer_end(drawer_end) {}

void DrawCollection::draw_beginning(IPoint* p)
{
    drawer_begin->draw_beginning(p);
}

void DrawCollection::draw_segment(IPoint* p1, IPoint* p2)
{
    drawer_segment->draw_segment(p1,p2);
}

void DrawCollection::draw_ending(IPoint* p1, IPoint* p2)
{
    drawer_end->draw_ending(p1,p2);
}
//Strategies impl

float getCurveLength::operator()(ICurve* curve, float coeff, float step)
{
    float length = 0.0f;
    for(float t = 0.0f+step; t <= coeff; t+=step)
    {
        IPoint* p1 = curve->get_point(t-step);
        IPoint* p2 = curve->get_point(t);
        length += std::sqrt(std::pow((p2->get_x() - p1->get_x()),2)+std::pow((p2->get_y() - p1->get_y()),2));
    }
    return length;
}

float getCoeff::operator()(ICurve* curve, float target_length, float step)
{
    float length = 0.0f;
    for(float t = 0.0f+step; t <= 1.0f; t+=step)
    {
        IPoint* p1 = curve->get_point(t-step);
        IPoint* p2 = curve->get_point(t);
        length += std::sqrt(std::pow((p2->get_x() - p1->get_x()),2)+std::pow((p2->get_y() - p1->get_y()),2));
        if(length>=target_length)
        {
            return t+step;
        }
    }
    return -1.0f;
}

// Decorator

Fragment::Fragment(ICurve* curve, double t_start, double t_finish): curve(curve), t_start(t_start), t_finish(t_finish) {}
IPoint*  Fragment::get_point(double t)
{
    return curve->get_point(t_start+(t_finish-t_start)*t);
}


MoveTo::MoveTo(ICurve* curve, IPoint* point): curve(curve), point(point){}

IPoint* MoveTo::get_point(double t)
{
    IPoint* p = curve->get_point(t);
    
    if(t < EPS)
    {
        sdvig_x = p->get_x() - point->get_x();
        sdvig_y = p->get_y() - point->get_y();
        p->set_x(point->get_x());
        p->set_y(point->get_y());
    }
    else
    {
        p->set_x(p->get_x()- sdvig_x);
        p->set_y(p->get_y()- sdvig_y);
    }
    return p;
}

//DrawableCurve

DrawableCurve::DrawableCurve(ICurve* curve): curve(curve) {}
IPoint* DrawableCurve::get_point(double t)
{
    return curve->get_point(t);
}