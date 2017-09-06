#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

void startupError(const char *);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &pri, const QString &sec, QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_tbPrimary_clicked();

    void on_tbSecondary_clicked();

    void on_pushButton_clicked();

private:
    QString m_pri;
    QString m_sec;
    QString m_pri_old;
    QString m_sec_old;

    Ui::MainWindow *ui;
    void update_labels(void);
};

#endif // MAINWINDOW_H
