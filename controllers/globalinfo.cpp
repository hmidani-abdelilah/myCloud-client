#include "globalinfo.h"

QString Color::GlobalInfo::grey = "2F3436";
QString Color::GlobalInfo::greyHover = "535c5f";
QString Color::GlobalInfo::greySolid = "25292A";
QString Color::GlobalInfo::lightBlue = "7aa8df";
QString Color::GlobalInfo::lightBlueSelection = "B5C6D8";
QString Color::GlobalInfo::mainBleu = "556080";
QString Color::GlobalInfo::greyLight = "F3F5F5";
QString Color::GlobalInfo::white = "FFFFFF";
QString Color::GlobalInfo::greyBorder = "EAECEC";
QString Color::GlobalInfo::greyText = "5b5b5b";
QString Color::GlobalInfo::greyBorderElement = "C6C6C6";
QString Color::GlobalInfo::backgroundLoginView = "282D31";

BoxDataBarItem* Server::GlobalInfo::uploadBarItem = NULL;
BoxDataBarItem* Server::GlobalInfo::downloadBarItem = NULL;

QString ColorTransfertBar::GlobalInfo::grey = "EDEDED";

QByteArray Server::GlobalInfo::sid = "";

QString Font::GlobalInfo::name = "Open Sans";

QString StyleSheet::GlobalInfo::tree = "QTreeView::branch:has-siblings:!adjoins-item {" \
                                       "border-image: url(:/tree/vline) 0;"\
                                       "}"\
                                       "QTreeWidget::item:selected {}"\
                                       "QTreeWidget::item:hover {background-color:#" + ColorTransfertBar::GlobalInfo::grey + "}"\
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

QString StyleSheet::GlobalInfo::scrollBarVertical =
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

QString StyleSheet::GlobalInfo::scrollBarHorizontal =
        "QScrollBar:horizontal {"\
        "border: 1px solid #f2f2f2;"\
        "background: #fcfcfc;"\
        "height: 10px;"\
        "margin: 0px 0px 0px 0px;"\
        "}"\
        "QScrollBar::handle:horizontal {"\
        "background: #e0e0e0;"\
        "min-width: 20px;"\
        "}"\
        "QScrollBar::handle:active:horizontal {"\
        "background: #d0d0d0;"\
        "min-width: 20px;"\
        "}"\
        "QScrollBar::add-line:horizontal {"\
        "border: 0px solid #f2f2f2;"\
        "background: #32CC99;"\
        "width: 0px;"\
        "subcontrol-position: right;"\
        "subcontrol-origin: margin;"\
        "}"\

        "QScrollBar::sub-line:horizontal {"\
        "border: 0px solid grey;"\
        "background: #32CC99;"\
        "width: 0px;"\
        "subcontrol-position: left;"\
        "subcontrol-origin: margin;"\
        "}"\
        "QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:horizontal {"\
        "border: 0px solid grey;"\
        "width: 0px;"\
        "height: 0px;"\
        "background: white;"\
        "}"\

        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"\
        "background: none;"\
        "}";

QString StyleSheet::GlobalInfo::button =
        "QPushButton {"\
        "background-color:#" + Color::GlobalInfo::white +";"\
        "border-radius: 10px;"\
        "border: 2px solid #" + Color::GlobalInfo::mainBleu + ";"\
        "}"\
        "QPushButton:hover {"\
        "background-color:#" + Color::GlobalInfo::mainBleu +";"\
        "color:#" + Color::GlobalInfo::white +";"\
        "}";

QString StyleSheet::GlobalInfo::input =
        "QLineEdit {"\
        "background-color:#1A1D22;"\
        "border: 1px solid #DDDDDD;"\
        "color:#FFFFFF;"\
        "padding-left:3px;"\
        "qproperty-frame: false;"\
        "}"\
        "QLineEdit:focus {"\
        "background-color:#FFFFFF;"\
        "border: 1px solid #000000;"\
        "color:#000000;"\
        "padding-left:3px;"\
        "qproperty-frame: false;"\
        "}";
