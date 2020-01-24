#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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
    Ui::MainWindow *ui;

    GeenSyntaxHighlighter* _highlighter;
};

}
