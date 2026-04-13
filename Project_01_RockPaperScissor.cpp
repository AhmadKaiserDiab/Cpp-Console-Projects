#include <iostream>
using namespace std;

enum enPosibilities { Paper = 1, Scissor = 2, Rock = 3 };
enum enWinner { Player = 0, Computer = 1 , Draw = 2 };

void StartGame();
void ResetScreen();
bool PlayGame();
int ReadPoisitveNumbers(string Message);
int RandomsGenerator(int From, int To);
void PlayRound(int GamePoints[3]);
enPosibilities GetPlayerChoice();
enPosibilities GetComputerChoice();
string GetChoice(enPosibilities Choice);
void ShowRoundWinner(enPosibilities PlayerChoice, enPosibilities ComputerChoice, int GamePoints[3]);
void PrintEndGameResult(int GamePoints[3]);

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
    int TotalGameRounds, ContinueGame, GamePoints[3] = {0};
    TotalGameRounds = ReadPoisitveNumbers("Enter How Many Round Do You Want To Play: ");
    for (int i = 1; i <= TotalGameRounds; i++)
    {
        cout << "\n__________Round [" << i << "] Begins:__________\n" << endl;
        PlayRound(GamePoints);
        cout << "____________________________________" << endl;
    }

    PrintEndGameResult(GamePoints);
    
    do
    {    
        ContinueGame = ReadPoisitveNumbers("Do You Want To Play Again?\n[0]No\n[1]Yes");
    } while (ContinueGame != 0 && ContinueGame != 1);    
    
    if (ContinueGame == 1)
        return true;
    return false;
}

int ReadPoisitveNumbers(string Message)
{
    int x;
    do
    {
        cout << Message << endl;
        cin >> x;
        if(x < 0)
        {
            cout<<"\n   Only Positive Numbers Allowed!!!";
        }
    } while (x < 0);
    return x;
}

void PlayRound(int GamePoints[3])
{
    enPosibilities PlayerChoice = GetPlayerChoice();
    enPosibilities ComputerChoice = GetComputerChoice();
    ShowRoundWinner(PlayerChoice, ComputerChoice, GamePoints);
}

int RandomsGenerator(int From, int To)
{
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

enPosibilities GetPlayerChoice() 
{
    return (enPosibilities)ReadPoisitveNumbers("Enter Your Choice:\n[1]Paper\n[2]Scissor\n[3]Stone");
}

enPosibilities GetComputerChoice() 
{
    return (enPosibilities)RandomsGenerator(1, 3);
}

string GetChoice(enPosibilities Choice) 
{
    switch (Choice)
    {
        case 1:
            return "Paper";
        case 2:
            return "Paper";
        case 3:
            return "Rock";
    }
}

void ShowRoundWinner(enPosibilities PlayerChoice, enPosibilities ComputerChoice, int GamePoints[3])
{
    cout<<"\nYou Choose:      "<<GetChoice(PlayerChoice)<<endl;
    cout<<"Computer Choose: "<<GetChoice(ComputerChoice)<<endl;

    if (PlayerChoice == ComputerChoice)
    {
        cout << "Round Winner:    [No Winner]" << endl;
        system("Color 6f");
        GamePoints[enWinner::Draw]++;
    }

    else if (PlayerChoice == enPosibilities::Rock && ComputerChoice == enPosibilities :: Scissor ||                      
            PlayerChoice == enPosibilities::Paper && ComputerChoice == enPosibilities :: Rock ||                      
            PlayerChoice == enPosibilities::Scissor && ComputerChoice == enPosibilities :: Paper )
    {
        cout << "Round Winner:    [You]" << endl;
        system("Color 2f");
        GamePoints[enWinner::Player]++;
    }
    else
    { 
        cout << "Round Winner:     [Computer]\a" << endl;
        system("Color 4f");
        GamePoints[enWinner::Computer]++;
    }
}

void PrintEndGameResult(int GamePoints[3]) 
{
    cout << "\n\t****************************************************";
    cout << "\n\t***************** G a m e  O v e r *****************";
    cout << "\n\t****************************************************" << endl;
    cout << "\t__________________[ Game Results ]__________________" << endl;
    cout << "\tTotal Game Rounds:  " << GamePoints[enWinner :: Player] + GamePoints[enWinner :: Computer] + GamePoints[enWinner :: Draw] << endl;
    cout << "\tPlayer Win Times:   " << GamePoints[enWinner :: Player] << endl;
    cout << "\tComputer Win Times: " << GamePoints[enWinner :: Computer] << endl;
    cout << "\tDraw Times:         " << GamePoints[enWinner :: Draw] << endl;
    cout << "\tFinal Winner:       ";
    
    if (GamePoints[enWinner::Player] > GamePoints[enWinner::Computer] &&
        GamePoints[enWinner::Player] > GamePoints[enWinner:: Draw])
    {
        cout << "Player" << endl;
        system("Color 2f");
    }

    else if(GamePoints[enWinner::Computer] > GamePoints[enWinner::Player] &&
            GamePoints[enWinner::Computer] > GamePoints[enWinner::Draw] )
    {
        cout << "Computer" << endl;
        system("Color 4f");
    }

    else
    {
        cout << "NoBody Wins, It's A Draw" << endl;
        system("Color 6f");
    }    
    cout << "\t____________________________________________________\n\n";
}
