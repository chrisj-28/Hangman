/**
 * Simple hangman c++ game with error checking
 * to practice topics learned in school c++ course
 * created by chris jiang
 */


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int NUM_WORDS = 50;
const int NUM_LETTERS = 26;
const int NUM_LIFE = 10;

int getWantedWord(string &, char []);
string createCurrentWord(int);
void printGameBoard(string, int, bool [], char []);
bool guessLetter(string, string &, bool [], int &);
bool findLetter(string, string, string &);

int main() 
{
    bool playAgain = true;

    char acceptedInputs[NUM_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                                       'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                                       'o', 'p', 'q', 'r', 's', 't', 'u', 
                                       'v', 'w', 'x', 'y', 'z'};

    bool lettersUsed[NUM_LETTERS] = {false};

    int lives;
    int numChar = 0;
    string wantedWord;
    string currentWord;

    do {
        // init values
        lives = NUM_LIFE;
        for (int index = 0; index < NUM_LETTERS; index++)
            lettersUsed[index] = false;

        // get the word to guess
        numChar = getWantedWord(wantedWord, acceptedInputs);
        
        // create the hidden word
        currentWord = createCurrentWord(numChar);

        bool endGame = false;
        do
        {
            printGameBoard(currentWord, lives, lettersUsed, acceptedInputs);
            endGame = guessLetter(wantedWord, currentWord, lettersUsed, lives);

        } while (!endGame);

        if (currentWord == wantedWord)
        {
            system("CLS");
            cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Word to guess: " << currentWord << endl;
            cout << "Congratulations! You won!!!" << endl;
        }
        else
        {
            system("CLS");
            cout << "You run out of lives. You lost..." << endl;
            cout << "The word was: " << wantedWord << endl;

        }

        bool inputNeeded = true;
        while (inputNeeded)
        {
            cout << "\n\nDo you want to play again? (y/n) : ";
            string playAgainAnswer;
            getline(cin, playAgainAnswer);
            if (playAgainAnswer == "y")
            {
                playAgain = true;
                inputNeeded = false;
            }
            else if (playAgainAnswer == "n")
            {
                playAgain = false;
                inputNeeded = false;
            }
            else
                cout << "\nEnter y or n.";
        }
        

    } while (playAgain);

    system("CLS");
    cout << "See you next time!!!";
    
    return 0;
}

int getWantedWord(string & wantedWord, char acceptedInputs[NUM_LETTERS])
{
    bool wordIsGood = true;
    system("CLS");

    do
    {
        wordIsGood = true;
        cout << "Enter the word to win: ";
        getline (cin, wantedWord);

        bool charExists = false;
        for (int index = 0; index < wantedWord.length() && wordIsGood == true; index++)
        {
            charExists = false;
            for (int letter = 0; letter < NUM_LETTERS && charExists == false; letter++)
            {
                if (wantedWord[index] == acceptedInputs[letter])   
                    charExists = true;
            }
            if (charExists == false)
                wordIsGood = false;
        }

        if (wantedWord.length() == 0)
            cout << "You did not enter anything..." << endl;
        else if (wordIsGood == false)
        {
            cout << "Word should only contain lower-case letters from the english alphabet!" << endl;
            wantedWord.clear();
        }
        
    } while (!wordIsGood || wantedWord.length() == 0);

    system("CLS");

    return wantedWord.length();
    
}

string createCurrentWord(int numChar)
{
    string currentWord;
    for (int index = 0; index < numChar; index++)
    {
        currentWord += '-';
    }
    return currentWord;
}

void printGameBoard(string currentWord, int lives, bool lettersUsed[NUM_LETTERS], char acceptedInputs[NUM_LETTERS])
{
    system("CLS");
    cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Number of lives left: " << lives << endl;
    cout << "Letters used: ";
    for (int index = 0; index < NUM_LETTERS; index++)
        if (lettersUsed[index] == true)
            cout << acceptedInputs[index] << " ";
    cout << "\nWord to guess: " << currentWord << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

bool guessLetter(string wantedWord, string & currentWord, bool lettersUsed[NUM_LETTERS], int & lives)
{
    const int A_ASCII = 97;
    string inputLetter;
    bool endGame = false;

    // ask for letter and use ascii values
    bool accepted = false;
    do
    {
        cout << "Enter a letter: ";
        getline(cin, inputLetter);
        if (inputLetter.length() != 1)
            cout << "\nOnly one letter is allowed!" << endl;
        else if (int(inputLetter[0]) < A_ASCII || int(inputLetter[0]) > 122)
            cout << "Only lower-case english letters allowed!" << endl;
        else if (lettersUsed[int(inputLetter[0]) - A_ASCII] == true)
            cout << "You already used that letter!" << endl;
        else
            accepted = true;
        
    } while (!accepted);

    // update letters used by using ascii value
    lettersUsed[int(inputLetter[0]) - 97] = true;

    // find the letter in the word
    bool letterIsFound = findLetter(inputLetter, wantedWord, currentWord);

    if (!letterIsFound)
    {
        cout << "\n\n\n\nLETTER WAS NOT FOUND, YOU LOST ONE LIFE!" << endl;
        lives--;
    }
    else
        cout << "\n\n\n\nLETTER FOUND!" << endl;
    
    if (lives == 0 || wantedWord == currentWord)
        endGame = true;

    return endGame;
}

bool findLetter(string inputLetter, string wantedWord, string & currentWord)
{
    int wordLength = wantedWord.length();
    char letter = inputLetter[0];
    bool letterIsFound = false;

    for (int index = 0; index < wordLength; index++)
    {
        if (wantedWord[index] == letter)
        {
            currentWord[index] = letter;
            letterIsFound = true;
        }
    }

    return letterIsFound;
}
