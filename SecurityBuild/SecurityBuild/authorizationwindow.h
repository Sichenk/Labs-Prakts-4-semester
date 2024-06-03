#ifndef BUILDINGSSECURITY_AUTHORIZATIONMAINWINDOW_H
#define BUILDINGSSECURITY_AUTHORIZATIONMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include "./ui_emailconfirm.h"
#include "emailconfirmwindow.h"

class AuthorizationMenu : public QMainWindow {
    Q_OBJECT
public:
    QLineEdit* lineEdit_loginOrEmail = nullptr;
    QLineEdit* lineEdit_password = nullptr;

    AuthorizationMenu(QWidget* parent = nullptr, QTcpSocket* socket = nullptr): QMainWindow(parent), socket(socket) {}

private:
    int random_code = 0;
    QString sqlQuery = nullptr;
    QString last_name = nullptr;
    QString first_name = nullptr;
    QString middle_name = nullptr;
    QString username = nullptr;
    QString email = nullptr;
    QString password = nullptr;
public slots:
    QString hashString(const QString& data) {
        QByteArray dataBytes = data.toUtf8();
        QByteArray hashData = QCryptographicHash::hash(dataBytes, QCryptographicHash::Sha256);
        QString hashString = QString(hashData.toHex());
        return hashString.left(8);
    };
    void authorizeTheAccount() {
        QString searchLoginOrEmail = lineEdit_loginOrEmail->text();
        QString searchPassword = lineEdit_password->text();
        searchPassword = hashString(searchPassword);

        QString sqlQuery = "SELECT * FROM accounts_users WHERE ( username = '"
                           + searchLoginOrEmail + "' OR email = '" + searchLoginOrEmail + "' ) AND password = '" + searchPassword + "'";
        socket->write(sqlQuery.toUtf8());
        socket->waitForBytesWritten();
        connect(socket, &QTcpSocket::readyRead, this, &AuthorizationMenu::readResponse);
    };
    void readResponse() {
        QByteArray responseData = socket->readLine();
        QString response = QString::fromUtf8(responseData);
        if (!response.trimmed().isEmpty()) {
            QStringList parts = response.trimmed().split(QRegularExpression("[\\s()=]"), Qt::SkipEmptyParts);
            if (parts[0] == "SUCCESS") {
                last_name = parts[1];
                first_name = parts[2];
                middle_name = parts[3];
                username = parts[4];
                email = parts[5];
                password = parts[6];

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> dis(100000, 999999);
                random_code = dis(gen);

                EmailConfirmationMenu* window = new EmailConfirmationMenu(this, random_code, email, "SUCCESSFUL AUTHORIZATION", socket, false,
                                                                          first_name, last_name, middle_name, username, password);
                Ui::EmailConfirm emailConfirm;
                emailConfirm.setupUi(window);
                window->lineEdit_codeFromEmail = emailConfirm.lineEdit_codeFromEmail;
                window->show();
            }
            else if (parts[0] == "FAILURE"){
                QMessageBox::critical(nullptr, "Ошибка", "Пользователь не найден");
            }
            else {
                QMessageBox::critical(nullptr, "Ошибка", "Неизвестная ошибка");
            }
        }
    };
    void cancel() {
        this->close();
    };
private:
    QTcpSocket* socket;
};

#endif //BUILDINGSSECURITY_AUTHORIZATIONMAINWINDOW_H
