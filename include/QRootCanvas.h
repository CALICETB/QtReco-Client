/*
 * Author Eldwan Brianne
 * July 2015
 * PhD DESY
*/

#ifndef QROOTCANVAS_H
#define QROOTCANVAS_H

#include <QWidget>

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QPushButton;
class QTimer;
class TCanvas;

/*
 * QRootCanvas Class
 * TCanvas implementation in Qt
*/

class QRootCanvas : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    QRootCanvas(QWidget *parent);
    //Return TCanvas
    TCanvas* getCanvas() {return fCanvas;}

signals:

public slots:

protected:
    //overloaded functions to handle mouse events
    TCanvas   *fCanvas;
    virtual void  mouseMoveEvent(QMouseEvent *e);
    virtual void  mousePressEvent(QMouseEvent *e);
    virtual void  mouseReleaseEvent(QMouseEvent *e);
    virtual void  paintEvent(QPaintEvent *e);
    virtual void  resizeEvent(QResizeEvent *e);
};

#endif // QROOTCANVAS_H
