#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QToolBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addPlayer();
    void deletePlayer();
    void uploadDataset();
    void openDataAnalysis();  // Add this line

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *uploadButton;
    QPushButton *dataAnalysisButton; // Add this line
    QToolBar *toolBar;

    void readCSV(const QString &filename);
    void writeCSV(const QString &filename);
};

#endif // MAINWINDOW_H
