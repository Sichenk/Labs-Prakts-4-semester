#ifndef BUILDINGSSECURITY_REGISTRATIONWINDOW_H
#define BUILDINGSSECURITY_REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtNetwork>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QCryptographicHash>
#include <random>
#include "emailconfirmwindow.h"
#include "./ui_emailconfirm.h"


class RegistrationMenu : public QMainWindow {
    Q_OBJECT
public:
    RegistrationMenu(QWidget* parent = nullptr, QTcpSocket* socket = nullptr): QMainWindow(parent), socket(socket) {}

    QLineEdit* lineEdit_firstName = nullptr;
    QLineEdit* lineEdit_secondName = nullptr;
    QLineEdit* lineEdit_thirdName = nullptr;
    QLineEdit* lineEdit_login = nullptr;
    QLineEdit* lineEdit_email = nullptr;
    QLineEdit* lineEdit_password = nullptr;
    QLineEdit* lineEdit_repeatedPassword = nullptr;

public slots:
    QString hashString(const QString& data) {
        QByteArray dataBytes = data.toUtf8();
        QByteArray hashData = QCryptographicHash::hash(dataBytes, QCryptographicHash::Sha256);
        QString hashString = QString(hashData.toHex());
        return hashString.left(8);
    };
    void registrate() {
        QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
        if (lineEdit_firstName->text() == nullptr || lineEdit_secondName->text() == nullptr ||
            lineEdit_thirdName->text() == nullptr || lineEdit_login->text() == nullptr ||
            lineEdit_email->text() == nullptr || lineEdit_password->text() == nullptr ||
            lineEdit_repeatedPassword->text() == nullptr) {
            QMessageBox::warning(nullptr, "Внимание", "Все обязательные поля должны быть заполнены.");
            return;
        }
        else if (!emailRegex.match( lineEdit_email->text()).hasMatch()) {
            QMessageBox::warning(nullptr, "Внимание", "Пожалуйста, введите корректный адрес электронной почты.");
            return;
        }
        else if (lineEdit_password->text() != lineEdit_repeatedPassword->text()) {
            QMessageBox::warning(nullptr, "Внимание", "Пароли не совпадают.");
            return;
        }
        else if (lineEdit_password->text().length() < 8){
            QMessageBox::warning(nullptr, "Внимание", "Пароль должен содержать минимум 8 символов.");
            return;
        }

        QString firstName = lineEdit_firstName->text();
        QString lastName = lineEdit_secondName->text();
        QString middleName = lineEdit_thirdName->text();
        QString username = lineEdit_login->text();
        QString email = lineEdit_email->text();
        QString password = lineEdit_password->text();
        password = hashString(password);
        QString repeated_password = lineEdit_repeatedPassword->text();

        QString sqlCheckUniqueQuery = "SELECT COUNT(*) FROM accounts_users WHERE username = '" + username + "' OR email = '" + email + "'";
        socket->write(sqlCheckUniqueQuery.toUtf8());
        socket->waitForBytesWritten();
        disconnect(socket, &QTcpSocket::readyRead, nullptr, nullptr);
        connect(socket, &QTcpSocket::readyRead, this, [=]() { handleReadyRead(firstName, lastName, middleName, username, email, password); });
    };
    void handleReadyRead(const QString &firstName, const QString &lastName, const QString &middleName,
                         const QString &username, const QString &email, const QString &password){
        QByteArray responseDataCheckUniqueQuery = socket->readLine();
        QString response = QString::fromUtf8(responseDataCheckUniqueQuery);
        QStringList parts = response.trimmed().split(QRegularExpression("[\\s()=]"), Qt::SkipEmptyParts);
        for(int i = 0; i < parts.size(); i++) {
            if (!parts[i].isEmpty()) {
                if (parts[i].toInt() == 0) {
                    QString sqlQuery = "INSERT INTO accounts_users (first_name, last_name, middle_name, username, email, password) "
                                       "VALUES ('" + firstName + "', '" +
                                       lastName + "', '" +
                                       middleName + "', '" +
                                       username + "', '" +
                                       email + "', '" +
                                       password + "')";
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> dis(100000, 999999);
                    random_code = dis(gen);

                    EmailConfirmationMenu* window = new EmailConfirmationMenu(this, random_code, email, sqlQuery, socket, true);
                    Ui::EmailConfirm emailConfirm;
                    emailConfirm.setupUi(window);
                    window->lineEdit_codeFromEmail = emailConfirm.lineEdit_codeFromEmail;
                    window->show();

                    /*socket->write(sqlQuery.toUtf8());
                    socket->waitForBytesWritten();
                    QMessageBox::information(nullptr, "Успех", "Пользователь успешно зарегистрирован.");
                    this->close();*/
                } else {
                    QMessageBox::warning(nullptr, "Ошибка", "Имя пользователя или адрес электронной почты уже заняты.");
                }
            }
        }

    };
    void cancel() {
        this->close();
    };
private:
    QTcpSocket* socket;
    int random_code = 0;
};

#endif //BUILDINGSSECURITY_REGISTRATIONWINDOW_H
