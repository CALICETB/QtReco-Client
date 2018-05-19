#include "TCPClient.h"

TCPClient::TCPClient(QString HostIP, QString Port)
{
  m_hostIP = HostIP;
  m_port = Port;
  stop = false;
  IsConnected = false;
}

//-----------------------------------------------------------------------------------------------

TCPClient::~TCPClient()
{
  emit log("DEBUG", "TCP Client : DESTROYED");
  
  if(pClient)
    delete pClient;
  if(mon)
    delete mon;
}

//-----------------------------------------------------------------------------------------------

void TCPClient::run()
{
  this->StartClient();

  pClient->Close();
  mon->RemoveAll();
  emit connected("Disconnected", 0);
  emit disconnected();
  IsConnected = false;
      
  return;
}

//-----------------------------------------------------------------------------------------------

void TCPClient::StartClient()
{
  pClient = new TSocket(m_hostIP.toLocal8Bit().data(), m_port.toInt());

  if(!pClient->IsValid())
    {
      IsConnected = false;
      if(pClient->GetErrorCode() == -1)
	emit connected("Failed creating socket", -1);
      else if(pClient->GetErrorCode() == -2)
	emit connected("Failed to bind", -1);
      else if(pClient->GetErrorCode() == -3)
	emit connected("Failed to listen", -1);
      else
	emit connected("Unknown Error", -1);

      return;
    }
  else
    {
      mon = new TMonitor();
      mon->Add(pClient);

      emit connected("Connected", 1);
      IsConnected = true;
	
      while(1)
	{
	  if(stop)
	    break;
	    
	  TSocket *s;
	  if((s = mon->Select()) != (TSocket*)-1)
	    ReadTCP(s);

	  sleep(1);
	}
      
      return;
    }
}

//-----------------------------------------------------------------------------------------------

void TCPClient::StopClient()
{
  stop = true;
  emit log("DEBUG", "TCP Client : Shuting down");
}

//-----------------------------------------------------------------------------------------------

void TCPClient::SendMessage(int type, QString m_runNumber)
{
  TMessage mess(kMESS_STRING);
  std::string message;
  message.append("Run_");
  message.append(m_runNumber.toStdString());
  message.append(",");

  switch(type)
    {
      /*case 1:
      message.append("T0_Correlation");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 2:
      message.append("T0_Difference");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 3:
      message.append("T0_Sum");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;*/
    case 4:
      message.append("NHits_Profile");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 5:
      message.append("NHits_Layer");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 6:
      message.append("Energy_Sum");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 7:
      message.append("Shower");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 8:
      message.append("HitMap");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 13:
      message.append("HitMap_Energy");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 9:
      message.append("Temperature");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
      /*case 10:
      message.append("EnergyPerLayer");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;*/
    case 11:
      message.append("Hit_Time");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 12:
      message.append("EnergyPerChannel");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
    case 14:
      message.append("RMSPerChannel");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
   case 15:
      message.append("HitMap_Log");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
   case 16:
      message.append("nHitscogZ");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
   case 17:
      message.append("EnergyLayer");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;
   case 18:
      message.append("nHits_Per_Event");
      mess.WriteStdString(message);
      pClient->Send(mess);
      return;

    }
}

//-----------------------------------------------------------------------------------------------

void TCPClient::ReadTCP(TSocket *s)
{
  TMessage *mess;
  int recv = s->Recv(mess);

  emit log("DEBUG", QString("TCP Client: Received sth %1").arg(QString::number(recv)));

  if(recv <= 0)
    {
      emit log("ERROR", "TCP Client: Server disconnected");
      s->Close();
      mon->Remove(s);
      emit disconnected();
      return;
    }
  else
    {
      if(mess->What() == kMESS_STRING)
        {
	  std::string message;
	  mess->ReadStdString(message);
	  emit log("ERROR", QString::fromStdString(message));
	  return;
        }
      else if(mess->What() == kMESS_OBJECT)
        {
	  TList *m_list = new TList();
	  m_list = (TList*)mess->ReadObject(mess->GetClass());

	  if(m_list->IsEmpty())
            {
	      emit log("ERROR", "TCP Client: Received List Error");
	      return;
            }
	  else
            {
	      emit log("DEBUG", QString("TCP Client: List %1 Size %2").arg(QString::fromLocal8Bit(m_list->GetName()), QString::number(m_list->GetSize())));
	      emit list(m_list);
	      delete mess;
	      return;
            }
        }
      else
        {
	  emit log("ERROR", "TCP Client: Unknown message");
	  return;
        }
    }
}
