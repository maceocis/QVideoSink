import QtQuick
import QtQuick.Window
import QtMultimedia

Window {
    width: 480
    height: 800
    visible: true
    title: qsTr("Hello World")

    //to be run after window object has been instantiated.
    Component.onCompleted: {
        frameProvider.videoSink = videoOutput.videoSink        
    }

    VideoOutput{
        id: videoOutput
        anchors.fill: parent
    }

}
