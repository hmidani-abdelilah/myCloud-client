######################################################################
# Automatically generated by qmake (3.0) sam. sept. 17 18:06:51 2016
######################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_MAC_SDK = macosx10.12

QT += network
QT += core
QT += websockets
QT += svg
QT += macextras

LIBS+= -lcurl

INCLUDEPATH += $$PWD/headers\
            += $$PWD/headers/elements\
            += $$PWD/headers/request\
            += $$PWD/headers/message_box\
            += $$PWD/headers/exceptions\
            += $$PWD/headers/info_elements\
            += $$PWD/headers/helpers\
            += $$PWD/headers/page\
            += $$PWD/headers/factory\
            += $$PWD/headers/custom_widget\
            += $$PWD/headers/box


TEMPLATE = app
TARGET = my_cloud
ICON = my_cloud.icns

INCLUDEPATH += /Users/Aurelien/Qt/5.7/ios/mkspecs/macx-ios-clang/ios .

# Input
HEADERS += headers/btnleftmenu.h \
           headers/credentailstable.h \
           headers/filemanager.h \
           headers/flowlayout.h \
           headers/globalinfo.h \
           headers/jsonmanager.h \
           headers/lineEditCustom.h \
           headers/login.h \
           headers/mainwindow.h \
           headers/managerelements.h \
           headers/mycloudapplication.h \
           headers/panel.h \
           headers/custom_widget/qlabelcustom.h \
           headers/socketmanager.h \
           headers/userInfo.h \
           headers/elements/element.h \
           headers/elements/fileelement.h \
           headers/elements/folderelement.h \
           headers/request/filerequest.h \
           headers/request/pathrequest.h \
           headers/request/serviceRequest.h \
           headers/request/userrequest.h \
           headers/displaypath.h \
           headers/elementpath.h \
           headers/transfertbar.h \
           headers/page/transfertpage.h \
           headers/headerbar.h \
           headers/page/page.h \
           headers/page/viewfilespage.h \
           headers/message_box/messageboxnaming.h \
           headers/request/folderrequest.h \
           headers/request/routeparams.h \
           headers/exceptions/httperror.h \
           headers/exceptions/jsonerror.h \
           headers/info_elements/infoelement.h \
           headers/info_elements/downloadelement.h \
           headers/info_elements/uploadelement.h \
           headers/dialoguedropelement.h \
           headers/dialogdropheaderelement.h \
           headers/helpers/generator.h \
           headers/request/historicrequest.h \
           headers/elements/factoryelement.h \
           headers/statselement.h \
           headers/helpers/image.h \
           headers/page/sortpage.h \
           headers/treeelement.h \
           headers/treerepositoryserver.h \
           headers/itemrepositoryserver.h \
           headers/managerelementsorder.h \
           headers/factory/factorybutton.h \
           headers/custom_widget/qpushbuttoncustom.h \
    headers/page/profilpage.h \
    headers/box/box.h \
    headers/box/boxglobalutilization.h \
    headers/box/boxdata.h \
    headers/box/boxdatabaritem.h \
    headers/box/boxtranfert.h \
    headers/factory/factoryfont.h \
    headers/subscribepopup.h

FORMS += btnleftmenu.ui element.ui login.ui mainwindow.ui panel.ui \
    dialogdropheaderelement.ui
SOURCES += main.cpp \
           controllers/btnleftmenu.cpp \
           controllers/credentailstable.cpp \
           controllers/filemanager.cpp \
           controllers/flowlayout.cpp \
           controllers/globalinfo.cpp \
           controllers/jsonmanager.cpp \
           controllers/lineEditCustom.cpp \
           controllers/login.cpp \
           controllers/mainwindow.cpp \
           controllers/managerelements.cpp \
           controllers/mycloudapplication.cpp \
           controllers/panel.cpp \
           controllers/custom_widget/qlabelcustom.cpp \
           controllers/socketmanager.cpp \
           controllers/userInfo.cpp \
           controllers/elements/element.cpp \
           controllers/elements/fileelement.cpp \
           controllers/elements/folderelement.cpp \
           controllers/request/filerequest.cpp \
           controllers/request/pathrequest.cpp \
           controllers/request/serviceRequest.cpp \
           controllers/request/userrequest.cpp \
           controllers/page/transfertpage.cpp \
           controllers/displaypath.cpp \
           controllers/elementpath.cpp \
           controllers/transfertbar.cpp \
           controllers/headerbar.cpp \
           controllers/page/page.cpp \
           controllers/page/viewfilespage.cpp \
           controllers/message_box/messageboxnaming.cpp \
           controllers/request/folderrequest.cpp \
           controllers/request/routeparams.cpp \
           controllers/exceptions/httperror.cpp \
           controllers/exceptions/jsonerror.cpp \
           controllers/info_elements/infoelement.cpp \
           controllers/info_elements/downloadelement.cpp \
           controllers/info_elements/uploadelement.cpp \
           controllers/dialoguedropelement.cpp \
           controllers/dialogdropheaderelement.cpp \
           controllers/helpers/generator.cpp \
           controllers/request/historicrequest.cpp \
           controllers/elements/factoryelement.cpp \
           controllers/statselement.cpp \
           controllers/helpers/image.cpp \
           controllers/page/sortpage.cpp \
           controllers/treeelement.cpp \
           controllers/treerepositoryserver.cpp \
           controllers/itemrepositoryserver.cpp \
           controllers/managerelementsorder.cpp \
           controllers/factory/factorybutton.cpp \
           controllers/custom_widget/qpushbuttoncustom.cpp \
    controllers/page/profilpage.cpp \
    controllers/box/box.cpp \
    controllers/box/boxglobalutilization.cpp \
    controllers/box/boxdata.cpp \
    controllers/box/boxdatabaritem.cpp \
    controllers/box/boxtranfert.cpp \
    controllers/factory/factoryfont.cpp \
    controllers/subscribepopup.cpp

RESOURCES += assets.qrc
