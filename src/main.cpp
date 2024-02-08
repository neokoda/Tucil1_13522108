#include <iostream>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

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
        Coordinate(int c, int r) : col(c), row(r) {}
};

int numTokens;
std::vector<std::string> tokens;

int bufferSize;
std::vector<std::vector<Coordinate>> buffers;

int matWidth;
int matHeight;
std::vector<std::vector<std::string>> matrix;

int numSeq;
std::vector<Sequence> sequences;
int maxSeqSize;

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

void readFromFile() {
    std::string path;

    std::cout << "Please enter file path: ";
    std::cin >> path;

    while (!fs::exists(path)) {
        std::cout << "The path you provided doesn't exist. Please re-enter a new path: " << std::endl;
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
        std::cout << seqLine << std::endl;
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

void displayInfo() {
    std::cout << "numTokens: " << numTokens << std::endl;
    std::cout << "tokens: ";
    for (const auto& token : tokens) {
        std::cout << token << ' ';
    }
    std::cout << std::endl;

    std::cout << "bufferSize: " << bufferSize << std::endl;
    std::cout << "buffers: " << std::endl;
    for (const auto& buffer : buffers) {
        for (const auto& coord : buffer) {
            std::cout << "("<< coord.col << "," << coord.row << ")";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "matrix_size: " << matrix[0].size() << " " << matrix.size() << std::endl;
    std::cout << "matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "numSeq: " << numSeq << std::endl;
    std::cout << "sequences:" << std::endl;
    for (const auto& seq : sequences) {
        for (const auto& token : seq.seqArray) {
            std::cout << token << ' ';
        }
        std::cout << "reward: " << seq.reward << std::endl;
    }
    std::cout << "maxSeqSize: " << maxSeqSize << std::endl;
}

bool coordinateTravelled(const std::vector<Coordinate>& vec, int targetCol, int targetRow) {
    for (const Coordinate& coord : vec) {
        if (coord.col == targetCol && coord.row == targetRow) {
            return true;
        }
    }
    return false;
}

// find all moves from current coordinate and add to buffers if move is the size of bufferSize
void findPossibleMoves(Coordinate currentCoord, std::vector<Coordinate> currentBuffer, bool vertical) {
    if (currentCoord.col == 0 && currentCoord.row == 0) {
        for (int i = 0; i < matrix[0].size(); i++) {
            Coordinate coord(i + 1, 1);
            currentBuffer.push_back(coord);
            findPossibleMoves(coord, currentBuffer, true);
            currentBuffer.pop_back();
        }
    } else if (currentBuffer.size() == bufferSize) {
        buffers.push_back(currentBuffer);
    } else {
        if (vertical) {
            for (int i = 0; i < matrix.size(); i++) {
                if (!coordinateTravelled(currentBuffer, currentCoord.col, i + 1)) {
                    Coordinate coord(currentCoord.col, i + 1);
                    currentBuffer.push_back(coord);
                    findPossibleMoves(coord, currentBuffer, false);
                    currentBuffer.pop_back();
                }
            }
        } else {
            for (int i = 0; i < matrix[0].size(); i++) {
                if (!coordinateTravelled(currentBuffer, i + 1, currentCoord.row)) {
                    Coordinate coord(i + 1, currentCoord.row);
                    currentBuffer.push_back(coord);
                    findPossibleMoves(coord, currentBuffer, true);
                    currentBuffer.pop_back();
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int opt;

    std::cout << "Welcome to Cyberpunk 2077 Breach Protocol Solver!" << std::endl << std::endl;

    std::cout << "Choose your input method: " << std::endl;
    std::cout << "1. From file" << std::endl;
    std::cout << "2. From keyboard input" << std::endl;
    std::cin >> opt;

    while (opt != 1 && opt != 2) {
        std::cout << std::endl <<  "Please input either 1 or 2." << std::endl;
        std::cout << "Choose your input method: " << std::endl;
        std::cout << "1. From file" << std::endl;
        std::cout << "2. From keyboard input" << std::endl;
        std::cin >> opt;
    }

    if (opt == 1) {
        readFromFile();
    } else {  
        readFromInput();
    }

    Coordinate start(0, 0);
    std::vector<Coordinate> initBuffer;
    findPossibleMoves(start, initBuffer, false);

    displayInfo();

    return 0;
}