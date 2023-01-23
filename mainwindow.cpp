#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(0);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP 1251"));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../db/db.db");

    if (db.open())
    {
//      ui->statusDB->setText("База данных "+db.databaseName()+" загружена!");
        model = new QSqlTableModel(this,db);
        model->setTable("patients");
        model->select();
        model->setHeaderData(0,Qt::Horizontal,"№",Qt::DisplayRole);
        model->setHeaderData(1,Qt::Horizontal,"Дата",Qt::DisplayRole);
        model->setHeaderData(2,Qt::Horizontal,"ФИО",Qt::DisplayRole);
        model->setHeaderData(3,Qt::Horizontal,"OD",Qt::DisplayRole);
        model->setHeaderData(4,Qt::Horizontal,"OS",Qt::DisplayRole);


        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    else
    {
//      ui->statusDB->setText("База данных "+db.databaseName()+" не загружена. Ошибка: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_diagnosticBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->frame->hide();
}


void MainWindow::on_listBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->frame->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_8_clicked()
{
        QString str;
        QString filename;
        filename =  ui->nameEdit->text()+"_"+ui->snameEdit->text();
        str = "Дата обследования: " + ui->dateEdit->text() + "\nИмя пациента:" + ui->nameEdit->text() +
              "\nФамилия пациента:" + ui->snameEdit->text() + "\nОтчество пациента:" + ui->mnameEdit->text() +
              "\nЖалобы:" + ui->comEdit->toPlainText() + "\nВизометрия:" + "\n OD с:" + ui->odsEdit->text() + " До: " +ui->odfEdit->text() +
              "\n OS с:" + ui->ossEdit->text() + " До: " +ui->osfEdit->text() + "\nАнамез заболевания:" + ui->anamEdit->toPlainText() +
              "\nДиогноз:" + ui->diagEdit->toPlainText();
        std::ofstream out;
        out.open(filename.toStdString() + ".txt");
        out << str.toStdString() << std::endl;
        out.close();

        QDate n(0, 0, 00);
        QString n1(' ');
        ui->nameEdit->setText(n1); ui->snameEdit->setText(n1); ui->mnameEdit->setText(n1); ui->comEdit->setPlainText(n1); ui->odsEdit->setText(n1); ui->odfEdit->setText(n1);
        ui->ossEdit->setText(n1); ui->osfEdit->setText(n1); ui->anamEdit->setPlainText(n1); ui->diagEdit->setPlainText(n1);
        ui->stackedWidget_2->setCurrentIndex(0);

}


void MainWindow::on_pushButton_3_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_helpBtn_clicked()
{
    ui->frame->hide();
}


void MainWindow::on_aboutBtn_clicked()
{
    ui->frame->hide();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}


void MainWindow::on_pushButton_clicked()
{
    model->removeRow(currentRow);
}


void MainWindow::on_pushButton_2_clicked()
{
    model->select();
}

