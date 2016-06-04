#include "GuiClient.h"
#include "ui_GuiClient.h"

#include <QTimer>
#include <QDebug>
#include <QMessageBox>

#include "TSystem.h"

GUIClient::GUIClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUIClient)
{
    m_list = new TList();

    ui->setupUi(this);
    connect(ui->Exit, SIGNAL(clicked()), this, SLOT(Quit()));
    ui->Show_status->setText("Disconnected");

    ui->TabWidget->setEnabled(false);

    connect(ui->GetT0_Correlation, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetT0s_Difference, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetT0s_Sum, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetHits, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetHits_perLayer, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetEnergySum, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetEnergyPerLayer, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetShower, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetShower_others, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetHitMap, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(ui->GetTemp, SIGNAL(clicked()), this, SLOT(OnClick()));

    connect(ui->Connect, SIGNAL(clicked()), this, SLOT(OnConnect()));

    fRootTimer = new QTimer(this);
    QObject::connect(fRootTimer, SIGNAL(timeout()), this, SLOT(UpdateGUI()));
    fRootTimer->start(100);

    connect(this, SIGNAL(log(QString, QString)), ui->LoggerWid, SLOT(Log(QString,QString)));

    emit log("DEBUG", "Client Started");
    canvas = NULL;
    tcpclient = NULL;
}

//-----------------------------------------------------------------------------------------------

void GUIClient::Quit()
{
    if(tcpclient)
        tcpclient->Stop();

    QEventLoop loop;
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(3000);
    loop.exec();
    close();
}

//-----------------------------------------------------------------------------------------------

void GUIClient::OnConnect()
{
    m_port = "5622";
    if(!m_hostIP.isEmpty())
    {
        tcpclient = new TCPClient(m_hostIP, m_port);
        canvas = new QCanvasWidget();
        connect(canvas, SIGNAL(log(QString,QString)), ui->LoggerWid, SLOT(Log(QString,QString)));
        connect(tcpclient, SIGNAL(log(QString, QString)), ui->LoggerWid, SLOT(Log(QString,QString)));
        connect(tcpclient, SIGNAL(connected(QString,int)), this, SLOT(StatusTCP(QString,int)));

        tcpclient->start();

        QEventLoop loop;
        QTimer timer;
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(1500);
        loop.exec();

        if(tcpclient->isConnected())
        {
            connect(this, SIGNAL(message(int,QString)), tcpclient, SLOT(SendMessage(int,QString)));
            connect(tcpclient, SIGNAL(list(TList*)), canvas, SLOT(Draw(TList*)));
            connect(tcpclient, SIGNAL(disconnected()), this, SLOT(OnDisconnect()));

            emit log("DEBUG", QString("Connected to %1 on port %2").arg(m_hostIP, m_port));
        }
        else
        {
            emit log("ERROR", QString("System Error, can't connect to %1 on port %2. Is QtReco open on the host?").arg(m_hostIP, m_port));
        }
    }
    else
    {
        emit log("ERROR", "No IP provided");
        return;
    }
}

//-----------------------------------------------------------------------------------------------

void GUIClient::OnDisconnect()
{
    ui->Connect->setEnabled(true);
    ui->TabWidget->setEnabled(false);
    ui->Show_status->setText("Disconnected");
}

//-----------------------------------------------------------------------------------------------

GUIClient::~GUIClient()
{
    delete ui;
}

//-----------------------------------------------------------------------------------------------

void GUIClient::UpdateGUI()
{
    gSystem->ProcessEvents();
    m_runNumber = ui->RunNumber->text();
    m_hostIP = ui->Line_IP->text();
}

//-----------------------------------------------------------------------------------------------

void GUIClient::StatusTCP(QString str, int status)
{
    if(status == 1)
    {
        ui->Show_status->setText(str);
        ui->Connect->setEnabled(false);
        ui->TabWidget->setEnabled(true);
    }
    if(status == 0)
    {
        ui->Connect->setEnabled(true);
        ui->TabWidget->setEnabled(false);
        ui->Show_status->setText(str);
    }
    if(status == -1)
    {
        ui->Show_status->setText(str);
        ui->Connect->setEnabled(true);
    }
}

//-----------------------------------------------------------------------------------------------

void GUIClient::OnClick()
{
    if(!m_runNumber.isEmpty())
    {
        QPushButton *button = qobject_cast<QPushButton*>(sender());

        if(button == ui->GetT0_Correlation)
        {
            canvas->show();
            emit message(1, m_runNumber);
            emit log("DEBUG", "Message Get T0_Correlation send");
        }
        if(button == ui->GetT0s_Difference)
        {
            canvas->show();
            emit message(2, m_runNumber);
            emit log("DEBUG", "Message Get T0_Difference send");
        }
        if(button == ui->GetT0s_Sum)
        {
            canvas->show();
            emit message(3, m_runNumber);
            emit log("DEBUG", "Message Get T0_Sum send");
        }
        if(button == ui->GetHits)
        {
            canvas->show();
            emit message(4, m_runNumber);
            emit log("DEBUG", "Message GetHits send");
        }
        if(button == ui->GetHits_perLayer)
        {
            canvas->show();
            emit message(5, m_runNumber);
            emit log("DEBUG", "Message GetHits per layer send");
        }
        if(button == ui->GetEnergySum)
        {
            canvas->show();
            emit message(6, m_runNumber);
            emit log("DEBUG", "Message Get Energy Sum send");
        }
        if(button == ui->GetShower)
        {
            canvas->show();
            emit message(7, m_runNumber);
            emit log("DEBUG", "Message Get Shower send");
        }
        if(button == ui->GetShower_others)
        {
            canvas->show();
            emit message(7, m_runNumber);
            emit log("DEBUG", "Message Get Shower send");
        }
        if(button == ui->GetHitMap)
        {
            canvas->show();
            emit message(8, m_runNumber);
            emit log("DEBUG", "Message Get HitMap send");
        }
        if(button == ui->GetTemp)
        {
            canvas->show();
            emit message(9, m_runNumber);
            emit log("DEBUG", "Message Get Temperature send");
        }
        if(button == ui->GetEnergyPerLayer)
        {
            canvas->show();
            emit message(10, m_runNumber);
            emit log("DEBUG", "Message Get Energy Per Layer send");
        }
    }
    else
    {
        emit log("DEBUG", "No Run Number provided!!");
        return;
    }
}
