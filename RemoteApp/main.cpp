#include "remotewindow.h"

#include <DWidgetUtil>


int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setTheme("light");
    a.setOrganizationName("deepin");
    a.setApplicationName("远程协助");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon(":/images/logo.svg"));
    a.setProductName("远程协助");
    a.setApplicationDescription("This is a dtk template application.");

    RemoteWindow w;
    w.show();
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
