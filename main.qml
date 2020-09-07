import QtQuick 2.12
import QtQuick.Window 2.12

Window {        
    id: mainWindow
    objectName: "mainWindow"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.WindowStaysOnTopHint | Qt.Tool | Qt.WindowTransparentForInput
    x: 1700
    y: 980
    width: 200
    height: 80
    visible: true   
    color: "#00000000"
    Text {
        id: textContainer        
        text: messageConnection.message
        objectName: "textContainer"        
        color: "#00FF00"
        font.pixelSize: 50
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        opacity: 0
                        
        onTextChanged: {
            if (fader.running) {
                fader.stop();
            }

            fader.start();
        }

        Component.onCompleted: {            
            messageConnection.startMonitor();
        }
    }
    
    OpacityAnimator {
        id: fader
        target: textContainer
        from: 1
        to: 0
        duration: 500
    }
    
}
