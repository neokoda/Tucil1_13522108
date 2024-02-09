// Nama      : Muhammad Neo Cicero Koda
// Kelas/NIM : K02/13522108

// Header files
#include <iostream>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

// Namespace
namespace fs = std::filesystem;

// Custom classes
class Sequence {
    public:
        std::vector<std::string> seqArray;
        int reward;

    Sequence(const std::vector<std::string>& seqArr, int rwd) : seqArray(seqArr), reward(rwd) {}
};

class Coordinate {
    public: 
        int col;
        int row;
        std::string token;
        Coordinate(int c, int r, std::string t) : col(c), row(r), token(t) {}
};

// Variables used
int numTokens;
std::vector<std::string> tokens;

int bufferSize;
std::vector<Coordinate> maxBuffer;
int maxReward;

int matWidth;
int matHeight;
std::vector<std::vector<std::string>> matrix;

int numSeq;
std::vector<Sequence> sequences;
int maxSeqSize;

int timeTaken; // save time taken to get solution

// Helper functions
Sequence generateSequence() {
    int size = rand() % (maxSeqSize - 1) + 2;
    std::vector<std::string> seqArray;
    for (int i = 0; i < size; i++) {
        seqArray.push_back(tokens[rand() % tokens.size()]);
    }
    int reward = rand() % (41) + 10;
    
    Sequence sequence(seqArray, reward);

    return sequence;
};

bool coordinateTravelled(const std::vector<Coordinate>& vec, int targetCol, int targetRow) {
    for (const Coordinate& coord : vec) {
        if (coord.col == targetCol && coord.row == targetRow) {
            return true;
        }
    }
    return false;
}

bool hasSequence(Sequence seq, std::vector<Coordinate> buffer) {
    if (seq.seqArray.size() > buffer.size()) {
        return false;
    }
    auto itSeq = seq.seqArray.begin();
    for (Coordinate coord : buffer) {
        if (coord.token == *itSeq) {
            itSeq++;
            if (itSeq == seq.seqArray.end()) {
                return true;
            }
        } else {
            itSeq = seq.seqArray.begin();
        }
    }
    return false;
}

// Brute force algorithm (recursive)
void findPossibleMoves(Coordinate currentCoord, std::vector<Coordinate> currentBuffer, bool vertical) {
    if (currentCoord.col == 0 && currentCoord.row == 0) { // first move
        for (int i = 0; i < matrix[0].size(); i++) {
            Coordinate coord(i + 1, 1, matrix[0][i]);
            currentBuffer.push_back(coord);
            findPossibleMoves(coord, currentBuffer, true);
            currentBuffer.pop_back();
        }
    } else if (currentBuffer.size() == bufferSize) { // count reward
        int bufferReward = 0;
        for (Sequence seq : sequences) {
            if (hasSequence(seq, currentBuffer)) {
                bufferReward += seq.reward;
            }
        }
        if (bufferReward > maxReward) {
            maxBuffer = currentBuffer;
            maxReward = bufferReward;
        }
    } else {
        if (vertical) { // vertical move
            for (int i = 0; i < matrix.size(); i++) {
                if (!coordinateTravelled(currentBuffer, currentCoord.col, i + 1)) {
                    Coordinate coord(currentCoord.col, i + 1, matrix[i][currentCoord.col - 1]);
                    currentBuffer.push_back(coord);
                    findPossibleMoves(coord, currentBuffer, false);
                    currentBuffer.pop_back();
                }
            }
        } else { // horizontal move
            for (int i = 0; i < matrix[0].size(); i++) {
                if (!coordinateTravelled(currentBuffer, i + 1, currentCoord.row)) {
                    Coordinate coord(i + 1, currentCoord.row, matrix[currentCoord.row - 1][i]);
                    currentBuffer.push_back(coord);
                    findPossibleMoves(coord, currentBuffer, true);
                    currentBuffer.pop_back();
                }
            }
        }
    }
}

