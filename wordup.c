// By- Naman Sharma
// Professor- Erin Keith
// Project - 10 ( Making Wordup)
#include <stdio.h>

// Macros used

#define length 5
#define reTries 6
#define str 6
#define increseLength 50

int totalLength;

// Prototypes

void lengthFinder(char input[]);
void checkForWords(char word1[], char word2[], int* result);
void GetWord(char userWord[]);
void getguess(char guess[], int turn);
void validity(char guess[], int* valid);
void lower(char userWord[]);
void copyguess(char source[], char dest[]);
void final(char guess[], char word[], char display[][str], char marks[][str], int attempt);


int main() {
	char word[str];
	char guess[str];
	char display[reTries][str];
	char marks[reTries][str];
	int tries = 0;
	int match = 1;

	GetWord(word);

	while (tries < reTries) {
		getguess(guess, tries + 1);
		final(guess, word, display, marks, tries);

		checkForWords(guess, word, &match);
		if (match == 0) {
			printf("================================\n");
			printf("                %s\n", display[tries]);
			printf("        You won in %d guess%s !\n", tries + 1, (tries == 0) ? "" : "es");

			switch (tries + 1) {
			case 1:
				printf("               GOATED!\n");
				break;
			case 2:
				printf("               Amazing!\n");
				break;
			case 3:
				printf("               Amazing!\n");
				break;
			case 4:
				printf("               Nice!\n");
				break;
			case 5:
				printf("               Nice!\n");
				break;
			
			}


			return 0;
		}


		tries++;
	}

	printf("You lost, better luck next time!\n");
	return 0;
}

// FUNCTION DEFINITIONS

// to find length of the string

void lengthFinder(char input[]) {
	int i = 0;
	while (input[i] != '\0') {
		i++;
	}
	totalLength = i;
}

// Comparison of the words

void checkForWords(char word1[], char word2[], int* result) {
	int i = 0;
	*result = 0;
	while (word1[i] != '\0' && word2[i] != '\0') {
		if (word1[i] != word2[i]) {
			*result = 1;
			return;
		}
		i++;
	}
	if (word1[i] != '\0' || word2[i] != '\0') {
		*result = 1;
	}
}

// This will see/read word from txt file for comprison

void GetWord(char userWord[]) {
	FILE* fp;
	fp = fopen("mystery.txt", "r");

	if (fp == NULL) {
		printf("Could not open file. \n");
		userWord[0] = '\0';
		return;
	}

	fscanf(fp, "%6s", userWord);
	fclose(fp);
	lower(userWord);
}
// convert it to lower case

void lower(char userWord[]) {
	int i = 0;
	while (userWord[i] != '\0') {
		if (userWord[i] >= 'A' && userWord[i] <= 'Z') {
			userWord[i] = userWord[i] + 32;
		}
		i++;
	}
}

void validity(char guess[], int* valid) {
	int i = 0;
	*valid = 1;
	while (guess[i] != '\0') {
		if ((guess[i] < 'A' || (guess[i] > 'Z' && guess[i] < 'a') || guess[i] > 'z')) {
			*valid = 0;
			break;
		}
		i++;
	}
}

// This copy the words from source to this one and will convert upper case if any to lower case

void copyguess(char source[], char destination[]) {
	int i;
	for (i = 0; i < length; i++) {
		if (source[i] >= 'A' && source[i] <= 'Z') {
			destination[i] = source[i] + 32;
		} else {
			destination[i] = source[i];
		}
	}
	destination[length] = '\0';
}

// takes the input and tells if it is good or no

void getguess(char guess[], int turn) {
	char temporary[increseLength];
	int CheckValid = 0;
	int leng = 0;
	int valid = 0;

	while (CheckValid == 0) {
		if (turn == reTries) {
			printf("FINAL GUESS: ");
		} else {
			printf("GUESS %d! Enter your guess: ", turn);
		}

		scanf("%10s", temporary);

		lengthFinder(temporary);
		leng = totalLength;

		validity(temporary, &valid);



		if(leng != length && valid == 0) {
			printf("Your guess must be 5 letters long. Your guess must contain only letters.\n");
		}

		else if (leng != length) {
			printf("Your guess must be 5 letters long.\n");
		}
		else if (valid == 0) {
			printf("Your guess must contain only letters.\n");
		}


		else {
			copyguess(temporary, guess);
			CheckValid = 1;
		}
	}


	printf("================================\n");
}

// Check the input and covert the correct ones to Upper Case and mark "^" like compares user input with the word

void final(char guess[], char word[], char display[][str], char marks[][str], int attempt) {
	int match[length];
	int i, j;


	for (i = 0; i < length; i++) {
		match[i] = 0;
		display[attempt][i] = guess[i];
		marks[attempt][i] = ' ';
	}

	display[attempt][length] = '\0';
	marks[attempt][length] = '\0';

	for (i = 0; i < length; i++) {
		if (guess[i] == word[i]) {
			if (display[attempt][i] >= 'a' && display[attempt][i] <= 'z') {
				display[attempt][i] = display[attempt][i] - 32;
			}
			match[i] = 1;
		}
	}

	for (i = 0; i < length; i++) {
		if (guess[i] != word[i]) {
			for (j = 0; j < length; j++) {
				if (guess[i] == word[j]) {
					if (match[j] == 0) {
						marks[attempt][i] = '^';
						match[j] = 1;
						break;
					}
				}
			}
		}
	}

	for (i = 0; i <= attempt; i++) {
		printf("%s\n", display[i]);
		printf("%s\n", marks[i]);
	}
}
