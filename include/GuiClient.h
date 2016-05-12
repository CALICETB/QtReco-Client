/*
 * Author Eldwan Brianne
 * July 2015
 * PhD DESY
*/

#ifndef GUICLIENT_H
#define GUICLIENT_H

#include <QMainWindow>
#include <QObject>

#include "TSocket.h"
#include "TMessage.h"
#include "TList.h"

#include "QCanvasWidget.h"
#include "QRootCanvas.h"
#include "TCPClient.h"
#include "Logger.h"

namespace Ui {
class GUIClient;
}

/*
 * UI Class
 * General Class for ui client
*/

class GUIClient : public QMainWindow
{
    Q_OBJECT
public:
    //Constructor
    explicit GUIClient(QWidget *parent = 0);
    //Destructor
    ~GUIClient();

public slots:
    //Get Server status
    void StatusTCP(QString str, int status);
    //Update UI
    void UpdateGUI();
    //Connect to server
    void OnConnect();
    //Exit
    void Quit();
    //Request Plot
    void OnClick();
    //Disconnect to server
    void OnDisconnect();

signals:
    //Signal to Logger
    void log(QString type, QString message);
    void connected();
    void message(int type, QString runNumber);

private:
    //Class variables
    Ui::GUIClient *ui;
    QString m_hostIP, m_port, m_runNumber;
    QCanvasWidget *canvas;
    //TCP Client pointer
    TCPClient *tcpclient;
    QTimer *fRootTimer;
    TList *m_list;
};

#endif // GUICLIENT_H
