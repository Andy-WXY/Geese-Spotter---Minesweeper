#include <iostream>
#include "geesespotter_lib.h"
#include "geesespotter.h"


char *createBoard(std::size_t xdim, std::size_t ydim){
  char *board = new char[xdim * ydim]{};
  for(int i = 0; i < xdim * ydim; ++ i){
    board[i] = 0;
  }

  return board;
} 

void cleanBoard(char *board){
    delete []board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){
  int temp = 0;
  for(int i = 0; i < ydim; ++i){
    for(int j = 0; j < xdim; ++j){
      if(board[temp] & markedBit()){
        std::cout<<"M";
      }
      else if(board[temp] & hiddenBit()){
        std::cout<<"*";
      }
      else{
        std::cout<<(board[temp] & valueMask());//<<" ";
      }
      ++ temp;
    }
    std::cout<<std::endl;
  }
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
  int temp = 0;
    for(int i = 0; i < ydim; ++i){
        for(int j = 0; j < xdim; ++j){
          if(board[temp] != 9){
            for(int m = i - 1; m <= i + 1; ++ m){
              for(int n = j - 1; n <= j + 1; ++ n){
                  if(m >= 0 && m < ydim && n >= 0 && n < xdim && (board[m * xdim + n] == 9)){
                    board[temp] += 1;
                  }
                }
              }
          }
          ++ temp;
        }
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
  for(int i = 0; i < (xdim * ydim); ++i){
    board[i] += hiddenBit();
  }
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
  if(board[yloc * xdim + xloc] & hiddenBit()){
    board[yloc * xdim + xloc] ^= markedBit();
    return 0;
  }
  return 2;
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
  if((board[yloc * xdim + xloc] & markedBit()) == markedBit()){
    return 1;
  }
  else if((board[yloc * xdim + xloc] & hiddenBit()) != hiddenBit()){
    return 2;
  }
  else if((board[yloc * xdim + xloc] & valueMask()) == 9){
    board[yloc * xdim + xloc] -= hiddenBit();
    return 9;
  }
  else if((board[yloc * xdim + xloc] & valueMask()) == 0){
      board[yloc * xdim + xloc] -= hiddenBit();
    for(int i = (int)yloc - 1; i <= (int)yloc + 1; ++ i){
      for(int j = (int)xloc - 1; j <= (int)xloc + 1; ++ j){
        if(i >= 0 && i < ydim && j >= 0 && j < xdim && (board[i * xdim + j] & hiddenBit()) && !(board[i * xdim + j] & markedBit()) && (i * xdim + j != yloc * xdim + xloc)){
            reveal(board, xdim, ydim, j, i);
        }
      }
    }
  }
  else{
    board[yloc * xdim + xloc]  -= hiddenBit();
  }
  return 0;
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
  bool all_revealed = true;
  for(int i = 0; i < (xdim * ydim); ++i){
    if(((board[i] & hiddenBit()) == hiddenBit()) && ((board[i] & valueMask()) != 9)){
      all_revealed = false;
    }
  }
  return all_revealed;
}