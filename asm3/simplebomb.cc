/* 
 * HARVARD
 *
 * simplebomb.cc - Code inspired by the "I Packed My Suitcase"
 * kid's game. The two "kid" routines call each other.
 */

#include <cstdlib>
#include <cstdio>
#include <assert.h>

#define MAX_LINE 160

const char* const words[] = {"apple", "banana", "candy", "dog", "elephant",
                             "frog", "goat", "heart", "ice", "jacks",
                             "keds", "llama", "mouse", "nothing"};

#define MAX_TURN 5
#define SUITCASE_START 3

// input from student
char allie_answer[MAX_LINE];
char bobby_answer[MAX_LINE];

void allie(int turn, const char** his_answer);
void bobby(int turn, const char** his_answer);


void big_boom()
{
    printf("BOOM!!!\n");
    exit(8);
}


void allie(int turn, const char** his_answer) {
    if (turn > MAX_TURN)
        return;
    
    const char *my_answer;
    if (turn == 1) {
         my_answer = words[SUITCASE_START];
    } else {
        char last_1st_letter = (*his_answer)[0];
        if (turn == 5) {
            if (allie_answer[0] == last_1st_letter + 1)
                my_answer = bobby_answer;
            else
                big_boom();
        } else {
            my_answer = words[(last_1st_letter - 'a') + 1];
        }
    }
    bobby(++turn, &my_answer);
}


void bobby(int turn, const char** her_answer) {
    if (turn > MAX_TURN)
        return;
    
    const char *my_answer;
    char last_1st_letter = (*her_answer)[0];
    if (turn == 2) {
        if (bobby_answer[0] == last_1st_letter + 1)
            my_answer = bobby_answer;
        else
            big_boom();
    } else {
        my_answer = words[(last_1st_letter - 'a') + 1];
    }

    allie(++turn, &my_answer);
}


/* phase_4
 * Reads two words, which are the missing answers to Suitcase game
 * script.  Allie goes first in turn 1.  The code is missing Allie's
 * word in turn 5 and Bobby's word in turn 2.
 */
void phase_4(char *input) {
    int numScanned;
    numScanned = sscanf(input, "%s %s",
                        allie_answer, bobby_answer);
    if (numScanned != 2)
	big_boom();

    // start the game
    allie(1, nullptr);
}


void phase_5(char *input) {
    printf("phase_5: %s\n", input);
}


int main(int argc, char *argv[]) {
    assert(argc == 2);
    phase_4(argv[1]);       // first arg is the phase input
    printf("Simplebomb DEFUSED! Yea!\n");
}
