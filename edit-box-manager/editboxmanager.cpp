#include "editboxmanager.h"
#include "../calculation-manager/calculationmanager.h"


EditBoxManager::EditBoxManager(QLineEdit* inputOutputEditBox)
{
    editBox = inputOutputEditBox;
    //entryTracker = std::make_unique<EntryTracker>();
}

void EditBoxManager::InsertEntry(const QString& sString, const EntryType& entryType, const EntryValue& entryValue)
{
    editBox->insert(sString);

    EntryProperty entryProperty(entryType, entryValue);
    entryTracker.InsertEntry(entryProperty);
}

//TODO: Promeni ovde entryType i entryValue u EntryProperty i isto to i u calculatorDialogu (imao sam neki problem sa tim pre)
void EditBoxManager::InsertOperatorEntry(const QString& sString, const EntryType& entryType, const EntryValue& entryValue)
{
    if (entryType != OPERATOR)
        return;
    else if (entryType == OPERATOR && entryTracker.GetLastEntryType() == DECIMAL_POINT)
        return;

    if (entryType == OPERATOR && (entryTracker.GetLastEntryType() == OPERATOR && entryTracker.GetLastEntryValue() != SUBTRACT))
        DeleteLastEntry();
    else if (entryValue == SUBTRACT && (entryTracker.IsEmpty() || entryTracker.GetLastEntryType() == LEFT_PARENTHESIS))
    {
        // TODO: Vidi sredi ovo, ne svidja mi se kako trenutno izgleda:
        // 1. da li pozvati na dva mesta insert entry ovako?
        // 2. Da li obrisati const sa entryType i entryValue i sString i dodeliti novu vrednost
        // 3. da li napraviti na pocetku funkcije 3 varijable koje uzimaju parametre i prosledjuju ih u insert entry a ovde ih promeniti
        // samo ako udje u ovaj uslov
        InsertEntry("-", UNARY_MINUS, NEG);
        return;
    }
    InsertEntry(sString, entryType, entryValue);
}

std::string EditBoxManager::Calculate()
{
    return CalculationManager::Calculate(entryTracker);
}

DecimalPointStatus EditBoxManager::GetDecimalPointInsertStatus()
{
    return entryTracker.GetDecimalPointInsertStatus();
}

void EditBoxManager::DeleteAllEntries()
{
    if (entryTracker.IsEmpty())
        return;

    editBox->clear();
    entryTracker.DeleteAllEntries();
}

void EditBoxManager::DeleteLastEntry()
{
    if (entryTracker.IsEmpty())
        return;

    EntryType editBoxLastEntry = entryTracker.GetLastEntryType();

    if (editBoxLastEntry == OPERATOR)
        BackspaceOperatorEntry();
    else
        BackspaceEntry();

    entryTracker.DeleteLastEntry();
}

void EditBoxManager::BackspaceOperatorEntry()
{
    // For Math operators: call backspace() three times (deletes blank spaces around them)
    for (int i = 0; i < 3; i++)
        editBox->backspace();
}

void EditBoxManager::BackspaceEntry()
{
    // For any other entry call backspace() once
    editBox->backspace();
}
