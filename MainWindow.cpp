#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PositionForm.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QSettings>
#include <QStandardItemModel>
#include <QMenu>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createObjects();
    configureObjects();
    connectObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browsePushButton_clicked()
{
    auto dirname = QFileDialog::getExistingDirectory(this);
    setFolder(dirname);
}

void MainWindow::on_playPushButton_clicked()
{
    play(ui->listView->currentIndex().row());
}

void MainWindow::on_pausePushButton_clicked()
{
    mMediaPlayer->pause();
}

void MainWindow::on_stopPushButton_clicked()
{
    mMediaPlayer->stop();
}

void MainWindow::on_previousPushButton_clicked()
{
    mMediaPlayer->stop();
    play(ui->listView->currentIndex().row() - 1);
}

void MainWindow::on_nextPushButton_clicked()
{
    mMediaPlayer->stop();
    play(ui->listView->currentIndex().row() + 1);
}

void MainWindow::on_volumeDial_valueChanged(int value)
{
    setVolume(value);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSettings();
    QMainWindow::closeEvent(e);
}

void MainWindow::play(int index)
{
    auto mediaPlayerState = mMediaPlayer->state();
    if (mediaPlayerState == QMediaPlayer::PausedState) {
        mMediaPlayer->play();
        return;
    } else if (mediaPlayerState == QMediaPlayer::PlayingState) {
        return;
    }
    if (index == -1 || index >= mNumberOfFiles) {
        return;
    }
    auto filename = ui->folderLineEdit->text()
            + "/" + mModel->index(index, 0).data().toString();
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mMediaPlayer->play();
    ui->listView->setCurrentIndex(mModel->index(index, 0));
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("mediaplayer");
    const auto foldername = settings.value("folder", "/").toString();
    const int volume = settings.value("volume", 100).toInt();
    const int currentIndex = settings.value("currentindex", 0).toInt();
    settings.endGroup();

    setFolder(foldername);
    setVolume(volume);
    setCurrentIndex(currentIndex);
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("mediaplayer");
    settings.setValue("folder", ui->folderLineEdit->text());
    settings.setValue("volume", ui->volumeDial->value());
    settings.setValue("currentindex", ui->listView->currentIndex()
                      .data().toInt());
    settings.endGroup();
}

void MainWindow::setFolder(const QString &foldername)
{
    mModel->clear();
    ui->folderLineEdit->setText(foldername);
    QDir dir(foldername);
    for (uint ix = 2; ix < dir.count(); ++ix) {
        mModel->appendRow(new QStandardItem(dir[ix]));
    }
    mNumberOfFiles = dir.count() - 2;
    ui->numberOfFilesLabel->setText(QString("Número de archivos: %1")
                                    .arg(mNumberOfFiles));
}

void MainWindow::setVolume(int volume)
{
    ui->volumeDial->setValue(volume);
    ui->volumeLabel->setText(QString("Volumen: ")
                             + QString::number(volume) + "%");
    ui->volumeProgressBar->setValue(volume);
    mMediaPlayer->setVolume(volume);
}

void MainWindow::setCurrentIndex(int currentIndex)
{
    ui->listView->setCurrentIndex(mModel->index(currentIndex, 0));
}

void MainWindow::createObjects()
{
    mMediaPlayer = new QMediaPlayer(this);
    mModel = new QStandardItemModel(this);
    mPositionForm = new PositionForm(this);
    mNumberOfFiles = 0;
}

void MainWindow::configureObjects()
{
    setWindowTitle("DuMusicPlayer");
    ui->listView->setModel(mModel);
    ui->folderLineEdit->setReadOnly(true);
    ui->progressBar->setValue(0);
    auto layout = new QVBoxLayout;
    layout->addWidget(mPositionForm);
    auto menu = new QMenu(this);
    menu->setLayout(layout);
    ui->positionPushButton->setMenu(menu);
    loadSettings();
}

void MainWindow::connectObjects()
{
    connect(mMediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 dur) {
        ui->progressBar->setRange(0, dur);
        mPositionForm->setRange(0, dur);
    });

    connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        ui->progressBar->setValue(pos);
        mPositionForm->showCurrentPosition(pos);
    });

    connect(mMediaPlayer, &QMediaPlayer::mediaStatusChanged,
            [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            on_nextPushButton_clicked();
        }
    });

    connect(mPositionForm, &PositionForm::accepted, [&](int pos) {
        mMediaPlayer->setPosition(pos);
    });
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    mMediaPlayer->stop();
    play(index.row());
}
