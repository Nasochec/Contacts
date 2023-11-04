// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import projectus1

ApplicationWindow {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: qsTr("Contacts")

    ViewContact{
        id:view
    }

    header: Button{
            text: qsTr("Добавить")
            onClicked:{
                stackView.push(view)
                // edit.c =
                view.onClosed.connect(function () {
                    // contact.insert(edit.c)
                    stackView.pop()
                })
            }
        }
    StackView{
        anchors.fill: parent
        // height:parent.height
        id: stackView
        initialItem:Item{
            id: listView
            Label{
                text: qsTr("Список контаков:")

            }
            ListModel{
                id:trashModel
                ListElement { name: "white"; }
            }

//            ListView{
//                anchors.fill: parent
//                // width: parent.width
//                // height: parent.width
//                model: contactModel
//                // trashModel
//                delegate: Rectangle{
//                    height: 50
//                    width: parent.width
//                    color: "red"
//                    Column{
//                        Label{
//                            text: name
//                        }
//                        Label{
//                            text: status
//                        }
//                    }

//                    // Label{
//                    //     text: model.status

//                    // }
//                }

//            }
        }
    }
}

