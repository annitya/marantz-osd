import QtQuick 2.12
import QtQuick.Window 2.12

Window {        
    id: mainWindow
    objectName: "mainWindow"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    visible: true
    visibility: Window.fullScreen
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "#00000000"
    Text {
        id: textContainer
        objectName: "textContainer"
        text: "bottom right"
        color: "#00FF00"
        font.pixelSize: 50
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }  
}