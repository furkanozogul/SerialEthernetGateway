#ifndef CONNECTION_H
#define CONNECTION_H

#include <errno.h>

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <3rd/qextserialport/src/qextserialport.h>

class QTimer;

class Connection : public QObject
{
	Q_OBJECT
public:
	explicit Connection(QObject *parent = 0);
	int openSerialPort();
	void initServer(quint16 port);

signals:
	void newDataAvailable(QTcpSocket *sock, const QByteArray &data);

public slots:
	void newConnection();
	void dataReady();
	void clientDisconnected();
	void readyReadSerial();


protected slots:
	virtual void timeout();
private:
	QTimer *timer;
	QTcpSocket *sock;
	QTcpServer *serv;
	QextSerialPort *port;
	QList<QTcpSocket *> clients;
	QHash<QTcpSocket *, quint16> blockSizes;
};

#endif // CONNECTION_H
