#ifndef _LAB__H
#define _LAB__H
#include <iostream>

class Shape {
private:
    static double PI;
    double area;

public:
    Shape() {}
    double getPI();
    void setArea(const double& in_area);
    double getArea() const;
    virtual void calculateArea() = 0;
    virtual void print() = 0;
};

class TwoDimensional: public Shape {
protected:
    double width;
    double height;
    double radius;
public:
    TwoDimensional(const double& w, const double& h, const double& r)
        : width(w), height(h), radius(r) {}
    virtual void calculateArea() = 0;
    virtual void print() = 0;
};

class ThreeDimensional: public Shape {
private:
    double volume;
protected:
    double width;
    double height;
    double depth;
    double radius;
public:
    ThreeDimensional(const double& w, const double& h, const double& d, const double& r)
        : width(w), height(h), depth(d), radius(r) {}
    void setVolume(const double& v);
    double getVolume() const;
    virtual void calculateArea() = 0;
    virtual void calculateVolume() = 0;
    virtual void print() = 0;
};

class Triangle: public TwoDimensional {
private:
    virtual void calculateArea() override;

public:
    Triangle(const double& w, const double& h): TwoDimensional(w, h, 0.0) {}
    virtual void print() override;
};

class Rectangle: public TwoDimensional {
private:
    virtual void calculateArea() override;
public:
    Rectangle(const double &w, const double &h): TwoDimensional(w, h, 0.0) {}
    virtual void print() override;
};

class Circle: public TwoDimensional {
private:
    virtual void calculateArea() override;
public:
    Circle(const double &r): TwoDimensional(0.0, 0.0, r) {}
    virtual void print() override;
};

class Cube: public ThreeDimensional {
private:
    virtual void calculateArea() override;
    virtual void calculateVolume() override;
public:
    Cube(const double& w, const double& d, const double& h)
        : ThreeDimensional(w, d, h, 0.0) {}
    virtual void print() override;
};

class Sphere: public ThreeDimensional {
private:
    virtual void calculateArea() override;
    virtual void calculateVolume() override;
public:
    Sphere(const double &r)
        : ThreeDimensional(0.0, 0.0, 0.0, r) {}
    virtual void print() override;
};

#endif