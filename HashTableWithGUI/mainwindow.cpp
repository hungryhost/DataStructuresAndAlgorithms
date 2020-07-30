#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QTextCodec>
#include <QObject>
#include <bits/stdc++.h>
#include "QStandardItemModel"
#include "../hashtable/hashtable.h"
#include "QStandardItem"
#include <QStringListModel>

// THIS IS A MAINWINDOW FILE FOR LAB ¹ 2 (PART 2) (HASHTABLE)
// YURY BORODIN 2019


typedef   HashT<std::string, std::string> HashTableStrStr;
static QString filepathto = "";
static QString filepathfrom = "";
static HashTableStrStr nf1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->deleteButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->listButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::raiseError(){
    QMessageBox::information(0,"info", "File not\n specified");
    return;
}
void MainWindow::fillTheTable(QString pathToFile, int choice){

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item1, *item2;
    if(pathToFile == ""){

        ui->tableView->setModel(model);
        return;
    }
    std::string pathToFileste = pathToFile.toStdString();
    std::string line1, line2, linetest;
    std::fstream finas;
    finas.open(pathToFileste);
    if(choice == 2){
        QStringListModel *model1 = new QStringListModel(this);
        QStringList List;
        while(!finas.eof()){
            finas >> line1 >> line2;
            std::istringstream ss(line1);
            std::istringstream ss1(line2);
            std::string word1, word2;
            ss >> word1;
            QString qsWord1 = QString::fromStdString(word1);
            ss1 >> word2;
            List << qsWord1;
        }
        model1->setStringList(List);
        ui->listView->setModel(model1);
    }
    else if(choice == 1){
        QStringList horizontalHeader;
        horizontalHeader.append("Prof.");
        horizontalHeader.append("Stud.");
        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->setModel(model);
        int i = 0, j = 0, k = 0;
        while(!finas.eof()){
            finas >> line1 >> line2;
            std::istringstream ss(line1);
            std::istringstream ss1(line2);
            std::string word1, word2;
            ss >> word1;
            ss1 >> word2;
            QString qsWord1 = QString::fromStdString(word1);
            QString qsWord2 = QString::fromStdString(word2);
            item1 = new QStandardItem(qsWord1);
            item2 = new QStandardItem(qsWord2);
            model->setItem(j, i, item1);
            model->setItem(k, i+1, item2);
            j++;
            k++;
        }
    }
    else return;
}
void MainWindow::on_inputButton_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    filepathfrom = QFileDialog::getOpenFileName(this, tr("Open file"), "C://",
                "All files (*.*);;Text file (*.txt);;");
    if(::filepathfrom.toStdString() == "")
        raiseError();
    else{
        fillTheTable(::filepathfrom, 1);
        ui->deleteButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
        ui->listButton->setEnabled(true);
        ui->saveButton->setEnabled(true);
    }
}

void MainWindow::on_outputButton_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    filepathto = QFileDialog::getOpenFileName(this, tr("Open file"), "C://",
                "All files (*.*);;Text file (*.txt);;");
}

void MainWindow::on_clearButton_clicked()
{

    HashTableStrStr nf;
    QPushButton * b = qobject_cast<QPushButton *>(sender());
    QString filepath1 = filepathfrom;
    QString filepath2 = filepathto;
    std::string pathto = filepath2.toStdString();
    std::string path = filepath1.toStdString();
    b->setEnabled(false);
    if(path == ""){
        nf1.delAll();
        if(::nf1.count() == 0){
            ui->deleteButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->listButton->setEnabled(false);
            ui->saveButton->setEnabled(false);
            }
        fillTheTable("", 1);

    }
    else{
        if(pathto == ""){
            nf1.delAll();
            if(::nf1.count() == 0){
                ui->deleteButton->setEnabled(false);
                ui->clearButton->setEnabled(false);
                ui->listButton->setEnabled(false);
                ui->saveButton->setEnabled(false);

                }
            fillTheTable("", 1);

        }
        else{
            nf1.delAll();
            if(::nf1.count() == 0){
                ui->deleteButton->setEnabled(false);
                ui->clearButton->setEnabled(false);
                ui->listButton->setEnabled(false);
                ui->saveButton->setEnabled(false);
            }
            nf.input(path);
            nf.delAll();
            nf.output(path);
            fillTheTable(filepath1, 1);
            QStandardItemModel *model = new QStandardItemModel;
            ui->listView->setModel(model);
            ui->studName->clear();
            ui->studNameFind->clear();
            ui->profName->clear();
            ui->nameToDelete->clear();
            fillTheTable("", 1);
        }
    }

}

