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
            this->initMainMenu();
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

void MainWindow::initMainMenu()
{
    auto mainMenu = menuBar();

    // File Menu
    {
        auto fileMenu = mainMenu->findChild<QMenu*>("menuFile", Qt::FindDirectChildrenOnly);
        Q_ASSERT(fileMenu);

        auto newMenu = fileMenu->addMenu(QIcon{":/IconResource/icons/new.png" }, "New");
        initNewMenu(newMenu);


        fileMenu->addAction(QIcon{":/IconResource/icons/open.png" }, "Open");
        fileMenu->addSeparator();
        fileMenu->addAction(QIcon{":/IconResource/icons/Save.png" }, "Save");
        fileMenu->addAction(QIcon{":/IconResource/icons/saveas.png" }, "Save as ..");
        fileMenu->addSeparator();

        auto quitAction = fileMenu->addAction(QIcon{":/IconResource/icons/exit.png" }, "Exit");
        quitAction->setMenuRole(QAction::QuitRole);
        quitAction->setShortcut(QKeySequence::Quit);
        QObject::connect(quitAction, &QAction::triggered,[this]() { close(); });
    }
}

void MainWindow::initNewMenu(QMenu* menu)
{
    {
        auto document = menu->addAction("Document");
        QObject::connect(document, &QAction::triggered,[]() { qDebug() << "new Document"; });
    }

    {
        auto document = menu->addAction("Clipboard Monitor");
        QObject::connect(document, &QAction::triggered,[]() { qDebug() << "new Clipboard Monitor"; });
    }
}

}

