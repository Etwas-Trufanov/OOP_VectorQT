#include "vectorwindow.h"
#include "./ui_vectorwindow.h"

VectorWindow::VectorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VectorWindow)
{
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    currentOperation = Vectors::operations::MULTVALUE;
    setResultVectorVisible(true);
    setVectorVisible(false);
}

// Деструктор окна
VectorWindow::~VectorWindow()
{
    delete ui;
}

// Сокрытие второго вектора
// И скрыть поле ввода константы
// True - вектор видим, False - вектор скрыт
void VectorWindow::setVectorVisible(bool mode) {
    // Учитываем предыдущее состояние
    static auto vectorVisible = true;
    if (vectorVisible != mode) {
        ui->x_edit_2->clear();
        ui->y_edit_2->clear();
        ui->constEdit->clear();
    }
    ui->x_edit_2->setVisible(mode);
    ui->y_edit_2->setVisible(mode);
    ui->x_label_2->setVisible(mode);
    ui->y_label_2->setVisible(mode);
    ui->constEdit->setVisible(!mode);
    vectorVisible = mode;
}

void VectorWindow::setResultVectorVisible(bool mode) {
    ui->result_x->clear();
    ui->result_y->clear();
    ui->resultField->clear();
    ui->result_x->setVisible(mode);
    ui->result_y->setVisible(mode);
    ui->result_x_label->setVisible(mode);
    ui->result_y_label->setVisible(mode);
    ui->resultField->setVisible(!mode);
    ui->valueLabel->setVisible(!mode);
}

void VectorWindow::lockConstField(bool mode) {
    ui->constEdit->setEnabled(!mode);
}

bool VectorWindow::validateBaseVector() {
    bool okX = false;
    double xValue = ui->x_edit->text().toDouble(&okX);
    // Если ошибка:
    if (!okX) {
        ui->x_edit->setStyleSheet("background-color: red;");
        return false;
    }
    baseVector.set_x(xValue);
    ui->x_edit->setStyleSheet("");
    bool okY = false;
    double yValue = ui->y_edit->text().toDouble(&okY);
    // Если ошибка:
    if (!okY) {
        ui->y_edit->setStyleSheet("background-color: red;");
        return false;
    }
    baseVector.set_y(yValue);
    ui->y_edit->setStyleSheet("");
    return true;
}

bool VectorWindow::validateSecondVector() {
    bool okX = false;
    double xValue = ui->x_edit_2->text().toDouble(&okX);
    // Если ошибка:
    if (!okX) {
        ui->x_edit_2->setStyleSheet("background-color: red;");
        return false;
    }
    secondVector.set_x(xValue);
    ui->x_edit_2->setStyleSheet("");
    bool okY = false;
    double yValue = ui->y_edit_2->text().toDouble(&okY);
    // Если ошибка:
    if (!okY) {
        ui->y_edit_2->setStyleSheet("background-color: red;");
        return false;
    }
    secondVector.set_y(yValue);
    ui->y_edit_2->setStyleSheet("");
    return true;
}
bool VectorWindow::validateValue() {
    bool ok = false;
    double Value = ui->constEdit->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->constEdit->setStyleSheet("background-color: red;");
        return false;
    }
    value = Value;
    ui->constEdit->setStyleSheet("");
    return true;
}

// Обрабатываем ввод x в базовый вектор
void VectorWindow::on_x_edit_editingFinished() {
    calculate();
}


// Обрабатываем ввод y в базовый вектор
void VectorWindow::on_y_edit_editingFinished() {
    calculate();
}


// Обрабатываем ввод x во второй вектор
void VectorWindow::on_x_edit_2_editingFinished() {
    calculate();
}

// Обрабатываем ввод y во второй вектор
void VectorWindow::on_y_edit_2_editingFinished() {
    calculate();
}



// Обрабатываем ввод константы
void VectorWindow::on_constEdit_editingFinished() {
    calculate();
}


// Выбор операции
void VectorWindow::on_operation_currentIndexChanged(int index) {
    switch (index) {
        case 0: {
            // Текущая операция - умножение на значение (на скаляр)
            currentOperation = Vectors::operations::MULTVALUE;
            // Скрываем второй вектор
            setVectorVisible(false);
            // Результат - вектор
            setResultVectorVisible(true);
            // Включаем поле ввода
            lockConstField(false);
            break;
        }
        case 1: {
            currentOperation = Vectors::operations::MODULE;
            setVectorVisible(false);
            setResultVectorVisible(false);
            lockConstField(true);
            break;
        }
        case 2: {
            currentOperation = Vectors::operations::SUMM;
            setVectorVisible(true);
            setResultVectorVisible(true);
            break;
        }
        case 3: {
            currentOperation = Vectors::operations::SUBSTRACT;
            setVectorVisible(true);
            setResultVectorVisible(true);
            break;
        }
        case 4: {
            currentOperation = Vectors::operations::SCALAR;
            setVectorVisible(true);
            setResultVectorVisible(false);
            lockConstField(false);
            break;
        }
    }
    calculate();
}



void VectorWindow::calculate() {
    switch (currentOperation) {
    case Vectors::operations::MULTVALUE:
        if (validateBaseVector() and validateValue()) {
            Vectors::TVector tmp = baseVector.multScalar(value);
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::MODULE:
        if (validateBaseVector()) {
            double tmp = baseVector.module();
            ui->resultField->setText(QString::number(tmp));
        }
        break;
    case Vectors::operations::SUMM:
        if (validateBaseVector() and validateSecondVector()) {
            Vectors::TVector tmp = baseVector + secondVector;
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::SUBSTRACT:
        if (validateBaseVector() and validateSecondVector()) {
            Vectors::TVector tmp = baseVector - secondVector;
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::SCALAR:
        if (validateBaseVector() and validateSecondVector()) {
            double tmp = baseVector.scalarMult(secondVector);
            ui->resultField->setText(QString::number(tmp));
        }
        break;

    default:
        break;
    }
}

