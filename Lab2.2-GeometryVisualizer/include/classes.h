#pragma once
#include "graphical_interface.h"

class IPoint
{
public:
    virtual double get_x() const = 0;
    virtual double get_y() const = 0;
    virtual void set_x(double) = 0;
    virtual void set_y(double) = 0;
};

class ICurve
{
public:
    virtual IPoint* get_point(double t) = 0;
};

class IDrawer
{
protected:
    sf::RenderTexture* picture;
public:
    IDrawer(sf::RenderTexture*);
    virtual void draw_beginning(IPoint*) = 0;
    virtual void draw_segment(IPoint*, IPoint*) = 0;
    virtual void draw_ending(IPoint*, IPoint*) = 0;
};

class IDrawable
{
public:
    virtual void draw(IDrawer*, IDrawer*, IDrawer*) = 0; // Realize Weak brige (params: object to draw curves)
};

class Point : public IPoint
{
private:
    double x;
    double y;
public:
    Point(double x_value, double y_value);
    double get_x() const override;
    double get_y() const override;
    void set_x(double value) override;
    void set_y(double value) override;
};

class ACurve : public ICurve
{
protected:
    IPoint* a;
    IPoint* b;
public:
    ACurve(IPoint* a_ptr, IPoint* b_ptr);
};

class Line : public ACurve
{
public:
    Line(IPoint* a_ptr, IPoint* b_ptr);
    IPoint* get_point(double t) override;
};

class Bezier : public ACurve
{
private:
    IPoint* c;
    IPoint* d;
public:
    Bezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr);
    IPoint* get_point(double t) override;
};

class VisualCurve : public ICurve, public IDrawable
{
public:
    void draw(IDrawer*, IDrawer*, IDrawer*) override;
};

class VisualLine : public VisualCurve, public Line
{
public:
    VisualLine(IPoint* a_ptr, IPoint* b_ptr);
    IPoint* get_point(double t) override;
};

class VisualBezier : public VisualCurve, public Bezier
{
public:
    VisualBezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr);
    IPoint* get_point(double t) override;
};

class DrawerLucky : public IDrawer
{
public:
    DrawerLucky(sf::RenderTexture* picture);
    void draw_beginning(IPoint*) override;
    void draw_segment(IPoint*, IPoint*) override;
    void draw_ending(IPoint*, IPoint*) override;
};

class DrawerUnlucky : public IDrawer
{
private:
    std::size_t periodicity;
    std::size_t current_per;
public:
    DrawerUnlucky(sf::RenderTexture* picture, std::size_t periodicity);
    void draw_beginning(IPoint*) override;
    void draw_segment(IPoint*, IPoint*) override;
    void draw_ending(IPoint*, IPoint*) override;
};