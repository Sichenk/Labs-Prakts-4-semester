#include "serverwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

int main(int argc, char *argv[]) {
    QString directoryName = "./databases";
    QDir directory;

    if (!directory.exists(directoryName)) {
        directory.mkdir(directoryName);
    }
    QString pathToDatabase = "./databases/users.db";

    // Проверяем, существует ли файл базы данных
    if (!QFile::exists(pathToDatabase)) {
        // Если файл базы данных не существует, создаем его
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(pathToDatabase);

        // Пытаемся открыть базу данных
        if (!db.open()) {
            QString errorMessage = "Ошибка открытия базы данных: " + db.lastError().text();
            QMessageBox::critical(nullptr, "Ошибка", errorMessage);
            return -1;
        }
        QSqlQuery query;
        if (!query.exec("CREATE TABLE accounts_users ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "first_name VARCHAR(50),"
                        "last_name VARCHAR(50),"
                        "middle_name VARCHAR(50),"
                        "username VARCHAR(50) UNIQUE,"
                        "email VARCHAR(100) UNIQUE,"
                        "password VARCHAR(255))")) {
            QString errorMessage = "Ошибка создания таблицы: " + query.lastError().text();
            QMessageBox::critical(nullptr, "Ошибка", errorMessage);
            return -1;
        }
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToDatabase);

    // Пытаемся открыть базу данных
    if (!db.open()) {
        QString errorMessage = "Ошибка открытия базы данных: " + db.lastError().text();
        QMessageBox::critical(nullptr, "Ошибка", errorMessage);
        return -1;
    }
    QApplication a(argc, argv);
    ServerMenu* window = new ServerMenu(nullptr);
    Ui::Server serverMenu;
    serverMenu.setupUi(window);
    window->show();
    return a.exec();
}
