#include <iostream>

using namespace std;

class position {
public:
    int* get() {
        int* arr = new int[2];
        arr[0] = row;
        arr[1] = column;
        return arr;
    }
    position() {
        row = 0;
        column = 0;
    }
    position(int r, int col) {
        row = r;
        column = col;
    }
    bool equals(position p2) {
        int* myp2 = p2.get();
        if (this->row == myp2[0] && this->column == myp2[1]) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    int row;
    int column;
};

// return the indices of the possible moves from current position 
// (only check for elgibility of index to be within boundaries of the 2d array, doesnot check wether the square is visited or not)
position* getPossibleMoves(position currentP,int* size) {
    position* possibleMoves=new position[8];
    int* current = currentP.get();
    if (current[1] + 2 < 8 and current[1] + 2 > -1) {
        if (current[0] + 1 < 8) {
            possibleMoves[*size] = position(current[0] + 1, current[1] + 2);
            (*size)++;
        }
        if (current[0] - 1 > -1) {
            possibleMoves[*size] = position(current[0] - 1, current[1] + 2);
            (*size)++;
        }
    }
    
    if (current[0] + 2 < 8 and current[0] + 2 > -1) {
        if (current[1] + 1 < 8) {
            possibleMoves[*size]= position(current[0] + 2, current[1] + 1);
            (*size)++;
        }
        if (current[1] - 1 > -1) {
            possibleMoves[*size] =  position(current[0] + 2, current[1] - 1);
            (*size)++;
        }
    }
                
    if (current[1] - 2 > -1 and current[1] - 2 < 8) {
        if (current[0] + 1 < 8) {
            possibleMoves[*size] =  position(current[0] + 1, current[1] - 2);
            (*size)++;
        }
        if (current[0] - 1 > -1) {
            possibleMoves[*size] =  position(current[0] - 1, current[1] - 2);
            (*size)++;
        }
    }
    
    if (current[0] - 2 > -1 and current[0] - 2 < 8) {
        if (current[1] + 1 < 8) {
            possibleMoves[*size] =  position(current[0] - 2, current[1] + 1);
            (*size)++;
        }
        if (current[1] - 1 > -1) {
            possibleMoves[*size] =  position(current[0] - 2, current[1] - 1);
            (*size)++;
        }
    }
    return possibleMoves;
}

// this function calculates the available moves for each next move from current position so that 
// we select the next position with least available moves considering the current square as visited.
int calculateAvailableNextMoves(position currentP, position nextP, int(*myBoard)[8][8]) {
    int moveCount = 0;
    int* current = currentP.get();
    int temp = (*myBoard)[current[0]][current[1]];
    (*myBoard)[current[0]][current[1]] = 1;
    int* nextMove = nextP.get();
    if (nextMove[1] + 2 < 8) {
        if (nextMove[0] + 1 < 8) {
            if ((*myBoard)[nextMove[0] + 1][nextMove[1] + 2] == 0) {
                moveCount += 1;
            }
        }
        if (nextMove[0] - 1 > -1) {
            if ((*myBoard)[nextMove[0] - 1][nextMove[1] + 2] == 0) {
                moveCount += 1;
            }
        }
    }
    
    if (nextMove[0] + 2 < 8) {
        if (nextMove[1] + 1 < 8) {
            if ((*myBoard)[nextMove[0] + 2][nextMove[1] + 1] == 0) {
                moveCount += 1;
            }
        }
        if (nextMove[1] - 1 > -1) {
            if ((*myBoard)[nextMove[0] + 2][nextMove[1] - 1] == 0) {
                moveCount += 1;
            }
        }         
    }

    if (nextMove[1] - 2 > -1) {
        if (nextMove[0] + 1 < 8) {
            if ((*myBoard)[nextMove[0] + 1][nextMove[1] - 2] == 0) {
                moveCount += 1;
            }
        }
        if (nextMove[0] - 1 > -1) {
            if ((*myBoard)[nextMove[0] - 1][nextMove[1] - 2] == 0) {
                moveCount += 1;
            }
        }
    }

    if (nextMove[0] - 2 > -1) {
        if (nextMove[1] + 1 < 8) {
            if ((*myBoard)[nextMove[0] - 2][nextMove[1] + 1] == 0) {
                moveCount += 1;
            }
        }
        if (nextMove[1] - 1 > -1) {
            if ((*myBoard)[nextMove[0] - 2][nextMove[1] - 1] == 0) {
                moveCount += 1;
            }
        } 
    }
    ((*myBoard))[current[0]][current[1]] = temp;

    return moveCount;
}




int main() {
    int n = 0;
    int count = 1;
    //initializing board
    int board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    position visited[64];
    position current = position(0, 0);
    position lastPosition = position(2, 1);
    visited[n] = current;
    board[current.get()[0]][current.get()[1]]=count;

    while (count < 64) {
        position prev = current;
        int possibleMovesSize = 0;
        position* possibleMoves = getPossibleMoves(current,&possibleMovesSize);
        if (count != 63) {
            for (int i = 0; i < possibleMovesSize; i++) {
                if (possibleMoves[i].equals(lastPosition)) {
                    //remove last position from possible moves through shifting
                    for (int j = i; j < possibleMovesSize-1; j++) {
                        possibleMoves[j] = possibleMoves[j + 1];
                    }
                    possibleMovesSize -= 1;
                }
            }
        }
        int movesCount[8] = {0};
        for (int i = 0; i < possibleMovesSize; i++) {
            int* move = possibleMoves[i].get();
            if (board[move[0]][move[1]] == 0) {
                movesCount[i] = calculateAvailableNextMoves(current, possibleMoves[i], &board);
            }
            else {
                movesCount[i] = 1000;
            }
        }
        int select = 0;
        int min = movesCount[0];
        for (int i = 1; i < possibleMovesSize; i++) {
            if (movesCount[i] < min) {
                select = i;
                min = movesCount[i];
            }
        }
        current = possibleMoves[select];

        if (prev.equals(current)) {
            cout << "Stop Position: (" << current.get()[0] << "," << current.get()[1] << ")" << endl;
            break;
        }
        n++;
        count++;
        board[current.get()[0]][current.get()[1]] = count;
        visited[n] = current;
        if (current.get()[0] < 0 || current.get()[1] < 0) {
            cout << "Invalid Position: (" << current.get()[0] << "," << current.get()[1] << ")" << endl;
            break;
        }

    }


    cout << "Count=" << count << "    n=" << n << endl;
    cout << "[";
    for (int i = 0; i < 64; i++) {
        int* v = visited[i].get();
        cout << "(" << v[0] << "," << v[1] << ")" << ", ";
    }
    cout << "]" << endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << "    ";
        }
        cout<<endl;
    }
}

