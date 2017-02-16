#include "profilpage.h"
#include "boxglobalutilization.h"
#include "jsonmanager.h"
#include "httperror.h"

#include <QPushButton>
#include <QSpacerItem>

ProfilPage::ProfilPage(QWidget *parent) : Page()
{
    QVBoxLayout *vBoxLayoutLeft = new QVBoxLayout();
    QVBoxLayout *vBoxLayoutRight = new QVBoxLayout();
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    _pathRequest = new PathRequest();

    connect(_pathRequest, &PathRequest::signalStatsRepository, this, &ProfilPage::responseStatsRepository);

    hBoxLayout->setContentsMargins(18, 18, 18, 18);

    _boxGlobalUtilization = new BoxGlobalUtilization("Global utilization");
    _boxData = new BoxData("Server data");
    _boxTransfert = new BoxTranfert("Transfert resume");

    _boxGlobalUtilization->setFixedHeight(130);
    vBoxLayoutLeft->addWidget(_boxGlobalUtilization);

    _boxData->setFixedHeight(180);
    vBoxLayoutRight->addWidget(_boxData);
    vBoxLayoutRight->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    _boxTransfert->setFixedHeight(110);
    vBoxLayoutLeft->addWidget(_boxTransfert);
    vBoxLayoutLeft->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    hBoxLayout->addLayout(vBoxLayoutLeft);
    hBoxLayout->addLayout(vBoxLayoutRight);

    vBoxLayoutLeft->setSpacing(18);
    vBoxLayoutRight->setSpacing(18);
    hBoxLayout->setSpacing(18);

        this->setStyleSheet("background-color:#FFFFFF;");
    _pathRequest->request(PathRequest::Type::GET, PathRequest::StatsRepository);

    setLayout(hBoxLayout);

    setHeaderBar();
}

void ProfilPage::responseStatsRepository(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    JsonManager json(reply);
    QMap<QString, QVariant> map;

    map = json.getJson();

    _boxGlobalUtilization->setFreeSize(map["totalSizeFree"].toLongLong());
    _boxGlobalUtilization->setUsedSize(map["totalSizeUsed"].toLongLong());
    _boxGlobalUtilization->setProgressBarValue(map["pourcentage"].toInt());

    _boxData->setValueBarItem("All of the files", map["totalSizeUsed"].toLongLong(), map["totalFiles"].toLongLong());
    _boxData->setValueBarItem("All of the folder", map["sizeFolders"].toLongLong(), map["totalFolders"].toLongLong());
    _boxData->setValueBarItem("All of the pictures", map["sizePictures"].toLongLong(), map["totalPictures"].toLongLong());
    _boxData->setValueBarItem("All of the movies", map["sizeMovies"].toLongLong(), map["totalMovies"].toLongLong());
}

void ProfilPage::setHeaderBar() {
    QHBoxLayout *layout = new QHBoxLayout();

    _headerLayout->setContentsMargins(0, 0, 12, 0);

    _headerLayout->setLayout(layout);
}
