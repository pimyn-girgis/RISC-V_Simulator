#ifndef FILEBUTTONMENU_H
#define FILEBUTTONMENU_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QLabel>

namespace Ui {
class fileButtonMenu;
}

class fileButtonMenu : public QWidget
{
    Q_OBJECT

public:
    explicit fileButtonMenu(QWidget *parent = nullptr, QPlainTextEdit* doc = nullptr);
    ~fileButtonMenu();
    QString          _fileName; ///AW: make a getter later
    bool       _newFile = true;

signals:
    void            file_opened(const QString &filename);


private slots:

    void       file_open_event();
    void on_saveButton_clicked();
    void on_openButton_clicked();


private:

    Ui::fileButtonMenu     *ui;
    QPlainTextEdit       *_doc;
    QFileDialog openedFileName;
    QPlainTextEdit* newFilePrompt = new QPlainTextEdit(nullptr);
protected:
    bool eventFilter(QObject* o, QEvent* e) override;
};

#endif // FILEBUTTONMENU_H