void MainWindow::on_addButton_clicked()
{
    QString filepath1 = filepathfrom;
    QString filepath2 = filepathto;
    std::string spathto =
      ("C:\\Users\\Yury Borodin\\Documents\\hashtable\\serviceFileGlobal.txt");
    std::string pathto = filepath2.toStdString();
    std::string path = filepath1.toStdString();
    HashTableStrStr nf;
    QString profName = ui->profName->text();
    QString studName = ui->studName->text();
    if(profName.toStdString() == ""){
        profName = "Professor";
    }
    if(studName.toStdString() == ""){
        studName = "Student";
    }
    if(path == "" && !profName.toStdString().empty() &&
            !studName.toStdString().empty()){
        nf1.add(profName.toStdString(), studName.toStdString());
        std::string pathto = spathto;
        nf1.output(pathto);
        QString path1 = QString::fromStdString(pathto);
        fillTheTable(path1, 1);
        ui->deleteButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
        ui->listButton->setEnabled(true);
        ui->saveButton->setEnabled(true);
        QStandardItemModel *model = new QStandardItemModel;
        ui->listView->setModel(model);
        ui->studName->clear();
        ui->studNameFind->clear();
        ui->profName->clear();
        ui->nameToDelete->clear();

    }else{
        nf.input(path);
        QString profName = ui->profName->text();
        QString studName = ui->studName->text();
        nf.add(profName.toStdString(), studName.toStdString());
        nf.output(path);
        ui->deleteButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
        ui->listButton->setEnabled(true);
        ui->saveButton->setEnabled(true);
        fillTheTable(::filepathfrom, 1);
        QStandardItemModel *model = new QStandardItemModel;
        ui->listView->setModel(model);
        ui->studName->clear();
        ui->studNameFind->clear();
        ui->profName->clear();
        ui->nameToDelete->clear();

    }
}

void MainWindow::on_listButton_clicked()
{
    QString filepath1 = filepathfrom;
    std::string pathto =
            "C:\\Users\\Yury Borodin\\Documents\\hashtable\\serviceFile.txt";
    QString filepath2 = QString::fromStdString(pathto);
    std::string path = filepath1.toStdString();
    HashTableStrStr nf;
    QString studName = ui->studNameFind->text();
    if(path == "" && nf1.count() == 0)
        raiseError();
    else if(nf1.count() != 0 && path == ""){
        if(studName.toStdString() ==  "") return;
        else{
            nf1.returnKeysByValue(studName.toStdString(), pathto);
            fillTheTable(QString::fromStdString(pathto), 2);
            ui->studName->clear();
            ui->studNameFind->clear();
            ui->profName->clear();
            ui->nameToDelete->clear();
        }
    }
    else{
        nf.input(path);
        if(studName.toStdString() ==  "") return; else {
            nf.returnKeysByValue(studName.toStdString(), pathto);
            fillTheTable(filepath2, 2);
            ui->studName->clear();
            ui->studNameFind->clear();
            ui->profName->clear();
            ui->nameToDelete->clear();
        }
    }

}

void MainWindow::on_deleteButton_clicked()
{
    QString filepath1 = filepathfrom;
    std::string pathto =
         "C:\\Users\\Yury Borodin\\Documents\\hashtable\\serviceFileGlobal.txt";
    std::string path = filepath1.toStdString();
   HashTableStrStr nf;
    QString keyToDel = ui->nameToDelete->text();
    if(path == "" && nf1.count() == 0)
        raiseError();
    else if(nf1.count() != 0 && path == ""){
        nf1.del(keyToDel.toStdString());
        nf1.output(pathto);
        if(nf1.count() == 0){
            ui->deleteButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->listButton->setEnabled(false);
            ui->saveButton->setEnabled(false);
            }
        fillTheTable(QString::fromStdString(pathto), 1);
        QStandardItemModel *model = new QStandardItemModel;
        ui->listView->setModel(model);
        ui->studName->clear();
        ui->studNameFind->clear();
        ui->profName->clear();
        ui->nameToDelete->clear();

    }
    else{
        nf.input(path);
        nf.del(keyToDel.toStdString());
        nf.output(path);
        if(nf.count() == 0){
            ui->deleteButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->listButton->setEnabled(false);
            ui->saveButton->setEnabled(false);

        }
        fillTheTable(::filepathfrom, 1);
        QStandardItemModel *model = new QStandardItemModel;
        ui->listView->setModel(model);
        ui->studName->clear();
        ui->studNameFind->clear();
        ui->profName->clear();
        ui->nameToDelete->clear();
    }
}

void MainWindow::on_saveButton_clicked()
{
     QString filepath2 = filepathto;
     if(filepath2.toStdString() == "")
         raiseError();
     else{
         if(nf1.count() == 0 && filepathfrom.toStdString() != ""){
              HashTableStrStr nf;
              nf.input(filepathfrom.toStdString());
              nf.output(filepathto.toStdString());
              QMessageBox::information(0,"info", "Saved!");
              ui->studName->clear();
              ui->studNameFind->clear();
              ui->profName->clear();
              ui->nameToDelete->clear();
         }else if(nf1.count() != 0  && filepathto.toStdString() != ""){
             nf1.output(filepath2.toStdString());
             QMessageBox::information(0,"info", "Saved!");
             ui->studName->clear();
             ui->studNameFind->clear();
             ui->profName->clear();
             ui->nameToDelete->clear();
         }
     }
}

