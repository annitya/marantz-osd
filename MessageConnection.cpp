#include <qtimer.h>
#include "MessageConnection.h"

MessageConnection::MessageConnection() {
    _message = "lel";
    connection = new TelnetConnection("192.168.10.128");
    connection->open();
}


string MessageConnection::formatMessage(string message) {
    float value = stof(message) - 80;

    stringstream stream;
    stream << fixed << setprecision(1) << value;
    string dbValue = stream.str();

    return dbValue + " dB";
}

string MessageConnection::parseMessage(char* buffer) {
    string value = (string)buffer;

    if (value.length() == 0) {
        return "";
    }

    int valueEndIndex = value.find("\r") - 2;
    string numberPart = value.substr(2, valueEndIndex);
    // MVMAX 80\rAX 80\r => max volume
    if (numberPart[0] == 'M') {
        return "";
    }
    // MV47\r 80\rAX 80\r => current integer volume
    if (numberPart.length() == 2) {
        return formatMessage(numberPart);
    }
    // MV475\r80\rAX 80\r => current volume with "decimal"
    if (numberPart.length() == 3) {
        string numberValue = numberPart.substr(0, 2) + "." + numberPart[2];
        return formatMessage(numberValue);
    }

    return "";
}

QString MessageConnection::message() {	
	return QString::fromStdString(_message);
}

void MessageConnection::getCurrentMessage() {
    char* message = connection->getCurrentMessage();
    
    if (message != "") {
        _message = parseMessage(message);
        emit messageChanged();
    }

    QTimer::singleShot(0, this, SLOT(getCurrentMessage()));
}

void MessageConnection::startMonitor() {
    QTimer::singleShot(0, this, SLOT(getCurrentMessage()));
}