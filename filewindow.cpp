#include "filewindow.h"
#include "ui_filewindow.h"

fileWindow::fileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fileWindow)
{
    ui->setupUi(this);
}

fileWindow::~fileWindow()
{
    delete ui;
}
