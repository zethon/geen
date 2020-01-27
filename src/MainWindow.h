#pragma once

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class QLabel;

namespace geen
{

class GeenSyntaxHighlighter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void on_actionExit_triggered();

private:
    void initStatusBar();

private:
    Ui::MainWindow *ui;

    QLabel*                     _blockCount;
    GeenSyntaxHighlighter*      _highlighter;
};

}
