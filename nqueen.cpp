#include<string>
#include<vector>
#include<iostream>
#include<chrono>

bool Safe(std::vector<std::string> board, int r, int c) {
    if (r == 0) {
        return true;
    }

    int N = board.size();
    // vertical check
    for (int i = r-1; i >= 0; i--) {
        if (board[i][c] == 'Q') {
            return false;
        }
    }
    // diagonal check
    for (int i = 0; i <= r-1; i++) {
        for (int j = 0; j < N; j++) {
            if (abs(r - i) == abs(c - j) && board[i][j] == 'Q') {
                return false;
            }
        }
    }
    return true;
}

void NQueen(int N, int i, std::vector<std::string>& board, std::vector<std::vector<std::string> >& ans) {
    if (i == N) {
        ans.push_back(board);
        return;
    }                          
    for (int j = 0; j < N; j++) {
        if (Safe(board, i , j)) {
            board[i][j] = 'Q';
            NQueen(N , i+1, board, ans);
            board[i][j] = '.';
        }
    }
    return;
}

std::vector<std::vector<std::string> > SolveNQueens(int N) {
    std::vector<std::string> board;
    std::vector<std::vector<std::string> > ans;
    for (int i = 0; i < N; i++) {
        board.push_back(std::string(N, '.'));
    }
    NQueen(N, 0, board, ans);
    return ans;
}

signed main(int argc, char *argv[]){
    // input
    int N = atoi(argv[1]);

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();
    std::vector<std::vector<std::string> > ans = SolveNQueens(N); // solve
    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout << "Elapsed time: " << elapsed << "[µs]\n";

    // output
    if (ans.size() == 0) {
        std::cout << "No solution\n";
        return 0;
    }
    std::cout << "There are " << ans.size() << " solutions for N = " << N << "\n";
    for (int i = 0; i < N; i++) {
        std::cout << ans[0][i] << "\n";
    }

    return 0;
}