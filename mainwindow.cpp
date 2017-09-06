#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QSettings>

MainWindow::MainWindow(const QString &pri, const QString &sec, QWidget *parent) :
    QMainWindow(parent),
    m_pri(pri),
    m_sec(sec),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_labels();
    m_pri_old = m_pri;
    m_sec_old = m_sec;

    QFile element(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/panel-background.svg");
    element.open(QIODevice::ReadWrite);
    QTextStream in (&element);
    QString contents = in.readAll();
    if (contents.contains("fill-opacity:0.6"))
        ui->rbTranslucent->setChecked(true);
    element.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_labels()
{
    QString priBackground = QString("color: white;background-color: #%1;").arg(m_pri);
    ui->labelPrimary->setStyleSheet(priBackground);
    QString secBackground = QString("color: white;background-color: #%1;").arg(m_sec);
    ui->labelSecondary->setStyleSheet(secBackground);
}

void MainWindow::on_tbPrimary_clicked()
{
    QString b = QString("#%1").arg(m_pri);
    QColor c = QColorDialog::getColor(b, this);
    if (c.isValid()) {
        QString tmp(c.name());
        m_pri = tmp.remove(0,1);
        update_labels();
    }
}

void MainWindow::on_tbSecondary_clicked()
{
    QString b = QString("#%1").arg(m_sec);
    QColor c = QColorDialog::getColor(b, this);
    if (c.isValid()) {
        QString tmp(c.name());
        m_sec = tmp.remove(0,1);
        update_labels();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QSettings settings(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/customrc",
                       QSettings::NativeFormat);
    // Primary colour grep
    QStringList priFiles;
    priFiles << "clock.svg" << "scrollbar.svg" << "tasks.svg" << "viewitem.svg";

    foreach (const QString &curFile, priFiles) {
        QFile element(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/" + curFile);
        element.open(QIODevice::ReadWrite);
        QTextStream in (&element);
        QString contents = in.readAll();
        contents.replace(m_pri_old, m_pri, Qt::CaseSensitive);
        element.seek(0);
        QTextStream out(&element);
        out << contents;
        element.close();
    }

    settings.setValue("Primary", m_pri);

    // Secondary colour grep
    QStringList secFiles;
    secFiles << "slider.svg" << "tasks.svg";

    foreach (const QString &curFile, secFiles) {
        QFile element(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/" + curFile);
        element.open(QIODevice::ReadWrite);
        QTextStream in (&element);
        QString contents = in.readAll();
        contents.replace(m_sec_old, m_sec, Qt::CaseSensitive);
        element.seek(0);
        QTextStream out(&element);
        out << contents;
        element.close();
    }

    settings.setValue("Secondary", m_sec);

    m_pri_old = m_pri;
    m_sec_old = m_sec;

    // Panel translucency
    QFile element(QDir::homePath() + "/.local/share/plasma/desktoptheme/Klone10/widgets/panel-background.svg");
    element.open(QIODevice::ReadWrite);
    QTextStream in (&element);
    QString contents = in.readAll();

    if (ui->rbOpaque->isChecked()) {
        contents.replace("fill:#030303;fill-opacity:0.6", "fill:#030303;fill-opacity:1.0", Qt::CaseSensitive);
    } else {
        contents.replace("fill:#030303;fill-opacity:1.0", "fill:#030303;fill-opacity:0.6", Qt::CaseSensitive);
    }

    element.seek(0);
    QTextStream out(&element);
    out << contents;
    element.close();

    system("kwriteconfig5 --file=plasmarc --group=Theme --key=name Default; \
                sleep 0.6; \
                kwriteconfig5 --file=plasmarc --group=Theme --key=name Klone10");
}
