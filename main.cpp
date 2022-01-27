#include "gui.h"
#include <QApplication>

// Es ist unverändert geblieben
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();

    return a.exec();
}
