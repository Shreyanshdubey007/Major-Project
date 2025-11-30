#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "hangman.h"

char word[MAX_WORD_LENGTH];
char guessed[MAX_WORD_LENGTH];
int wrongGuesses = 0;
char usedLetters[26] = {0};

const char *wordList[] = {
    "COMPUTER", "PROGRAMMING", "DEVELOPER", "KEYBOARD", "MONITOR",
    "ALGORITHM", "DATABASE", "FUNCTION", "VARIABLE", "POINTER",
    "ARRAY", "STRUCTURE", "CLASS", "OBJECT", "PYTHON", "JAVA",
    "HANGMAN", "GITHUB", "CODING", "DEBUGGING"
};
const int TOTAL_WORDS = 20;

// 7 Stages of Hangman (0 to 6 wrong guesses)
void printHangman() {
    printf("\n");
    printf("   ======\n");
    printf("   |     |\n");
    printf("   |     %c\n", (wrongGuesses >= 1 ? 'O' : ' '));
    printf("   |    %c%c%c\n", (wrongGuesses >= 3 ? '/' : ' '),
                               (wrongGuesses >= 2 ? '|' : ' '),
                               (wrongGuesses >= 4 ? '\\' : ' '));
    printf("   |    %c %c\n", (wrongGuesses >= 5 ? '/' : ' '),
                              (wrongGuesses >= 6 ? '\\' : ' '));
    printf("  ===\n\n");
}

void printWord() {
    printf("   WORD: ");
    for (int i = 0; word[i]; i++) {
        if (guessed[i] != 0)
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n\n");
}

void printUsedLetters() {
    printf("   Used Letters: ");
    for (int i = 0; i < 26; i++) {
        if (usedLetters[i])
            printf("%c ", 'A' + i);
    }
    printf("\n");
}

int isLetterInWord(char ch) {
    int found = 0;
    for (int i = 0; word[i]; i++) {
        if (toupper(word[i]) == ch) {
            guessed[i] = word[i];
            found = 1;
        }
    }
    return found;
}

int isGameOver() {
    // Win
    if (strchr(guessed, 0) == NULL) {
        printf("\nCONGRATULATIONS! YOU WIN!\n");
        printf("   The word was: %s\n", word);
        return 1;
    }
    // Lose
    if (wrongGuesses >= MAX_GUESSES) {
        printHangman();
        printf("\nGAME OVER! YOU LOST!\n");
        printf("   The word was: %s\n", word);
        return 1;
    }
    return 0;
}

void playHangman() {
    srand(time(0));
    strcpy(word, wordList[rand() % TOTAL_WORDS]);
    memset(guessed, 0, sizeof(guessed));
    wrongGuesses = 0;
    memset(usedLetters, 0, sizeof(usedLetters));

    printf("\nWELCOME TO HANGMAN GAME!\n");
    printf("Guess the word! You have %d lives.\n\n", MAX_GUESSES);

    while (!isGameOver()) {
        printHangman();
        printWord();
        printUsedLetters();
        printf("   Lives left: %d\n", MAX_GUESSES - wrongGuesses);
        printf("\n   Enter a letter: ");
        
        char ch = getchar();
        while (getchar() != '\n'); // clear buffer
        ch = toupper(ch);

        if (!isalpha(ch)) {
            printf("   Please enter a valid letter!\n");
            continue;
        }
        if (usedLetters[ch - 'A']) {
            printf("   You already tried '%c'!\n", ch);
            continue;
        }

        usedLetters[ch - 'A'] = 1;

        if (isLetterInWord(ch)) {
            printf("\n   CORRECT!\n");
        } else {
            wrongGuesses++;
            printf("\n   WRONG! %d lives left.\n", MAX_GUESSES - wrongGuesses);
        }
    }
}
