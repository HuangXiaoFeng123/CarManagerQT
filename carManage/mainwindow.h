#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include "donxml.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);
    void connectDB(void);
    void initData(void);

private slots:
    void on_actionCar_triggered(void);
    void on_actionCalc_triggered(void);
    void on_comboBoxFactory_currentIndexChanged(const QString &arg1);
    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_ButtonCancel_clicked(void);
    void on_ButtonSure_clicked(void);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
