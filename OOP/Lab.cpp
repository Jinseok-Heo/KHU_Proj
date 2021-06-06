#include "Lab.h"
double Shape::PI = 3.141592;
double Shape::getPI() {
    return PI;
}
void Shape::setArea(const double &in_area) {
    area = in_area;
}
double Shape::getArea() const {
    return area;
}

void ThreeDimensional::setVolume(const double& v) {
    volume = v;
} 
double ThreeDimensional::getVolume() const {
    return volume;
}

void Triangle::calculateArea() {
    setArea(width * height / 2);
}
void Triangle::print() {
    calculateArea();
    std::cout << "Triangle Information\n";
    std::cout << "Width: " << width << '\n';
    std::cout << "Height: " << height << '\n';
    std::cout << "Area: " << getArea() << '\n';
}

void Rectangle::calculateArea() {
    setArea(width * height);
}
void Rectangle::print() {
    calculateArea();
    std::cout << "Rectangle Information\n";
    std::cout << "Width: " << width << '\n';
    std::cout << "Height: " << height << '\n';
    std::cout << "Area: " << getArea() << '\n';
}

void Circle::calculateArea() {
    double out_area = getPI() * radius * radius;
    setArea(out_area);
}
void Circle::print() {
    calculateArea();
    std::cout << "Circle Information\n";
    std::cout << "Radius: " << radius << '\n';
    std::cout << "Area: " << getArea() << '\n';
}

void Cube::calculateArea() {
    setArea(2 * (width * depth + depth * height + height * width));
}
void Cube::calculateVolume() {
    setVolume(width * depth * height);
}
void Cube::print() {
    calculateArea();
    calculateVolume();
    std::cout << "Cube Information\n";
    std::cout << "Width: " << width << '\n';
    std::cout << "Depth: " << depth << '\n';
    std::cout << "Height: " << height << '\n';
    std::cout << "Area: " << getArea() << '\n';
    std::cout << "Volume: " << getVolume() << '\n';
}

void Sphere::calculateArea() {
    double out_area = getPI() * 4 * radius * radius;
    setArea(out_area);
}
void Sphere::calculateVolume() {
    double out_volume = getPI() * 4 * radius * radius * radius / 3;
    setVolume(out_volume);
}
void Sphere::print() {
    calculateArea();
    calculateVolume();
    std::cout << "Sphere Information\n";
    std::cout << "Radius: " << radius << '\n';
    std::cout << "Area: " << getArea() << '\n';
    std::cout << "Volume: " << getVolume() << '\n';
}