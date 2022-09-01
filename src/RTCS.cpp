#include "RTCS.h"

RTCS::RTCS() : QObject()
{
	main_window = new RTCSMainWindow();
}

void RTCS::showMainWindow(bool fullscreen) {
	if (fullscreen)
		main_window->setWindowState(Qt::WindowFullScreen);
	main_window->show();
}

void RTCS::hideMainWindow() {
	main_window->hide();
}