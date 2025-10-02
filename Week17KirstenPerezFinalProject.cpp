#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>
#include <random>
#include <vector>

using namespace std;

// ===================== Utility Functions =====================

// Shuffle an array/vector
void shuffleArray(vector<string> &arr) {
    random_device rd;
    mt19937 generator(rd());
    for (int i = arr.size() - 1; i > 0; --i) {
        uniform_int_distribution<int> distribution(0, i);
        int j = distribution(generator);
        swap(arr[i], arr[j]);
    }
}

// Print grid
void printGrid(const vector<string> &grid, int rows, int cols) {
    const int cellWidth = 15;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << left << setw(cellWidth) << grid[i * cols + j];
        }
        cout << endl;
    }
}

// Load words from a file into a vector
vector<string> loadWords(const string &filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening " << filename << endl;
        return {};
    }

    vector<string> words;
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    return words;
}

// ===================== Game Setup =====================

// Get theme choice
vector<string> chooseTheme() {
    cout << "Select Theme" << endl;
    cout << "1. Colors " << endl;
    cout << "2. Anime Characters " << endl;
    cout << "3. Animals " << endl;
    cout << "Enter (1, 2, 3): ";
    int theme;
    cin >> theme;

    if (theme == 1) return loadWords("Week10KirstenPerez50WordsColors1.txt");
    if (theme == 2) return loadWords("Week10KirstenPerez50WordsAnimeCharacters2.txt");
    if (theme == 3) return loadWords("Week10KirstenPerez50WordsAnimals3.txt");

    cerr << "Invalid theme selection." << endl;
    return {};
}

// Get grid size
pair<int, int> chooseGridSize() {
    cout << "Select Size of Play" << endl;
    cout << "E. 4x4 grid (Small) " << endl;
    cout << "M. 6x6 grid (Medium) " << endl;
    cout << "D. 8x8 grid (Large) " << endl;
    cout << "Enter (E, M, D): ";
    char size;
    cin >> size;

    if (size == 'E') return {4, 4};
    if (size == 'M') return {6, 6};
    if (size == 'D') return {8, 8};

    cerr << "Invalid size selection." << endl;
    return {0, 0};
}

// Get display time
int chooseTime() {
    cout << "Select Time word pair remain on screen" << endl;
    cout << "F. 2 seconds (Fast) " << endl;
    cout << "M. 4 seconds (Moderate) " << endl;
    cout << "S. 6 seconds (Slow) " << endl;
    cout << "Enter (F, M, S): ";
    char timeChoice;
    cin >> timeChoice;

    if (timeChoice == 'F') return 2;
    if (timeChoice == 'M') return 4;
    if (timeChoice == 'S') return 6;

    cerr << "Invalid time selection." << endl;
    return 0;
}

// ===================== Gameplay =====================

bool playGame(const vector<string> &themeWords, int rows, int cols, int displayTime) {
    int gridSize = rows * cols;

    // Create grid with paired words
    vector<string> grid(gridSize);
    for (int i = 0; i < gridSize / 2; ++i) {
        grid[i] = themeWords[i % themeWords.size()];
        grid[i + gridSize / 2] = themeWords[i % themeWords.size()];
    }

    // Shuffle grid
    shuffleArray(grid);

    // Show grid
    printGrid(grid, rows, cols);

    // Countdown
    for (int countdown = displayTime; countdown >= 1; --countdown) {
        cout << "\rTime left: " << countdown << " seconds" << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Clear screen
    cout << "\033[2J\033[1;1H";
    cout << "Time's up!" << endl;

    // Hidden grid
    vector<string> hiddenGrid(gridSize, "*");
    printGrid(hiddenGrid, rows, cols);

    // Gameplay loop
    int lives = 3;
    while (true) {
        cout << "You have " << lives << " lives left." << endl;

        // First pick
        int row1, col1;
        cout << "Enter row and col for first pick (e.g., 1 2): ";
        cin >> row1 >> col1;
        if (row1 < 1 || row1 > rows || col1 < 1 || col1 > cols) {
            cout << "Invalid input." << endl;
            continue;
        }
        int index1 = (row1 - 1) * cols + (col1 - 1);

        // Second pick
        int row2, col2;
        cout << "Enter row and col for second pick: ";
        cin >> row2 >> col2;
        if (row2 < 1 || row2 > rows || col2 < 1 || col2 > cols) {
            cout << "Invalid input." << endl;
            continue;
        }
        int index2 = (row2 - 1) * cols + (col2 - 1);

        // Match check
        if (grid[index1] == grid[index2]) {
            cout << "Match found!" << endl;
            hiddenGrid[index1] = grid[index1];
            hiddenGrid[index2] = grid[index2];
        } else {
            cout << "No match!" << endl;
            lives--;
        }

        printGrid(hiddenGrid, rows, cols);

        // Win condition
        bool gameWon = true;
        for (const auto &cell : hiddenGrid) {
            if (cell == "*") { gameWon = false; break; }
        }
        if (gameWon) {
            cout << "🎉 Congratulations! You've won the game!" << endl;
            return true;
        }

        // Lose condition
        if (lives == 0) {
            cout << "💀 Game Over! You ran out of lives." << endl;
            cout << "Here was the grid:" << endl;
            printGrid(grid, rows, cols);
            return false;
        }
    }
}

// ===================== Main =====================

int main() {
    cout << "Kirsten Perez - Memory Game" << endl;

    bool playAgain = true;
    while (playAgain) {
        // Setup
        vector<string> themeWords = chooseTheme();
        if (themeWords.empty()) break;

        auto [rows, cols] = chooseGridSize();
        if (rows == 0) break;

        int displayTime = chooseTime();
        if (displayTime == 0) break;

        shuffleArray(themeWords);

        // Play one round
        playGame(themeWords, rows, cols, displayTime);

        // Replay option
        cout << "Would you like to play again? (Y/N): ";
        char replayChoice;
        cin >> replayChoice;
        playAgain = (replayChoice == 'Y' || replayChoice == 'y');
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}