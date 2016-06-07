#include "GuiClient.h"

#include <TApplication.h>
#include <QApplication>

int main(int argc, char *argv[])
{
  TApplication app("rootapp", &argc, argv);
  QApplication a(argc, argv);
  
  GUIClient w;
  w.show();
  
  return a.exec();
}
