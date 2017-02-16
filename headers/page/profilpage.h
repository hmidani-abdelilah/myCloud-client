#ifndef PROFILPAGE_H
#define PROFILPAGE_H

#include "page.h"
#include "boxglobalutilization.h"
#include "boxdata.h"
#include "boxtranfert.h"
#include "pathrequest.h"

class ProfilPage : public Page
{
public:
    ProfilPage(QWidget *parent = 0);

protected:
    void setHeaderBar();
    BoxGlobalUtilization *_boxGlobalUtilization;
    BoxTranfert          *_boxTransfert;
    BoxData              *_boxData;
    PathRequest          *_pathRequest;

private slots:
    void responseStatsRepository(QNetworkReply *reply);
};

#endif // PROFILPAGE_H
