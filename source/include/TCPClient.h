/*
 * Author Eldwan Brianne
 * July 2015
 * PhD DESY
 */

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QThread>

#include "TSocket.h"
#include "TMonitor.h"
#include "TMessage.h"
#include "TList.h"

/*
 * TCP Client Class
 * Class to communicate with the server to get plots
 */

class TCPClient : public QThread
{
  Q_OBJECT
 public:
  //Contructor with host and port
  TCPClient(QString HostIP, QString Port);
  //Destructor
  ~TCPClient();

  //QThread overloaded method
  void run();
  //Read message from server
  void ReadTCP(TSocket *s);
  //Check connection status
  bool isConnected() {return IsConnected;}

  public slots:
    void StartClient();
    //Slot to send message
    void SendMessage(int type, QString m_runNumber);
    //Slot to stop socket
    void StopClient();

 signals:
    void connected(QString strConnect, int status);
    //Signal to Logger
    void log(QString type, QString message);
    //Signal to send list of histo across threads
    void list(TList *tlist);
    void disconnected();

 private:
    //Class variables
    QString m_hostIP, m_port;
    TSocket *pClient;
    TMonitor *mon;
    bool stop, IsConnected;
};

#endif // TCPCLIENT_H
