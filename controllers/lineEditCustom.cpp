#include "lineEditCustom.h"
#include "globalinfo.h"
#include <QCoreApplication>
#include <QKeyEvent>

LineEditCustom::LineEditCustom(QWidget *parent) : QLineEdit(parent)
{
    this->setStyleSheet(StyleSheet::GlobalInfo::input);

    this->setMinimumHeight(35);
    this->setContentsMargins(13, 0, 13, 0);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_MacShowFocusRect, 0);
    setPlaceholderText("email");
}
