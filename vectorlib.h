#ifndef VECTORLIB_H
#define VECTORLIB_H

class TVector {
protected:
    double x;
    double y;

public:
    // Конструкторы
    TVector();
    TVector(double x, double y);

    // Геттеры
    double get_x() const;
    double get_y() const;

    // Сеттеры
    void set_x(const double newX) {
        x = newX;
    }

    // Сеттеры
    void set_y(const double newY) {
        x = newY;
    }

    // Операторы сложения и вычитания
    TVector operator+(const TVector &other) const;
    TVector operator-(const TVector &other) const;

    // Скалярное произведение
    double scalar(const TVector &other) const;

    // Умножение вектора на число
    TVector multValue(double value) const;

    // Векторное произведение (для 2D возвращает Z-компонент)
    double vectorMult(const TVector &other) const;
};

#endif // VECTORLIB_H