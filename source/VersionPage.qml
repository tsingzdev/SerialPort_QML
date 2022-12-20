import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Window{
    width: 300
    height: 150
    title: "About"

    Rectangle{
        anchors.fill:parent
        Text {
            anchors.fill: parent
            text: "Serial Port （in Qt Quick)"+"\n"+"\n"+"Version V0.1"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
