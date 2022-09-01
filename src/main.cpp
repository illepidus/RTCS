#include "global.h"
#include "RTCS.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("Centrogas");
	QCoreApplication::setApplicationName("RTCS");

	RTCS rtcs;
	rtcs.showMainWindow();

	return app.exec();
}
