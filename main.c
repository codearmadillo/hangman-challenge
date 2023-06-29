#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POSSIBLE_FALSE_GUESSES 5

#define STATUS_INGAME 0
#define STATUS_LOST 1
#define STATUS_WON 2

char* createWord();
bool* createAnswerBuffer(char* word);
int getWordLength(char* word);
void printGameState(int state, char* word, bool* answers, int wordLength, int wrongGuesses);
int getGameState(char* word, bool* answers, int wordLength, int guesses);

int main(void)
{
    char* word = createWord();
    int wordLength = getWordLength(word);
    bool* answers = createAnswerBuffer(word);

    int wrongGuesses = 0;

    while (true) {
        int status = getGameState(word, answers, wordLength, wrongGuesses);
        
        // Print status
        printGameState(status, word, answers, wordLength, wrongGuesses);
        
        // Break out if game is over
        if (status != STATUS_INGAME) {
            break;
        }
    
        // Get user input
        char userInput;
        printf("\nGuess a letter: ");
        scanf(" %c", &userInput);
        
        // Check if user input is correct
        bool answerFound = false;
        for (int i = 0; i < wordLength; i++) {
            if (userInput == word[i]) {
                answers[i] = true;
                answerFound = true;
            }
        }
        
        // If no answer was found - print message that character was not found
        if (answerFound) {
            printf("%c is correct!", userInput);
        } else {
            printf("O-oh - %c is not correct. You just lost one life!", userInput);
            wrongGuesses++;
        }
    }
    
    free(answers);
    free(word);

    return 0;
}

int getGameState(char* word, bool* answers, int wordLength, int guesses) {
    // player is over limit
    if (guesses > POSSIBLE_FALSE_GUESSES) {
        return STATUS_LOST;
    }
    // player won the game or is still playing
    bool allLettersResolved = true;
    for (int i = 0; i < wordLength; i++) {
        if (!answers[i]) {
            allLettersResolved = false;
            break;
        }
    }
    return allLettersResolved ? STATUS_WON : STATUS_INGAME;
}

void printGameState(int state, char* word, bool* answers, int wordLength, int wrongGuesses) {
    printf("\n\n");
    
    if (state == STATUS_WON) {
        printf("You won! The letter was %s", word);
    }
    if (state == STATUS_LOST) {
        printf("You lost.. The letter was %s", word);
    }
    if (state == STATUS_INGAME) {
        printf("You have %i lives left. The length of the word is %i characters", POSSIBLE_FALSE_GUESSES - wrongGuesses + 1, wordLength);
        for (int i = 0; i < wordLength; i++) {
            if (answers[i]) {
                printf("%c", word[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");
    }
}

char* createWord() {
    // load word
    
    // create buffer
    char* word = malloc(6 * sizeof(char));
    word[0] = 'h';
    word[1] = 'e';
    word[2] = 'l';
    word[3] = 'l';
    word[4] = 'o';
    word[5] = '\0';
    
    // return that buffer - duh
    return word;
}

int getWordLength(char* word) {
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }
    return len;
}

bool* createAnswerBuffer(char* word) {
    int len = getWordLength(word);
    bool* buffer = malloc(len * sizeof(bool));
    
    for (int i = 0; i < len; i++) {
        buffer[i] = false;
    }
    
    return buffer;
}
