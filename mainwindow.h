#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void selectSource();   // 選擇來源
    void selectSaveDir();  // 選擇儲存資料夾
    void convertImage();   // 執行轉換

private:
    void setupLanguage();  // 設定語言邏輯

    QLineEdit *inputPathEdit;
    QLineEdit *savePathEdit;
    QComboBox *formatCombo;
    QLabel *statusLabel;
    
    // UI 文字變數 (為了動態語系)
    QString textTitle, textSource, textSave, textFormat, textBtn, textReady;
};

#endif