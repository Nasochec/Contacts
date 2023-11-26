import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contact
import Contacts

Flickable{
    id: view
    property bool result: false
    signal close

    Grid{
        anchors.margins:{left:50;right:50;top:50;bottom:50;}
        id:grid
        columns: 2
        rows: 5
        property int leftWidth: 900
        property font font: Constants.smallFont
        spacing: 20
        Label{
            text: "Событие:"
            font: grid.font
        }
        TextField{
            id: name
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Статус:"
            font: grid.font
        }
        TextField{
            id: status
            font: grid.font
            width: grid.leftWidth
        }
//        Label{
//            text: "Добавить домашний адрес:"
//            font: grid.font
//        }
//        CheckBox{
//            id:address
//            checked: false
//        }
        Button{
            font: Constants.font
            text: qsTr("Готово")
            onClicked:{
               view.result = true
               view.close()
            }
        }
        Button{
            font: Constants.font
            text: qsTr("Отмена")
            onClicked:{
                action.invite(status.text,name.text)
                view.result = false
                view.close()
            }
        }
    }
}

