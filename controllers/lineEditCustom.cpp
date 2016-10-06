#include "lineEditCustom.h"
#include <QCoreApplication>
#include <QKeyEvent>

LineEditCustom::LineEditCustom(QWidget *parent) : QLineEdit(parent)
{
    this->setStyleSheet("background-color:#1A1D22; padding-left:3px;margin-left:13px;margin-right:13px;");
    this->_placeHolder = true;
    this->changeTextColor(QString("#CCCCCC"));
    this->setAttribute(Qt::WA_MacShowFocusRect, 0);
    this->setMinimumHeight(35);
}

void LineEditCustom::focusInEvent(QFocusEvent *) {
    if (_placeHolder == true) {
        _placeHolder = false;
        savPlaceHolder = this->text();
        this->changeTextColor(QString("#FFFFFF"));
        this->setText("");
    }
}


void LineEditCustom::focusOutEvent(QFocusEvent *) {
    if (_placeHolder == false && this->text().length() == 0) {
        _placeHolder = true;
        this->changeTextColor(QString("#CCCCCC"));
        this->setText(savPlaceHolder);
    }
}

void LineEditCustom::changeTextColor(QString color) {
    QPalette pal = QPalette();
    QColor colorText = QColor(color);
    pal.setColor(QPalette::Text, colorText);
    this->setPalette(pal);
}
