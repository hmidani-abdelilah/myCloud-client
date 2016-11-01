#include "messageboxnaming.h"

MessageBoxNaming::MessageBoxNaming(QString text, QString btnNamingText) : QDialog()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _mainText = new QLabel(text);
    _input = new QLineEdit();
    _cancelBtn = new QPushButton("Cancel");
    _acceptBtn = new QPushButton(btnNamingText);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(_cancelBtn);
    btnLayout->addWidget(_acceptBtn);

    mainLayout->addWidget(_mainText);
    mainLayout->addWidget(_input);
    mainLayout->addLayout(btnLayout);

    connect(_cancelBtn, &QPushButton::clicked, this, &MessageBoxNaming::close);
    connect(_acceptBtn, &QPushButton::clicked, this, &MessageBoxNaming::validate);
    this->setLayout(mainLayout);
}

void MessageBoxNaming::validate() {
    _recordText = _input->text();
    _input->setText("");
    accept();
}

QString MessageBoxNaming::text() {
    return _recordText;
}
