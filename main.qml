import QtQuick
import QtQuick.Window
import QtMultimedia
import com.heine.components 1.0

Window {
    width: 480
    height: 800
    visible: true

    Rendyboi{
        anchors.fill: parent
        pipeline: gstpipe
    }

}
