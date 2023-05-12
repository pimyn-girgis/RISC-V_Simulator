#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>

namespace Ui {
class fileWindow;
}

class fileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileWindow(QWidget *parent = nullptr);
    ~fileWindow();

private:
    Ui::fileWindow *ui;
};

#endif // FILEWINDOW_H
