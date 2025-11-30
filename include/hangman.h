#ifndef HANGMAN_H
#define HANGMAN_H

#define MAX_WORD_LENGTH 30
#define MAX_GUESSES 6

extern char word[MAX_WORD_LENGTH];
extern char guessed[MAX_WORD_LENGTH];
extern int wrongGuesses;
extern char usedLetters[26];

void printHangman();
void printWord();
int isGameOver();
void playHangman();

#endif
