#ifdef QT_NO_DEBUG_OUTPUT
#undef QT_NO_DEBUG_OUTPUT
#endif

#include <QApplication>

#include "Core.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    geen::MainWindow w;

    w.setWindowIcon(QIcon(":/IconResource/icons/cupcake.png"));
    w.setWindowTitle(APP_TITLE);

    w.show();
    return a.exec();
}
