#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("DuMusicPlayer");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("DuarteCorporation");
    a.setOrganizationDomain("www.duartecorp.com");
    a.setStyle("fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
