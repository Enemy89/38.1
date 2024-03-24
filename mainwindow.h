// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onImageButtonClicked();

private:
    Ui::MainWindow *ui;
    ImageButton *mImageButton;
    QMediaPlayer *mPlayer;
    QAudioOutput *mAudioOutput;
};

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton(QWidget *parent = nullptr);

    // Публичный метод для изменения состояния кнопки
    void toggleState();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QPixmap mButtonUpPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mCurrentButtonPixmap;
    bool mIsDown;

    // Приватный метод для изменения изображения кнопки
    void setDown();
};

#endif // MAINWINDOW_H
