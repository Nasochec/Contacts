import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contacts

Rectangle{
    GridLayout{
        anchors.fill: parent
        columns:3
        rows:2
        Label{
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.columnSpan: 3
            font: Constants.font
            text: "Сортировать по:"
        }
        Label{
            font: Constants.font
            text: "Имени"
        }
        Slider{
            font: Constants.font
            height: 100
            id: sortSlider
            value: 0
            from: 0
            to: 1
            stepSize: 1
            snapMode: Slider.SnapAlways
            onValueChanged: {
                if(value == 1)
                    db.sortByStatus();
                if(value == 0)
                    db.sortByName();
            }
        }
        Label{
            font: Constants.font
            text: "Статусу"
        }
        Component.onCompleted: db.sortByName();
    }

}
