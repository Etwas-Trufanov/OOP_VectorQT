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
    showResultVector();
    hideSecondVector(false);
}

// Деструктор окна
VectorWindow::~VectorWindow()
{
    delete ui;
}

// Сокрытие второго вектора
// И скрыть поле ввода константы
void VectorWindow::hideSecondVector(bool disableConstEdit) {
    ui->x_edit_2->clear();
    ui->y_edit_2->clear();
    ui->x_edit_2->hide();
    ui->y_edit_2->hide();
    ui->x_label_2->hide();
    ui->y_label_2->hide();

    ui->constEdit->show();
}

// Показать второй вектор
// И скрыть поле ввода константы
void VectorWindow::showSecondVector() {
    ui->constEdit->clear();
    ui->x_edit_2->show();
    ui->y_edit_2->show();
    ui->x_label_2->show();
    ui->y_label_2->show();

    ui->constEdit->hide();
}

void VectorWindow::showResultOneField() {
    ui->valueLabel->show();
    ui->result_x->hide();
    ui->result_x_label->hide();
    ui->result_y->hide();
    ui->result_y_label->hide();

    ui->resultField->show();
}

void VectorWindow::showResultVector() {
    ui->valueLabel->hide();
    ui->result_x->show();
    ui->result_x_label->show();
    ui->result_y->show();
    ui->result_y_label->show();

    ui->resultField->hide();
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
            hideSecondVector(false);
            // Результат - вектор
            showResultVector();
            break;
        }
        case 1: {
            currentOperation = Vectors::operations::MODULE;
            hideSecondVector(true);
            showResultOneField();
            ui->constEdit->setDisabled(true);
            break;
        }
        case 2: {
            currentOperation = Vectors::operations::SUMM;
            showSecondVector();
            showResultVector();
            break;
        }
        case 3: {
            currentOperation = Vectors::operations::SUBSTRACT;
            showSecondVector();
            showResultVector();
            break;
        }
        case 4: {
            currentOperation = Vectors::operations::SCALAR;
            showSecondVector();
            showResultOneField();
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

