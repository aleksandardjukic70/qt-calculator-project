#include "calculationmanager.h"


CalculationManager::CalculationManager() {}

// U ovu funkciju ide sve. Ako se nadje zagrada, sve izmedju se smesta u novi vektor i poziva se ovo opet i tako u krug sve dok se ne izracunaju sve zagrade unutar zagrada.
// TODO: Kako nadomestiti rezultat i obrisati operatore i zagrade iz vektora
std::string CalculationManager::Calculate(EntryTracker& entryTracker) // ovaj EntryTracker MORA da bude kopija, ne smemo da diramo onaj koji se posalje jer u njega dodajemo rezultat
{
    std::queue<std::variant<double, EntryValue>> expressionQueue;

    // Phase 1: InfixToRPN
    InfixToRPN(entryTracker, expressionQueue);

    // Phase 2: RPN evaluation
    double dResult = EvaluateRPN(expressionQueue);

    std::string sResult = std::to_string(dResult);



    return sResult;//std::to_string(dResult);

}

double CalculationManager::EvaluateRPN(std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    std::stack<double> numberStack;

    while (!expressionQueue.empty())
    {
        if (std::holds_alternative<double>(expressionQueue.front()))
        {
            numberStack.push(std::get<double>(expressionQueue.front()));
            expressionQueue.pop();
        }
        else
        {
            EntryValue mathOperator = std::get<EntryValue>(expressionQueue.front());
            expressionQueue.pop();

            if (mathOperator == NEG)
            {
                double number = numberStack.top();
                numberStack.pop();

                numberStack.push(Operation(number, 0, mathOperator));
            }
            else
            {
                double numberTwo = numberStack.top();
                numberStack.pop();

                double numberOne = numberStack.top();
                numberStack.pop();

                numberStack.push(Operation(numberOne, numberTwo, mathOperator));
            }
        }
    }
    return numberStack.top();

}

void CalculationManager::InfixToRPN(const EntryTracker& entryTracker, std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    std::stack<EntryValue> operatorStack;
    EntryTracker operand;

    for (int i = 0; i < entryTracker.Size(); i++)
    {
        EntryProperty entryProperty = entryTracker.GetEntryPropertyAtIndex(i);

        // TODO: u dijalogu za zagrade staviti uslov da NE MOZE da se unese parenthesis ukoliko poslednji karakter u editboxu nije broj, znaci ne moze decimal point ni operator, samo broj
        if (entryProperty.entryType == LEFT_PARENTHESIS)
        {
            if (!operand.IsEmpty() && operand.GetLastEntryValue() == NEG)
            {
                // TODO: refactor - Ovde 0 za index je hack zato sto znam da ne moze biti nista na drugom mestu ali mi se ne svidja
                InsertOperatorToOperatorStack(operand.GetEntryPropertyAtIndex(0), operatorStack, expressionQueue);
                operand.DeleteAllEntries();
            }
            operatorStack.push(entryProperty.entryValue);
        }
        else if (entryProperty.entryType == RIGHT_PARENTHESIS)
        {
            InsertOperandToExpressionQueue(operand, expressionQueue);

            while(operatorStack.top() != LEFT)
                InsertOperatorToExpressionQueue(operatorStack, expressionQueue);

            operatorStack.pop();
        }
        if (entryProperty.entryType == NUMBER || entryProperty.entryType == DECIMAL_POINT || entryProperty.entryType == UNARY_MINUS)
            operand.InsertEntry(entryProperty);
        else if (entryProperty.entryType == OPERATOR)
        {
            InsertOperandToExpressionQueue(operand, expressionQueue);

            InsertOperatorToOperatorStack(entryProperty, operatorStack, expressionQueue);
        }
    }

    InsertRemainingElementsToExpressionQueue(operand, operatorStack, expressionQueue);
}

int CalculationManager::GetOperatorPrecedence(const EntryValue& entryValue)
{
    switch(entryValue)
    {
    case NEG:
        return 3;
    case MULTIPLY:
        return 2;
    case DIVIDE:
        return 2;
    case ADD:
        return 1;
    case SUBTRACT:
        return 1;
    default:
        return 0;
    }
}

