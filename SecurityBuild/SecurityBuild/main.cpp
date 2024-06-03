#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QDir>
#include "enteringwindow.h"
#include "./ui_entering.h"
//#include "interactionwindow.h"
//#include "./ui_interaction.h"

int main(int argc, char *argv[]) {
    /*QApplication a(argc, argv);
    InteractionMenu window(nullptr, "Сильченко", "Никита", "Сергеевич", "sichenk", "nik.silchenko.2020@mail.ru", "12345678");
    Ui::Interaction interactionMenu;
    interactionMenu.setupUi(&window);
    window.lineEdit_cameraIndex = interactionMenu.lineEdit_cameraIndex;
    window.show();*/

    QApplication a(argc, argv);
    EnteringMenu window(nullptr);
    Ui::Entering enteringMenu;
    enteringMenu.setupUi(&window);
    window.show();

    return QApplication::exec();
}
