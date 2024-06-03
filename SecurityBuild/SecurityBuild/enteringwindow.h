#ifndef BUILDINGSSECURITY_ENTERINGWINDOW_H
#define BUILDINGSSECURITY_ENTERINGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QTcpSocket>
#include "./ui_authorization.h"
#include "./ui_registration.h"
#include "authorizationwindow.h"
#include "registrationwindow.h"

class EnteringMenu : public QMainWindow {
    Q_OBJECT
public:
    EnteringMenu(QWidget* parent = nullptr): QMainWindow(parent){}

public slots:
    void registrationTheAccount() {
        if (!_connected) {
            QMessageBox::critical(nullptr, "Ошибка", "Нет подключения к серверу. Пожалуйста, установите соединение с сервером.");
            return;
        }
        RegistrationMenu* window = new RegistrationMenu(this, &socket_for_registration);
        Ui::Registration registrationMenu;
        registrationMenu.setupUi(window);
        window->lineEdit_firstName = registrationMenu.lineEdit_firstName;
        window->lineEdit_secondName = registrationMenu.lineEdit_secondName;
        window->lineEdit_thirdName = registrationMenu.lineEdit_thirdName;
        window->lineEdit_login = registrationMenu.lineEdit_login;
        window->lineEdit_email = registrationMenu.lineEdit_email;
        window->lineEdit_password = registrationMenu.lineEdit_password;
        window->lineEdit_repeatedPassword = registrationMenu.lineEdit_repeatedPassword;
        window->show();
    };

    void enterTheAccount() {
        if (!_connected) {
            QMessageBox::critical(nullptr, "Ошибка", "Нет подключения к серверу. Пожалуйста, установите соединение с сервером.");
            return;
        }
        AuthorizationMenu* window = new AuthorizationMenu(this, &socket_for_authorization);
        Ui::Authorization authorizationMenu;
        authorizationMenu.setupUi(window);
        window->lineEdit_loginOrEmail = authorizationMenu.lineEdit_loginOrEmail;
        window->lineEdit_password = authorizationMenu.lineEdit_password;
        window->show();
    };

    void connectToServer(){
        socket_for_registration.connectToHost("127.0.0.1", 6666);
        socket_for_authorization.connectToHost("127.0.0.1", 6665);
        bool connected_first = socket_for_registration.waitForConnected(1000);
        bool connected_second = socket_for_authorization.waitForConnected(1000);
        if (connected_first && connected_second){
            QMessageBox::information(nullptr, "Успех", "Подключение к серверу успешно установлено.");
            _connected = true;
        } else {
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к серверу: "
                + socket_for_registration.errorString() + " " + socket_for_authorization.errorString());
            _connected = false;
        }
    };
private:
    bool _connected = false;
    QTcpSocket socket_for_registration;
    QTcpSocket socket_for_authorization;
};

#endif //BUILDINGSSECURITY_ENTERINGWINDOW_H
