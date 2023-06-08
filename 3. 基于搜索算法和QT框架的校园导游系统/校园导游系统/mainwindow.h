#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <graph.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void onReadButtonClicked();
    void onFindButtonClicked();

    void onStartButtonClicked();
    void onCancelButtonClicked();


private:

    QGraphicsScene *scene;
    QGraphicsView *view;

    QStringList dataArray;
    QPushButton *readButton;
    QPushButton *findButton;
    QPushButton *startButton;
    QPushButton *cancelButton;

    QLineEdit *startNodeLineEdit;
    QLineEdit *endNodeLineEdit;
    QLabel *resultLabel;

    Graph graph;

    void drawGraph();
    void addGraph();
};

#endif // MAINWINDOW_H
