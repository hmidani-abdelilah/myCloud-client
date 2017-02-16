#include "headers/factory/factoryfont.h"

FactoryFont::FactoryFont(QString name)
{
    _font = QFont(name);
}

FactoryFont FactoryFont::size(int size) {
    _font.setPixelSize(size);
    return *this;
}

FactoryFont FactoryFont::styleName(QString styleName) {
    _font.setStyleName(styleName);
    return *this;
}

FactoryFont FactoryFont::letterSpacing(int spacing) {
    _font.setLetterSpacing(QFont::PercentageSpacing, spacing);
    return *this;
}

FactoryFont FactoryFont::weight(int weight) {
    _font.setWeight(weight);
    return *this;
}

QFont FactoryFont::gen() {
    return _font;
}
