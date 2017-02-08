#ifndef DIALOGUEDROPELEMENT_H
#define DIALOGUEDROPELEMENT_H

#include "element.h"
#include "dialogdropheaderelement.h"
#include "statselement.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QFileDialog>

class DialogueDropElement : public QDialog
{
public:
    DialogueDropElement();

public:
    void setFiles(QVector<StatsElement::Stats> fileDatas);

    QString getSelectedPath();

private slots:
    void slotDirectoryEntered(const QString &directory);
private:
    QVector<StatsElement::Stats>    _itemsSelected;
    DialogDropHeaderElement *_header;
    void createHeaderWithOneFile(StatsElement::Stats fileData);
    void createHeaderWithMultiFiles(QVector<StatsElement::Stats> fileDatas);
    QFileDialog *_fileDialog;
};

#endif // DIALOGUEDROPELEMENT_H
