#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    board.resize(3, std::vector<Piece>(4, Blank));
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for (int i = 0; i < (int)board.size(); i++){
        for (int j = 0; j < (int)board[i].size(); j++){
            board[i][j] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    // First, check that column is within bounds
    if (column < 0 || column > 3)
        return Invalid;

    // Check that this column is not full
    if (board[2][column] == Blank){
        // X's turn, so we place a piece at the first available row in the column
        switch(turn){
            case X:
                if (board[0][column] == Blank){
                    board[0][column] = X;
                } else if (board[1][column] == Blank){
                    board[1][column] = X;
                } else {
                    board[2][column] = X;
                }
                turn = O;
                return X;
            case O:
                if (board[0][column] == Blank){
                    board[0][column] = O;
                } else if (board[1][column] == Blank){
                    board[1][column] = O;
                } else {
                    board[2][column] = O;
                }
                turn = X;
                return O;
            default:
                return Blank;
        }
    // If column is full, the other player gets their turn; return Blank.
    } else {
        switch(turn){
            case X:
                turn = O;
                break;
            case O:
                turn = X;
                break;
        }
        return Blank;
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if ( (row > -1 && row < 3) && (column > -1 && column < 4) ){
        return board[row][column];
    } else {
        return Invalid;
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    // Check that the board has been filled
    for (int i = 0; i < (int)board.size(); i++){
        for (int j = 0; j < (int)board[i].size(); i++){
            // If not, return invalid.
            if (board[i][j] == Blank)
                return Invalid;
        }
    }
    /*
    Board[row,col]:
    * [2,0][2,1][2,2][2,3]
    * [1,0][1,1][1,2][1,3]
    * [0,0][0,1][0,2][0,3]
    */
    bool player_X_wins = false;
    bool player_O_wins = false;
    // Otherwise, we need to figure out who won:
    // Check for the same piece on every column
    // 3x1
    for (int i = 0; i < 4; i++){
        if ( (board[2][i] == board[1][i]) && (board[1][i] == board[0][i]) ){
            if (board[2][i] == X){
                player_X_wins = true;
            } else {
                player_O_wins = true;
            }
        }
    }
    // Check for the same piece on every row
    // 3x1
    for (int i = 0; i < 3; i++){
        if ( (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) ){
            if (board[i][1] == X){
                player_X_wins = true;
            } else {
                player_O_wins = true;
            }
        } else if ( (board[i][1] == board[i][2]) && (board[i][2] == board[i][3]) ){
            if (board[i][1] == X){
                player_X_wins = true;
            } else {
                player_O_wins = true;
            }
        }
    }
    // 4x1
    for (int i = 0; i < 3; i++){
        if ( (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][2] == board[i][3]) ){
            if (board[i][0] == X){
                player_X_wins = true;
                player_O_wins = false;
            } else {
                player_O_wins = true;
                player_X_wins = false;
            }
        }
    }

    if (player_X_wins && !player_O_wins){
        return X;
    } else if (player_O_wins && !player_X_wins){
        return O;
    } else {
        return Blank;
    }
}