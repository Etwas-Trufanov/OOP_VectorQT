#ifndef VECTORLIB_H
#define VECTORLIB_H

#include <cmath>

namespace Vectors {
    // Виды операций
    enum operations {
        SCALAR,             // Скалярное произведение векторов
        MULTVALUE,          // Умножение на скаляр
        SUMM,                // Сумма векторов
        SUBSTRACT,             // Вычитание векторов
        MODULE,             // Модуль (длина вектора)
        NORMAL              // Нормализация (приведение к длине 1)
    };

    // Шаблон класса
    template<typename T>
    class TVector {
    protected:
        T x;    // X значение вектора
        T y;    // Y значение вектора

    public:
        // Конструктор
        TVector() : x(0), y(0) {}
        // Конструктор с параметрами
        TVector(T x, T y) : x(x), y(y) {}

        // Геттеры
        T get_x() const {
            return x;
        }
        T get_y() const {
            return y;
        }

        // Сеттеры
        void set_x(const T newX) {
            x = newX;
        }
        void set_y(const T newY) {
            y = newY;
        }

        // Сложение векторов
        // other второй вектор
        TVector operator+(const TVector &other) const {
            return TVector(x + other.x, y + other.y);
        }
        // Вычитание векторов
        // other второй вектор
        TVector operator-(const TVector &other) const {
            return TVector(x - other.x, y - other.y);
        }

        // Скалярное произведение двух векторов
        // other второй вектор
        T scalarMult(const TVector &other) const {
            return x * other.x + y * other.y;
        }

        // Умножение вектора на скалярное число
        // value - число
        TVector multScalar(T const value) const {
            return TVector(x * value, y * value);
        }

        // Длина вектора
        T module() const {
            return sqrt((y*y)+(x*x));
        }

        // Нормализация вектора (приведение к длине 1, без потери направления)
        TVector normalize() const {
            double tmpModule = module();
            return TVector(x/tmpModule, y/tmpModule);
        }
    };
}




#endif // VECTORLIB_H