#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace geen
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:


private:
    Ui::MainWindow *ui;
    QString file_path;
};

}
