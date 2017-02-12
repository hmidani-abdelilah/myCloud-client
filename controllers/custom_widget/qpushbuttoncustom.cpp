#include "qpushbuttoncustom.h"
#include "generator.h"
#include "globalinfo.h"

#include <QPainter>

QPushButtonCustom::QPushButtonCustom(QString title) : QPushButton(title)
{

}

void QPushButtonCustom::enterEvent(QEvent *)
{
    if (isEnabled())
        this->setIcon(Generator::changeLogoColor(this->icon().pixmap(this->iconSize()), Color::GlobalInfo::white));
}

void QPushButtonCustom::leaveEvent(QEvent *)
{
    if (isEnabled())
        this->setIcon(Generator::changeLogoColor(this->icon().pixmap(this->iconSize()), Color::GlobalInfo::mainBleu));
}
