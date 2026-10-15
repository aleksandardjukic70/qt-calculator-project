#include "entrytracker.h"

EntryTracker::EntryTracker() {}

EntryProperty EntryTracker::GetEntryPropertyAtIndex(const int& index) const
{
    return vEditBoxEntryTracker.at(index);
}

void DeleteEntryAt(const int& index);

void EntryTracker::DeleteEntryAt(const int& index)
{
    vEditBoxEntryTracker.erase(vEditBoxEntryTracker.begin() + index);
}

EntryType EntryTracker::GetLastEntryType()
{
    if (vEditBoxEntryTracker.empty())
        return EMPTY;
    else
        return vEditBoxEntryTracker.back().entryType;
}

EntryValue EntryTracker::GetLastEntryValue()
{
    if (vEditBoxEntryTracker.empty())
        return NO_ENTRY;
    else
        return vEditBoxEntryTracker.back().entryValue;
}

void EntryTracker::InsertEntry(const EntryProperty& entryProperty)
{
    vEditBoxEntryTracker.emplace_back(entryProperty);
}

DecimalPointStatus EntryTracker::GetDecimalPointInsertStatus()
{
    EntryType editBoxLastEntry = EMPTY;
    if (!vEditBoxEntryTracker.empty())
        editBoxLastEntry = vEditBoxEntryTracker.back().GetEntryType();

    if (editBoxLastEntry == DECIMAL_POINT)
        return DONT_INSERT;

    if (editBoxLastEntry == EMPTY || editBoxLastEntry == OPERATOR)
        return INSERT_ZERO_BEFORE_DECIMAL;

    int iOperatorIndex = -1;
    int iDecimalPointIndex = -1;

    for (int i = vEditBoxEntryTracker.size() - 1; i >= 0; i--)
    {
        if (vEditBoxEntryTracker[i].GetEntryType() == OPERATOR && iOperatorIndex == -1)
            iOperatorIndex = i;
        else if (vEditBoxEntryTracker[i].GetEntryType() == DECIMAL_POINT && iDecimalPointIndex == -1)
            iDecimalPointIndex = i;

        if (iOperatorIndex != -1)
            break;
    }

    if (iDecimalPointIndex > iOperatorIndex)
        return DONT_INSERT; // TODO: put error message here

    return INSERT;
}

void EntryTracker::InsertEntryProperty(const EntryProperty& entryProperty)
{
    vEditBoxEntryTracker.emplace_back(entryProperty);
}

void EntryTracker::InsertEntryPropertyAt(const EntryProperty& entryProperty, const int& index)
{
    vEditBoxEntryTracker.insert(vEditBoxEntryTracker.begin() + index, entryProperty);

}

int EntryTracker::Size() const
{
    return vEditBoxEntryTracker.size();
}

bool EntryTracker::IsEmpty()
{
    return vEditBoxEntryTracker.empty();
}

void EntryTracker::DeleteAllEntries()
{
    vEditBoxEntryTracker.clear();
}

void EntryTracker::DeleteLastEntry()
{
    vEditBoxEntryTracker.pop_back();
}