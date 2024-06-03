#ifndef BUILDINGSSECURITY_INTERACTIONWINDOW_H
#define BUILDINGSSECURITY_INTERACTIONWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWidgets/QLineEdit>
#include <QDebug>
#include <QTcpSocket>
#include <QDir>
#include <QTimer>
#include <QImage>
#include <QFileInfo>
#include <QFileInfoList>
#include "./ui_profile.h"
#include "opencv2/core/cvdef.h"
#include "profilewindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <algorithm>

class InteractionMenu : public QMainWindow {
    Q_OBJECT
public:
    InteractionMenu(QWidget* parent = nullptr, const QString& firstName = nullptr, const QString& secondName = nullptr, const QString& thirdName = nullptr,
                    const QString& username = nullptr, const QString& email = nullptr, const QString& password = nullptr) : QMainWindow(parent),
        firstName(firstName), secondName(secondName), thirdName(thirdName), username(username), email(email), password(password) {

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &InteractionMenu::stopRecording);
        reconnectTimer = new QTimer(this);
        connect(reconnectTimer, &QTimer::timeout, this, &InteractionMenu::resetConnectionState);

        // Инициализация состояния подключения
        stopConnecting = true;
        manualStop = false;
        qDebug() << "I am in constructor!";
    }

    QString firstName = nullptr;
    QString secondName = nullptr;
    QString thirdName = nullptr;
    QString username = nullptr;
    QString email = nullptr;
    QString password = nullptr;
    QLineEdit* lineEdit_cameraIndex = nullptr;
    QLabel* labelForCamera = nullptr;
    QTimer* timer = nullptr;
    QTimer* reconnectTimer = nullptr; // Таймер для переподключения
private:
    bool stopConnecting = true;
    bool manualStop = false; // Флаг для отслеживания ручной остановки
    cv::VideoCapture capture;
    cv::VideoWriter video;
    const double MAX_FOLDER_SIZE = 50 * 1024; // 10 ГБ в байтах
    void cleanUpFolder(const QString& folderName) {
        QDir folder(folderName);
        QFileInfoList files = folder.entryInfoList(QDir::Files, QDir::Time | QDir::Reversed);
        double totalSize = 0;

        // Подсчет общего размера папки
        for (const QFileInfo& file : files) {
            totalSize += file.size() / 1024 / 1024;
        }
        qDebug () << totalSize << " " << MAX_FOLDER_SIZE;

        // Удаление старых файлов, пока общий размер не станет меньше 10 ГБ
        while (totalSize > MAX_FOLDER_SIZE && !files.isEmpty()) {
            QFileInfo oldestFile = files.takeLast();
            totalSize -= oldestFile.size();
            QFile::remove(oldestFile.filePath());
        }
    }

public slots:
    void connectToCamera() {
        if (!stopConnecting) {
            QMessageBox::warning(this, "Ошибка", "Сначала отключитесь от камеры");
            return;
        }
        if (lineEdit_cameraIndex->text().isEmpty() || lineEdit_cameraIndex->text().toInt() < 0) {
            QMessageBox::warning(this, "Ошибка", "Индекс камеры не должен быть пустым и должен быть больше 0");
            return;
        }

        try {
            capture.open(lineEdit_cameraIndex->text().toInt()); // Подключение к камере
            if (!capture.isOpened()) {
                throw std::runtime_error("Не удалось подключиться к вебкамере.");
            }

            stopConnecting = false;
            manualStop = false;

            QString folderName = "video_recordings_" + username + "/" + lineEdit_cameraIndex->text();
            QDir folder(folderName);
            if (!folder.exists()) {
                folder.mkpath(".");
            } else {
                qDebug() << "Папка" << folderName << "уже существует.";
            }

            std::time_t t = std::time(nullptr);
            std::stringstream ss;
            ss << folderName.toStdString() << "/video_" << t << ".avi";
            std::string filename = ss.str();

            // Отображение видео в окне
            cv::namedWindow("Camera", cv::WINDOW_NORMAL);
            cv::setWindowProperty("Camera", cv::WND_PROP_AUTOSIZE, cv::WINDOW_AUTOSIZE);

            int frame_width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
            int frame_height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
            video.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 15, cv::Size(frame_width, frame_height));
            if (!video.isOpened()) {
                throw std::runtime_error("Не удалось открыть файл для записи видео.");
            }

            timer->start(1800000); // 30 минут в миллисекундах

            const double brightnessThreshold = 80.0; // Порог яркости для переключения режимов

            cv::Mat frame, grayFrame, nightVisionFrame;
            while (!stopConnecting) {
                capture >> frame; // Получение кадра с камеры

                if (frame.empty()) {
                    throw std::runtime_error("Не удалось получить кадр с вебкамеры.");
                }

                cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

                cv::Scalar meanBrightness = cv::mean(grayFrame);

                if (meanBrightness[0] < brightnessThreshold) {
                    cv::Mat channels[] = { cv::Mat::zeros(grayFrame.size(), grayFrame.type()), grayFrame, cv::Mat::zeros(grayFrame.size(), grayFrame.type()) };
                    cv::merge(channels, 3, nightVisionFrame);
                    nightVisionFrame.convertTo(nightVisionFrame, -1, 2, 0);
                    cv::imshow("Camera", nightVisionFrame);
                    video.write(nightVisionFrame);
                } else {
                    cv::imshow("Camera", frame);
                    video.write(frame);
                }

                int key = cv::waitKey(1);
                if (key == 27) { // Остановка по нажатию клавиши ESC
                    stopConnecting = true;
                }
            }

            stopRecording();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Ошибка", e.what());
            stopRecording();
        }
    };

    void stopRecording() {
        stopConnecting = true;
        qDebug() << stopConnecting << " " << manualStop;
        timer->stop();

        if (capture.isOpened()) {
            capture.release();
        }
        if (video.isOpened()) {
            video.release();
        }
        cv::destroyAllWindows();

        QString folderName = "video_recordings_" + username + "/" + lineEdit_cameraIndex->text();
        cleanUpFolder(folderName);

        if (!manualStop) {
            reconnectTimer->start(1000); // Переподключение через 1 секунду
        }
    };

    void resetConnectionState() {
        reconnectTimer->stop();
        stopConnecting = true;
        connectToCamera();
    }

    void profile() {
        UserProfile* window = new UserProfile(this);
        Ui::Profile userProfile;
        userProfile.setupUi(window);
        window->lineEdit_firstName = userProfile.lineEdit_secondName;
        window->lineEdit_secondName = userProfile.lineEdit_firstName;
        window->lineEdit_thirdName = userProfile.lineEdit_thirdName;
        window->lineEdit_login = userProfile.lineEdit_login;
        window->lineEdit_email = userProfile.lineEdit_email;
        window->lineEdit_password = userProfile.lineEdit_password;
        window->initialize(firstName, secondName, thirdName, username, email, password);
        window->show();
    };

    void poweroff() {
        manualStop = true;
        stopConnecting = true;
        timer->stop();
        reconnectTimer->stop();
    };

    void exit() {
        manualStop = true;
        stopConnecting = true;
        timer->stop();
        reconnectTimer->stop();
        this->close();
    };

};

#endif // BUILDINGSSECURITY_INTERACTIONWINDOW_H
