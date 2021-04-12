#ifndef POSITIONFORM_H
#define POSITIONFORM_H

#include <QWidget>

namespace Ui
{
class PositionForm;
}

class PositionForm : public QWidget
{
    Q_OBJECT
public:
    explicit PositionForm(QWidget *parent = nullptr);
    ~PositionForm();
    void setRange(int min, int max);
    void showCurrentPosition(int pos);
signals:
    void accepted(int);
private slots:
    void on_acceptPushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void on_holdPushButton_clicked();

private:
    Ui::PositionForm *ui;
    int mCurrentPosition;
};

#endif // POSITIONFORM_H
