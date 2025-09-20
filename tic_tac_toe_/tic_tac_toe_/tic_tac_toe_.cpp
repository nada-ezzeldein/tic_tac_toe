#include <iostream>
#include <windows.h>
using namespace std;
char arr[3][3] = { '1','2','3','4','5','6','7','8','9' };
char player = 'x';
//===========================================================
//===========================================================

void print_table() {
    system("cls");
    cout << "\n ____________\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " | " << arr[i][j];
        }
        cout << " | \n ____________\n";
    }
}
//==============================================================

void playing(char& player, bool switch_player = true) {
    int position;
    bool valid = false;

    while (!valid) {
        cout << "please choose your position:" << " " << "player" << " " << "(" << player << ")" << "\n";
        cin >> position;
        if (position < 1 || position > 9 || cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 9.\n";
            continue;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i][j] == position + '0') {
                    arr[i][j] = player;
                    valid = true;
                    break;
                }
            }
            if (valid) break;
        }

        if (!valid) {
            cout << "This position is already taken. Try another one.\n";
        }
    }
    print_table();
    if (switch_player) {
        player = (player == 'x') ? 'o' : 'x';
    }
}

//==============================================================
char winner() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
            return arr[i][0];
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (arr[0][j] == arr[1][j] && arr[1][j] == arr[2][j])
            return arr[0][j];
    }

    // Check diagonals
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
        return arr[0][0];
    if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
        return arr[0][2];

    // Check for draw
    bool draw = true;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (arr[i][j] != 'x' && arr[i][j] != 'o')
                draw = false;

    if (draw) return 'd'; // draw
    return '*'; // game still going
}
//==============================================================
// =======================================level_2======================================
//function to check winner
bool check_winner(char board[3][3], char player) {
    // rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    // coulumns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    // diagonal (main)
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    // diagonal (sec)
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    else {
        return false;
    }
}
//==============================================================
// function to make the computer play
void level_2(char board[3][3]) {
    // check if their is any valid move that he can do to win
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num;
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                num = board[i][j];
                board[i][j] = 'o'; // try to put 'o' in the frist impety index
                if (check_winner(board, 'o'))
                    return; // if it wins keep it
                else {
                    board[i][j] = num; // if not remove it
                }
            }
        }
    }
    // check if their is any valid move that make the player win
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num;
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                num = board[i][j];
                board[i][j] = 'x'; // try to play as the player
                if (check_winner(board, 'x')) {
                    board[i][j] = 'o'; // if this move makes the player wins put 'o'
                    return;
                }
                else {
                    board[i][j] = num;// remove the simbol if the move isn't true
                }
            }
        }
    }
    // if the middle of the board is impety play there
    if (board[1][1] != 'x' && board[1][1] != 'o') {
        board[1][1] = 'o';
        return;
    }
    // if there is no moves to make the player or computer wins , play in the frist impety index
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                board[i][j] = 'o';
                return;
            }
        }
    }
}

//==============================================================
int main() {
    bool again = 1;
    while (again) {
        cout << "                                 _________________________________________" << endl;
        cout << "                                       (welcome to Tic-Tac-Toe GAME)                                   " << endl;
        cout << "                                 _________________________________________" << endl;
        cout << "\n\n Which level do you want to play?\n";
        cout << "1) Level 1  [player vs player]\n";
        cout << "2) Level 2  [player vs Computer]\n";
        cout << "========================================================\n";
        int level;
        cin >> level;
        //to make sure that the input is valid
        cin.ignore(10000, '\n');
        while (level > 2 || level < 1 || cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. please enter another number\n";
            cin >> level;
            cin.ignore(10000, '\n');
        }

        switch (level) {
        case 1:
        {
            cout << "                                   Level 1  [player vs player]\n";
            cout << "                        **************************************************\n";
            //to reset the board
            char number = '1';
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    arr[i][j] = number++;
                }
            }

            print_table();
            while (winner() == '*') {
                playing(player);
                winner();
            }
            if (winner() == 'x') {
                cout << "Player (x) wins!\n";
            }
            else if (winner() == 'o') {
                cout << "Player (o) wins!\n";
            }
            else {
                cout << "NO Winner!\n";
            }
            break;
        }
        case 2: {
            //to reset the board
            char number = '1';
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    arr[i][j] = number++;
                }
            }
            print_table();
            while (winner() == '*') {
                cout << "\nYour turn (player x):\n";
                playing(player, false); // the player play
                if (winner() != '*') {
                    break;
                }
                // computer turn
                cout << "\nComputer is thinking...\n";
                Sleep(1000); // computer wait 1 second (1000 ml_sec)
                level_2(arr); //the computer play
                print_table();// print the table after every move
                cout << "Computer played!\n";
            }
            if (winner() == 'x') {
                cout << "Player (x) wins!\n";
            }
            else if (winner() == 'o') {
                cout << "Computer wins!\n";
            }
            else {
                cout << "DRAW!\n";
            }
            break;
        }

        }
        cout << "Do you want to play again?\n\ Press 1 to play again and 0 to exit:";
        cin >> again;
        while (again > 1 || again < 0 || cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid number. please enter another number\n";
            cin >> again;
        }
    }
    cout << "Thank you for using our programme\n";
    return 0;
}