#include "vectorlib.h"

// Конструктор по умолчанию
TVector::TVector() : x(0), y(0) {}

// Конструктор с параметрами
TVector::TVector(double x, double y) : x(x), y(y) {}

// Геттер X
double TVector::get_x() const {
    return x;
}

// Геттер Y
double TVector::get_y() const {
    return y;
}

// Сложение векторов
TVector TVector::operator+(const TVector &other) const {
    return TVector(x + other.x, y + other.y);
}

// Вычитание векторов
TVector TVector::operator-(const TVector &other) const {
    return TVector(x - other.x, y - other.y);
}

// Скалярное произведение двух векторов
double TVector::scalar(const TVector &other) const {
    return x * other.x + y * other.y;
}

// Умножение вектора на скалярное число
TVector TVector::multValue(double value) const {
    return TVector(x * value, y * value);
}

// Векторное произведение (для 2D возвращается Z-компонента результата)
double TVector::vectorMult(const TVector &other) const {
    // Для 2D векторов векторное произведение = |i*(x1*y2 - x2*y1)|
    return x * other.y - y * other.x;
}