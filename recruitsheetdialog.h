#ifndef RECRUITSHEETDIALOG_H
#define RECRUITSHEETDIALOG_H

#include <QDialog>

namespace Ui {
class RecruitSheetDialog;
}

class RecruitSheetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecruitSheetDialog(QWidget *parent = nullptr);
    ~RecruitSheetDialog();

private:
    Ui::RecruitSheetDialog *ui;

private slots:
    void on_submitButton_clicked();

    void enableSubmitButtonIfFormIsReady();

    void on_appearanceChoice1_clicked();
    void on_appearanceChoice2_clicked();
    void on_appearanceChoice3_clicked();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_correctAnswer1RadioButton_clicked();
    void on_correctAnswer2RadioButton_clicked();

public slots:
    QString getName();
    QString getRank();
    int getAppearanceChoice();
};

#endif // RECRUITSHEETDIALOG_H
