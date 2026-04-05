#include "vectorwindow.h"
#include "./ui_vectorwindow.h"

VectorWindow::VectorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VectorWindow)
{
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    baseVectorXGood = false;
    baseVectorYGood = false;
    secondVectorXGood = false;
    secondVectorYGood = false;
    valueIsGood = false;
    currentOperation = Vectors::operations::MULTVALUE;
    showResultVector();
    hideSecondVector();
}

// Деструктор окна
VectorWindow::~VectorWindow()
{
    delete ui;
}

// Сокрытие второго вектора
// И скрыть поле ввода константы
void VectorWindow::hideSecondVector() {
    ui->x_edit_2->hide();
    ui->y_edit_2->hide();
    ui->x_label_2->hide();
    ui->y_label_2->hide();

    ui->constEdit->show();
}

// Показать второй вектор
// И скрыть поле ввода константы
void VectorWindow::showSecondVector() {
    ui->x_edit_2->show();
    ui->y_edit_2->show();
    ui->x_label_2->show();
    ui->y_label_2->show();

    ui->constEdit->hide();
}

void VectorWindow::showResultOneField() {
    ui->result_x->hide();
    ui->result_x_label->hide();
    ui->result_y->hide();
    ui->result_y_label->hide();

    ui->resultField->show();
}

void VectorWindow::showResultVector() {
    ui->result_x->show();
    ui->result_x_label->show();
    ui->result_y->show();
    ui->result_y_label->show();

    ui->resultField->hide();
}

// Обрабатываем ввод x в базовый вектор
void VectorWindow::on_x_edit_editingFinished() {
    bool ok = false;
    double xValue = ui->x_edit->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->x_edit->setStyleSheet("background-color: red;");
        return;
    }
    baseVectorXGood = ok;
    baseVector.set_x(xValue);
    ui->x_edit->setStyleSheet("");
    calculate();
}


// Обрабатываем ввод y в базовый вектор
void VectorWindow::on_y_edit_editingFinished() {
    bool ok = false;
    double yValue = ui->y_edit->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->y_edit->setStyleSheet("background-color: red;");
        return;
    }
    baseVectorYGood = ok;
    baseVector.set_y(yValue);
    ui->y_edit->setStyleSheet("");
    calculate();
}


// Обрабатываем ввод x во второй вектор
void VectorWindow::on_x_edit_2_editingFinished() {
    bool ok = false;
    double xValue = ui->x_edit_2->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->x_edit_2->setStyleSheet("background-color: red;");
        return;
    }
    secondVectorXGood = ok;
    secondVector.set_x(xValue);
    ui->x_edit_2->setStyleSheet("");
    calculate();
}

// Обрабатываем ввод y во второй вектор
void VectorWindow::on_y_edit_2_editingFinished() {
    bool ok = false;
    double yValue = ui->y_edit_2->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->y_edit_2->setStyleSheet("background-color: red;");
        return;
    }
    secondVectorYGood = ok;
    secondVector.set_y(yValue);
    ui->y_edit_2->setStyleSheet("");
    calculate();
}



// Обрабатываем ввод константы
void VectorWindow::on_constEdit_editingFinished() {
    bool ok = false;
    double Value = ui->constEdit->text().toDouble(&ok);
    // Если ошибка:
    if (!ok) {
        ui->constEdit->setStyleSheet("background-color: red;");
        return;
    }
    valueIsGood = ok;
    value = Value;
    ui->constEdit->setStyleSheet("");
    calculate();
}


// Выбор операции
void VectorWindow::on_operation_currentIndexChanged(int index) {
    switch (index) {
        case 0: {
            currentOperation = Vectors::operations::MULTVALUE;
            hideSecondVector();
            showResultVector();
            break;
        }
        case 1: {
            hideSecondVector();
            currentOperation = Vectors::operations::MODULE;
            showResultOneField();
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
        if (baseVectorXGood and baseVectorYGood and valueIsGood) {
            Vectors::TVector tmp = baseVector.multScalar(value);
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::MODULE:
        if (baseVectorXGood and baseVectorYGood) {
            double tmp = baseVector.module();
            ui->resultField->setText(QString::number(tmp));
        }
        break;
    case Vectors::operations::SUMM:
        if (baseVectorXGood and baseVectorYGood and secondVectorXGood and secondVectorYGood) {
            Vectors::TVector tmp = baseVector + secondVector;
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::SUBSTRACT:
        if (baseVectorXGood and baseVectorYGood and secondVectorXGood and secondVectorYGood) {
            Vectors::TVector tmp = baseVector - secondVector;
            ui->result_x->setText(QString::number(tmp.get_x()));
            ui->result_y->setText(QString::number(tmp.get_y()));
        }
        break;
    case Vectors::operations::SCALAR:
        if (baseVectorXGood and baseVectorYGood and secondVectorXGood and secondVectorYGood) {
            double tmp = baseVector.scalarMult(secondVector);
            ui->resultField->setText(QString::number(tmp));
        }
        break;

    default:
        break;
    }
}

