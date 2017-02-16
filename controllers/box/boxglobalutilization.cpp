#include "headers/box/boxglobalutilization.h"
#include "qlabelcustom.h"
#include "globalinfo.h"
#include "generator.h"

#include <QLabel>
#include <QProgressBar>
#include <QPixmap>
#include <QFont>

BoxGlobalUtilization::BoxGlobalUtilization(QString title) : Box(title)
{
    QHBoxLayout *layoutMemoryUse = new QHBoxLayout();
    QHBoxLayout *layoutTotalMemory = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    _usedSize = new QLabel("4.45 Go");
    _sizeFree = new QLabel("2.54 To");
    _progressBar = new QProgressBar();
    _progressBar->setValue(50);

    QFont f = QFont(Font::GlobalInfo::name, 26);
    f.setStyleName("Moyen");
    f.setLetterSpacing(QFont::PercentageSpacing, 105);
    f.setWeight(400);

    _usedSize->setFont(f);
    _usedSize->setFixedHeight(40);

    layoutMemoryUse->setSpacing(20);
    layoutMemoryUse->addWidget(new QLabelCustom(":/logo/cloud", 50, 32));
    layoutMemoryUse->addWidget(_usedSize);

    layoutTotalMemory->addWidget(_progressBar);
    layoutTotalMemory->addWidget(_sizeFree);

    vLayout->addLayout(layoutMemoryUse);
    vLayout->addLayout(layoutTotalMemory);
    vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    addLayout(vLayout, 1, 0);
}

void BoxGlobalUtilization::setUsedSize(qint64 sizeUsed) {
    _usedSize->setText(Generator::getFormatSize(sizeUsed));
}

void BoxGlobalUtilization::setFreeSize(qint64 sizeFree) {
    _sizeFree->setText(Generator::getFormatSize(sizeFree));
}

void BoxGlobalUtilization::setProgressBarValue(int value) {
    _progressBar->setValue(value);
}
