#include "vectorwindow.h"
#include "./ui_vectorwindow.h"

VectorWindow::VectorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VectorWindow)
{
    ui->setupUi(this);
    // ui->secondVector->
    stdpalette = ui->x_edit->palette();
    redpalette = ui->x_edit->palette();
    redpalette.setColor(QPalette::Base, Qt::red);
    ui->x_edit->setAutoFillBackground(false);
}

VectorWindow::~VectorWindow()
{
    delete ui;
}

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


void VectorWindow::on_x_edit_2_editingFinished()
{

}


void VectorWindow::on_y_edit_2_editingFinished()
{

}


void VectorWindow::on_constEdit_editingFinished()
{

}

