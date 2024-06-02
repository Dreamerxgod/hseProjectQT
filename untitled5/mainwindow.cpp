#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    tableWidget = new QTableWidget(this);
    setCentralWidget(tableWidget);
    tableWidget->setColumnCount(23); // Adjust columns based on your CSV
    tableWidget->setHorizontalHeaderLabels({
        "Player Name", "Salary", "Position", "Age", "Team", "Games Played", "Games Started","Min/Game", "FG", "FGA", "3P", "3PA",
        "2P", "2PA", "ORB", "DRB", "AST", "STL", "BLK", "PF", "PTS", "Total minutes", "PER",
    });

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    addButton = new QPushButton("Add Player", this);
    deleteButton = new QPushButton("Delete Player", this);
    uploadButton = new QPushButton("Upload Dataset", this);
    dataAnalysisButton = new QPushButton("Data Analysis", this);
    uploadButton->setStyleSheet("background-color: red; color: white;");

    toolBar->addWidget(addButton);
    toolBar->addWidget(deleteButton);
    toolBar->addWidget(uploadButton);
    toolBar->addWidget(dataAnalysisButton);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addPlayer);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deletePlayer);
    connect(uploadButton, &QPushButton::clicked, this, &MainWindow::uploadDataset);
    connect(dataAnalysisButton, &QPushButton::clicked, this, &MainWindow::openDataAnalysis);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::readCSV(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            tableWidget->insertRow(row);
            for (int col = 0; col < fields.size(); ++col) {
                tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
            }
            ++row;
        }
        file.close();
    }
}

void MainWindow::writeCSV(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                rowData << tableWidget->item(row, col)->text();
            }
            out << rowData.join(",") << "\n";
        }
        file.close();
    }
}

void MainWindow::addPlayer() {
    QStringList labels = {
        "Player Name", "Salary", "Position", "Age", "Team", "Games Played", "Games Started","Min/Game", "FG", "FGA", "3P", "3PA",
        "2P", "2PA", "ORB", "DRB", "AST", "STL", "BLK", "PF", "PTS", "Total minutes", "PER",
    };

    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    for (int col = 0; col < labels.size(); ++col) {
        QString value = QInputDialog::getText(this, "Add Player", labels[col] + ":");
        tableWidget->setItem(row, col, new QTableWidgetItem(value));
    }

    writeCSV("data.csv");
}

void MainWindow::deletePlayer() {
    int row = tableWidget->currentRow();
    if (row != -1) {
        tableWidget->removeRow(row);
        writeCSV("data.csv");
    } else {
        QMessageBox::warning(this, "Delete Player", "No player selected");
    }
}

void MainWindow::uploadDataset() {
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV File", QDir::homePath() + "/Downloads", "CSV Files (*.csv)");
    if (!filename.isEmpty()) {
        tableWidget->setRowCount(0); // Clear existing rows
        readCSV(filename);
    }
}

void MainWindow::openDataAnalysis() {
    Dialog *dialog = new Dialog(this);
    dialog->exec();
}
