#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;

signals:
    void connexionSuccess();

public slots:
    void getDataConnexion(QNetworkReply *reply);

private slots:
    void clickBtnSignIn();

};

#endif // LOGIN_H
