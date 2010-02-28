#include "archiver.h"
#include <QMessageBox>

Archiver::Archiver(QWidget *parent)
    : QDialog(parent)
{
  ui.setupUi(this);
  connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(doTest()));
}

Archiver::~Archiver()
{

}

void Archiver::doTest()
{
  QMessageBox::information(this, "Email Archiver", "Passed test.");
}
