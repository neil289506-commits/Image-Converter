#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QImage>
#include <QFileInfo>
#include <QMessageBox>
#include <QIcon>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupLanguage(); // 先偵測語言

    this->setWindowTitle(textTitle);
    this->setWindowIcon(QIcon(":/images/logo.ico"));
    this->resize(500, 300);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // --- 來源欄位 ---
    mainLayout->addWidget(new QLabel(textSource));
    QHBoxLayout *srcLayout = new QHBoxLayout();
    inputPathEdit = new QLineEdit();
    QPushButton *btnSrc = new QPushButton("...");
    srcLayout->addWidget(inputPathEdit);
    srcLayout->addWidget(btnSrc);
    mainLayout->addLayout(srcLayout);

    // --- 儲存欄位 (新增) ---
    mainLayout->addWidget(new QLabel(textSave));
    QHBoxLayout *saveLayout = new QHBoxLayout();
    savePathEdit = new QLineEdit();
    QPushButton *btnSave = new QPushButton("...");
    saveLayout->addWidget(savePathEdit);
    saveLayout->addWidget(btnSave);
    mainLayout->addLayout(saveLayout);

    // --- 格式選擇 ---
    mainLayout->addWidget(new QLabel(textFormat));
    formatCombo = new QComboBox();
    formatCombo->addItems({"PNG", "JPG", "BMP", "WEBP", "ICO", "TIFF", "AVIF", "ICNS"});
    mainLayout->addWidget(formatCombo);

    // --- 轉換按鈕 ---
    mainLayout->addSpacing(15);
    QPushButton *convertBtn = new QPushButton(textBtn);
    convertBtn->setFixedHeight(40);
    statusLabel = new QLabel(textReady);
    mainLayout->addWidget(convertBtn);
    mainLayout->addWidget(statusLabel);

    setCentralWidget(centralWidget);

    // 連接訊號
    connect(btnSrc, &QPushButton::clicked, this, &MainWindow::selectSource);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::selectSaveDir);
    connect(convertBtn, &QPushButton::clicked, this, &MainWindow::convertImage);
}

void MainWindow::setupLanguage() {
    QLocale locale = QLocale::system();
    // 判斷是否為繁體或簡體中文
    if (locale.language() == QLocale::Chinese) {
        textTitle = "圖片格式轉換器";
        textSource = "來源圖片路徑:";
        textSave = "儲存目標資料夾:";
        textFormat = "目標格式:";
        textBtn = "開始轉換";
        textReady = "狀態: 準備就緒";
    } else {
        textTitle = "Image Converter";
        textSource = "Source Image Path:";
        textSave = "Save Target Directory:";
        textFormat = "Target Format:";
        textBtn = "Start Convert";
        textReady = "Status: Ready";
    }
}

void MainWindow::selectSource() {
    QString path = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.webp *.ico *.tiff *.avif *.icns)");
    if (!path.isEmpty()) {
        inputPathEdit->setText(path);
        // 自動預設儲存資料夾為來源資料夾
        if (savePathEdit->text().isEmpty()) {
            savePathEdit->setText(QFileInfo(path).absolutePath());
        }
    }
}

void MainWindow::selectSaveDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", savePathEdit->text());
    if (!dir.isEmpty()) savePathEdit->setText(dir);
}

void MainWindow::convertImage() {
    QString input = inputPathEdit->text();
    QString saveDir = savePathEdit->text();
    QString target = formatCombo->currentText();

    if (input.isEmpty() || saveDir.isEmpty()) return;

    QImage img;
    if (!img.load(input)) {
        statusLabel->setText("Error: Load failed");
        return;
    }

    QFileInfo info(input);
    QString outputPath = saveDir + "/" + info.baseName() + "." + target.toLower();

    if (img.save(outputPath, target.toLatin1().data())) {
        statusLabel->setText("Success: " + QFileInfo(outputPath).fileName());
        QMessageBox::information(this, "Done", "Saved to:\n" + outputPath);
    } else {
        statusLabel->setText("Error: Save failed");
    }
}