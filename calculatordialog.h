#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include <QMainWindow>
#include "edit-box-manager/editboxmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalculatorDialog;
}
QT_END_NAMESPACE

class CalculatorDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorDialog(QWidget *parent = nullptr);
    ~CalculatorDialog() override;

private slots:
    // Buttons: Numbers
    void on_btnDecimal_clicked();
    void on_btnNumZero_clicked();
    void on_btnNumOne_clicked();
    void on_btnNumTwo_clicked();
    void on_btnNumThree_clicked();
    void on_btnNumFour_clicked();
    void on_btnNumFive_clicked();
    void on_btnNumSix_clicked();
    void on_btnNumSeven_clicked();
    void on_btnNumEight_clicked();
    void on_btnNumNine_clicked();

    // Buttons: Math operators
    void on_btnAddition_clicked();
    void on_btnSubtraction_clicked();
    void on_btnMultiplication_clicked();
    void on_btnDivision_clicked();
    void on_btnChangeSign_clicked();

    // Buttons: Calculations
    void on_btnEquals_clicked();
    void on_btnPercentage_clicked();

    // Buttons: Erasing symbols
    void on_btnEraseLast_clicked();
    void on_btnEraseAll_clicked();

    void on_btnLeftParenthesis_clicked();

    void on_btnRightParenthesis_clicked();

private:
    Ui::CalculatorDialog *ui;
    std::unique_ptr<EditBoxManager> editBoxManager;
};
#endif // CALCULATORDIALOG_H
