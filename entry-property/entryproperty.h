#ifndef ENTRYPROPERTY_H
#define ENTRYPROPERTY_H

#endif // ENTRYPROPERTY_H

enum EntryType
{
    EMPTY = 0,
    NUMBER = 1,
    OPERATOR = 2,
    DECIMAL_POINT = 3, // Ovo me se ne svidja
    LEFT_PARENTHESIS = 4,
    RIGHT_PARENTHESIS = 5,
    UNARY_MINUS = 6

};

enum EntryValue
{
    NO_ENTRY = -1,

    // ENTRIES
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    POINT = 10, // TODO: Ovo me se ne svidja

    // Operators
    ADD = 20,
    SUBTRACT = 21,
    MULTIPLY = 22,
    DIVIDE = 23,

    NEG = 24,

    // Parenthesis
    LEFT = 32,
    RIGHT = 33,

    EQUALS = 34,
    PERCENTAGE = 35

};

enum DecimalPointStatus
{
    DONT_INSERT = 0,
    INSERT = 1,
    INSERT_ZERO_BEFORE_DECIMAL = 2
};

struct EntryProperty
{
    EntryProperty(const EntryType& propertyEntryType, const EntryValue& propertyEntryValue)
        : entryType(propertyEntryType), entryValue(propertyEntryValue) {};

    EntryType GetEntryType() { return entryType; };
    EntryValue GetEntryValue() {return entryValue; };

    EntryType entryType;
    EntryValue entryValue;

};