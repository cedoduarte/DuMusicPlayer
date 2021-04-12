#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QMediaPlayer;
class QStandardItemModel;
class PositionForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_browsePushButton_clicked();
    void on_playPushButton_clicked();
    void on_pausePushButton_clicked();
    void on_stopPushButton_clicked();
    void on_previousPushButton_clicked();
    void on_nextPushButton_clicked();
    void on_volumeDial_valueChanged(int value);
    void on_listView_clicked(const QModelIndex &index);
protected:
    void closeEvent(QCloseEvent *e) override;
private:
    void play(int index);
    void loadSettings();
    void saveSettings();
    void setFolder(const QString &foldername);
    void setVolume(int volume);
    void setCurrentIndex(int currentIndex);
    void createObjects();
    void configureObjects();
    void connectObjects();

    Ui::MainWindow *ui;
    QMediaPlayer *mMediaPlayer;
    QStandardItemModel *mModel;
    PositionForm *mPositionForm;
    int mNumberOfFiles;
};

#endif // MAINWINDOW_H
