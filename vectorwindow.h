#ifndef VECTORWINDOW_H
#define VECTORWINDOW_H

#include "vectorlib.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class VectorWindow;
}
QT_END_NAMESPACE

class VectorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VectorWindow(QWidget *parent = nullptr);
    ~VectorWindow() override;

private slots:
    void on_x_edit_editingFinished();

    void on_y_edit_editingFinished();

    void on_x_edit_2_editingFinished();

    void on_y_edit_2_editingFinished();

    void on_constEdit_editingFinished();

private:
    Ui::VectorWindow *ui;

    TVector vectorbase;

    TVector vectorsecond;

    double additonalValue;

    QPalette stdpalette;

    QPalette redpalette;
};
#endif // VECTORWINDOW_H
