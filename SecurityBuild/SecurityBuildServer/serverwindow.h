#ifndef BUILDINGSSECURITY_SERVERWINDOW_H
#define BUILDINGSSECURITY_SERVERWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QStringList>
#include <QCryptographicHash>
#include "./ui_serverwindow.h"

class ServerMenu : public QMainWindow {
    Q_OBJECT
public:
    ServerMenu(QWidget *parent = nullptr): QMainWindow(parent) {
        connect(&server_for_reg, &QTcpServer::newConnection, this, &ServerMenu::newConnectionForReg);
        connect(&server_for_auth, &QTcpServer::newConnection, this, &ServerMenu::newConnectionForAuth);
    }
private:
    QString hashString(const QString& data) {
        QByteArray dataBytes = data.toUtf8();
        QByteArray hashData = QCryptographicHash::hash(dataBytes, QCryptographicHash::Sha256);
        QString hashString = QString(hashData.toHex());
        return hashString.left(8);
    };
public slots:
    void startServer() {
        bool first_ok = false, second_ok = false;
        if (server_for_reg.listen(QHostAddress::Any, 6666)) {
            first_ok = true;
        }
        if (server_for_auth.listen(QHostAddress::Any, 6665)) {
            second_ok = true;
        }
        if (first_ok && second_ok) {
            QMessageBox::information(nullptr, "Успех", "Сервер успешно запущен");
        }
    };

    void newConnectionForReg() {
        QTcpSocket *socket = server_for_reg.nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &ServerMenu::readData);
    };

    void newConnectionForAuth() {
        QTcpSocket *socket = server_for_auth.nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &ServerMenu::readData);
    };

    void readData() {
        // Получаем указатель на сокет, который готов к чтению
        QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

        // Читаем данные из сокета
        QByteArray data = socket->readAll();
        QString queryString;
        queryString.clear();
        queryString = QString::fromUtf8(data);

        // Определяем тип запроса
        QStringList query_parts = queryString.split(' ');
        QString queryType = query_parts[0] + " " + query_parts[1];
        QString successful = "1";
        // Выполняем соответствующие действия в зависимости от типа запроса
        if (queryType == "INSERT INTO") {
            handleInsertQuery(queryString);
        } else if (queryType == "SELECT *") {
            handleSelectQuery(queryString, socket);
        } else if (queryType == "SELECT COUNT(*)") {
            hanldeSelectCountQuery(queryString, socket);
        } else {
            // Неизвестный тип запроса
            qDebug() << "Неизвестный тип запроса:" << queryType;
        }
    };

    void handleInsertQuery(const QString& queryString) {
        QSqlQuery query(queryString);
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
            return;
        }
    };

    void handleSelectQuery(const QString& queryString, QTcpSocket* socket) {
        QSqlQuery query(queryString);
        // Выполняем запрос
        if (!query.exec()) {
            return;
        }
        QStringList parts = queryString.split(QRegularExpression("[\\s()=]"), Qt::SkipEmptyParts);
        QString username;
        QString email;
        QString password;

        // Обходим разделенные части запроса
        for (int i = 0; i < parts.size() - 1; i++) {
            QString key = parts[i];
            QString value = parts[i + 1];

            if (key == "username") {
                // Извлекаем подстроку без первого и последнего символов
                username = value.mid(1, value.length() - 2);
            } else if (key == "email") {
                // Извлекаем подстроку без первого и последнего символов
                email = value.mid(1, value.length() - 2);
            } else if (key == "password") {
                // Извлекаем подстроку без первого и последнего символов
                password = value.mid(1, value.length() - 2);
            }
        }
        // Обрабатываем результат запроса
        if (query.next()) {
            QString stored_username = query.value("username").toString();
            QString stored_email = query.value("email").toString();
            QString stored_password = query.value("password").toString();
            QString stored_first_name = query.value("first_name").toString();
            QString stored_last_name = query.value("last_name").toString();
            QString stored_middle_name = query.value("middle_name").toString();

            if ((username == stored_username || email == stored_email) && password == stored_password) {
                QString response = "SUCCESS ";
                response += stored_first_name + " " + stored_last_name + " " + stored_middle_name + " " +
                            stored_username + " " + stored_email + " " + stored_password;
                // Ответ обратно клиенту
                socket->write(response.toUtf8());
                socket->waitForBytesWritten();
            }
        } else {
            // Пользователь не найден
            QString response = "FAILURE";
            // Ответ обратно клиенту
            socket->write(response.toUtf8());
            socket->waitForBytesWritten();
        }
    };

    void hanldeSelectCountQuery(const QString& queryString, QTcpSocket* socket){
        QSqlQuery query(queryString);
        // Выполняем запрос
        if (!query.exec()) {
            return;
        }

        if (query.next()) {
            // Получаем значение COUNT(*) из результата запроса
            int count = query.value("COUNT(*)").toInt();

            // Преобразуем значение в строку
            QString countString = QString::number(count);
            // Отправляем результат клиенту
            QByteArray response = countString.toUtf8();
            socket->write(response);
            socket->waitForBytesWritten();
        } else {
            // Если запрос не вернул результатов, отправляем сообщение об ошибке клиенту
            QByteArray response = "FAILURE";
            socket->write(response);
            socket->waitForBytesWritten();
        }
    };

private:
    QTcpServer server_for_reg;
    QTcpServer server_for_auth;
};

#endif // SERVERWINDOW_H
