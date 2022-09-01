#include "global.h"
#include "RTCSMainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Centrogas");
    QCoreApplication::setApplicationName("RTCS");

    RTCSMainWindow *rtcs = new RTCSMainWindow();
    rtcs->setWindowState(Qt::WindowFullScreen);
    rtcs->show();

    return app.exec();
}
