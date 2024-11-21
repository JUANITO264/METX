#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // Agregar icono a la vetana
    setWindowIcon(QIcon("panal.png"));
    //
    mDatabase = QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setHostName("localhost");
    mDatabase.setDatabaseName("apiario1"); // nombre de la base
    mDatabase.setPort(3306);    // puerto en donde esta
    mDatabase.setUserName("JUANCHO"); // usuario
    mDatabase.setPassword("12345"); // contraseña

    if (!mDatabase.open()){
        QMessageBox::critical(this, "ERROR", mDatabase.lastError().text());
        return;
    }

    mModel = new QSqlTableModel(this);
    mModel->setTable(""); // tabla
    mModel->select();   // toda la tabla
    ui->tableView->setModel(mModel);
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}



