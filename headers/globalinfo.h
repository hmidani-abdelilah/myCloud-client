#ifndef GLOBALINFO_H
#define GLOBALINFO_H

#include <QString>
#include "boxdatabaritem.h"

namespace Color {
    class GlobalInfo
    {
    public:
        GlobalInfo();
        static QString grey;
        static QString greyHover;
        static QString mainBleu;
        static QString greySolid;
        static QString lightBlue;
        static QString greyLight;
        static QString white;
        static QString greyBorder;
        static QString lightBlueSelection;
        static QString greyText;
        static QString greyBorderElement;
        static QString backgroundLoginView;
    };
}

namespace ColorTransfertBar {
    class GlobalInfo
    {
        public:
        GlobalInfo();
        static QString grey;
    };
}

namespace Server {
    class GlobalInfo
    {
    public:
        GlobalInfo();
        static QByteArray sid;
        static BoxDataBarItem *uploadBarItem;
        static BoxDataBarItem *downloadBarItem;
    };
}

namespace Application {
    class GlobalInfo {
        public:
            GlobalInfo();
            static Qt::ApplicationState appState;
            static int notificationNumber;
    };
}
namespace Font {
    class GlobalInfo
    {
    public:
        GlobalInfo();
        static QString name;
    };
}

namespace StyleSheet {
    class GlobalInfo
    {
    public:
        GlobalInfo();
        static QString tree;
        static QString scrollBarVertical;
        static QString scrollBarHorizontal;
        static QString button;
        static QString input;
    };
}

#endif // GLOBALINFO_H
