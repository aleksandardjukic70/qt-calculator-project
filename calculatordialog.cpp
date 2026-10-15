#include "calculatordialog.h"
#include "./ui_calculatordialog.h"
#include <QStyle>

CalculatorDialog::CalculatorDialog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorDialog)
{
    ui->setupUi(this);
    ui->inputOtputEditBox->setAlignment(Qt::AlignRight);
    editBoxManager = std::make_unique<EditBoxManager>(ui->inputOtputEditBox);
    ui->btnEraseLast->setIcon(ui->btnEraseLast->style()->standardIcon(QStyle::SP_ArrowLeft));
}

CalculatorDialog::~CalculatorDialog()
{
    delete ui;
}


// Buttons: Removing entries
void CalculatorDialog::on_btnEraseAll_clicked()
{
    editBoxManager->DeleteAllEntries();
}

void CalculatorDialog::on_btnEraseLast_clicked()
{
    editBoxManager->DeleteLastEntry();
}


// Buttons: Entries
void CalculatorDialog::on_btnDecimal_clicked()
{
    DecimalPointStatus status = editBoxManager->GetDecimalPointInsertStatus();

    switch (status)
    {
    case DONT_INSERT:
        return;
    case INSERT_ZERO_BEFORE_DECIMAL:
    {
        editBoxManager->InsertEntry("0", NUMBER, ZERO);
        editBoxManager->InsertEntry(".", DECIMAL_POINT, POINT);
        return;
    }
    case INSERT:
    {
        editBoxManager->InsertEntry(".", DECIMAL_POINT, POINT);
        return;
    }
    default:
        break;
    }
}

void CalculatorDialog::on_btnNumZero_clicked()
{
   editBoxManager->InsertEntry("0", NUMBER, ZERO);
}

void CalculatorDialog::on_btnNumOne_clicked()
{
    editBoxManager->InsertEntry("1", NUMBER, ONE);
}

void CalculatorDialog::on_btnNumTwo_clicked()
{
    editBoxManager->InsertEntry("2", NUMBER, TWO);
}

void CalculatorDialog::on_btnNumThree_clicked()
{
    editBoxManager->InsertEntry("3", NUMBER, THREE);
}

void CalculatorDialog::on_btnNumFour_clicked()
{
    editBoxManager->InsertEntry("4", NUMBER, FOUR);
}

void CalculatorDialog::on_btnNumFive_clicked()
{
    editBoxManager->InsertEntry("5", NUMBER, FIVE);
}

void CalculatorDialog::on_btnNumSix_clicked()
{
    editBoxManager->InsertEntry("6", NUMBER, SIX);
}

void CalculatorDialog::on_btnNumSeven_clicked()
{
    editBoxManager->InsertEntry("7", NUMBER, SEVEN);
}

void CalculatorDialog::on_btnNumEight_clicked()
{
    editBoxManager->InsertEntry("8", NUMBER, EIGHT);
}

void CalculatorDialog::on_btnNumNine_clicked()
{
    editBoxManager->InsertEntry("9", NUMBER, NINE);
}


// Buttons: Operators
void CalculatorDialog::on_btnAddition_clicked()
{
    editBoxManager->InsertOperatorEntry(" + ", OPERATOR, ADD);
}

void CalculatorDialog::on_btnSubtraction_clicked()
{
    editBoxManager->InsertOperatorEntry(" - ", OPERATOR, SUBTRACT);
}

void CalculatorDialog::on_btnMultiplication_clicked()
{
    editBoxManager->InsertOperatorEntry(" * ", OPERATOR, MULTIPLY);
}

void CalculatorDialog::on_btnDivision_clicked()
{
    editBoxManager->InsertOperatorEntry(" / ", OPERATOR, DIVIDE);
}

void CalculatorDialog::on_btnEquals_clicked()
{

    std::string sResult = editBoxManager->Calculate();
    QString qResult = QString::fromStdString(sResult);

    editBoxManager->InsertOperatorEntry(" = ", OPERATOR, EQUALS);
    editBoxManager->InsertEntry(qResult, NUMBER, ZERO);

}

void CalculatorDialog::on_btnPercentage_clicked()
{
    editBoxManager->InsertOperatorEntry(" % ", OPERATOR, PERCENTAGE);
}

void CalculatorDialog::on_btnChangeSign_clicked()
{

}

void CalculatorDialog::on_btnLeftParenthesis_clicked()
{
    editBoxManager->InsertEntry("(", LEFT_PARENTHESIS, LEFT);
}


void CalculatorDialog::on_btnRightParenthesis_clicked()
{
    editBoxManager->InsertEntry(")", RIGHT_PARENTHESIS, RIGHT);

}

