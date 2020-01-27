#ifdef QT_NO_DEBUG_OUTPUT
#undef QT_NO_DEBUG_OUTPUT
#endif

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    geen::MainWindow w;

    w.setWindowIcon(QIcon(":/IconResource/icons/cupcake.png"));
    w.setWindowTitle(QObject::tr("geen text tool"));

    w.show();
    return a.exec();
}
