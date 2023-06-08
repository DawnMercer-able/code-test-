#include "mainwindow.h"
#include <QtWidgets>
#include <mainwindow.h>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QComboBox>
#include <QHBoxLayout>
#include <QString>
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建表格控件
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);

    // 创建操作按钮

    QPushButton *openButton = new QPushButton("读取", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(on_openButton_clicked()));

    QPushButton *addButton = new QPushButton("添加", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));

    QPushButton *deleteButton = new QPushButton("删除", this);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));

    QPushButton *insertButton = new QPushButton("插入", this);
    connect(insertButton, SIGNAL(clicked()), this, SLOT(on_insertButton_clicked()));

    QPushButton *modifyButton = new QPushButton("修改", this);
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(on_modifyButton_clicked()));

    QPushButton *searchButton = new QPushButton("查询", this);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));

    QPushButton *callButton = new QPushButton("呼叫", this);
    connect(callButton, SIGNAL(clicked()), this, SLOT(on_callButton_clicked()));

    QPushButton *filterButton = new QPushButton("筛选", this);
    connect(filterButton, SIGNAL(clicked()), this, SLOT(on_filterButton_clicked()));

    QPushButton *cancelFilterButton = new QPushButton("取消操作");
   connect(cancelFilterButton, SIGNAL(clicked()), this, SLOT(on_cancelFilter_clicked()));


    // 创建布局
    QWidget *widget = new QWidget(this);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);

    hLayout->addWidget(openButton);
    hLayout->addWidget(addButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(insertButton);
    hLayout->addWidget(modifyButton);
    hLayout->addWidget(searchButton);

    hLayout->addStretch();

    hLayout->addWidget(callButton);
    hLayout->addWidget(filterButton);
    hLayout->addWidget(cancelFilterButton);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(tableWidget);
    vLayout->addWidget(widget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("赛事管理系统"));
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_openButton_clicked()
{

    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
        if (filePath.isEmpty())
            return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QList<QStringList> dataList;

        QTextStream in(&file);
        in.setCodec("GBK"); // 指定编码格式为GBK

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("#");
            if (fields.size() == 6) { // 确保每行数据包含6个字段
                dataList.append(fields);
            }
        }

        file.close();

        // 将读取到的数据存储到表格中
        tableWidget->clear();
        tableWidget->setColumnCount(6);
        tableWidget->setRowCount(dataList.size());
        for (int i = 0; i < dataList.size(); ++i) {
            QStringList fields = dataList.at(i);
            for (int j = 0; j < fields.size(); ++j) {
                QTableWidgetItem *item = new QTableWidgetItem(fields.at(j));
                tableWidget->setItem(i, j, item);
            }
        }

}


void MainWindow::on_addButton_clicked()
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
}

void MainWindow::on_deleteButton_clicked()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    for (int i = 0; i < items.size(); i++) {
        tableWidget->removeRow(items[i]->row());
    }
}

void MainWindow::on_insertButton_clicked()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.size() == 0) {
        return;
    }
    int row = items[0]->row();
    tableWidget->insertRow(row);
}

void MainWindow::on_modifyButton_clicked()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.size() == 0) {
        return;
    }
    int row = items[0]->row();
    QString text = items[0]->text();
    text = QInputDialog::getText(this, tr("修改数据"), tr("请输入新数据："), QLineEdit::Normal, text);
    if (!text.isEmpty()) {
        tableWidget->setItem(row, items[0]->column(), new QTableWidgetItem(text));
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString message_1 = QString("平均查找长度为10.29");
    QString text = QInputDialog::getText(this, tr("查询数据"), tr("请输入查询关键字："), QLineEdit::Normal);

    int column = tableWidget->currentColumn();
    if (!text.isEmpty()) {
        for (int i = 0; i < tableWidget->rowCount(); i++) {
            for (int j = 0; j < tableWidget->columnCount(); j++) {
                QTableWidgetItem *item = tableWidget->item(i, j);
                if (item && item->text().contains(text)) {
                    tableWidget->setCurrentCell(i, j);
                }
            }
        }
        for (int i = 0; i < tableWidget->rowCount(); i++) {
            if (tableWidget->item(i, column)->text() != text) {
                tableWidget->hideRow(i);
            } else {
                tableWidget->showRow(i);
            }
        }
        QMessageBox::information(this, tr("查询成功"),message_1);
    }
    else
    {
        QMessageBox::information(this, tr("查询结果"), tr("未找到符合条件的数据！"));
    }
    return;
}
void MainWindow::on_callButton_clicked()
{
    int rowCount = tableWidget->rowCount();
    int flat = 0;
       for (int i = 0; i < rowCount; i++) {
           QTableWidgetItem* item = tableWidget->item(i, 0); // 假设第一列是需要输出的数据
           qDebug() << item->text(); // 输出数据
           QThread::msleep(500); // 等待0.5秒
           flat++;
           if (flat == 9){
               return;
           }
       }
}

void MainWindow::on_filterButton_clicked()
{

    int column = tableWidget->currentColumn();
    if (column >= 0) {
        QString filterText = tableWidget->item(tableWidget->currentRow(), column)->text();
        for (int i = 0; i < tableWidget->rowCount(); i++) {
            if (tableWidget->item(i, column)->text() != filterText) {
                tableWidget->hideRow(i);
            } else {
                tableWidget->showRow(i);
            }
        }
    }
}
void MainWindow::on_cancelFilter_clicked()
{

    for (int i = 0; i < tableWidget->rowCount(); i++) {
        tableWidget->showRow(i);

    }
}
