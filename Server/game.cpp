#include <bits/stdc++.h>
#include <stdlib.h>

int prevRow;    //track previous move
int curRow;
int curCol; 
bool isEnPassant; // special move
bool isPromotion; //special move
bool isCastle; //special move
bool canCastleB = true;
bool canCastleW = true;
int isFiftyMove = 0;

class GamePiece
{
public:
    GamePiece(char pieceColor) : pieceColor(pieceColor) {}
    ~GamePiece() {}
    virtual char GetPiece() const = 0;
    char GetColor() const {
        return pieceColor;
    }
    bool IsLegalMove(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        GamePiece* dest = GameBoard[destRow][destCol];
        if ((dest == 0) || (pieceColor != dest->GetColor())) {
            return IsLegalSquare(srcRow, srcCol, destRow, destCol, GameBoard);
        }
        return false;
    }

    bool operator==(const GamePiece& other) const {
        // Compare each element in the array
        return GetPiece() == other.GetPiece() && GetColor() == other.GetColor();
    }

private:
    virtual bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) = 0;
    char pieceColor;
};

class Pawn : public GamePiece
{
public:
    Pawn(char pieceColor) : GamePiece(pieceColor) {}
    ~Pawn() {}
private:
    virtual char GetPiece() const {
        return 'P';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        GamePiece* dest = GameBoard[destRow][destCol];
        if (dest == 0) {
            // Destination square is unoccupied
            if (srcCol == destCol) {
                if (GetColor() == 'W') {
                    if (srcRow == 1 && destRow == 3) return true;
                    if (destRow == srcRow + 1) {
                        if (destRow == 7) isPromotion = true; 
                        return true;
                    }
                } else {
                    if (srcRow == 6 && destRow == 4) return true;
                    if (destRow == srcRow - 1) {
                        if (destRow == 0) isPromotion = true;
                        return true;
                    }
                }
            }
            //En passant
            if ((srcCol == destCol + 1 || srcCol == destCol - 1) && curCol == destCol && GameBoard[srcRow][destCol] != 0 && GameBoard[srcRow][destCol]->GetPiece() == 'P') {
                if ((GetColor() == 'W' && srcRow == 4 && destRow == 5 && prevRow == 6 && curRow == 4) || (GetColor() == 'B' && srcRow == 3 && destRow == 2 && prevRow == 1 && curRow == 3)) {
                    // GameBoard[srcRow][destCol] = 0;
                    isEnPassant = true;
                    return true;
                }
            }
        } else {
            // Dest holds piece of opposite color
            if ((srcCol == destCol + 1) || (srcCol == destCol - 1)) {
                if (GetColor() == 'W') {
                    if (destRow == srcRow + 1) {
                        if (destRow == 7) isPromotion = true; 
                        return true;
                    }
                } else {
                    if (destRow == srcRow - 1) {
                        if (destRow == 0) isPromotion = true; 
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Knight : public GamePiece
{
public:
    Knight(char pieceColor) : GamePiece(pieceColor) {}
    ~Knight() {}
private:
    virtual char GetPiece() const {
        return 'N';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((srcCol == destCol + 1) || (srcCol == destCol - 1)) {
            if ((srcRow == destRow + 2) || (srcRow == destRow - 2)) {
                return true;
            }
        }
        if ((srcCol == destCol + 2) || (srcCol == destCol - 2)) {
            if ((srcRow == destRow + 1) || (srcRow == destRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class Bishop : public GamePiece
{
public:
    Bishop(char pieceColor) : GamePiece(pieceColor) {}
    ~Bishop() {}
private:
    virtual char GetPiece() const {
        return 'B';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        if ((destCol - srcCol == destRow - srcRow) || (destCol - srcCol == srcRow - destRow)) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            int checkRow;
            int checkCol;
            for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset;
                checkRow !=  destRow;
                checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
            {
                if (GameBoard[checkRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Rook : public GamePiece
{
public:
    Rook(char pieceColor) : GamePiece(pieceColor) {}
    ~Rook() {}
private:
    virtual char GetPiece() const {
        return 'R';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        if (srcRow == destRow) {
            // Make sure that all invervening squares are empty
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            for (int checkCol = srcCol + colOffset; checkCol !=  destCol; checkCol = checkCol + colOffset) {
                if (GameBoard[srcRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (destCol == srcCol) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            for (int checkRow = srcRow + rowOffset; checkRow !=  destRow; checkRow = checkRow + rowOffset) {
                if (GameBoard[checkRow][srcCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Queen : public GamePiece
{
public:
    Queen(char pieceColor) : GamePiece(pieceColor) {}
    ~Queen() {}
private:
    virtual char GetPiece() const {
        return 'Q';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        if (srcRow == destRow) {
            // Make sure intervening squares are empty
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            for (int checkCol = srcCol + colOffset; checkCol !=  destCol; checkCol = checkCol + colOffset) {
                if (GameBoard[srcRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (destCol == srcCol) {
            // Make sure intervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            for (int checkRow = srcRow + rowOffset; checkRow !=  destRow; checkRow = checkRow + rowOffset) {
                if (GameBoard[checkRow][srcCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((destCol - srcCol == destRow - srcRow) || (destCol - srcCol == srcRow - destRow)) {
            // Make sure intervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            int checkRow;
            int checkCol;
            for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset;
                checkRow !=  destRow;
                checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
            {
                if (GameBoard[checkRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class King : public GamePiece
{
public:
    King(char pieceColor) : GamePiece(pieceColor) {}
    ~King() {}
private:
    virtual char GetPiece() const {
        return 'K';
    }
    bool IsLegalSquare(int srcRow, int srcCol, int destRow, int destCol, GamePiece* GameBoard[8][8]) {
        int rowDelta = destRow - srcRow;
        int colDelta = destCol - srcCol;
        if (((rowDelta >= -1) && (rowDelta <= 1)) &&
            ((colDelta >= -1) && (colDelta <= 1)) && (rowDelta != 0 || colDelta != 0))
        {
            return true;
        }

        if (GetColor() == 'W') {
            if (canCastleW && destRow == 0) {
                if (destCol == 2 && GameBoard[0][1] == 0 && GameBoard[0][2] == 0 && GameBoard[0][3] == 0) {
                    isCastle = true;
                    return true;
                } else if (destCol == 6 && GameBoard[0][5] == 0 && GameBoard[0][6] == 0) {
                    isCastle = true;
                    return true;
                }
            }
        } else {
            if (canCastleB && destRow == 7) {
                if (destCol == 2 && GameBoard[7][1] == 0 && GameBoard[7][2] == 0 && GameBoard[7][3] == 0) {
                    isCastle = true;
                    return true;
                } else if (destCol == 6 && GameBoard[7][5] == 0 && GameBoard[7][6] == 0) {
                    isCastle = true;
                    return true;
                }
            }
        }

        return false;
    }
};

struct GamePieceHash {
    std::size_t operator()(const GamePiece* obj) const {
        // Use the hash function for int
        return std::hash<char>()(obj->GetPiece()) ^ std::hash<char>()(obj->GetColor());
    }
};

class CBoard
{
public:
    CBoard() {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                MainGameBoard[row][col] = 0;
            }
        }
        // Allocate and place black pieces
        for (int col = 0; col < 8; ++col) {
            MainGameBoard[6][col] = new Pawn('B');
        }
        MainGameBoard[7][0] = new Rook('B');
        MainGameBoard[7][1] = new Knight('B');
        MainGameBoard[7][2] = new Bishop('B');
        MainGameBoard[7][3] = new Queen('B');
        MainGameBoard[7][4] = new King('B');
        MainGameBoard[7][5] = new Bishop('B');
        MainGameBoard[7][6] = new Knight('B');
        MainGameBoard[7][7] = new Rook('B');
        // Allocate and place white pieces
        for (int col = 0; col < 8; ++col) {
            MainGameBoard[1][col] = new Pawn('W');
        }
        MainGameBoard[0][0] = new Rook('W');
        MainGameBoard[0][1] = new Knight('W');
        MainGameBoard[0][2] = new Bishop('W');
        MainGameBoard[0][3] = new Queen('W');
        MainGameBoard[0][4] = new King('W');
        MainGameBoard[0][5] = new Bishop('W');
        MainGameBoard[0][6] = new Knight('W');
        MainGameBoard[0][7] = new Rook('W');
    }
    ~CBoard() {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                delete(MainGameBoard[row][col]);
                MainGameBoard[row][col] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        const int squareWidth = 4;
        const int squareHeight = 3;
        for (int row = 0; row < 8*squareHeight; ++row) {
            int squareRow = row/squareHeight;
            // Print side border with numbering
            if (row % 3 == 1) {
                cout << '-' << (char)('1' + 7 - squareRow) << '-';
            } else {
                cout << "---";
            }
            // Print the chess board
            for (int col = 0; col < 8*squareWidth; ++col) {
                int squareCol = col/squareWidth;
                if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2) && MainGameBoard[7-squareRow][squareCol] != 0) {
                    if ((col % 4) == 1) {
                        cout << MainGameBoard[7-squareRow][squareCol]->GetColor();
                    } else {
                        cout << MainGameBoard[7-squareRow][squareCol]->GetPiece();
                    }
                } else {
                    if ((squareRow + squareCol) % 2 == 1) {
                        cout << '*';
                    } else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int row = 0; row < squareHeight; ++row) {
            if (row % 3 == 1) {
                cout << "---";
                for (int col = 0; col < 8*squareWidth; ++col) {
                    int squareCol = col/squareWidth;
                    if ((col % 4) == 1) {
                        cout << (squareCol + 1);
                    } else {
                        cout << '-';
                    }
                }
                cout << endl;
            } else {
                for (int col = 1; col < 9*squareWidth; ++col) {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char pieceColor) {
        // Find the king
        int kingRow;
        int kingCol;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (MainGameBoard[row][col] != 0) {
                    if (MainGameBoard[row][col]->GetColor() == pieceColor) {
                        if (MainGameBoard[row][col]->GetPiece() == 'K') {
                            kingRow = row;
                            kingCol = col;
                        }
                    }
                }
            }
        }
        // Run through all opponent's pieces and see if any can take the king
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (MainGameBoard[row][col] != 0) {
                    if (MainGameBoard[row][col]->GetColor() != pieceColor) {
                        if (MainGameBoard[row][col]->IsLegalMove(row, col, kingRow, kingCol, MainGameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char pieceColor) {
        // Run through all pieces
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (MainGameBoard[row][col] != 0) {
                    // If it is a piece of the current player, see if it has a legal move
                    if (MainGameBoard[row][col]->GetColor() == pieceColor) {
                        for (int moveRow = 0; moveRow < 8; ++moveRow) {
                            for (int moveCol = 0; moveCol < 8; ++moveCol) {
                                isCastle = false;
                                if (MainGameBoard[row][col]->IsLegalMove(row, col, moveRow, moveCol, MainGameBoard)) {
                                    if (isCastle && IsInCheck(pieceColor)) {
                                        continue;
                                    }
                                    // Make move and check whether king is in check
                                    GamePiece* temp                   = MainGameBoard[moveRow][moveCol];
                                    MainGameBoard[moveRow][moveCol]   = MainGameBoard[row][col];
                                    MainGameBoard[row][col]           = 0;
                                    bool bCanMove = !IsInCheck(pieceColor);
                                    // Undo the move
                                    MainGameBoard[row][col]           = MainGameBoard[moveRow][moveCol];
                                    MainGameBoard[moveRow][moveCol]   = temp;
                                    if (bCanMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool operator==(const CBoard& other) const {
        // Compare each element in the array
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (!(MainGameBoard[i][j] == other.MainGameBoard[i][j]))
                    return false;
        return true;
    }

    GamePiece* MainGameBoard[8][8];
};

struct GameBoardHash {
    std::size_t operator()(const CBoard& obj) const {
        std::size_t hashValue = 0;

        // Combine hash values of each InnerClass pointer in the array
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                hashValue ^= (GamePieceHash()(obj.MainGameBoard[i][j]) << (i * 8 + j));

        return hashValue;
    }
};

std::unordered_map<CBoard, int, GameBoardHash> countState;

class ChessGame
{
public:
    ChessGame() : playerTurn('W') {}
    ~ChessGame() {}

    // void Start() {
    //     using namespace std;
    //     cout<<endl<<endl<<"          Welcome to Chess Game Developed by Cppsecrets "<<endl<<endl<<endl;
    //     cout<<"                      Keys to sysmbols used "<<endl<<endl<<endl;
    //     cout<<" * = Black cell"<<endl;
    //     cout<<" Blank = white cell"<<endl;
    //     cout<<" WP = White pawn &  BP = Black pawn"<<endl;
    //     cout<<" WN = White Knight & BN = Black Knight"<<endl;
    //     cout<<" WB = White Bishop & BB = Black Bishop"<<endl;
    //     cout<<" WR = White Rook & BR = Black Rook"<<endl;
    //     cout<<" WQ = White Queen & BQ = Black Queen"<<endl;
    //     cout<<" WK = White King & BK =Black King"<<endl;
    //     cout<<"Rule for move is :"<<endl;
    //     cout<<"Move by selecting row & column to another valid location using row & column"<<endl<<endl<<endl;
    //     do {
    //         GetNextMove(chessboard.MainGameBoard);
    //         countState[chessboard]++;
    //         AlternateTurn();
    //     } while (!IsGameOver());
    //     chessboard.Print();
    // }

    int validateMove(GamePiece* GameBoard[8][8], int startRow, int startCol, int endRow, int endCol) {
        using namespace std;
        isEnPassant = false; 
        isPromotion = false;
        isCastle = false;  
        bool isCapture = false;
        int validMove = 0;

        // do {
        //     // system ("clear");
        //     cout << endl << endl;
            
            // chessboard.Print();
            
            // // Get input and convert to coordinates
            // cout << playerTurn << "'s Move From: ";
            // int startMove;
            // cin >> startMove;
            // int startRow = (startMove / 10) - 1;
            // int startCol = (startMove % 10) - 1;

            // cout << "To: ";
            // int endMove;
            // cin >> endMove;
            // int endRow = (endMove / 10) - 1;
            // int endCol = (endMove % 10) - 1;

            // Check that the indices are in range
            // and that the source and destination are different
        if ((startRow >= 0 && startRow <= 7) &&
            (startCol >= 0 && startCol <= 7) &&
            (endRow >= 0 && endRow <= 7) &&
            (endCol >= 0 && endCol <= 7)) {

            GamePiece* currPiece = GameBoard[startRow][startCol];
            // Check that the piece is the correct color
            if ((currPiece != 0) && (currPiece->GetColor() == playerTurn)) {
                // Check that the destination is a valid destination
                if (currPiece->IsLegalMove(startRow, startCol, endRow, endCol, GameBoard)) {
                    //Check for Castling
                    if (!chessboard.IsInCheck(playerTurn) && isCastle) {
                        GameBoard[startRow][(startCol + endCol)/2] = currPiece;
                        GameBoard[startRow][startCol] = 0;
                        bool check1 = chessboard.IsInCheck(playerTurn);
                        GameBoard[startRow][endCol] = currPiece;
                        GameBoard[startRow][(startCol + endCol)/2] = 0;
                        bool check2 = chessboard.IsInCheck(playerTurn);
                        
                        if (!check1 && !check2) {
                            int rookCol = (startCol > endCol) ? 0 : 7;
                            GamePiece *rook = GameBoard[startRow][rookCol];
                            GameBoard[startRow][rookCol] = 0;
                            GameBoard[startRow][(startCol + endCol)/2] = rook;
                            if (playerTurn == 'W') canCastleW = false;
                            else canCastleB = false;
                            validMove = 1;
                            isFiftyMove++;
                        } else {
                            GameBoard[startRow][startCol] = currPiece;
                            GameBoard[endRow][endCol] = 0;
                        }

                    } else {
                        // Make the move
                        if (GameBoard[endRow][endCol] != 0 || isEnPassant) isCapture = true;
                        GamePiece* temp                   = GameBoard[endRow][endCol];
                        GameBoard[endRow][endCol]     = GameBoard[startRow][startCol];
                        GameBoard[startRow][startCol] = 0;

                        // Make sure that the current player is not in check
                        if (!chessboard.IsInCheck(playerTurn)) {
                            //Check for special move    
                            if (isEnPassant) {
                                GameBoard[startRow][endCol] = 0;
                            }
                            if (isPromotion) {
                                // Promote(endRow, endCol, GameBoard);
                                validMove = 2;
                            } else validMove = 1;
                            if (currPiece->GetPiece() == 'R' || currPiece->GetPiece() == 'K') {
                                if (playerTurn == 'W') canCastleW = false;
                                else canCastleB = false;
                            }
                            if (isCapture) {isFiftyMove = 0; countState.clear();}
                            else isFiftyMove++;

                            //track previous move
                            curCol = endCol;
                            curRow = endRow;
                            prevRow = startRow;
                            delete(temp);
                        } else { // Undo the last move
                            GameBoard[startRow][startCol] = GameBoard[endRow][endCol];
                            GameBoard[endRow][endCol]  = temp;
                        }
                    }
                }
            }
        }
        if (validMove == 0) {
            cout << "Invalid Move!" << endl;
        }
        return validMove;
    }

    void Promote(char opt, int row, int col, GamePiece* GameBoard[8][8]) {
        using namespace std;
        
        switch(opt) {
            case 'Q': {
                GameBoard[row][col] = new Queen(playerTurn);
                break;
            }
            case 'R': {
                GameBoard[row][col] = new Rook(playerTurn);
                break;
            }
            case 'B': {
                GameBoard[row][col] = new Bishop(playerTurn);
                break;
            }
            case 'N': {
                GameBoard[row][col] = new Knight(playerTurn);
                break;
            }
            default: cout << "null" << endl;
        }
    }

    void AlternateTurn() {
        playerTurn = (playerTurn == 'W') ? 'B' : 'W';
    }

    bool IsThreeFoldRep() {
        for (auto& it : countState) {
            if (it.second >= 3) return true;
        }

        return false;
    }

    /*
        0: not over
        1: White wins
        2: Black wins
        3: Stalemate
        4: Three fold repetition
        5: fifty move rule
    */
    int IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        if (!chessboard.CanMove(playerTurn)) {
            if (chessboard.IsInCheck(playerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << playerTurn << " Wins!" << std::endl;
                if (playerTurn == 'W') return 1;
                else return 2;
            } else {
                std::cout << "Stalemate!" << std::endl;
                return 3;
            }
        }
        if (IsThreeFoldRep())
            return 4;

        if (isFiftyMove >= 100)
            return 5;

        return 0;
    }
    CBoard chessboard;
    char playerTurn;
    std::string moves; 
};

// int main() {
//     ChessGame Game;
//     // Game.Start();
//     return 0;
// }
