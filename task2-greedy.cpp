#include <iostream>

using namespace std;
const int n = 8;
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

position* getPossibleMoves(position currentP,int* size) {
    position* possibleMoves=new position[8];
    int* current = currentP.get();
    if (current[1] + 2 < n and current[1] + 2 > -1) {
        if (current[0] + 1 < n) {
            possibleMoves[*size] = position(current[0] + 1, current[1] + 2);
            (*size)++;
        }
        if (current[0] - 1 > -1) {
            possibleMoves[*size] = position(current[0] - 1, current[1] + 2);
            (*size)++;
        }
    }
    
    if (current[0] + 2 < n and current[0] + 2 > -1) {
        if (current[1] + 1 < n) {
            possibleMoves[*size]= position(current[0] + 2, current[1] + 1);
            (*size)++;
        }
        if (current[1] - 1 > -1) {
            possibleMoves[*size] =  position(current[0] + 2, current[1] - 1);
            (*size)++;
        }
    }
                
    if (current[1] - 2 > -1 and current[1] - 2 < n) {
        if (current[0] + 1 < n) {
            possibleMoves[*size] =  position(current[0] + 1, current[1] - 2);
            (*size)++;
        }
        if (current[0] - 1 > -1) {
            possibleMoves[*size] =  position(current[0] - 1, current[1] - 2);
            (*size)++;
        }
    }
    
    if (current[0] - 2 > -1 and current[0] - 2 < n) {
        if (current[1] + 1 < n) {
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

int calculateAvailableNextMoves(position currentP, position nextP, int(*myBoard)[n][n]) {
    int moveCount = 0;
    int* current = currentP.get();
    int temp = (*myBoard)[current[0]][current[1]];
    (*myBoard)[current[0]][current[1]] = 1;
    int* nextMove = nextP.get();
    if (nextMove[1] + 2 < n) {
        if (nextMove[0] + 1 < n) {
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
    
    if (nextMove[0] + 2 < n) {
        if (nextMove[1] + 1 < n) {
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
        if (nextMove[0] + 1 < n) {
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
        if (nextMove[1] + 1 < n) {
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
    int k = 0;
    int count = 1;
    //initializing board
    int board[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    position visited[n*n];
    position current = position(0, 0);
    position lastPosition = position(2, 1);
    visited[k] = current;
    board[current.get()[0]][current.get()[1]]=count;

    while (count < n*n) {
        position prev = current;
        int possibleMovesSize = 0;
        position* possibleMoves = getPossibleMoves(current,&possibleMovesSize);
        if (count != (n*n-1)) {
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
        k++;
        count++;
        board[current.get()[0]][current.get()[1]] = count;
        visited[k] = current;
        if (current.get()[0] < 0 || current.get()[1] < 0) {
            cout << "Invalid Position: (" << current.get()[0] << "," << current.get()[1] << ")" << endl;
            break;
        }

    }


    cout << "Count=" << count << "    k=" << k << endl;
    cout << "Sequence" << endl;
    cout << "[";
    for (int i = 0; i < n*n; i++) {
        int* v = visited[i].get();
        cout << "(" << v[0] << "," << v[1] << ")" << ", ";
    }
    cout << "]" << endl;
    cout << "Board" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << "    ";
        }
        cout<<endl;
    }
}

