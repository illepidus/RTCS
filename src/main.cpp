#include "global.h"
#include "RTCS.h"

#include <QApplication>
#include "Settings.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("centrogas");
	QCoreApplication::setApplicationName("rtcs");

	RTCS rtcs;
	rtcs.showMainWindow(true);
	Settings s;
	s.setValue("test", "test");
	qDebug() << s.fileName();

	return app.exec();
}
