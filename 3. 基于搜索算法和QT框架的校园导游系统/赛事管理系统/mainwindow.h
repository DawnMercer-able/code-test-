#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_openButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_insertButton_clicked();
    void on_modifyButton_clicked();
    void on_searchButton_clicked();
    void on_callButton_clicked();

    void on_filterButton_clicked();
    void on_cancelFilter_clicked();


private:
    QTableWidget *tableWidget;
    QComboBox *filterCombo;


};

#endif // MAINWINDOW_H
