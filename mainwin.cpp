#include "mainwin.h"
#include "ui_mainwin.h"

#include <QThread>
#include <QStandardItem>
#include "mapmodel.h"
#include <filesystem>
#include <map>

#define fs std::filesystem

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->setupUi(this);
    setupEditor();

    /// AW: we pass our plainTextEdit to it so we can save the written file
    fbm = new fileButtonMenu(nullptr, ui->plainTextEdit);
    fbm->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(fbm, &fileButtonMenu::file_opened, this, &MainWin::update_file_name_label);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->registerView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(false);

    ui->registerView->verticalHeader()->setVisible(false);
    ui->registerView->horizontalHeader()->setVisible(false);

    initRegFile = new fs::path("D:/academic/AUC/Spring 2023/RISC-V_Simulator/register_init.txt");
    initMemFile = new fs::path("D:/academic/AUC/Spring 2023/RISC-V_Simulator/memory_init.txt");
    writeRegFile = new fs::path("D:/academic/AUC/Spring 2023/RISC-V_Simulator/register_write.txt");
    writeMemFile = new fs::path("D:/academic/AUC/Spring 2023/RISC-V_Simulator/memory_write.txt");
    programFile = new fs::path("D:/academic/AUC/Spring 2023/RISC-V_Simulator/program.txt");


    std::string programFileStr = fbm->_fileName.QString::toStdString();

    RISC32.read_program(*programFile, initMemFile, writeMemFile, initRegFile, writeRegFile);

    set_plainText_doc((QString::fromStdString((programFile->fs::path::string()))));

    setupRiscV();
    update_tables();
}

void MainWin::set_plainText_doc(QString path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->plainTextEdit->setPlainText(file.readAll());

}

void MainWin::update_init_write_files(fs::path* ir, fs::path* im,fs::path* wr, fs::path* wm)
{
    initRegFile = ir;
    initMemFile = im;
    writeRegFile = wr;
    writeMemFile = wm;
}

void MainWin::update_table_maps(QMap<size_t, QString>* memoryTable, QMap<size_t, QString>* registerTable)
{
    _memoryBlock = *memoryTable;
    _registerBlock = *registerTable;
}

void MainWin::update_tables()
{
    ui->registerView->reset();
    ui->tableView->reset();


    MapModel* memoryMapModel = new MapModel();
    memoryMapModel->setMap(&_memoryBlock);
    ui->tableView->setModel(memoryMapModel);

    MapModel* registerMapModel = new MapModel();
    registerMapModel->setMap(&_registerBlock);
    ui->registerView->setModel(registerMapModel);


}


///AW: this is used for syntax highlighting, links the textedit document to our highlighter
void MainWin::setupEditor()
{

    highlighter = new Highlighter(ui->plainTextEdit->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->plainTextEdit->setPlainText(file.readAll());


}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::update_file_name_label(const QString& filename)
{
    ui->fileNameLabel->setText(filename);
}

void MainWin::on_exitButton_clicked()
{
    fbm->close();
    this->close();
}

QMap<size_t, QString>* MainWin::convert_to_string_map(std::map<size_t, int> m)
{
    QMap<size_t, QString>* ret = new QMap<size_t, QString>();
    char *output = new char[11];

    for(auto i : m)
    {
        sprintf(output, "0x%.8x", i.second);
        ret->insert(i.first, QString::fromStdString(output));
    }

    delete[] output;

    return ret;
}

void MainWin::setupRiscV()
{


    memory riscReg = RISC32.get_reg();
    memory riscMem = RISC32.get_mem();
    int riscPc = RISC32.get_pc();

    QMap<size_t, QString>* riscRegOut = new QMap<size_t, QString>();
    QMap<size_t, QString>* riscMemOut = new QMap<size_t, QString>();
    _registerBlock = *convert_to_string_map(*riscReg.get_block());
    _memoryBlock = *convert_to_string_map(*riscMem.get_block());


}

/// AW: hardcoded to minimize to half the screen width/height
/// honestly we need to store previous screen size and implement it here
void MainWin::minimize()
{
    if(_maximized)
    {
        this->resize(_prevSize.width(), _prevSize.height());
        this->move(_prevPos.x(), _prevPos.y());
        //set icon to maximize
        QPixmap maximizePix(":/resources/MAXIM.png");
        QIcon maximizeIcon(maximizePix);
        ui->maximizeButton->setIcon(maximizeIcon);
        _maximized = false;
    }
}

/// AW: idk how it will behave on multiple displays though
/// also we need to store previous pos from topBarWidget and update as a member here so it minimizes on the pos
void MainWin::on_maximizeButton_clicked()
{
    if(!_maximized)
    {
        _prevPos = this->pos();
        _prevSize = this->size();
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        this->move(0,0);
        this->resize(screenGeometry.width(), screenGeometry.height());
        _maximized = true;

        //set icon to minimize
        QPixmap minimizePix(":/resources/MAXIMIN .png");
        QIcon minimizeIcon(minimizePix);
        ui->maximizeButton->setIcon(minimizeIcon);
    }
    else
    {
        this->minimize();

        //set icon to maximize
        QPixmap maximizePix(":/resources/MAXIM.png");
        QIcon maximizeIcon(maximizePix);
        ui->maximizeButton->setIcon(maximizeIcon);
    }
}


void MainWin::on_minimizeButton_clicked()
{
    this->showMinimized();
}

void MainWin::on_fileButton_clicked()
{
    QPoint cursor_pos = QCursor::pos();

    if(_fileButtonMenuActive == false)
    {
        fbm->move(cursor_pos.x(), cursor_pos.y());
        fbm->show();
        _fileButtonMenuActive = true;
    }
    else
    {
        fbm->close();
        _fileButtonMenuActive = false;
    }
}

void MainWin::on_plainTextEdit_textChanged()
{
    connect(fbm, &fileButtonMenu::file_opened, this, &MainWin::update_file_name_label);


    ui->fileNameLabel->setText((fbm->_fileName)+"(UNSAVED)");
}


bool MainWin::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->plainTextEdit && (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease))
    {
        return true;
    }
    return false;
}

void MainWin::on_executeButton_clicked()
{
    RISC32.execute();
    setupRiscV();
    update_tables();



    MainWin::delay();
}

void MainWin::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
}

