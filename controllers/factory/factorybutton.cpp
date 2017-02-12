#include "factorybutton.h"
#include "globalinfo.h"
#include "generator.h"

FactoryButton::FactoryButton(QString title)
{
    _btn = new QPushButtonCustom(title);
    _btn->setCursor(Qt::PointingHandCursor);
    _btn->setStyleSheet(StyleSheet::GlobalInfo::button);

    QFont f = QFont(Font::GlobalInfo::name, 9);
    f.setStyleName("Moyen");
    f.setLetterSpacing(QFont::PercentageSpacing, 105);
    f.setWeight(450);
    _btn->setFont(f);
}

FactoryButton FactoryButton::size(QSize sizeButton) {
    _btn->setFixedSize(sizeButton);
    return *this;
}

FactoryButton FactoryButton::icon(QString icon, QSize iconSize) {
    QPixmap picture = Generator::changeLogoColor(QIcon(icon).pixmap(iconSize), Color::GlobalInfo::mainBleu);

    _btn->setIcon(QIcon(picture));
    _btn->setIconSize(iconSize);
    return *this;
}

FactoryButton FactoryButton::font(QFont font) {
    _btn->setFont(font);
    return *this;
}

QPushButtonCustom *FactoryButton::gen() {
    return _btn;
}
