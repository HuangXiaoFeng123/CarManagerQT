#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionCar_triggered();
    connectDB();
    initData();
}

MainWindow::~MainWindow(void)
{
    delete ui;
}

void MainWindow::on_actionCar_triggered(void)
{
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");
}

void MainWindow::on_actionCalc_triggered(void)
{
    ui->stackedWidget->setCurrentWidget(ui->calc);
    ui->label->setText("销售统计");
}

void MainWindow::connectDB(void)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("car");
    if(!db.open())
    {
        QMessageBox::warning(this,"error",db.lastError().text());
        return ;
    }
}

void MainWindow::initData(void)
{
    QSqlQueryModel *queryModel =new QSqlQueryModel(this);
    queryModel->setQuery("select name from factory;");
    ui->comboBoxFactory->setModel(queryModel);
    ui->labelLast->setText("0");
    ui->lineEditTotal->setEnabled(false);
}

void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1=="请选择厂家")
    {
        ui->comboBoxBrand->clear();    //品牌清空
        ui->lineEditPriece->clear();    //报价清空
        ui->labelLast->setText("0");    //剩余数量清空
        ui->lineEditTotal->clear();     //金额清空
        ui->spinBox->setValue(0);       //数量选择框
        ui->spinBox->setEnabled(false);
        ui->ButtonSure->setEnabled(false);
    }
    else
    {
        ui->comboBoxBrand->clear();
        QSqlQuery query;
        QString sql=QString("select name from brand where factory='%1';").arg(arg1);
        query.exec(sql);
        while(query.next())
        {
            QString name=query.value("name").toString();
            ui->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true);
    }
}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql=QString("select price,last from brand where factory='%1' and name='%2';").arg(ui->comboBoxFactory->currentText()).arg(arg1);
    query.exec(sql);
    while(query.next())
    {
        int price=query.value("price").toInt();
        int last=query.value("last").toInt();
        ui->lineEditPriece->setText(QString::number(price));
        ui->labelLast->setText(QString::number(last));
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if(arg1!=0)
    {
        ui->ButtonSure->setEnabled(true);
    }
    else
    {
        ui->ButtonSure->setEnabled(false);
    }
    QSqlQuery query;
    QString factoryStr=ui->comboBoxFactory->currentText();
    QString brandStr=ui->comboBoxBrand->currentText();
    QString sql=QString("select sum,last from brand where factory='%1' and name='%2';").arg(factoryStr).arg(brandStr);
    query.exec(sql);
    int last;
    while(query.next())
    {
        last=query.value("last").toInt();
    }
    if(arg1>last)
    {
        ui->spinBox->setValue(last);
        return ;
    }
    int tempNum=last-arg1;
    ui->labelLast->setText(QString::number(tempNum));
    int priece=ui->lineEditPriece->text().toInt();
    int tempsum=priece*arg1;
    ui->lineEditTotal->setText(QString::number(tempsum));
}

void MainWindow::on_ButtonCancel_clicked(void)
{
    ui->comboBoxFactory->setCurrentIndex(0);
    ui->labelLast->setText("0");
}

void MainWindow::on_ButtonSure_clicked(void)
{
    int num=ui->spinBox->value();   //销售数量
    int last=ui->labelLast->text().toInt();   //剩余
    QSqlQuery query;
    QString sql=QString("select sell from brand where factory='%1' and name='%2';")
            .arg(ui->comboBoxFactory->currentText()).arg(ui->comboBoxBrand->currentText());
    query.exec(sql);
    int sell;
    while(query.next())
    {
        sell=query.value("sell").toInt();
    }
    sell+=num;
    sql=QString("update brand set sell=%1,last=%2 where factory='%3' and name='%4';")
                .arg(sell)
                .arg(last)
                .arg(ui->comboBoxFactory->currentText())
                .arg(ui->comboBoxBrand->currentText());
    query.exec(sql);
    ui->ButtonSure->setEnabled(false);
    on_ButtonCancel_clicked();
}
