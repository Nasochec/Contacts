import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Grid{
    id: view
    columns: 2
    rows: 2

    signal closed

    Button{
       Layout.row:4
       text: qsTr("Готово")
       onClicked:{
//           editLayout.c.first_name = first_name_input.text
           console.log("stringi kristi")
           view.closed()
       }
    }

}
