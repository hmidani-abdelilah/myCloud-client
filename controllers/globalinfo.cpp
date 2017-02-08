#include "globalinfo.h"

QString Color::GlobalInfo::grey = "2F3436";
QString Color::GlobalInfo::greySolid = "25292A";
QString Color::GlobalInfo::lightBlue = "7aa8df";
QString Color::GlobalInfo::lightBlueSelection = "B5C6D8";
QString Color::GlobalInfo::greyLight = "F3F5F5";
QString Color::GlobalInfo::white = "FFFFFF";
QString Color::GlobalInfo::greyBorder = "EAECEC";

QByteArray Server::GlobalInfo::sid = "";

QString Font::GlobalInfo::name = "Open Sans";

QString StyleSheet::GlobalInfo::tree = "QTreeView::branch:has-siblings:!adjoins-item {" \
        "border-image: url(:/tree/vline) 0;"\
    "}"\

    "QTreeView::branch:has-siblings:adjoins-item {"\
        "border-image: url(:/tree/branch-more) 0;"\
    "}"\

    "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"\
        "border-image: url(:/tree/branch-end) 0;"\
    "}"\

    "QTreeView::branch:has-children:!has-siblings:closed,"\
    "QTreeView::branch:closed:has-children:has-siblings {"\
            "border-image: none;"\
            "image: url(:/tree/branch-closed);"\
    "}"\

    "QTreeView::branch:open:has-children:!has-siblings,"\
    "QTreeView::branch:open:has-children:has-siblings  {"\
            "border-image: none;"\
            "image: url(:/tree/branch-open);"\
    "};";
