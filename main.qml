import QtQuick 2.12
import QtQuick.Window 2.12

Window {    
    flags: Qt.WA_TranslucentBackground
    //flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "#00000000"
    Text {
        text: "bottom left"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }
    Text {
        text: "Top right"
        id: topright
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
    Text {
        font.pixelSize: 30
        text: "HELLO WORLD"
        anchors.centerIn: parent
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (parent.font.pixelSize == 50)
                {
                    parent.font.pixelSize = 30;
                    topright.text = "Serious mode";
                }
                else
                {
                    parent.font.pixelSize = 50;
                    topright.text = "KEK";
                }
            }
        }
    }
}