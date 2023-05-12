#ifndef FILEBUTTONLIST_H
#define FILEBUTTONLIST_H

#include <QWidget>

namespace Ui {
class fileButtonList;
}

class fileButtonList : public QWidget
{
    Q_OBJECT

public:
    explicit fileButtonList(QWidget *parent = nullptr);
    ~fileButtonList();

private:
    Ui::fileButtonList *ui;
};

#endif // FILEBUTTONLIST_H
