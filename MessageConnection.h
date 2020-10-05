#pragma once

#include <QObject>
#include "TelnetConnection.cpp"

class MessageConnection : public QObject
{
	Q_OBJECT		
	Q_PROPERTY(QString message READ message NOTIFY messageChanged)

signals:
	void messageChanged();

private:
	TelnetConnection* connection;
	string _message;
	string formatMessage(string message);
	string parseMessage(string value);

public:
	MessageConnection();
	QString message();
		
private slots:
	void getCurrentMessage();

public slots:
	void startMonitor();
	void logMessage(string message);
};
