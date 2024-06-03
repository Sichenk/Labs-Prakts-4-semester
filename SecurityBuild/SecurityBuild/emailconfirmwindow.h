#ifndef BUILDINGSSECURITY_EMAILCONFIRMWINDOW_H
#define BUILDINGSSECURITY_EMAILCONFIRMWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QMessageBox>
#include <QtNetwork>
#include <random>
#include "smtp.h"
#include "interactionwindow.h"
#include "./ui_interaction.h"

class EmailConfirmationMenu : public QMainWindow {
    Q_OBJECT
public:
    EmailConfirmationMenu(QWidget* parent = nullptr, const int& random_code = 0, const QString& email = nullptr,
                          const QString& sqlQuery = nullptr, QTcpSocket* socket = nullptr, bool from_registration_window = false,
                          const QString& first_name = nullptr,  const QString& last_name = nullptr,  const QString& middle_name = nullptr,
                          const QString& username = nullptr,  const QString& password = nullptr):
        QMainWindow(parent), from_registration_window(from_registration_window), random_code(random_code),
        email(email), sqlQuery(sqlQuery), socket(socket), first_name(first_name), last_name(last_name),
        middle_name(middle_name), username(username), password(password) {
        sendCodeToEmail();
    }

    QLineEdit* lineEdit_codeFromEmail = nullptr;

private:
    bool from_registration_window = false;
    int random_code;
    QString email;
    QString sqlQuery;
    QTcpSocket* socket;
    Smtp *smtp = nullptr;

    QString first_name;
    QString last_name;
    QString middle_name;
    QString username;
    QString password;
public slots:
    void sendAgain(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(100000, 999999);
        random_code = dis(gen);
        sendCodeToEmail();
    };
    void check_registration(){
        if (from_registration_window) {
            to_registration();
        }
        else {
            to_authorize();
        }
    };
    void to_registration(){
        QString random_codeQString = QString::number(random_code);
        if (random_codeQString == lineEdit_codeFromEmail->text()) {
            socket->write(sqlQuery.toUtf8());
            socket->waitForBytesWritten();
            QMessageBox::information(nullptr, "Успех", "Пользователь успешно зарегистрирован.");
            this->close();
            QWidget* parentWindow = this->parentWidget();
            if (parentWindow) {
                parentWindow->close(); // Закрытие родительского окна
            }
        }
        else {
            QMessageBox::critical(nullptr, "Ошибка", "Код неверен.");
        }
    };
    void to_authorize(){
        QString random_codeQString = QString::number(random_code);
        if (random_codeQString == lineEdit_codeFromEmail->text()) {
            QWidget* parentWindow = this->parentWidget();
            this->close(); // Закрытие текущего окна
            if (parentWindow) {
                parentWindow->close(); // Закрытие родительского окна
            }
            InteractionMenu* window = new InteractionMenu(this, first_name, last_name, middle_name, username, email, password);
            Ui::Interaction interactionMenu;
            interactionMenu.setupUi(window);
            window->lineEdit_cameraIndex = interactionMenu.lineEdit_cameraIndex;
            window->show();
        }
        else {
            QMessageBox::critical(nullptr, "Ошибка", "Код неверен.");
        }
    };
    void sendCodeToEmail() {
        QString subject = "Verification code";
        QString body = QString::number(random_code);

        QString smtpUser = "nik.silchenko.2020@gmail.com";
        QString smtpPass = "jzdszhyxrgjcdrmh";
        QString smtpHost = "smtp.gmail.com";
        int smtpPort = 465;
        int smtpTimeout = 30000;

        // Создание объекта Smtp и отправка письма
        smtp = new Smtp(smtpUser, smtpPass, smtpHost, smtpPort, smtpTimeout);
        connect(smtp, &Smtp::status, this, [](const QString &status) {
            QMessageBox::information(nullptr, "Статус отправки", status);
        });
        smtp->sendMail(smtpUser, email, subject, body);
    };
};

#endif // BUILDINGSSECURITY_EMAILCONFIRMWINDOW_H
