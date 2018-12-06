#include "connection.h"

#include <QMutex>
#include <QTimer>

static void dump(const QByteArray &ba)
{
	for (int i = 0; i < ba.size(); i++)
		 qDebug("%d: 0x%x", i, (uchar)ba.at(i));
}

Connection::Connection(QObject *parent) : QObject(parent)
{
	port = NULL;
	timer = new QTimer(this);
	initServer(8998);
	openSerialPort();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), SLOT(timeout()));
}

void Connection::newConnection()
{
	QTcpSocket *sock = serv->nextPendingConnection();
	connect(sock, SIGNAL(disconnected()), SLOT(clientDisconnected()));
	connect(sock, SIGNAL(readyRead()), SLOT(dataReady()));
	clients << sock;
	blockSizes[sock] = 0;
}

void Connection::initServer(quint16 port)
{
	serv = new QTcpServer(this);
	if(!serv->listen(QHostAddress::Any, port))
		qDebug() << "Server could not start";
	else qDebug() << "Server started!";
	qDebug() << "Serial port initializing...";
	connect(serv, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void Connection::dataReady()
{
	sock = (QTcpSocket *)sender();
	qint64 len = sock->bytesAvailable();
	QByteArray data = sock->read(len);
	qDebug() << "from tcp:"<< data.size();
	dump(data);
	port->write(data, len);
}

void Connection::clientDisconnected()
{
	sock = (QTcpSocket *)sender();
	clients.removeAll(sock);
	sock->deleteLater();
}

int Connection::openSerialPort()
{
	QString filename = "ttyS0";
	port = new QextSerialPort(filename, QextSerialPort::EventDriven);
	port->setBaudRate(BAUD9600);
	port->setFlowControl(FLOW_OFF);
	port->setParity(PAR_NONE);
	port->setDataBits(DATA_8);
	port->setStopBits(STOP_1);
	if (!port->open(QIODevice::ReadWrite)) {
		qDebug() << "error opening serial port ";
		return -EPERM;
	}
	connect(port, SIGNAL(readyRead()), SLOT(readyReadSerial()));
	return 0;
}

void Connection::readyReadSerial()
{
	QByteArray ba = port->readAll();
	qDebug() << "from serial:" << ba.size();
	dump(ba);
	sock->write(ba);
}

void Connection::timeout()
{
	//readyReadSerial();
//	newConnection();
}

