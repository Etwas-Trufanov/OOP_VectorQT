#include "vectorwindow.h"
#include "./ui_vectorwindow.h"

VectorWindow::VectorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VectorWindow)
{
    ui->setupUi(this);
    hideSecondVector();
}

VectorWindow::~VectorWindow()
{
    delete ui;
}

void VectorWindow::hideSecondVector() {
    ui->x_edit_2->hide();
    ui->y_edit_2->hide();
    ui->x_label_2->hide();
    ui->y_label_2->hide();

    ui->constEdit->show();
}

void VectorWindow::showSecondVector() {
    ui->x_edit_2->show();
    ui->y_edit_2->show();
    ui->x_label_2->show();
    ui->y_label_2->show();

    ui->constEdit->hide();
}

// Обрабатываем ввод в базовый вектор
void VectorWindow::on_x_edit_editingFinished() {
    bool ok = false;
    double xValue = ui->x_edit->text().toDouble(&ok);
    if (!ok) {
        ui->x_edit->setStyleSheet("background-color: red;");
        return;
    }
    vectorbase.set_x(xValue);
    ui->x_edit->setStyleSheet("");
}


void VectorWindow::on_y_edit_editingFinished() {
    bool ok = false;
    double yValue = ui->y_edit->text().toDouble(&ok);
    if (!ok) {
        ui->y_edit->setStyleSheet("background-color: red;");
        return;
    }
    vectorbase.set_y(yValue);
    ui->y_edit->setStyleSheet("");
}


void VectorWindow::on_x_edit_2_editingFinished() {
    bool ok = false;
    double xValue = ui->x_edit_2->text().toDouble(&ok);
    if (!ok) {
        ui->x_edit_2->setStyleSheet("background-color: red;");
        return;
    }
    vectorsecond.set_x(xValue);
    ui->x_edit_2->setStyleSheet("");
}

void VectorWindow::on_y_edit_2_editingFinished() {
    bool ok = false;
    double yValue = ui->y_edit_2->text().toDouble(&ok);
    if (!ok) {
        ui->y_edit_2->setStyleSheet("background-color: red;");
        return;
    }
    vectorsecond.set_y(yValue);
    ui->y_edit_2->setStyleSheet("");
}



void VectorWindow::on_constEdit_editingFinished() {
    bool ok = false;
    double Value = ui->constEdit->text().toDouble(&ok);
    if (!ok) {
        ui->constEdit->setStyleSheet("background-color: red;");
        return;
    }
    additonalValue = Value;
    ui->constEdit->setStyleSheet("");
}



void VectorWindow::on_operation_currentIndexChanged(int index)
{
    switch (index) {
        case 0: {
            ui->constEdit->setEnabled(true);
            hideSecondVector();
            break;
        }
        case 1: {
            hideSecondVector();
            ui->constEdit->setEnabled(false);
            break;
        }
        case 2: {
            ui->constEdit->setEnabled(true);
            showSecondVector();
            break;
        }
        case 3: {
            ui->constEdit->setEnabled(true);
            showSecondVector();
            break;
        }
        case 4: {
            ui->constEdit->setEnabled(true);
            showSecondVector();
            break;
        }
    }

    ui->y_edit_3->setText(QString::number(index));
}

