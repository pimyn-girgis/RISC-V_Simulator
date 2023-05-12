#include "filebuttonlist.h"
#include "ui_filebuttonlist.h"

fileButtonList::fileButtonList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileButtonList)
{
    ui->setupUi(this);
}

fileButtonList::~fileButtonList()
{
    delete ui;
}
