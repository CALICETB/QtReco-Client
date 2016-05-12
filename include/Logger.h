/*
 * Author Eldwan Brianne
 * July 2015
 * PhD DESY
*/
\
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QGroupBox>
#include <QColor>
#include <QTextEdit>

/*
 * Logger Class
 * Logging of user actions
*/

class Logger : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    Logger(QWidget *parent = 0);
    //Destructor
    ~Logger();

    //Color of Messages
    Qt::GlobalColor getColor(QString type);

signals:

public slots:
    //Slot for messages
    void Log(QString type, QString message);

private:
    QTextEdit *m_pLoggingWidget;
};

#endif // LOGGER_H
