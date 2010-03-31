#include "archivermain.h"

ArchiverMain::ArchiverMain(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	setCentralWidget(&archiver);
}

ArchiverMain::~ArchiverMain()
{

}
