#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum enGameChoices { Rock = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoices PlayerChoice;
    enGameChoices ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResult {
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string GameWinnerName = " ";
};

short RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 0; i < NumberOfTabs; i++) {
        t += "\t";
    }
    return t;
}

void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player:
        system("color 2F"); 
        break;
    case enWinner::Computer:
        system("color 4F"); 
        cout << "\a";       
        break;
    case enWinner::Draw:
        system("color 6F"); 
        break;
    }
}

short HowManyRounds() {
    short Rounds = 0;
    do {
        cout << "How many Rounds do you want to play (1 to 10)? ";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}

enGameChoices ReadPlayerChoice() {
    short PlayerChoice = 0;
    do {
        cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissor ? ";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);
    return (enGameChoices)PlayerChoice;
}

enGameChoices GetComputerChoice() {
    return (enGameChoices)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice) {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice) {
    case enGameChoices::Rock:
        if (RoundInfo.ComputerChoice == enGameChoices::Paper) return enWinner::Computer;
        break;
    case enGameChoices::Paper:
        if (RoundInfo.ComputerChoice == enGameChoices::Scissor) return enWinner::Computer;
        break;
    case enGameChoices::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoices::Rock) return enWinner::Computer;
        break;
    }
    return enWinner::Player;
}

string WinnerName(enWinner Winner) {
    string arrWinnerName[3] = { "Player", "Computer", "No Winner" };
    return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoices Choice) {
    string arrGameChoices[3] = { "Rock", "Paper", "Scissor" };
    return arrGameChoices[Choice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo) {
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n";
    cout << "Player Choice   : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Winner          : [" << RoundInfo.WinnerName << "]\n";
    cout << "___________________________________________\n";
    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short ComputerWins, short PlayerWins) {
    if (ComputerWins > PlayerWins) return enWinner::Computer;
    else if (PlayerWins > ComputerWins) return enWinner::Player;
    else return enWinner::Draw;
}

stGameResult FillGameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
    stGameResult GameResult;
    GameResult.GameRounds = GameRounds;
    GameResult.PlayerWinTimes = PlayerWinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame(ComputerWinTimes, PlayerWinTimes);
    GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);
    return GameResult;
}

void ShowGameOverScreen() {
    cout << endl << Tabs(2) << "__________________________________________________________\n";
    cout << Tabs(2) << "                 +++ G A M E  O V E R +++";
    cout << endl << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResult(stGameResult GameResults) {
    cout << Tabs(2) << "_____________________ [Game Results] _____________________\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Win Times   : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.GameWinnerName << endl;
    cout << Tabs(2) << "__________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}

stGameResult PlayGame(short NumberOfRounds) {
    short PlayerWinTime = 0, ComputerWinTime = 0, DrawTime = 0;

    for (short GameRound = 1; GameRound <= NumberOfRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] Begins:\n";
        stRoundInfo RoundInfo;
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player) PlayerWinTime++;
        else if (RoundInfo.Winner == enWinner::Computer) ComputerWinTime++;
        else DrawTime++;

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(NumberOfRounds, PlayerWinTime, ComputerWinTime, DrawTime);
}

void ResetScreen() {
    system("cls");   
    system("color 0F"); 
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResult GameResults = PlayGame(HowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResults);

        cout << endl << Tabs(2) << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}