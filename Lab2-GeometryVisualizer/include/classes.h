#pragma once

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

class IDrawable
{
public:
    virtual void draw()=0;
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

};

class VisualLine : public VisualCurve, public Line
{
public:
    VisualLine(IPoint* a_ptr, IPoint* b_ptr);
    void draw() override;
};

class VisualBezier : public VisualCurve, public Bezier
{
public:
    VisualBezier(IPoint* a_ptr, IPoint* c_ptr, IPoint* d_ptr, IPoint* b_ptr);
    void draw() override;
};