#include "recruitsheetdialog.h"
#include "ui_recruitsheetdialog.h"

#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QDialog>

RecruitSheetDialog::RecruitSheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecruitSheetDialog)
{
    ui->setupUi(this);


    QFile qss(":/qss/qss/onboarding.qss");
    if(qss.open(QFile::ReadOnly)) {
        QString styleString = QLatin1String(qss.readAll());
        setStyleSheet(styleString);
    }
    qss.close();

    QGraphicsDropShadowEffect* submitButtonShadow = new QGraphicsDropShadowEffect;
    submitButtonShadow->setColor(QColor(255, 0, 0, 27));
    submitButtonShadow->setBlurRadius(0);
    submitButtonShadow->setOffset(6.0);

    ui->submitButton->setGraphicsEffect(submitButtonShadow);

}

RecruitSheetDialog::~RecruitSheetDialog()
{
    delete ui;
}

void RecruitSheetDialog::on_submitButton_clicked()
{

    this->close();
    this->setResult(QDialog::Accepted);
}

void RecruitSheetDialog::enableSubmitButtonIfFormIsReady()
{
    if(
        (ui->appearanceChoice1->isChecked() || ui->appearanceChoice2->isChecked() || ui->appearanceChoice3->isChecked())
            && ui->rankComboBox->currentText().length() > 0
            && ui->nameLineEdit->text().length() > 0
            && (ui->correctAnswer1RadioButton->isChecked() || ui->correctAnswer2RadioButton->isChecked())
            )
    {
        ui->submitButton->setEnabled(true);
    }

}

void RecruitSheetDialog::on_appearanceChoice1_clicked()
{
    ui->appearanceChoice2->setChecked(false);
    ui->appearanceChoice3->setChecked(false);
    enableSubmitButtonIfFormIsReady();
}

void RecruitSheetDialog::on_appearanceChoice2_clicked()
{
    ui->appearanceChoice1->setChecked(false);
    ui->appearanceChoice3->setChecked(false);
    enableSubmitButtonIfFormIsReady();

}

void RecruitSheetDialog::on_appearanceChoice3_clicked()
{
    ui->appearanceChoice1->setChecked(false);
    ui->appearanceChoice2->setChecked(false);
    enableSubmitButtonIfFormIsReady();

}

void RecruitSheetDialog::on_nameLineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() > 0) {
        enableSubmitButtonIfFormIsReady();
    }
}

void RecruitSheetDialog::on_correctAnswer1RadioButton_clicked()
{
    enableSubmitButtonIfFormIsReady();
}

void RecruitSheetDialog::on_correctAnswer2RadioButton_clicked()
{
    enableSubmitButtonIfFormIsReady();
}

QString RecruitSheetDialog::getName()
{
    return ui->nameLineEdit->text();
}

QString RecruitSheetDialog::getRank()
{
    return ui->rankComboBox->currentText();
}

int RecruitSheetDialog::getAppearanceChoice()
{
    int res = 0;
    if(ui->appearanceChoice1->isChecked()) {
        res = 1;
    } else if (ui->appearanceChoice2->isChecked()) {
        res = 2;
    } else if (ui->appearanceChoice3->isChecked()) {
        res = 3;
    }

    return res;
}
