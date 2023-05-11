#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QPixmap>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPoint>
#include <QScreen>
#include <QPlainTextEdit>
#include <QCursor>
#include "highlighter.h"
#include "filebuttonmenu.h"
#include <QTextCursor>
#include "risc_srcs/riscv.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

    static void delay();

    bool eventFilter(QObject* obj, QEvent* event) override;

    void update_tables();

    void update_table_maps(QMap<size_t, QString>* memoryTable, QMap<size_t, QString>* registerTable);

    static QMap<size_t, QString>* convert_to_string_map(std::map<size_t, int> m);

    void update_init_write_files(fs::path* ir, fs::path* im,fs::path* wr, fs::path* wm);

    void set_plainText_doc(QString path);

private slots:
    void update_file_name_label(const QString& filename);

    void on_exitButton_clicked();

    void on_maximizeButton_clicked();

    void on_minimizeButton_clicked();

    void on_fileButton_clicked();

    void on_plainTextEdit_textChanged();

    void on_executeButton_clicked();

private:
    Ui::MainWin   *ui;
    QPoint   _prevPos;
    QSize   _prevSize;
    bool    _maximized = false;
    bool    _fileButtonMenuActive = false;
    bool    _disabledEditor = false;

    QMap<size_t, QString> _memoryBlock;
    QMap<size_t, QString> _registerBlock;

    riscv   RISC32;

    fs::path* initRegFile;
    fs::path* initMemFile;
    fs::path* writeRegFile;
    fs::path* writeMemFile;
    fs::path* programFile;


    void setupRiscV();
    void minimize();
    void setupEditor();

    fileButtonMenu* fbm;
    Highlighter *highlighter;

};
#endif // MAINWIN_H
