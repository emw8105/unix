#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

//returns # of wrong guesses
int playGame(string word) {
    cout << word << endl;

    string display = word;
    int n = word.length();
    for(int i=0; i<n; i++)
        display[i] = '*';

/* Pseudocode:
    while we have unexposed characters(*) in display
        ask the user for the next guess
        3 cases:
        1. valid guess - input is in word & unexposed
        2. invalid - already exposed
        3. invalid - not in word - increment wrong guess count
    return wrong guess count
*/
    int unexposed = n;
    char guess = ' ';
    int wrongGuesses = 0;

    while (unexposed > 0) {
        cout << "Enter a letter in word " << display << " > ";
        cin >> guess;

        bool found = false;
        for(int i=0; i<n; i++)
            if (guess == word[i]) {
                found = true;
                if (guess == display[i]) {
                    cout << guess << " is already in the word.\n";
                    break;
                } else {
                    //good guess!
                    display[i] = guess;
                    unexposed--;
                }
            }

        if (!found) {
            cout << guess << " is not in the word.\n";
            wrongGuesses++;
        }

    }
    cout << "The word is " << word << ".\n";
    cout << "You missed " << wrongGuesses << " times.\n";
}

int main() {
    string *words, temp;

    ifstream finput("dictionary.txt");
    //read # of words
    int numWords = 0;
    while (finput >> temp)
        numWords++;
    cout << numWords << " read.\n";

    //allocate array
    words = new string [numWords];

    //go back initial position in array
    finput.clear();
    finput.seekg(0);
    //read the words again to the array
    for(int i=0 ; i<numWords; i++)
        finput >> words[i];

    //select a random word
    srand(time(NULL));
    //play the game!
    while (true)
        playGame(words[abs(rand()*rand())%numWords]);
}
