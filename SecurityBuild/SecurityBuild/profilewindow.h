#ifndef BUILDINGSSECURITY_PROFILEWINDOW_H
#define BUILDINGSSECURITY_PROFILEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWidgets/QLineEdit>

class UserProfile : public QMainWindow {
    Q_OBJECT
public:
    UserProfile(QWidget* parent = nullptr): QMainWindow(parent){}

    void initialize(QString& firstName, QString& secondName, QString& thirdName, QString& username, QString& email, QString& password) {

        lineEdit_firstName->setText(firstName);
        lineEdit_secondName->setText(secondName);
        lineEdit_thirdName->setText(thirdName);
        lineEdit_login->setText(username);
        lineEdit_email->setText(email);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setText(password);
    }

    QLineEdit* lineEdit_firstName = nullptr;
    QLineEdit* lineEdit_secondName = nullptr;
    QLineEdit* lineEdit_thirdName = nullptr;
    QLineEdit* lineEdit_login = nullptr;
    QLineEdit* lineEdit_email = nullptr;
    QLineEdit* lineEdit_password = nullptr;

};

#endif // PROFILEWINDOW_H
