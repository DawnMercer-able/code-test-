#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <graph.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    setFixedSize(1500, 900);
    scene = new QGraphicsScene(this);

    view = new QGraphicsView(scene, this);
    view->setGeometry(10, 10, 1000, 800);

    readButton = new QPushButton("读取地点", this);
    readButton->setGeometry(1200, 50, 150, 30);
    connect(readButton, &QPushButton::clicked, this, &MainWindow::onReadButtonClicked);


    findButton = new QPushButton("查询地点", this);
    findButton->setGeometry(1200, 100, 150, 30);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindButtonClicked);

    startButton = new QPushButton("开始计算", this);
    startButton->setGeometry(1200, 150, 150, 30);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);

    cancelButton = new QPushButton("取消计算", this);
    cancelButton->setGeometry(1200, 200, 150, 30);
    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelButtonClicked);



    QLabel *startNodeLabel = new QLabel("起始节点：", this);
    startNodeLabel->setGeometry(1200, 250, 80, 30);
    startNodeLineEdit = new QLineEdit(this);
    startNodeLineEdit->setGeometry(1280, 250, 70, 30);

    QLabel *endNodeLabel = new QLabel("终止节点：", this);
    endNodeLabel->setGeometry(1200, 300, 80, 30);
    endNodeLineEdit = new QLineEdit(this);
    endNodeLineEdit->setGeometry(1280, 300, 70, 30);

    resultLabel = new QLabel("", this);
    resultLabel->setGeometry(1200, 350, 150 ,30);

    drawGraph();
}

MainWindow::~MainWindow()
{
}
void MainWindow::onReadButtonClicked(){
        // 打开文件对话框
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));

        if (fileName != "")
        {
            QFile file(fileName);

            // 检查文件是否成功打开
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, tr("Error"), tr("没有打开文件"));
                return;
            }

            QTextStream in(&file);

            // 创建字符串数组

            while (!in.atEnd())
            {
                QString line = in.readLine();

                // 将每一行数据以逗号分隔并存储到字符串数组中
                dataArray = line.split(",");
            }
            QMessageBox::information(this, tr("完成"), tr("已经打开并记录地点"));
            file.close();


        }
    }

void MainWindow::onFindButtonClicked() {
    bool ok;
        QString input = QInputDialog::getText(this, tr("查找"), tr("请输入序号:"), QLineEdit::Normal, "", &ok);

        if (ok && !input.isEmpty())
        {
            // 遍历dataArray数组并查找匹配项
            for (int i = 0; i < dataArray.size(); i++)
            {
                if (i == input)
                {
                    qDebug() << dataArray[i];
                }
            }
        }
}

void MainWindow::onStartButtonClicked() {
   int startNode = startNodeLineEdit->text().toInt();
   int endNode = endNodeLineEdit->text().toInt();

   if (graph.getNodeCount() == 0) {
       resultLabel->setText("请先生成图");
       return;
   }

   if (startNode < 0 || startNode >= graph.getNodeCount() ||
           endNode < 0 || endNode >= graph.getNodeCount()) {
       resultLabel->setText("节点序号不合法");
       return;
   }

   graph.calculateShortestPath(startNode);

   for (int i = 0; i < graph.getNodeCount(); ++i) {
       QGraphicsEllipseItem *nodeItem = graph.getNodeItem(i);
       if (graph.getShortestPath(i)) {
           nodeItem->setBrush(QBrush(Qt::green));
       } else {
           nodeItem->setBrush(QBrush(Qt::white));
       }
   }

   resultLabel->setText(QString("最短路径长度为 %1").arg(graph.getShortestPathLength(endNode)));

}

void MainWindow::onCancelButtonClicked() {
    graph.cancelCalculate();
       for (int i = 0; i < graph.getNodeCount(); ++i) {
           QGraphicsEllipseItem *nodeItem = graph.getNodeItem(i);
           nodeItem->setBrush(QBrush(Qt::white));
       }
}


void MainWindow::drawGraph() {
    int nodeCount = 12;

    //设定节点位置
    QPointF nodePositions[] = {QPointF(628, 75), QPointF(783, 188), QPointF(768, 356),
                               QPointF(837, 455), QPointF(798, 601),QPointF(578, 672),
                               QPointF(494, 586), QPointF(419, 482),QPointF(389, 360),
                               QPointF(494, 266), QPointF(164, 467),QPointF(93, 586)};
    for (int i = 0; i < nodeCount; ++i) {

        QGraphicsEllipseItem *nodeItem = scene->addEllipse(0, 0, 30, 30, QPen(Qt::black), QBrush(Qt::white));

        nodeItem->setPos(nodePositions[i]);

        QGraphicsTextItem *labelItem = scene->addText(QString::number(i));//标签实例化
        labelItem->setPos(nodeItem->pos().x()+5 , nodeItem->pos().y()+5);//标签位置

        graph.addNode(nodeItem, labelItem);
    }

}
