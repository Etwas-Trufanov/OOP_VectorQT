/**
 * @file vectorlib.h
 * @brief Библиотека для работы с двумерными векторами
 *
 * Содержит шаблонный класс TVector для представления и обработки 2D-векторов
 * с поддержкой арифметических операций, скалярного произведения и нормализации.
 */

#ifndef VECTORLIB_H
#define VECTORLIB_H

#include <cmath>

namespace Vectors {

    /**
     * @enum operations
     * @brief Перечисление поддерживаемых векторных операций
     *
     * Используется для идентификации типа операции при расширении функционала.
     */
    enum operations {
        SCALAR,             ///< Скалярное произведение векторов (возвращает скаляр)
        MULTVALUE,          ///< Умножение вектора на скалярное значение
        SUMM,               ///< Покомпонентное сложение двух векторов
        SUBSTRACT,          ///< Покомпонентное вычитание двух векторов
        MODULE,             ///< Вычисление евклидовой длины (модуля) вектора
        NORMAL              ///< Нормализация вектора (приведение к единичной длине)
    };

    /**
     * @class TVector
     * @tparam T Тип данных для компонентов вектора (должен поддерживать арифметические операции)
     *
     * @brief Шаблонный класс для представления двумерного вектора на плоскости.
     *
     * Класс реализует математические операции над 2D-векторами:
     * - Арифметика: сложение, вычитание, умножение на скаляр
     * - Геометрия: вычисление длины, нормализация
     * - Алгебра: скалярное произведение
     *
     * @note Все методы являются константными (не модифицируют исходный объект),
     *       кроме сеттеров. Класс потокобезопасен для чтения.
     *
     * @warning При нормализации нулевого вектора может возникнуть деление на ноль.
     *          Рекомендуется проверять module() > 0 перед вызовом normalize().
     *
     * @example
     * @code
     * #include "vectorlib.h"
     * #include <iostream>
     *
     * int main() {
     *     using namespace Vectors;
     *
     *     // Создание векторов
     *     TVector<double> v1(3.0, 4.0);
     *     TVector<double> v2(1.0, 2.0);
     *
     *     // Сложение векторов
     *     auto v3 = v1 + v2;  // (4.0, 6.0)
     *
     *     // Скалярное произведение
     *     double dot = v1.scalarMult(v2);  // 3*1 + 4*2 = 11
     *
     *     // Длина вектора
     *     double len = v1.module();  // sqrt(9+16) = 5.0
     *
     *     // Нормализация
     *     auto v_norm = v1.normalize();  // (0.6, 0.8)
     *
     *     // Умножение на скаляр
     *     auto v_scaled = v1.multScalar(2.0);  // (6.0, 8.0)
     *
     *     std::cout << "Normalized: (" << v_norm.get_x() << ", "
     *               << v_norm.get_y() << ")\n";
     *     return 0;
     * }
     * @endcode
     */
    template<typename T>
    class TVector {
    protected:
        T x;  ///< X-компонента вектора (горизонтальная координата)
        T y;  ///< Y-компонента вектора (вертикальная координата)

    public:
        /**
         * @brief Конструктор по умолчанию
         *
         * Инициализирует вектор нулевыми значениями (0, 0).
         *
         * @post get_x() == 0 && get_y() == 0
         */
        TVector() : x(0), y(0) {}

        /**
         * @brief Параметризированный конструктор
         *
         * @param x_value Значение для X-компоненты вектора
         * @param y_value Значение для Y-компоненты вектора
         *
         * @post get_x() == x_value && get_y() == y_value
         *
         * @example
         * TVector<int> vec(10, -5);  // Вектор с координатами (10, -5)
         */
        TVector(T x_value, T y_value) : x(x_value), y(y_value) {}

        /**
         * @brief Геттер для X-компоненты
         * @return Константная ссылка на значение X-компоненты
         *
         * @note Метод не модифицирует объект (const-корректность)
         */
        T get_x() const {
            return x;
        }

        /**
         * @brief Геттер для Y-компоненты
         * @return Константная ссылка на значение Y-компоненты
         *
         * @note Метод не модифицирует объект (const-корректность)
         */
        T get_y() const {
            return y;
        }

