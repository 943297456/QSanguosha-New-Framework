import QtQuick 2.4
import Cardirector.Resource 1.0
import "Client"

Item {
    id: root

    ClientSettings {
        id: config
    }

    ImageProvider {
        id: mogaraImage
        providerId: "mogara"

        function imagePath(imageId, requestedSize)
        {
            return ":/image/mogara/" + imageId + ".png";
        }
    }

    ImageProvider {
        providerId: "background"

        function imagePath(imageId, requestedSize) {
            // We prefer to using compact pictures as background to save storage space
            // @todo: consider supporting more common image formats
            return ":/image/background/" + imageId + ".jpg";
        }
    }

    ImageProvider {
        providerId: "tileicon"

        function imagePath(imageId, requestedSize) {
            return ":/image/tileIcon/" + imageId + ".png"
        }
    }

    Loader {
        id: splashLoader
        anchors.fill: parent
        z: 100
        focus: true
        source: "Gui/Splash.qml"

        Connections {
            target: splashLoader.item
            onDisappearing: startSceneLoader.source = "Gui/StartScene.qml";
            onDisappeared: splashLoader.source = "";
        }
    }

    Loader {
        id: startSceneLoader
        anchors.fill: parent
    }

    Loader {
        id: dialogLoader
        z: 100
        anchors.fill: parent
        onSourceChanged: startSceneLoader.visible = (source == "");
    }
}
