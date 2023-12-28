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
    GamePiece(char PieceColor) : mPieceColor(PieceColor) {}
    ~GamePiece() {}
    virtual char GetPiece() const = 0;
    char GetColor() const {
        return mPieceColor;
    }
    bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
        if ((qpDest == 0) || (mPieceColor != qpDest->GetColor())) {
            return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, GameBoard);
        }
        return false;
    }

    bool operator==(const GamePiece& other) const {
        // Compare each element in the array
        return GetPiece() == other.GetPiece() && GetColor() == other.GetColor();
    }

private:
    virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) = 0;
    char mPieceColor;
};

class PawnPiece : public GamePiece
{
public:
    PawnPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~PawnPiece() {}
private:
    virtual char GetPiece() const {
        return 'P';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
        if (qpDest == 0) {
            // Destination square is unoccupied
            if (iSrcCol == iDestCol) {
                if (GetColor() == 'W') {
                    if (iSrcRow == 1 && iDestRow == 3) return true;
                    if (iDestRow == iSrcRow + 1) {
                        if (iDestRow == 7) isPromotion = true; 
                        return true;
                    }
                } else {
                    if (iSrcRow == 6 && iDestRow == 4) return true;
                    if (iDestRow == iSrcRow - 1) {
                        if (iDestRow == 0) isPromotion = true;
                        return true;
                    }
                }
            }
            //En passant
            if ((iSrcCol == iDestCol + 1 || iSrcCol == iDestCol - 1) && curCol == iDestCol && GameBoard[iSrcRow][iDestCol] != 0 && GameBoard[iSrcRow][iDestCol]->GetPiece() == 'P') {
                if ((GetColor() == 'W' && iSrcRow == 4 && iDestRow == 5 && prevRow == 6 && curRow == 4) || (GetColor() == 'B' && iSrcRow == 3 && iDestRow == 2 && prevRow == 1 && curRow == 3)) {
                    // GameBoard[iSrcRow][iDestCol] = 0;
                    isEnPassant = true;
                    return true;
                }
            }
        } else {
            // Dest holds piece of opposite color
            if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
                if (GetColor() == 'W') {
                    if (iDestRow == iSrcRow + 1) {
                        if (iDestRow == 7) isPromotion = true; 
                        return true;
                    }
                } else {
                    if (iDestRow == iSrcRow - 1) {
                        if (iDestRow == 0) isPromotion = true; 
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class KnightPiece : public GamePiece
{
public:
    KnightPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KnightPiece() {}
private:
    virtual char GetPiece() const {
        return 'N';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
            if ((iSrcRow == iDestRow + 2) || (iSrcRow == iDestRow - 2)) {
                return true;
            }
        }
        if ((iSrcCol == iDestCol + 2) || (iSrcCol == iDestCol - 2)) {
            if ((iSrcRow == iDestRow + 1) || (iSrcRow == iDestRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class BishopPiece : public GamePiece
{
public:
    BishopPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~BishopPiece() {}
private:
    virtual char GetPiece() const {
        return 'B';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class RookPiece : public GamePiece
{
public:
    RookPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~RookPiece() {}
private:
    virtual char GetPiece() const {
        return 'R';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if (iSrcRow == iDestRow) {
            // Make sure that all invervening squares are empty
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class QueenPiece : public GamePiece
{
public:
    QueenPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~QueenPiece() {}
private:
    virtual char GetPiece() const {
        return 'Q';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if (iSrcRow == iDestRow) {
            // Make sure that all invervening squares are empty
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class KingPiece : public GamePiece
{
public:
    KingPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KingPiece() {}
private:
    virtual char GetPiece() const {
        return 'K';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        int iRowDelta = iDestRow - iSrcRow;
        int iColDelta = iDestCol - iSrcCol;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)) && (iRowDelta != 0 || iColDelta != 0))
        {
            return true;
        }

        if (GetColor() == 'W') {
            if (canCastleW && iDestRow == 0) {
                if (iDestCol == 2 && GameBoard[0][1] == 0 && GameBoard[0][2] == 0 && GameBoard[0][3] == 0) {
                    isCastle = true;
                    return true;
                } else if (iDestCol == 6 && GameBoard[0][5] == 0 && GameBoard[0][6] == 0) {
                    isCastle = true;
                    return true;
                }
            }
        } else {
            if (canCastleB && iDestRow == 7) {
                if (iDestCol == 2 && GameBoard[7][1] == 0 && GameBoard[7][2] == 0 && GameBoard[7][3] == 0) {
                    isCastle = true;
                    return true;
                } else if (iDestCol == 6 && GameBoard[7][5] == 0 && GameBoard[7][6] == 0) {
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
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                MainGameBoard[iRow][iCol] = 0;
            }
        }
        // Allocate and place black pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[6][iCol] = new PawnPiece('B');
        }
        MainGameBoard[7][0] = new RookPiece('B');
        MainGameBoard[7][1] = new KnightPiece('B');
        MainGameBoard[7][2] = new BishopPiece('B');
        MainGameBoard[7][3] = new QueenPiece('B');
        MainGameBoard[7][4] = new KingPiece('B');
        MainGameBoard[7][5] = new BishopPiece('B');
        MainGameBoard[7][6] = new KnightPiece('B');
        MainGameBoard[7][7] = new RookPiece('B');
        // Allocate and place white pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[1][iCol] = new PawnPiece('W');
        }
        MainGameBoard[0][0] = new RookPiece('W');
        MainGameBoard[0][1] = new KnightPiece('W');
        MainGameBoard[0][2] = new BishopPiece('W');
        MainGameBoard[0][3] = new QueenPiece('W');
        MainGameBoard[0][4] = new KingPiece('W');
        MainGameBoard[0][5] = new BishopPiece('W');
        MainGameBoard[0][6] = new KnightPiece('W');
        MainGameBoard[0][7] = new RookPiece('W');
    }
    ~CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                delete(MainGameBoard[iRow][iCol]);
                MainGameBoard[iRow][iCol] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        const int kiSquareWidth = 4;
        const int kiSquareHeight = 3;
        for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
            int iSquareRow = iRow/kiSquareHeight;
            // Print side border with numbering
            if (iRow % 3 == 1) {
                cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
            } else {
                cout << "---";
            }
            // Print the chess board
            for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                int iSquareCol = iCol/kiSquareWidth;
                if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && MainGameBoard[7-iSquareRow][iSquareCol] != 0) {
                    if ((iCol % 4) == 1) {
                        cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetColor();
                    } else {
                        cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetPiece();
                    }
                } else {
                    if ((iSquareRow + iSquareCol) % 2 == 1) {
                        cout << '*';
                    } else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
            if (iRow % 3 == 1) {
                cout << "---";
                for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                    int iSquareCol = iCol/kiSquareWidth;
                    if ((iCol % 4) == 1) {
                        cout << (iSquareCol + 1);
                    } else {
                        cout << '-';
                    }
                }
                cout << endl;
            } else {
                for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char PieceColor) {
        // Find the king
        int iKingRow;
        int iKingCol;
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        if (MainGameBoard[iRow][iCol]->GetPiece() == 'K') {
                            iKingRow = iRow;
                            iKingCol = iCol;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() != PieceColor) {
                        if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, MainGameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char PieceColor) {
        // Run through all pieces
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    // If it is a piece of the current player, see if it has a legal move
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
                                if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, MainGameBoard)) {
                                    // Make move and check whether king is in check
                                    GamePiece* qpTemp                   = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = MainGameBoard[iRow][iCol];
                                    MainGameBoard[iRow][iCol]           = 0;
                                    bool bCanMove = !IsInCheck(PieceColor);
                                    // Undo the move
                                    MainGameBoard[iRow][iCol]           = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = qpTemp;
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

class ChessBoard
{
public:
    ChessBoard() : mcPlayerTurn('W') {}
    ~ChessBoard() {}

    void Start() {
        using namespace std;
        cout<<endl<<endl<<"          Welcome to Chess Game Developed by Cppsecrets "<<endl<<endl<<endl;
        cout<<"                      Keys to sysmbols used "<<endl<<endl<<endl;
        cout<<" * = Black cell"<<endl;
        cout<<" Blank = white cell"<<endl;
        cout<<" WP = White pawn &  BP = Black pawn"<<endl;
        cout<<" WN = White Knight & BN = Black Knight"<<endl;
        cout<<" WB = White Bishop & BB = Black Bishop"<<endl;
        cout<<" WR = White Rook & BR = Black Rook"<<endl;
        cout<<" WQ = White Queen & BQ = Black Queen"<<endl;
        cout<<" WK = White King & BK =Black King"<<endl;
        cout<<"Rule for move is :"<<endl;
        cout<<"Move by selecting row & column to another valid location using row & column"<<endl<<endl<<endl;
        do {
            GetNextMove(mqGameBoard.MainGameBoard);
            countState[mqGameBoard]++;
            AlternateTurn();
        } while (!IsGameOver());
        mqGameBoard.Print();
    }

    void GetNextMove(GamePiece* GameBoard[8][8]) {
        using namespace std;
        isEnPassant = false; 
        isPromotion = false;
        isCastle = false;  
        bool isCapture = false;
        bool bValidMove     = false;

        do {
            // system ("clear");
            cout << endl << endl;
            
            mqGameBoard.Print();
            
            // Get input and convert to coordinates
            cout << mcPlayerTurn << "'s Move From: ";
            int iStartMove;
            cin >> iStartMove;
            int iStartRow = (iStartMove / 10) - 1;
            int iStartCol = (iStartMove % 10) - 1;

            cout << "To: ";
            int iEndMove;
            cin >> iEndMove;
            int iEndRow = (iEndMove / 10) - 1;
            int iEndCol = (iEndMove % 10) - 1;

            // Check that the indices are in range
            // and that the source and destination are different
            if ((iStartRow >= 0 && iStartRow <= 7) &&
                (iStartCol >= 0 && iStartCol <= 7) &&
                (iEndRow >= 0 && iEndRow <= 7) &&
                (iEndCol >= 0 && iEndCol <= 7)) {
                // Additional checks in here
                GamePiece* qpCurrPiece = GameBoard[iStartRow][iStartCol];
                // Check that the piece is the correct color
                if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, GameBoard)) {
                        //Check for Castling
                        if (!mqGameBoard.IsInCheck(mcPlayerTurn) && isCastle) {
                            GameBoard[iStartRow][(iStartCol + iEndCol)/2] = qpCurrPiece;
                            GameBoard[iStartRow][iStartCol] = 0;
                            bool check1 = mqGameBoard.IsInCheck(mcPlayerTurn);
                            GameBoard[iStartRow][iEndCol] = qpCurrPiece;
                            GameBoard[iStartRow][(iStartCol + iEndCol)/2] = 0;
                            bool check2 = mqGameBoard.IsInCheck(mcPlayerTurn);
                            
                            if (!check1 && !check2) {
                                int rookCol = (iStartCol > iEndCol) ? 0 : 7;
                                GamePiece *rook = GameBoard[iStartRow][rookCol];
                                GameBoard[iStartRow][rookCol] = 0;
                                GameBoard[iStartRow][(iStartCol + iEndCol)/2] = rook;
                                if (mcPlayerTurn == 'W') canCastleW = false;
                                else canCastleB = false;
                                bValidMove = true;
                                isFiftyMove++;
                            } else {
                                GameBoard[iStartRow][iStartCol] = qpCurrPiece;
                                GameBoard[iEndRow][iEndCol] = 0;
                            }

                        } else {
                            // Make the move
                            if (GameBoard[iEndRow][iEndCol] != 0) isCapture = true;
                            GamePiece* qpTemp                   = GameBoard[iEndRow][iEndCol];
                            GameBoard[iEndRow][iEndCol]     = GameBoard[iStartRow][iStartCol];
                            GameBoard[iStartRow][iStartCol] = 0;

                            // Make sure that the current player is not in check
                            if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
                                //Check for special move    
                                if (isEnPassant) {
                                    GameBoard[iStartRow][iEndCol] = 0;
                                }
                                if (isPromotion) {
                                    Promote(iEndRow, iEndCol, GameBoard);
                                }
                                if (qpCurrPiece->GetPiece() == 'R' || qpCurrPiece->GetPiece() == 'K') {
                                    if (mcPlayerTurn == 'W') canCastleW = false;
                                    else canCastleB = false;
                                }
                                if (isCapture) {isFiftyMove = 0; countState.clear();}
                                else isFiftyMove++;

                                //track previous move
                                curCol = iEndCol;
                                curRow = iEndRow;
                                prevRow = iStartRow;
                                delete(qpTemp);
                                bValidMove = true;
                            } else { // Undo the last move
                                GameBoard[iStartRow][iStartCol] = GameBoard[iEndRow][iEndCol];
                                GameBoard[iEndRow][iEndCol]     = qpTemp;
                            }
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "Invalid Move!" << endl;
            }
        } while (!bValidMove);
    }

    void Promote(int row, int col, GamePiece* GameBoard[8][8]) {
        using namespace std;
        int opt;
        do {
            cout << "Promote to? " << endl;
            cout << "1. Queen\n2.Rook\n3.Bishop\n4.Knight\n";
            cout << "choose from 1-4" << endl;
            
            cin >> opt;
        } while (opt <= 4 && opt >= 1);
        
        switch(opt) {
            case 1: {
                GameBoard[row][col] = new QueenPiece(mcPlayerTurn);
                break;
            }
            case 2: {
                GameBoard[row][col] = new RookPiece(mcPlayerTurn);
                break;
            }
            case 3: {
                GameBoard[row][col] = new BishopPiece(mcPlayerTurn);
                break;
            }
            case 4: {
                GameBoard[row][col] = new KnightPiece(mcPlayerTurn);
                break;
            }
            default: cout << "null" << endl;
        }
    }

    void AlternateTurn() {
        mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
    }

    bool IsThreeFoldRep() {
        for (auto& it : countState) {
            if (it.second >= 3) return true;
        }

        return false;
    }


    bool IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        if (!mqGameBoard.CanMove(mcPlayerTurn)) {
            if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
            } else {
                std::cout << "Stalemate!" << std::endl;
            }

            return true;
        }
        if (IsThreeFoldRep() || isFiftyMove >= 100){
            return true;
        }
        return false;
    }
private:
    CBoard mqGameBoard;
    char mcPlayerTurn;
};

int main() {
    ChessBoard qGame;
    qGame.Start();
    return 0;
}