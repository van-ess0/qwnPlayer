import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    property color accentColor: settings.globalAccentColor

    Column{

        Text {
            // http://www.flaticon.com/authors/daniel-bruce
            textFormat: Text.RichText
            color: accentColor
            text: qsTr('Thanks for the icons to
                        <a href="http://www.flaticon.com/authors/daniel-bruce">Daniel Bruce</a>')
        }

        Text {
            text: qsTr("Authors:")
            color: accentColor
        }

        Text {
            textFormat: Text.RichText
            color: accentColor
            text: "Suratov Vladislav<br>
                   <a href='https://twitter.com/suratovvlad'>@suratovvlad</a><br>
                   <a href='https://github.com/suratovvlad'>GitHub</a>"
        }

        Text {
            textFormat: Text.RichText
            color: accentColor
            text: "Piskunov Ivan<br>
                  <a href='https://twitter.com/Van_ess0'>@Van_ess0</a><br>
                  <a href='https://github.com/van-ess0'>GitHub</a>"
        }
    }
}

