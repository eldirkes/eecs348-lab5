#include <stdio.h>

int main() {
	// Get the score from the user
    int score;
    printf("Enter a score: "); scanf("%d", &score);
	
	// If the score from the user is not a valid number, ask again
	while (score < 2) {
		printf("Enter a score (must be at least 2): "); scanf("%d", &score);
    }
	
	// Keep track of the "current score" of the calculation
	int curScore = 0;
	printf("Possbile combinations of scoring plays:\n");
	
	/*
		An interesting process for calculating the different combinations of scores.
		The first loop tracks the number of touchdowns with a two-point conversion (td_2p)
		The second loop tracks the number of touchdowns with an extra point (td_fg)
		The third loop tracks the number of touchdowns with no points after (td)
		The fourth loop tracks the number of field goals made (fg)
		The final loop tracks the number of safeties (safety)
		
		The loops follow the current score that is being calculated, and stops once that
		score is no longer smaller than the needed score. Once curScore is larger than score,
		curScore gets recalculated with all the current numbers from the former loops.
		
		If this is not done, with the way I have this set up, then once curScore is larger than score,
		all the for loops exit instead of exiting the current one. Instead, the number gets backtracked
		after a loop exits so that the calculations can continue.
	*/
	for (int td_2p = 0; curScore < score; td_2p++) {	// loop for touchdowns with two-point conversion
		for (int td_fg = 0; curScore < score; td_fg++) {	// loop for touchdowns with extra point
			for (int td = 0; curScore < score; td++) {	// loop for touchdowns with no points after
				for (int fg = 0; curScore < score; fg++) {	// loop for field goals made
					for (int safety = 0; curScore < score; safety++) {	// loop for safeties
						curScore = 8*td_2p + 7*td_fg + 6*td + 3*fg + 2*safety;	// calculate the final current score
						
						// print the combination if the current score matches the actual score
						if (curScore == score) {
							printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td_2p, td_fg, td, fg, safety);
						}
					}
					curScore = 8*td_2p + 7*td_fg + 6*td + 3*fg;	// backtrack to score w/o 2pts
				}
				curScore = 8*td_2p + 7*td_fg + 6*td;	// backtrack to score w/o 3pts + 2pts
			}
			curScore = 8*td_2p + 7*td_fg;	// backtrack to score w/o 6pts + 3pts + 2pts
		}
		curScore = 8*td_2p;	// backtrack to score w/o 7pts + 6pts + 3pts + 2pts
	}
    return 0;
}