        /**
         * @brief Сеттер для X-компоненты
         * @param newX Новое значение для X-компоненты
         *
         * @post get_x() == newX
         */
        void set_x(const T newX) {
            x = newX;
        }

        /**
         * @brief Сеттер для Y-компоненты
         * @param newY Новое значение для Y-компоненты
         *
         * @post get_y() == newY
         */
        void set_y(const T newY) {
            y = newY;
        }

        /**
         * @brief Оператор сложения векторов
         *
         * Выполняет покомпонентное сложение: (x1+x2, y1+y2)
         *
         * @param other Ссылка на второй вектор для сложения
         * @return Новый объект TVector, результат сложения
         *
         * @note Оператор не модифицирует исходные объекты
         *
         * @example
         * TVector<double> a(1, 2), b(3, 4);
         * auto c = a + b;  // c = (4, 6)
         */
        TVector operator+(const TVector &other) const {
            return TVector(x + other.x, y + other.y);
        }

        /**
         * @brief Оператор вычитания векторов
         *
         * Выполняет покомпонентное вычитание: (x1-x2, y1-y2)
         *
         * @param other Ссылка на второй вектор для вычитания
         * @return Новый объект TVector, результат вычитания
         *
         * @note Оператор не модифицирует исходные объекты
         *
         * @example
         * TVector<double> a(5, 7), b(2, 3);
         * auto c = a - b;  // c = (3, 4)
         */
        TVector operator-(const TVector &other) const {
            return TVector(x - other.x, y - other.y);
        }

        /**
         * @brief Вычисление скалярного произведения векторов
         *
         * Формула: x₁×x₂ + y₁×y₂
         *
         * @param other Ссылка на второй вектор
         * @return Скалярное значение типа T (результат произведения)
         *
         * @note Возвращаемое значение может быть отрицательным,
         *       нулевым (перпендикулярные векторы) или положительным
         *
         * @example
         * TVector<double> a(2, 3), b(4, -1);
         * double result = a.scalarMult(b);  // 2*4 + 3*(-1) = 5
         */
        T scalarMult(const TVector &other) const {
            return x * other.x + y * other.y;
        }

        /**
         * @brief Умножение вектора на скалярное значение
         *
         * Выполняет масштабирование вектора: (x×value, y×value)
         *
         * @param value Скалярный множитель типа T
         * @return Новый объект TVector с масштабированными компонентами
         *
         * @note При value < 0 направление вектора меняется на противоположное
         *
         * @example
         * TVector<double> v(3, 4);
         * auto scaled = v.multScalar(2.0);  // (6.0, 8.0)
         */
        TVector multScalar(T const value) const {
            return TVector(x * value, y * value);
        }

        /**
         * @brief Вычисление длины (модуля) вектора
         *
         * Формула: √(x² + y²) — евклидова норма
         *
         * @return Неотрицательное значение длины типа T
         *
         * @note Для целочисленных типов T результат может быть усечён.
         *       Рекомендуется использовать floating-point типы (float/double)
         *       для точных вычислений.
         *
         * @example
         * TVector<double> v(3, 4);
         * double len = v.module();  // 5.0
         */
        T module() const {
            return sqrt((y*y)+(x*x));
        }

        /**
         * @brief Нормализация вектора (приведение к единичной длине)
         *
         * Возвращает вектор того же направления с длиной, равной 1.
         * Формула: (x/|v|, y/|v|), где |v| — длина вектора
         *
         * @return Новый объект TVector с длиной ≈ 1.0
         *
         * @warning Если module() == 0, произойдёт деление на ноль.
         *          Перед вызовом проверьте: if (vec.module() > 0) ...
         *
         * @note Возвращаемый вектор сохраняет направление исходного
         *
         * @example
         * TVector<double> v(3, 4);
         * auto normalized = v.normalize();  // (0.6, 0.8)
         * // Проверка: normalized.module() ≈ 1.0
         */
        TVector normalize() const {
            double tmpModule = module();
            return TVector(x/tmpModule, y/tmpModule);
        }
    };
}

#endif // VECTORLIB_H
