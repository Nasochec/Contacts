import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contact
import Contacts

ApplicationWindow {
    width: Constants.width
    height: Constants.height

    visible: true
    title: qsTr("Контакты")
    header: Button{
            id:button
            text: qsTr("Добавить контакт")
            font: Constants.font
            onClicked:{
                stackView.push(view)
                view.visible = true
                view.contact = db.getEmptyContact()
                view.open()
                button.visible = false
                var insertContactF = () => {
                    if(view.result)
                        db.insertContact(view.contact)
                    stackView.pop()
                    button.visible = true
                    view.onClose.disconnect(insertContactF)
                }
                view.onClose.connect(insertContactF)
            }
        }
    StackView{
        anchors.fill: parent
        id: stackView
        initialItem:
        ListView{
            id: listView
            anchors.fill: parent
            model: db.model
            spacing: 20
            delegate: Rectangle{
                height: 300
                width: listView.width
                color: "lightgray"
                radius: 40
                Column{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height:parent.height
                    Label{
                        text: model.name
                        font: Constants.font
                    }
                    Label{
                        text: model.status
                        font: Constants.smallFont
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        stackView.push(view)
                        view.visible = true
                        view.contact = db.getContact(model.itemId)
                        view.open()
                        button.visible = false
                        var editContactF = () => {
                            if(view.result)
                                db.editContact(view.contact)
                            stackView.pop()
                            button.visible = true
                            view.onClose.disconnect(editContactF)
                        }
                        view.onClose.connect(editContactF)
                    }
                }
                Button{
                    text: "X"
                    font: Constants.font
                    anchors.right: parent.right
                    onClicked: db.deleteContactById(model.itemId)
                }
            }
            SortChoose{
                anchors.bottom:parent.bottom
                height: 250
                width: listView.width
            }
        }

        ViewContact{
            id:view
            visible: false
        }
    }

}

