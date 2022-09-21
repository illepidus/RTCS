#include "global.h"
#include "RTCS.h"

#include <QApplication>
#include "Device.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("centrogas");
	QCoreApplication::setApplicationName("rtcs");
	QStringList args = QCoreApplication::arguments();
	qDebug() << "RTCS command line arguments = " << args;
	qDebug() << "RTCS configuration file = " << QSettings().fileName();

	bool gui = (args.contains("--nogui")) ? false : true;
	bool fullscreen = (args.contains("--nofullscreen")) ? false : true;

	RTCS rtcs;
	if (gui) rtcs.showMainWindow(fullscreen);

	return app.exec();
}
