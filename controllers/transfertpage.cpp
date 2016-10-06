#include "transfertpage.h"
#include "transfertbar.h"

TransfertPage::TransfertPage() : QVBoxLayout()
{
    QWidget* spacer = new QWidget();
    _fileManager = FileManager::getInstanceFileM();
    _timer = new QTimer();
    _listBar = new QVector<TransfertBar *>;
    connect(_fileManager, &FileManager::startUploadFile, this, &TransfertPage::addNewUpload);
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);
    this->setMargin(0);

    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateData()));
    _timer->start(1000);

    addWidget(spacer);
}

void TransfertPage::addNewUpload(QString id) {
    TransfertBar *bar = new TransfertBar(_fileManager->getFile(id));
    _listBar->append(bar);

    insertLayout(0, bar);
}

void TransfertPage::updateData() {
    for (int i = 0 ; i < _listBar->length() ; i++) {
        _listBar->at(i)->updateElement();
    }
    _timer->start(1000);
}
