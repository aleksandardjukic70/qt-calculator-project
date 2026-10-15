#ifndef CALCULATIONMANAGER_H
#define CALCULATIONMANAGER_H

#include "../entrytracker.h"
#include <string>
#include <queue>
#include <stack>
#include <variant>


class CalculationManager
{
public:
    CalculationManager();

    static std::string Calculate(EntryTracker& entryTracker);
    static void InfixToRPN(const EntryTracker& entryTracker, std::queue<std::variant<double, EntryValue>>& expressionQueue);
    static double EvaluateRPN(std::queue<std::variant<double, EntryValue>>& expressionQueue);



    static EntryTracker DivideAndMultiply(EntryTracker& entryTracker);

    static std::string EntryValueToString(const EntryValue& entryValue);
    static EntryValue StringToEntryValue(char& stringEntryValue);

    static double Operation(const double& dNumberOne, const double& dNumberTwo, const EntryValue& mathOperator);

    static void InsertOperandToExpressionQueue(EntryTracker& operand, std::queue<std::variant<double, EntryValue>>& expressionQueue);
    static void InsertOperatorToExpressionQueue(std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue);
    static void InsertOperatorToOperatorStack(const EntryProperty& entryProperty, std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue);

    static void InsertRemainingElementsToExpressionQueue(EntryTracker& operand, std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue);

    static int GetOperatorPrecedence(const EntryValue& entryValue);

};

#endif // CALCULATIONMANAGER_H
