#ifndef FACTORYFONT_H
#define FACTORYFONT_H

#include <QFont>

class FactoryFont
{
public:
    FactoryFont(QString name);

    FactoryFont size(int size);
    FactoryFont styleName(QString styleName);
    FactoryFont letterSpacing(int spacing);
    FactoryFont weight(int weight);
    QFont gen();

private:
    QFont _font;
};

#endif // FACTORYFONT_H
