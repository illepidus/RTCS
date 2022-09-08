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

	QSettings s;
	$d(s.fileName());
	s.setValue("editor/wrapMargin", 68);

	return app.exec();
}
