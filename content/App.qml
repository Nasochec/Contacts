import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contacts

ApplicationWindow {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: qsTr("Contacts")

    ViewContact{
        id:view
    }

    header: Button{
            id:button
            text: qsTr("Добавить")
            onClicked:{
                stackView.push(view)
                button.visible = false

            }
            Component.onCompleted:{
                view.onClose.connect(function () {
                    db.insertContact(null)
                    console.log(db.items())
                    stackView.pop()
                    button.visible = true
                })
            }
        }
    StackView{
        anchors.fill: parent
//        anchors.margins: {top:20;bottom:20;left:20;right:20}
        // height:parent.height
        id: stackView
        initialItem:Item{
//            id: listView
            Label{
                text: qsTr("Список контаков:")
                font.pixelSize: 50
            }
            Label{
                y:100
                text: qsTr("Контактов:")+ db.items()
                font.pixelSize: 50
            }
            ListView{
                id: listView
                anchors.fill: parent
                model: db.model
                delegate: Rectangle{
                    height: 300
                    width: 900
//                        parent.width
                    color: "red"
                    Column{
                        Label{
                            text: model.itemId
                            font.pixelSize: 50
                        }
                        Label{
                            text: model.name
                            font.pixelSize: 50
                        }
                        Label{
                            text: model.status
                            font.pixelSize: 50
                        }
                    }
                    Button{
                        text: "X"
                        font.pixelSize: 50
                        onClicked: db.deleteContactById(model.itemId)
                    }
                }
                Component.onCompleted: {
//                    db.model.onDataChanged.connect(listView)
                }
            }
        }
    }
}

