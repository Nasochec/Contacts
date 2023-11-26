import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contact
import Contacts

Flickable{
    id: view
    property Contact contact: db.getEmptyContact()
    property bool editMode: false
    property bool result: false
    signal close
    signal open

    Grid{
        Component.onCompleted: {
            open.connect(()=>{
                lastName.text = view.contact.lastName
                firstName.text = view.contact.firstName
                middleName.text = view.contact.middleName
                phoneNumber.text = view.contact.phoneNumber
                homeNumber.text = view.contact.homeNumber
                address.text = view.contact.address
                status.text = view.contact.status
            })
        }
        anchors.margins:{left:50;right:50;top:50;bottom:50;}
        id:grid
        columns: 2
        rows: 8
        property int leftWidth: 900
        property font font: Constants.smallFont
        spacing: 20
        Label{
            text: "Фамилия:"
            font: grid.font
        }
        TextField{
            id: lastName
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Имя:"
            font: grid.font
        }
        TextField{
            id: firstName
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Отчество:"
            font: grid.font
        }
        TextField{
            id: middleName
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Моб. телефон:"
            font: grid.font
        }
        TextField{
            id: phoneNumber
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Дом. телефон:"
            font: grid.font
        }
        TextField{
            id: homeNumber
            font: grid.font
            width: grid.leftWidth
        }
        Label{
            text: "Адрес:"
            font: grid.font
        }
        TextField{
            id: address
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
        Button{
            font: Constants.font
            text: qsTr("Готово")
            onClicked:{
                view.contact.lastName = lastName.text
                view.contact.firstName = firstName.text
                view.contact.middleName = middleName.text
                view.contact.phoneNumber = phoneNumber.text
                view.contact.homeNumber = homeNumber.text
                view.contact.address = address.text
                view.contact.status = status.text
                view.result = true
                view.close()
            }
        }
        Button{
            font: Constants.font
            text: qsTr("Отмена")
            onClicked:{
                view.result = false
                view.close()
            }
        }
    }
}

