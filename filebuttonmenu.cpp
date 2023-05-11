#include "filebuttonmenu.h"
#include "ui_filebuttonmenu.h"

fileButtonMenu::fileButtonMenu(QWidget *parent, QPlainTextEdit* doc) :
    QWidget(parent),
    ui(new Ui::fileButtonMenu)
{
    ui->setupUi(this);
    _doc =  doc;
    _fileName = "D:/academic/AUC/Spring 2023/CompOrg & Assm/QtThemeTest/program.txt";

    setMouseTracking(true);
    installEventFilter(this);
}

fileButtonMenu::~fileButtonMenu()
{
    delete ui;
}

bool isFileDialogOpen()
{
    QList<QWidget*> widgets = qApp->topLevelWidgets();
    for (QWidget* widget : widgets) {
        if (widget->metaObject()->className() == QString("QFileDialog") && widget->isVisible()) {
            return true;
        }
    }
    return false;
}

void fileButtonMenu::on_saveButton_clicked()
{
    if(_newFile)
    {
        QString tempfileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
        _fileName = tempfileName;

        if (tempfileName.isEmpty()) {
            return;
        }

        QFile file(tempfileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Error handling
            return;
        }


        QTextStream out(&file);
        out << _doc->toPlainText();
        file_open_event();

        _newFile = false;
        return;
    }

    QFile file(_fileName);
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QTextStream fileStream(&file);
        fileStream << _doc->toPlainText();
        file_open_event();
    }
}


bool fileButtonMenu::eventFilter(QObject* o, QEvent* e)
{
    if(e->type() == QEvent::Leave && !(isFileDialogOpen()))
    {
        this->close();
    }
    return QWidget::event(e);
}


void fileButtonMenu::file_open_event()
{

    emit file_opened(_fileName + "(SAVED)");
}

void fileButtonMenu::on_openButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec())
    {
        _fileName = dialog.selectedFiles()[0]; ///AW: really needs to change here
        file_open_event();
    }

    QFile file(_fileName);
    file.open(QFile::ReadWrite | QFile::Text);
    QTextStream fileStream(&file);
    _doc->setPlainText(fileStream.readAll());
}

