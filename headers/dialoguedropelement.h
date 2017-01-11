#ifndef DIALOGUEDROPELEMENT_H
#define DIALOGUEDROPELEMENT_H

#include "element.h"
#include "dialogdropheaderelement.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QFileDialog>

class DialogueDropElement : public QDialog
{
public:
    DialogueDropElement();

public:
    void setFiles(QVector<DataElement> fileDatas);

    QString getSelectedPath();

private slots:
    void slotDirectoryEntered(const QString &directory);
private:
    QVector<DataElement>    _itemsSelected;
    DialogDropHeaderElement *_header;
    void createHeaderWithOneFile(DataElement fileData);
    void createHeaderWithMultiFiles(QVector<DataElement> fileDatas);
    QFileDialog *_fileDialog;
};

#endif // DIALOGUEDROPELEMENT_H