// I/O Functions
void readFromFile() {
    std::string path;
    std::cout << "Mohon masukkan path file: ";
    std::cin >> path;

    while (!(fs::exists(path) && (path.length() >= 4) && (path.substr(path.length() - 4) == ".txt"))) {
        std::cout << "Path yang diberikan tidak ditemukan atau bukan file txt. Mohon masukkan ulang path: ";
        std::cin >> path;
    }

    std::ifstream inputFile(path);

    inputFile >> bufferSize;

    inputFile >> matWidth >> matHeight;
    matrix.resize(matHeight, std::vector<std::string>(matWidth));
    for (int i = 0; i < matHeight; i++) {
        for (int j = 0; j < matWidth; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile >> numSeq;
    inputFile.ignore(); 
    std::string seqLine;
    int reward;
    for (int i = 0; i < numSeq; i++) {
        std::getline(inputFile, seqLine);
        std::string token;
        std::vector<std::string> seqArray;
        std::istringstream iss(seqLine);
        while (iss >> token) {
            seqArray.push_back(token);
        }

        inputFile >> reward;
        inputFile.ignore(); 
        Sequence sequence(seqArray, reward);
        sequences.push_back(sequence);
    }
}

void readFromInput() {
    std::cout << std::endl << "Masukkan informasi tentang matriks dan sekuens yang digunakan: " << std::endl;
    std::cin >> numTokens;
    tokens.resize(numTokens);
    for (int i = 0; i < numTokens; i++) {
        std::cin >> tokens[i];
    }

    std::cin >> bufferSize;

    std::cin >> matWidth >> matHeight;
    matrix.resize(matHeight, std::vector<std::string>(matWidth));
    for (int i = 0; i < matHeight; i++) {
        for (int j = 0; j < matWidth; j++) {
            matrix[i][j] = tokens[rand() % numTokens];
        }
    }
    
    std::cin >> numSeq;
    std::cin >> maxSeqSize;
    for (int i = 0; i < numSeq; i++) {
        sequences.push_back(generateSequence());
    }
};

void displayInputInfo() {
    std::cout << std::endl << "Matriks yang digunakan: " << std::endl;
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Sekuens yang digunakan: " << std::endl;
    for (const auto& seq : sequences) {
        for (const auto& token : seq.seqArray) {
            std::cout << token << ' ';
        }
        std::cout << std::endl << "Reward: " << seq.reward << std::endl;
    }
}

void displayOutput() {
    std::cout << std::endl;

    if (maxReward != 0) {
        std::cout << maxReward << std::endl;

        for (const auto& coord : maxBuffer) {
            std::cout << coord.token << ' ';
        }
        std::cout << std::endl;

        for (const auto& coord : maxBuffer) {
            std::cout << coord.col << ' ' << coord.row << std::endl;
        }
    } else {
        std::cout << maxReward << std::endl;
    }

    std::cout << std::endl;
}

void saveSolution() {
    std::string path;
    std::cout << "Mohon masukkan path file: ";
    std::cin >> path;

    while (!((path.length() >= 4) && (path.substr(path.length() - 4) == ".txt"))) {
        std::cout << "Path yang diberikan bukan file txt. Mohon masukkan ulang path: ";
        std::cin >> path;
    }

    std::ofstream outputFile(path);

    if (maxReward != 0) {
        outputFile << maxReward << std::endl;

        for (const auto& coord : maxBuffer) {
            outputFile << coord.token << ' ';
        }
        outputFile << std::endl;

        for (const auto& coord : maxBuffer) {
            outputFile << coord.col << ' ' << coord.row << std::endl;
        }
    } else {
        outputFile << maxReward << std::endl;
    }

    outputFile << std::endl << timeTaken << " ms";
    outputFile.close();

    std::cout << std::endl << "Solusi berhasil disimpan!" << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // set seed

    std::cout << R"(
    _________        ___.               __________              __     _________________________________    _________      .__                     
    \_   ___ \___.__.\_ |__   __________\______   \__ __  ____ |  | __ \_____  \   _  \______  \______  \  /   _____/ ____ |  |___  __ ___________ 
    /    \  \<   |  | | __ \_/ __ \_  __ \     ___/  |  \/    \|  |/ /  /  ____/  /_\  \  /    /   /    /  \_____  \ /  _ \|  |\  \/ // __ \_  __ \
    \     \___\___  | | \_\ \  ___/|  | \/    |   |  |  /   |  \    <  /       \  \_/   \/    /   /    /   /        (  <_> )  |_\   /\  ___/|  | \/
    \______  /  ____| |___/\___  >_|  |__|    |___/|___|  /_|_  \ \_______ \_____  /____/   /____/   /_______  /\___/|____/\_/  \___  >__|  |  | 
    )" << std::endl << std::endl;
    std::cout << "Welcome to Cyberpunk 2077 Breach Protocol Solver!" << std::endl << std::endl;

    // get input
    int opt;
    std::cout << "1. File" << std::endl;
    std::cout << "2. Masukan keyboard" << std::endl;
    std::cout << "Pilih metode inputmu: ";
    std::cin >> opt;

    while (opt != 1 && opt != 2) {
        std::cout << std::endl <<  "Mohon pilih antara 1 atau 2." << std::endl;
        std::cout << "1. File" << std::endl;
        std::cout << "2. Masukan keyboard" << std::endl;
        std::cout << "Pilih metode inputmu: ";
        std::cin >> opt;
    }

    if (opt == 1) {
        readFromFile();
    } else {  
        readFromInput();
        displayInputInfo();
    }

    // process input while calculating time taken
    auto startTime = std::chrono::high_resolution_clock::now();

    Coordinate start(0, 0, ""); // initialize starting coordinate
    std::vector<Coordinate> initBuffer;
    findPossibleMoves(start, initBuffer, false);
    displayOutput();

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    timeTaken = duration.count();
    std::cout << duration.count() << " ms" << std::endl;


    // save solution
    char opt2;
    std::cout << std::endl << "Apakah ingin menyimpan solusi? (y/n) ";
    std::cin >> opt2;

    while (opt2 != 'y' && opt2 != 'n' && opt2 != 'Y' && opt2 != 'N') {
        std::cout << std::endl <<  "Mohon ketik y atau n.";
        std::cout << std::endl << "Apakah ingin menyimpan solusi? (y/n) ";
        std::cin >> opt2;
    }

    if (opt2 == 'y' || opt2 == 'Y') {
        saveSolution();
    }

    std::cout << std::endl << "Terima kasih!" << std::endl << std::endl;

    return 0;
}