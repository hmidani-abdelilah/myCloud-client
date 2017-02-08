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
                                       "QTreeWidget::item:selected {}"
                                       "QTreeView {show-decoration-selected: 0;}"\

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

QString StyleSheet::GlobalInfo::scrollBar =
        "QScrollBar:vertical {"\
            "border: 1px solid #f2f2f2;"\
            "background: #fcfcfc;"\
            "width: 10px;"\
            "margin: 0px 0 0px 0;"\
        "}"\
        "QScrollBar::handle:vertical {"\
            "background: #e0e0e0;"\
            "min-height: 20px;"\
        "}"\
        "QScrollBar::handle:active:vertical {"\
            "background: #d0d0d0;"\
            "min-height: 20px;"\
        "}"\
        "QScrollBar::add-line:vertical {"\
            "border: 0px solid #f2f2f2;"\
            "background: #32CC99;"\
            "height: 0px;"\
            "subcontrol-position: bottom;"\
            "subcontrol-origin: margin;"\
        "}"\

        "QScrollBar::sub-line:vertical {"\
            "border: 0px solid grey;"\
            "background: #32CC99;"\
            "height: 0px;"\
            "subcontrol-position: top;"\
            "subcontrol-origin: margin;"\
        "}"\
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"\
            "border: 0px solid grey;"\
            "width: 0px;"\
            "height: 0px;"\
            "background: white;"\
        "}"\

        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"\
            "background: none;"\
        "}";
