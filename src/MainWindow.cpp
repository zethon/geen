#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <qtextedit.h>
#include <QFontDialog>
#include <QFont>
#include <QFontDatabase>
#include <QTextCursor>
#include <QColor>
#include <QColorDialog>
#include <QSyntaxHighlighter>
#include <QtGui>

#include "GeenTextEditor.h"
#include "GeenSyntaxHighlighter.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace geen
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    _highlighter = new GeenSyntaxHighlighter(ui->textEdit->document());

#ifdef Q_OS_MAC
    QFont editorFont;
    editorFont.setPixelSize(16);
    editorFont.setFamily("Consolas");
    ui->textEdit->setFont(editorFont);
#endif

    QObject::connect(ui->textEdit, &QPlainTextEdit::blockCountChanged,
        [](int newBlockCount)
        {
            std::cout << "newBlockCount: " << newBlockCount << '\n';
        });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QGuiApplication::exit();
}

}

