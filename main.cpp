#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>

int getCurrentSettings(QString &primary, QString &secondary)
{
    int flag = 0;

    QFile rcfile(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/customrc");

    if (!rcfile.exists()) {
        startupError("Cannot locate Klone settings. Check your installation.");
        flag = 1;
    }

    QSettings settings(rcfile.fileName(), QSettings::NativeFormat);
    primary = settings.value("Primary").toString();
    secondary = settings.value("Secondary").toString();

    return flag;
}

void startupError(const char *message)
{
    QMessageBox mb;
    mb.setText(message);
    mb.setWindowTitle("Klone Config Error");
    mb.setIcon(QMessageBox::Critical);
    mb.exec();
}

int main(int argc, char *argv[])
{
    QString colorPrimary("");
    QString colorSecondary("");
    QApplication a(argc, argv);

    if (getCurrentSettings(colorPrimary, colorSecondary) == 1)
        return 1;

    MainWindow w(colorPrimary, colorSecondary);
    w.show();

    return a.exec();

}
