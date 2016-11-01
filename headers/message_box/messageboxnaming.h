#ifndef MESSAGEBOXNAMING_H
#define MESSAGEBOXNAMING_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class MessageBoxNaming : public QDialog
{

public:
    MessageBoxNaming(QString text, QString btnNamingText);
    QString text();

private:
    QLabel    *_mainText;
    QLineEdit *_input;
    QPushButton *_cancelBtn;
    QPushButton *_acceptBtn;
    QString     _recordText;

protected slots:
    void validate();
};

#endif // MESSAGEBOXNAMING_H
