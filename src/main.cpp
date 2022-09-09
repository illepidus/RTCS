#include "global.h"
#include "RTCS.h"

#include <QApplication>
#include "Device.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("centrogas");
	QCoreApplication::setApplicationName("rtcs");

	RTCS rtcs;
	rtcs.showMainWindow(true);

	Device d("Test");

	return app.exec();
}
