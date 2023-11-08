import QtQuick 6.2
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import Contact

//Page{
    Grid{
        id: view
        columns: 2
        rows: 2
        Contact{
            id:defaultContact
            firstName: "gladko"
        }
        property Contact contact: defaultContact
        signal close
        Button{
            Layout.row:4
            text: qsTr("Готово")
            onClicked:{
//                db.insertContact(null)
                //           editLayout.c.first_name = first_name_input.text
                console.log("stringi kristi y "+ view.contact.firstName)
//                        )
                view.close()
            }
        }
    }
//}
