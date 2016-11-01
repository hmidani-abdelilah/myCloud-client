#ifndef PANEL_H
#define PANEL_H

#include "btnleftmenu.h"
#include "managerelements.h"
#include "ui_panel.h"
#include "globalinfo.h"
#include "flowlayout.h"
#include "folderelement.h"
#include "fileelement.h"
#include "filemanager.h"
#include "qlabelcustom.h"
#include "transfertpage.h"
#include "viewfilespage.h"
#include <QIcon>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include "displaypath.h"

namespace Ui {
class Panel;
}

class Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();

    enum TypeHeaderBar {
        MANAGE_ELEMENTS,
        TRANSFERT_PAGE
    };

public slots:
    void btnMenuClicked(QString title);
    void getPreviousPath();

private:
    BtnLeftMenu     *createBtnLeftMenu(QPixmap picture, QString title, bool value = false);
  //  void            configureHeaderBarManageElements();
    void            setHeaderBar(TypeHeaderBar type);


private:
    Ui::Panel               *ui;
    QHBoxLayout             *_headerManageElements;
    QHBoxLayout             *_headerTransfertPage;

    QVector<BtnLeftMenu*>   *_listBtnLeftMenu;
    QPushButton             *_btnBack;
    ViewFilesPage           *_viewFilesPage;

    QLabelCustom            *_previousAction;
    DisplayPath             *_displayPath;
    TransfertPage           *_transfertPage;
    QVector<QWidget*>       *_listPages;
    void initializeHeaderBar();
};

#endif // PANEL_H
