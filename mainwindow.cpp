#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "logincredentials.h"
#include "passworddelegate.h";
#include <QString>;

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    mylist = ui->listWidget;
    mylist->setContextMenuPolicy(Qt::CustomContextMenu);
    mylist->setItemDelegate(new PasswordDelegate(mylist));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/sqlite-tools-win32-x86-3270200/passwords.db");

}

void MainWindow::ShowContextMenu(const QPoint &){
    QMenu* contextMenu = new QMenu();
    contextMenu->addAction("Delete", this, SLOT(deleteItem()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(!db.isOpen()) db.open();
    QSqlQuery query;

    query.exec("Select * From Passwords");

    while(query.next()){
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setData(Qt::DisplayRole, query.value(1).toString());
        newItem->setData(Qt::UserRole + 1, query.value(2).toString());
        newItem->setData(Qt::UserRole + 2, query.value(0).toString());
        mylist->addItem(newItem);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QListWidget* list = ui->listWidget;
    QString website = ui->lineEdit_3->text();
    QString username = ui->lineEdit_2->text();
    QString password = ui->lineEdit->text();

    db.open();
    QString query = "insert into passwords values ( '" + website + "', '" + username + "', '" +
            password + "')";
    QSqlQuery  res = db.exec(query);
    qDebug() << db.lastError().text();

    db.commit();

    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setData(Qt::DisplayRole, username);
    newItem->setData(Qt::UserRole + 1, password);
    newItem->setData(Qt::UserRole + 2, website);

    list->addItem(newItem);



}



void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{

    QMenu menu("contextMenu", this);
    QAction deleteItem("Delete", this);
    menu.addAction(&deleteItem);
    connect(&deleteItem, SIGNAL(triggered()), this, SLOT(deleteItem()));
    menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));

}

void MainWindow::deleteItem(){
    QListWidget* list = ui->listWidget;

    for( int i = 0 ; i < list->selectedItems().size() ; i++){
        QListWidgetItem *item = list->takeItem(list->currentRow());

        QString username =  item->data(Qt::DisplayRole).toString();
        QString password = item->data(Qt::UserRole +1).toString();
        QString website = item->data(Qt::UserRole + 2).toString();

        QString query  = "DELETE FROM 'passwords' WHERE website == '" + website +  "' and username == '" + username + "' and password == '" + password + "' ";

        QSqlQuery  res = db.exec(query);
        qDebug() << db.lastError().text();

        db.commit();

        delete item;
    }
}
