#ifndef ENTRYTRACKER_H
#define ENTRYTRACKER_H

#include "entry-property/entryproperty.h"
#include <vector>

class EntryTracker
{
public:
    EntryTracker();

    EntryType GetLastEntryType();
    EntryValue GetLastEntryValue();
    EntryProperty GetEntryPropertyAtIndex(const int& index) const;

    void InsertEntry(const EntryProperty& entryProperty);
    DecimalPointStatus GetDecimalPointInsertStatus();

    void InsertEntryProperty(const EntryProperty& entryProperty);
    void InsertEntryPropertyAt(const EntryProperty& entryProperty, const int& index);
    int Size() const;
    bool IsEmpty();
    void DeleteAllEntries();
    void DeleteLastEntry();
    void DeleteEntryAt(const int& index);



private:
    std::vector<EntryProperty> vEditBoxEntryTracker;
};

#endif // ENTRYTRACKER_H