void CalculationManager::InsertOperandToExpressionQueue(EntryTracker& operand, std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    if (!operand.IsEmpty())
    {
        std::string sOperand;

        for (int j = 0; j <operand.Size(); j++)
            sOperand += EntryValueToString(operand.GetEntryPropertyAtIndex(j).entryValue);

        expressionQueue.push(std::stod(sOperand));
        operand.DeleteAllEntries();
    }
}

void CalculationManager::InsertOperatorToExpressionQueue(std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    expressionQueue.push(operatorStack.top());
    operatorStack.pop();
}

void CalculationManager::InsertOperatorToOperatorStack(const EntryProperty& entryProperty, std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    int trackerOperatorPresedence = GetOperatorPrecedence(entryProperty.entryValue);
    int stackOperatorPresedence = operatorStack.empty() ? 0 : GetOperatorPrecedence(operatorStack.top());

    // TODO: Pomeriti komentare ili ih smanjiti ali da i dalje imaju smisla
    //
    // Korak 1: Proveriti da li je operatorStack prazan -> ako jeste preskoci na korak 4 ako nije idi na korak 2
    //  Korak 2: Uporediti jačinu operatora na vrhu operatorStack-a sa jačinom trenutnog operatora (onog iz entryProperty koji se sada obrađuje).
    //      2a. Ako je jačina vrha steka VEĆA ILI JEDNAKA jačini trenutnog operatora → izvrši korak 3.
    //      2b. Ako je jačina vrha steka MANJA od jačine trenutnog operatora → preskoči korak 3, idi na korak 4.
    while(!operatorStack.empty() && (stackOperatorPresedence >= trackerOperatorPresedence))
    {
        //Korak 3: Izbaciti operator sa vrha operatorStack-a i dodati ga u expression.
        //Nakon toga, vratiti se na korak 1 (ne na korak 4!): ponovo proveriti da li je stek sada prazan, i ako nije, ponovo uporediti jačinu novog vrha steka.
        //Ovaj korak se ponavlja onoliko puta koliko je potrebno, dok se ne ispuni uslov za prelazak na korak 4.
        InsertOperatorToExpressionQueue(operatorStack, expressionQueue);
    }
    // Korak 4: Gurnuti trenutni operator (onaj koji se obrađuje u ovoj iteraciji glavne for petlje) na operatorStack.
    operatorStack.push(entryProperty.entryValue);
}

void CalculationManager::InsertRemainingElementsToExpressionQueue(EntryTracker& operand, std::stack<EntryValue>& operatorStack, std::queue<std::variant<double, EntryValue>>& expressionQueue)
{
    InsertOperandToExpressionQueue(operand, expressionQueue);

    while(!operatorStack.empty())
        InsertOperatorToExpressionQueue(operatorStack, expressionQueue);
}

EntryValue CalculationManager::StringToEntryValue(char& stringEntryValue)
{
    switch (stringEntryValue)
    {
    case '.':
        return POINT;
    case '0':
        return ZERO;
    case '1':
        return ONE;
    case '2':
        return TWO;
    case '3':
        return THREE;
    case '4':
        return FOUR;
    case '5':
        return FIVE;
    case '6':
        return SIX;
    case '7':
        return SEVEN;
    case '8':
        return EIGHT;
    case '9':
        return NINE;
    default:
        return NO_ENTRY;
    }
}

std::string CalculationManager::EntryValueToString(const EntryValue& entryValue)
{
    switch (entryValue)
    {
    case NEG:
        return "-";
    case POINT:
        return ".";
    case ZERO:
        return "0";
    case ONE:
        return "1";
    case TWO:
        return "2";
    case THREE:
        return "3";
    case FOUR:
        return "4";
    case FIVE:
        return "5";
    case SIX:
        return "6";
    case SEVEN:
        return "7";
    case EIGHT:
        return "8";
    case NINE:
        return "9";
    default:
        return "";
    }
}

double CalculationManager::Operation(const double& dNumberOne, const double& dNumberTwo, const EntryValue& mathOperator)
{
    switch(mathOperator)
    {
    case ADD:
        return dNumberOne + dNumberTwo;
    case SUBTRACT:
        return dNumberOne - dNumberTwo;
    case MULTIPLY:
        return dNumberOne * dNumberTwo;
    case DIVIDE:
        return dNumberOne / dNumberTwo;
    case PERCENTAGE:
        return dNumberOne * dNumberTwo / 100;
    case NEG:
        return -dNumberOne;
    default:
        return 0.0;
    }
}