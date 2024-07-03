#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawingArea = new DrawingArea(this);
    drawingArea->setStyleSheet("border: 3px solid black;");
    ui->verticalLayout->addWidget(drawingArea);

    connect(ui->changeOutlineColorButton, &QPushButton::clicked, this, &MainWindow::on_changeOutlineColorButton_clicked);
    connect(ui->changeFillColorButton, &QPushButton::clicked, this, &MainWindow::on_changeFillColorButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rectangle_clicked()
{
    drawingArea->setCurrentMode("Rectangle");
}

void MainWindow::on_ellipse_clicked()
{
    drawingArea->setCurrentMode("Ellipse");
}

void MainWindow::on_triangle_clicked()
{
    drawingArea->setCurrentMode("Triangle");
}

void MainWindow::on_connection_clicked()
{
    drawingArea->setCurrentMode("Connection");
}

void MainWindow::on_move_clicked()
{
    drawingArea->setCurrentMode("");
    drawingArea->setMoving(true);
}

void MainWindow::on_delete_2_clicked()
{
    drawingArea->setCurrentMode("");
    drawingArea->setDeleting(true);
}

void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Drawing"), "", tr("Images (*.jpg *.png)"));
    if (!fileName.isEmpty()) {
        drawingArea->saveToFile(fileName);
    }
}

void MainWindow::on_changeOutlineColorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose outline color");
    if (color.isValid()) {
        drawingArea->setOutlineColor(color);
    }
}

void MainWindow::on_changeFillColorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose fill color");
    if (color.isValid()) {
        drawingArea->setFillColor(color);
    }
}
