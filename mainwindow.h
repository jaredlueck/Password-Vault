#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;
    QListWidget* mylist;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void ShowContextMenu(const QPoint &);
    void deleteItem();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
