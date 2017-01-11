#include "dialoguedropelement.h"

#include <QPushButton>
#include <QFileSystemModel>
#include <QStandardPaths>

DialogueDropElement::DialogueDropElement()
{
    setAcceptDrops(true);
//    QHBoxLayout *toto = new QHBoxLayout(this);

    _fileDialog = new QFileDialog();
    _fileDialog->setLabelText(QFileDialog::Accept, "Download");
    _fileDialog->setLabelText(QFileDialog::FileName, "Directory");
    _fileDialog->setFileMode(QFileDialog::DirectoryOnly);
    _fileDialog->setOption(QFileDialog::DontUseNativeDialog, true);
    _fileDialog->setOption(QFileDialog::ShowDirsOnly, true);
    _fileDialog->setOption(QFileDialog::HideNameFilterDetails, true);
    _fileDialog->setOption(QFileDialog::ReadOnly);
    _fileDialog->setViewMode(QFileDialog::List);
    _fileDialog->setDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    connect(_fileDialog, &QFileDialog::accepted, this, &DialogueDropElement::accept);
    connect(_fileDialog, &QFileDialog::rejected, this, &DialogueDropElement::reject);
    _header = new DialogDropHeaderElement(this);
    QGridLayout *layout = new QGridLayout(this);

    layout->setMargin(0);
    layout->addWidget(_header);
    layout->addWidget(_fileDialog);
}

void DialogueDropElement::setFiles(QVector<DataElement> fileDatas)
{
    _itemsSelected = fileDatas;
    switch (fileDatas.size()) {
    case 0:
        qDebug("EXEPTION"); //TODO Thow exeption
        break;
    case 1:
        createHeaderWithOneFile(fileDatas[0]);
        break;
    default:
        createHeaderWithMultiFiles(fileDatas);
        break;
    }
}

QString DialogueDropElement::getSelectedPath() {
    return _fileDialog->directoryUrl().toString();
}

void DialogueDropElement::createHeaderWithOneFile(DataElement fileData) {
    _header->setInformation(fileData.image, fileData.name, fileData.path, "Created at 24h00 on 24 septembre", fileData.size);
}

void DialogueDropElement::createHeaderWithMultiFiles(QVector<DataElement> fileDatas) {
    _header->setInformation(QPixmap(":/logo/files"), QString::number(fileDatas.size()) + " files to upload", "multiple files path", "File created between 24/12/02 and today", 546);
}

