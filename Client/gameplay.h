#ifndef GAMEPLAY_H
#define GAMEPLAY_H

extern int prevRow;    //track previous move
extern int curRow;
extern int curCol; 
extern bool isEnPassant; // special move
extern bool isPromotion; //special move
extern bool isCastle; //special move
extern bool canCastleB;
extern bool canCastleW;
extern int isFiftyMove;

#endif // GAMEPLAY_H