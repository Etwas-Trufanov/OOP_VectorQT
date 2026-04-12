#include <QTest>
#include "../vectorlib.h"

class VectorTest : public QObject
{
    Q_OBJECT

private slots:
    void test_constructor();
    void test_getters_setters();
    void test_addition();
    void test_subtraction();
    void test_scalar_product();
    void test_mult_by_value();
    void test_module();
    void test_normalize();
};

// Проверяем конструкторы: по умолчанию и с параметрами
void VectorTest::test_constructor() {
    Vectors::TVector<double> v1;
    QCOMPARE(v1.get_x(), 0.0);
    QCOMPARE(v1.get_y(), 0.0);

    Vectors::TVector<double> v2(3.0, 4.0);
    QCOMPARE(v2.get_x(), 3.0);
    QCOMPARE(v2.get_y(), 4.0);
}

// Проверяем, что сеттеры и геттеры работают корректно
void VectorTest::test_getters_setters() {
    Vectors::TVector<double> v;
    v.set_x(5.0);
    v.set_y(-2.0);

    QCOMPARE(v.get_x(), 5.0);
    QCOMPARE(v.get_y(), -2.0);
}

// Проверяем оператор сложения векторов
void VectorTest::test_addition() {
    Vectors::TVector<double> v1(1.0, 2.0);
    Vectors::TVector<double> v2(3.0, 4.0);

    auto result = v1 + v2;

    QCOMPARE(result.get_x(), 4.0);
    QCOMPARE(result.get_y(), 6.0);
}

// Проверяем оператор вычитания векторов
void VectorTest::test_subtraction() {
    Vectors::TVector<double> v1(10.0, 5.0);
    Vectors::TVector<double> v2(3.0, 2.0);

    auto result = v1 - v2;

    QCOMPARE(result.get_x(), 7.0);
    QCOMPARE(result.get_y(), 3.0);
}

// Проверяем скалярное произведение двух векторов
void VectorTest::test_scalar_product() {
    Vectors::TVector<double> v1(2.0, 3.0);
    Vectors::TVector<double> v2(4.0, -1.0);

    double result = v1.scalarMult(v2);

    QCOMPARE(result, 5.0);  // 2*4 + 3*(-1) = 5
}

// Проверяем умножение вектора на скаляр
void VectorTest::test_mult_by_value() {
    Vectors::TVector<double> v(2.0, -3.0);

    auto result = v.multScalar(2.0);

    QCOMPARE(result.get_x(), 4.0);
    QCOMPARE(result.get_y(), -6.0);
}

// Проверяем вычисление длины вектора (теорема Пифагора)
void VectorTest::test_module() {
    Vectors::TVector<double> v(3.0, 4.0);

    double len = v.module();

    QVERIFY(qFuzzyCompare(len, 5.0));
}

// Проверяем нормализацию, длина должна стать 1.0
void VectorTest::test_normalize() {
    Vectors::TVector<double> v(3.0, 4.0);

    auto norm = v.normalize();

    QVERIFY(qFuzzyCompare(norm.module(), 1.0));
    QVERIFY(qFuzzyCompare(norm.get_x(), 0.6));
    QVERIFY(qFuzzyCompare(norm.get_y(), 0.8));
}

QTEST_APPLESS_MAIN(VectorTest)

#include "tst_vectortest.moc"