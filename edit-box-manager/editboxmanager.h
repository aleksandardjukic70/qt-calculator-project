#ifndef EDITBOXMANAGER_H
#define EDITBOXMANAGER_H

#include <QLineEdit>
//#include <memory>
#include "../entrytracker.h"

class EditBoxManager
{
public:
    EditBoxManager(QLineEdit* inputOutputEditBox);
    ~EditBoxManager() {};

    void InsertEntry(const QString& sString, const EntryType& entryType, const EntryValue& entryValue);
    void InsertOperatorEntry(const QString& sString, const EntryType& entryType, const EntryValue& entryValue);
    std::string Calculate();

    DecimalPointStatus GetDecimalPointInsertStatus();
    void DeleteAllEntries();
    void DeleteLastEntry();
    void BackspaceOperatorEntry();
    void BackspaceEntry();

private:
    QLineEdit* editBox;
    EntryTracker entryTracker;
};

#endif // EDITBOXMANAGER_H
