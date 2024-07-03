#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rectangle_clicked();
    void on_ellipse_clicked();
    void on_triangle_clicked();
    void on_connection_clicked();
    void on_move_clicked();
    void on_delete_2_clicked();
    void on_save_clicked();
    void on_changeOutlineColorButton_clicked();
    void on_changeFillColorButton_clicked();


private:
    Ui::MainWindow *ui;
    DrawingArea *drawingArea;
};

#endif // MAINWINDOW_H
