#include <stdio.h>
#include <stdlib.h>
#include "hangman.h"

int main() {
    printf("\n");
    printf("   ███████████████████████████████████\n");
    printf("   █     H A N G M A N  G A M E      █\n");
    printf("   ███████████████████████████████████\n\n");

    char playAgain;
    do {
        playHangman();
        
        printf("\n   Play again? (y/n): ");
        scanf(" %c", &playAgain);
        while (getchar() != '\n');
        
    } while (tolower(playAgain) == 'y');

    printf("\n   Thanks for playing! Goodbye!\n\n");
    return 0;
}
