#include <vector>
#include <stack>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include<chrono>

void EqualOne(std::vector<int> literals, std::vector<std::vector<int> >& cnf) {
    int N = literals.size();
    cnf.push_back(literals);
    std::vector<int> clause; 
    for (int j = 0; j< N-1; j++){
        for (int k = j+1; k < N; k++){
            clause.push_back(-literals[j]);
            clause.push_back(-literals[k]);
            cnf.push_back(clause);
            clause.clear();
        }
    }
}

void LessEqualOne(std::vector<int> literals, std::vector<std::vector<int> >& cnf) {
    int N = literals.size();
    std::vector<int> clause; 
    for (int j = 0; j < N-1; j++){
        for (int k = j+1; k < N; k++){
            clause.push_back(-literals[j]);
            clause.push_back(-literals[k]);
            cnf.push_back(clause);
            clause.clear();
        }
    }
}

int main(int argc, char *argv[]) {
    // input
    int N = atoi(argv[1]);
    int numVars = N * N;

    // variable names 1 ~ N^2
    int **VarName = new int * [N];
    int k = 1;
    for (int i = 0; i < N; i++){
        VarName[i] = new int [N];
        for (int j = 0; j < N; j++){
            VarName[i][j] = k++;
        }
    }

    std::vector<std::vector<int> > cnf;  
    std::vector<int> vars;

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();
    
    // vertical check
    // per row
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            vars.push_back(VarName[i][j]);
        }
        EqualOne(vars, cnf);
        vars.clear();
    }
    // per column
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            vars.push_back(VarName[j][i]);
        }
        EqualOne(vars, cnf);
        vars.clear();
    }

    // diagonal check
    // upper triangle
    for (int i = 0; i < N-1; i++){
        for (int j = 0; j < N-i; j++){
            vars.push_back(VarName[j][i+j]);
        }
        LessEqualOne(vars, cnf);
        vars.clear();
    }
    // lower triangle
    for (int i = 1; i < N-1; i++){
        for (int j = 0; j < N-i; j++){
            vars.push_back(VarName[j+i][j]);
        }
        LessEqualOne(vars, cnf);
        vars.clear();
    }
    // upper left triangle
    for (int i = 0; i < N-1; i++){
        for (int j = 0; j < N-i; j++){
            vars.push_back(VarName[j][N-1-(i+j)]);
        }
        LessEqualOne(vars, cnf);
        vars.clear();
    }
    // lower right triangle
    for (int i = 1; i < N-1; i++){
        for (int j = 0; j < N-i; j++){
            vars.push_back(VarName[j+i][N-1-j]);
        }
        LessEqualOne(vars, cnf);
        vars.clear();
    }

    end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout << "Elapsed time: " << elapsed << "[µs]\n";

    // output
    std::ofstream fout;
    std::string fname;
    if (argc <= 2) {
        fname = "exaple.cnf";
    } else {
        fname = argv[2];
    }
    fout.open(fname, std::ofstream::out);

    fout << "p cnf " << numVars << " " << cnf.size() << std::endl;

    int nClause = cnf.size();
    for (int i = 0; i < nClause; i++){
        int nElemClause = cnf[i].size();
        for (int j = 0; j < nElemClause; j++){
            fout << cnf[i][j] << " ";
        }
        fout << "0" << std::endl;
    }
    fout << std::endl;
    
    return 0;
}