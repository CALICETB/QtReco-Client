/*
 * Author Eldwan Brianne
 * July 2015
 * PhD DESY
*/

#ifndef QCANVASWIDGET_H
#define QCANVASWIDGET_H

#include <QWidget>

#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "QRootCanvas.h"

/*
 * QCanvasWidget Class
 * Widget class use to display plots
*/

class QCanvasWidget : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    QCanvasWidget(QWidget *parent = 0);
    //Destructor
    ~QCanvasWidget();

    //Handle mouse click
    virtual void changeEvent(QEvent *e);
    //Reverse axis for HitMap
    void ReverseXAxis(TH2 *h);

public slots:
    //Draw histograms
    void Draw(TList *m_list);

signals:
    //Signal to Logger
    void log(QString type, QString message);

private:
    //Pointer to TCanvas implementation
    QRootCanvas *TCanvas;
};

#endif // QCANVASWIDGET_H
