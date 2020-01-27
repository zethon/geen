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
#include <QLabel>
#include <QSpacerItem>

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

    // initialization to be done after the window has been painted
    QTimer::singleShot(0,
        [this]()
        {
            this->initStatusBar();
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

void MainWindow::initStatusBar()
{
    _blockCount = new QLabel(this);
    _blockCount->setStyleSheet("QLabel { color: #FFFFFF; }");
    _blockCount->setText(QString("Ln %1, Col %2    Lines: %3")
        .arg(1).arg(1).arg(1));

    ui->statusBar->addWidget(_blockCount);
    ui->statusBar->setStyleSheet("QStatusBar { background: #007ACD; color: #FFFFFF; }");

    QObject::connect(ui->textEdit, &QPlainTextEdit::cursorPositionChanged,
        [this]()
        {
            auto blocknumber = this->ui->textEdit->textCursor().blockNumber() + 1;
            auto posinblock = this->ui->textEdit->textCursor().positionInBlock() + 1;

            _blockCount->setText(QString("Ln %1, Col %2    Lines: %3")
                .arg(blocknumber)
                .arg(posinblock)
                .arg(ui->textEdit->blockCount()));

        });
}

}

