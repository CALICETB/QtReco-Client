#include "GuiClient.h"

#include <QApplication>

#include <TApplication.h>
#include <TSystem.h>

int main(int argc, char *argv[])
{
  TApplication rootapp("Simple Qt ROOT Application", &argc, argv);
  QApplication a(argc, argv);
  
  GUIClient w;
  w.show();
  
  return a.exec();
}
