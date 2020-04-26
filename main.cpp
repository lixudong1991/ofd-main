#include "OfdMainWidget.h"

#include <QApplication>

int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(ofd);

    QApplication app(argv, args);
    OfdMainWidget mainWindow;
   // mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.showMaximized();

    return app.exec();
}
