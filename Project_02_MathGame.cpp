#include <iostream>
using namespace std;


enum enQuestionsLevel { Easy = 1, Mediuem = 2, Hard = 3, MixedLevels = 4 };
enum enOperationType { Add  = 1, Sub = 2, Multipli = 3, Divide = 4, MixedOperations = 5 };
enum enAnswerResult { False = 0, True = 1 };


void StartGame();
void ResetScreen();
bool PlayGame();
int ReadPoisitveNumbers(string Message);
enQuestionsLevel GetQuestionsLevel();
enOperationType GetOperationType();
int RandomsGenerator(int From, int To);
void GenerateQuestions(enQuestionsLevel Level, enOperationType OperationType, int GamePoints[2]);
void GenerateNumbers(int &Number1, int &Number2, enQuestionsLevel Level);
void GenerateFormula(int Number1, int Number2, enOperationType OperationType, int & FormulaResult);
void EvaluateFormula(double FormulaResult, int GamePoints[2]);
void PrintEndGameResult(enQuestionsLevel Level, enOperationType OperationType, int GamePoints[]);
string GetOperationText(enOperationType OperationType);
string GetLevelText(enQuestionsLevel Level);



int main() 
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}

void StartGame() 
{
    bool ContinueGame = true;
    while (ContinueGame)
    {
        cout << "Welcome To The Game" << endl;
        ContinueGame = PlayGame();
        if (ContinueGame)
            ResetScreen();
    }
}

void ResetScreen()
{
    system("cls");
    system("Color 0f");
}

bool PlayGame()
{
    int TotalQuestionsCount, ContinueGame, GamePoints[2] = {0};
    TotalQuestionsCount = ReadPoisitveNumbers("Enter How Many Questions Do You Want To Answer: ");
    enQuestionsLevel Level = GetQuestionsLevel();
    enOperationType OperationType = GetOperationType();
    
    for (int i = 1; i <= TotalQuestionsCount; i++)
    {
        cout << "Question[" << i << "/"<<TotalQuestionsCount<<"]"<< endl;
        GenerateQuestions(Level , OperationType , GamePoints);
    }
    PrintEndGameResult(Level , OperationType , GamePoints);

    do
    {    
        ContinueGame = ReadPoisitveNumbers("\nDo You Want To Play Again? [0]No [1]Yes: ");
    } while (ContinueGame != 0 && ContinueGame != 1);    

    return (ContinueGame == 1);
}

int ReadPoisitveNumbers(string Message)
{
    int x;
    do
    {
        cout << Message;
        cin >> x;
        cout<<"\n";
    } while (x < 0);
    return x;
}

enQuestionsLevel GetQuestionsLevel()
{
    int Choice = ReadPoisitveNumbers("Enter Question Level:\n[1]Easy\n[2]Mediuem\n[3]Hard\n[4]mix\n");
    return (enQuestionsLevel)Choice;
}

enOperationType GetOperationType()
{
    int Choice = ReadPoisitveNumbers(
        "Choose The Operation:\n[1]Add + \n[2]Sub - \n[3]Multipli * \n[4]Divide / \n[5]Mix + - * /\n");
    return (enOperationType)Choice;
}

void GenerateQuestions(enQuestionsLevel Level, enOperationType OperationType, int GamePoints[2])
{
    int Number1, Number2, FormulaResult;
    
    if(Level == enQuestionsLevel::MixedLevels)
            Level = (enQuestionsLevel)RandomsGenerator(1,4);
    if(OperationType == enOperationType::MixedOperations)
        OperationType = (enOperationType)RandomsGenerator(1,4);
    
    GenerateNumbers(Number1,Number2,Level);
    GenerateFormula(Number1, Number2, OperationType, FormulaResult);
    EvaluateFormula(FormulaResult, GamePoints);
    cout<<"\n";
}

int RandomsGenerator(int From, int To)
{
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

void GenerateNumbers(int &Number1 , int &Number2 , enQuestionsLevel Level)
{
    switch(Level)
    {
        case 1:
            Number1 = RandomsGenerator(1,10);
            Number2 = RandomsGenerator(1,10);
            break;
        case 2:
            Number1 = RandomsGenerator(11,50);
            Number2 = RandomsGenerator(11,50);
            break;
        case 3:
            Number1 = RandomsGenerator(51,100);
            Number2 = RandomsGenerator(51,100);
        case 4:
            Number1 = RandomsGenerator(1,100);
            Number2 = RandomsGenerator(1,100);
            break;
    }
}

void GenerateFormula(int Number1, int Number2, enOperationType OperationType, int & FormulaResult)
{
    cout<<Number1<<endl;
    cout<<Number2<<"\t";
    switch (OperationType) 
    {
        case enOperationType::Add :
            cout<<"  +"<<endl;
            FormulaResult = Number1 + Number2;
            break;

        case enOperationType::Sub :
            cout<<"  -"<<endl;
            FormulaResult = Number1 - Number2;
            break;
        
        case enOperationType::Multipli :
            cout<<"  *"<<endl;
            FormulaResult = Number1 * Number2;
            break;

        case enOperationType::Divide :
            cout<<"  /"<<endl;
            FormulaResult = Number1 / Number2;
            break;
    }
    cout<<"----------------------"<<endl;
}

void EvaluateFormula(double FormulaResult, int GamePoints[2])
{
    int UserAnswer = 0;
    cin>>UserAnswer;

    if(UserAnswer == FormulaResult)
    {
        system("color 2f");    
        GamePoints[enAnswerResult::True]++;
    }
    else
    {
        system("color 4f");
        GamePoints[enAnswerResult::False]++;
    }
}

void PrintEndGameResult(enQuestionsLevel Level, enOperationType OperationType, int GamePoints[])
{
    //! We Add More Question In Case Number of Questions
    //!  Were Even and Both The "True" and "False" Answers Were Equal;
    if (GamePoints[enAnswerResult::True] == GamePoints[enAnswerResult::False])
    {
        GenerateQuestions(Level, OperationType, GamePoints);
    }

    cout << "\t****************************************************" << endl;
    cout << "\t     F I N A L   R E S U L T   I S :   ";
    
    if (GamePoints[enAnswerResult::True] > GamePoints[enAnswerResult::False])
    {
        cout << "P A S S" << endl;
        system("color 2f");
    }
    else
    {
        cout << "F A I L E D" << endl;
        system("color 4f");
    }
    cout<<"\t****************************************************" << endl;
    cout<<"\tQuestions Number       : " <<  GamePoints[enAnswerResult::False] + GamePoints[enAnswerResult::True]<< endl;
    cout<<"\tQuestions Level        : " << GetLevelText(Level)<<endl; 
    cout<<"\tOperatin Type          : " << GetOperationText(OperationType)<<endl;
    cout<<"\tNumber of Right Answers: " << GamePoints[enAnswerResult::True] << endl;
    cout<<"\tNumber of Wrong Answers: " << GamePoints[enAnswerResult::True] << endl;
    cout<<"\t****************************************************" << endl;
}

string GetLevelText(enQuestionsLevel Level)
{
    switch(Level)
    {
        case 1:
            return "Easy";
        case 2:
            return "Mediuem";
        case 3:
            return "Hard";
        case 4:
            return "Mix";
        default:
            return "Error";
    }
}

string GetOperationText(enOperationType OperationType)
{
    switch(OperationType)
    {
        case 1:
            return "Add +";
        case 2:
            return "Subtract -";
        case 3:
            return "Multiplication *";
        case 4:
            return "Divide /";
        case 5:
            return "Mix + - * / ";
        default:
            return "Error";
    }
}
