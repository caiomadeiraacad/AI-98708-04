
/*
Caio Madeira & Guilherme Cavazotto

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned wins[8][3] = {
    {0,1,2}, {3,4,5},{6,7,8},
    {0,3,6},{1,4,7},{2,5,8},
    {0,4,8},{2,4,6}
};


int gridChar(int i)
{
    switch(i) 
    {
        case 1: return 'O';  
        case -1: return 'X';
        case 0: return ' ';
        default: return '-';
    }
}

void draw(int b[9]) {
    printf(" %c | %c | %c\n", gridChar(b[0]) ,gridChar(b[1]), gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(b[3]), gridChar(b[4]) ,gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(b[6]), gridChar(b[7]), gridChar(b[8]));
}

int win(const int board[9]) {
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    int winner = win(board);
    if(winner != 0) return winner*player;
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}

void randomMove(int board[9]) 
{
    int empty_spots[9];
    int count = 0;
    int i;

    for(i = 0; i < 9; ++i) {
        if (board[i] == 0) {
            empty_spots[count] = i;
            count++;
        }
    }

    if (count > 0) {
        int random_index = rand() % count;
        int move = empty_spots[random_index];
        board[move] = 1;
    }

} 

void computerMove(int board[9], int level) {
    int r = rand() % 100;
    int use_minmax = 0;
    if (level == 2) { use_minmax = 1; }
    else if (level == 1) { if (r < 50) use_minmax = 1; }
    else if (level == 0) { if (r < 25) use_minmax = 1; }
    if (use_minmax) {
        int move = -1;
        int score = -2;
        int i;
        for(i = 0; i < 9; ++i) {
            if(board[i] == 0) {
                board[i] = 1;
                int tempScore = -minimax(board, -1);
                board[i] = 0;
                if(tempScore > score) {
                    score = tempScore;
                    move = i;
                }
            }
        }
        if (move != -1) board[move] = 1;
    } else {
        randomMove(board);
    }
}

void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nescolha a posição ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move < 0 || move > 8 || board[move] != 0);
    board[move] = -1;
}



int main(int argc, char** argv)
{
     srand(time(NULL));
    int level = 0;
    printf("Selecione a dificuldade:\n0 - fácil\n1 - medio\n2 - difícil\n");
    if (scanf("%d", &level) > 0 && (level >= 0 && level <= 2)) 
    {
        printf("Iniciando no modo -> %d\n", level);
        int board[9] = {0,0,0,0,0,0,0,0,0};
        printf("Computador: O, Você: X\nJogar primeiro ou em segundo? ");
        int player=0;
        scanf("%d",&player);
        printf("\n");
        unsigned turn;

        for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
            if((turn+player) % 2 == 0)
                computerMove(board, level);
            else {
                draw(board);
                playerMove(board);
            }
        }
        switch(win(board)) {
            case 0:
                printf("Deu velha.\n");
                break;
            case 1:
                draw(board);
                printf("Você perdeu.\n");
                break;
            case -1:
                printf("Você venceu!!!!!\n");
                break;
        }

    } else {
        perror("Erro: input inválido\n");
        return -1;
    }
    return 0;
}