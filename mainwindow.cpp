#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mImageButton = new ImageButton(this);
    connect(mImageButton, &QPushButton::clicked, this, &MainWindow::onImageButtonClicked);

    // Инициализация QMediaPlayer и QAudioOutput
    mPlayer = new QMediaPlayer(this);
    mAudioOutput = new QAudioOutput(this);
    mPlayer->setAudioOutput(mAudioOutput);

    // Получаем текущий рабочий каталог приложения
    QString currentPath = QCoreApplication::applicationDirPath();

    // Строим путь к файлу звука относительно текущего каталога
    QString relativePath = currentPath + "/../sound/snap.mp3";

    // Проверяем существование файла
    QFile file(relativePath);
    if (!file.exists()) {
        qDebug() << "Файл звука не найден!";
    } else {
        // Устанавливаем источник мультимедиа для QMediaPlayer
        mPlayer->setSource(QUrl::fromLocalFile(relativePath));
        qDebug() << "Файл звука найден и установлен!";
    }
    mAudioOutput->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mPlayer;
    delete mAudioOutput;
}

void ImageButton::toggleState()
{
    setDown();
}

void MainWindow::onImageButtonClicked()
{
    // Воспроизводим звук при нажатии кнопки
    mPlayer->play();

    // Изменяем изображение кнопки
    mImageButton->toggleState();
}

ImageButton::ImageButton(QWidget *parent) : QPushButton(parent), mIsDown(true)
{
    mButtonUpPixmap = QPixmap(":/images/on.png");
    mButtonDownPixmap = QPixmap(":/images/off.png");
    mCurrentButtonPixmap = mButtonDownPixmap;
    setFixedSize(100, 100);
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

void ImageButton::setDown()
{
    mCurrentButtonPixmap = (mIsDown) ? mButtonUpPixmap : mButtonDownPixmap;
    mIsDown = !mIsDown;
    update();
}
