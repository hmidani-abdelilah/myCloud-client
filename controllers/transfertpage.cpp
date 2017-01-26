#include "transfertpage.h"
#include "transfertbar.h"
#include <QPushButton>

TransfertPage::TransfertPage() : Page()
{
    QWidget* spacer = new QWidget();
    _fileManager = FileManager::getInstanceFileM();
    _timer = new QTimer();
    _listBar = new QVector<TransfertBar *>;
    _layout = new QVBoxLayout();
    _barSelected = NULL;

    connect(_fileManager, &FileManager::startUploadFile, this, &TransfertPage::addNewTransfertBar);
    connect(_fileManager, &FileManager::fileDeletedInHistoric, this, &TransfertPage::slotDeleteTransfertBar);

    this->setContentsMargins(0, 0, 0, 0);

    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);

    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateData()));
    _timer->start(1000);

    _layout->addWidget(spacer);

    setLayout(_layout);
    setHeaderBar();
}

void TransfertPage::addNewTransfertBar(quint64 id) {

    TransfertBar *bar = new TransfertBar(_fileManager->getFile(id));

    connect(bar, &TransfertBar::clickOnDelete, this, &TransfertPage::slotDeleteAllFile);
    connect(bar, &TransfertBar::clicked, this, &TransfertPage::barHasBeenClicked);

    _listBar->append(bar);
    _layout->insertWidget(0, bar);
}

void TransfertPage::updateData() { // OPTIMISATION : Active this function only when we are on the transfertpage
    for (int i = 0 ; i < _listBar->length() ; i++) {
        if (_listBar->at(i))
            _listBar->at(i)->updateElement();
    }
    _timer->start(1000);
}

void TransfertPage::barHasBeenClicked (quint64 id) {
    for (int i = 0 ; i < _listBar->length() ; i++) {
        if (_listBar->at(i) && _listBar->at(i)->id() == id)
            _barSelected = _listBar->at(i);
        _listBar->at(i)->hasBeenSelected(_listBar->at(i)->id() == id);
    }
    updateHeaderBar();
}

void TransfertPage::slotDeleteTransfertBar(quint64 id)
{
    for (int i = 0 ; i < _layout->count() ; i++) {
        if (reinterpret_cast<TransfertBar*>(_layout->itemAt(i)->widget())->id() == id) {
            delete _layout->takeAt(i)->widget();
            break;
        }
    }

    for (int i = 0 ; i < _listBar->count() ; i++) {
        if (_listBar->at(i)->id() == id) {
            _listBar->removeAt(i);
            _fileManager->deleteFile(id);
        }
    }
}

void TransfertPage::updateHeaderBar() {
    if (_barSelected == NULL) {
        _deleteBtn->setEnabled(false);
        _pauseBtn->setEnabled(false);
        _startBtn->setEnabled(false);
        return;
    }

    switch (_barSelected->status()) {
    case InfoElement::Status::EN_COURS:
        _deleteBtn->setEnabled(true);
        _pauseBtn->setEnabled(true);
        _startBtn->setEnabled(false);
        break;
    case InfoElement::Status::PAUSE:
        _deleteBtn->setEnabled(true);
        _pauseBtn->setEnabled(false);
        _startBtn->setEnabled(true);
        break;
    case InfoElement::Status::DELETE:
        _deleteBtn->setEnabled(false);
        _pauseBtn->setEnabled(true);
        _startBtn->setEnabled(true);
        break;
    case InfoElement::Status::FINISH:
        _deleteBtn->setEnabled(true);
        _pauseBtn->setEnabled(false);
        _startBtn->setEnabled(false);
    default:
        break;
    }
}

void TransfertPage::setHeaderBar() {
    QHBoxLayout *layout = new QHBoxLayout();

    _deleteBtn = new QPushButton("Delete");
    _pauseBtn = new QPushButton("Pause");
    _startBtn = new QPushButton("Start");

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored);

    _deleteBtn->setEnabled(false);
    _pauseBtn->setEnabled(false);
    _startBtn->setEnabled(false);

    connect(_deleteBtn, &QPushButton::clicked, this, &TransfertPage::slotDeleteTransfert);
    connect(_pauseBtn, &QPushButton::clicked, this, &TransfertPage::slotPauseTransfert);
    connect(_startBtn, &QPushButton::clicked, this, &TransfertPage::slotStartTransfert);

    layout->addSpacerItem(spacer);
    layout->addWidget(_startBtn);
    layout->addWidget(_pauseBtn);
    layout->addWidget(_deleteBtn);
    _headerLayout->setLayout(layout);
}

void TransfertPage::slotDeleteTransfert() {
    slotDeleteAllFile(_barSelected);
    updateHeaderBar();
}

void TransfertPage::slotPauseTransfert() {
    _barSelected->changeStatusOfFile(InfoElement::Status::PAUSE);
    updateHeaderBar();
}

void TransfertPage::slotStartTransfert() {
    _barSelected->changeStatusOfFile(InfoElement::Status::EN_COURS);
    updateHeaderBar();
}

void TransfertPage::slotDeleteAllFile(TransfertBar *bar) { // delete file + historic
    if (bar == _barSelected)
    {
        _barSelected = NULL;
        updateHeaderBar();
    }
    bar->changeStatusOfFile(InfoElement::Status::DELETE);
}
