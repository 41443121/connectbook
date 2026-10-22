#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include<QFile>
#include<QDebug>
QString mFilename = "C:/test/myfile.txt";
void Write(QString Filename,QString str)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return ;
    }
    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 設定表格欄位與初始無資料
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"學號", "班級", "姓名", "電話"});
    ui->tableWidget->setRowCount(0); // 確保建置時 widget 中無資料[cite: 1]
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_importButton_clicked()
{
    // 選擇指定的 csv 檔案
    QString filePath = QFileDialog::getOpenFileName(this, "選擇 CSV 檔案", "", "CSV 檔案 (*.csv);;所有檔案 (*.*)");

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "錯誤", "無法開啟檔案！");
        return;
    }

    QTextStream in(&file);
    ui->tableWidget->setRowCount(0); // 匯入前先清空
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(','); // 依逗號分隔 CSV 資料

        ui->tableWidget->insertRow(row);
        // 依序對應 4 個欄位：學號、班級、姓名、電話[cite: 6]
        for (int col = 0; col < fields.size() && col < 4; ++col) {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields[col].trimmed()));
        }
        row++;
    }

    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;

    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,-1,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow4);




}


void MainWindow::on_pushButton_2_clicked()
{
    QString saveFile="";
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=ui->tableWidget->item(i,j)->text()+",";
        }
        saveFile+="\n";
    }
    Write(mFilename,saveFile);
}

