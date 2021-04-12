#include "PositionForm.h"
#include "ui_PositionForm.h"

PositionForm::PositionForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PositionForm)
{
    ui->setupUi(this);
    mCurrentPosition = -1;

    ui->horizontalSlider->setMinimumWidth(100);
    layout()->setMargin(1);
}

PositionForm::~PositionForm()
{
    delete ui;
}

void PositionForm::setRange(int min, int max)
{
    ui->horizontalSlider->setMinimum(min);
    ui->horizontalSlider->setMaximum(max);
}

void PositionForm::showCurrentPosition(int pos)
{
    mCurrentPosition = pos;
    ui->currentPositionLabel->setText(QString("Posición actual: %1")
                                      .arg(pos));
}

void PositionForm::on_acceptPushButton_clicked()
{
    emit accepted(ui->horizontalSlider->value());
}

void PositionForm::on_horizontalSlider_valueChanged(int value)
{
    ui->valueLabel->setText(QString("Posición deseada: %1").arg(value));
}

void PositionForm::on_holdPushButton_clicked()
{
    ui->valueLabel->setText(QString("Posición deseada: %1").arg(mCurrentPosition));
    ui->horizontalSlider->setValue(mCurrentPosition);
}
