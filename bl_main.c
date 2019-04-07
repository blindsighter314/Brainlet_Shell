// Brainlet Shell Version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bl_bf.h"
#include "bl_routing.h"

char commands[50][200]; // Limits: 10000 lines; 50 params each; 200 chars each; 95.367 MB

unsigned char memory[5242880];
long blindex = 0;
long memoryLimit = 0;
long highestAllocation = 0;
unsigned char BFMode = 0;

unsigned char seed[100];
unsigned char seedLocation = 0;

int line = 0;

/*
0 = libraries; can't be disabled
1 = Math
2 = Memory
3 = IO
4 = Logic
5 = Clipboard
6 = Random
*/
unsigned char libraries[7] = {1, 1, 1, 1, 1, 1, 1};

void execute(void) {
	if (BFMode == 0) {
		if (strcmp(commands[0], "EXEC") == 0) {
			BFMode++;
		} else {
			routeCommand(commands);
		}
	} else {
		if (strcmp(commands[0], "ENDEXEC") == 0) {
			BFMode--;
		} else {
			bfInterpret(commands);
		}
	}
}

void acceptInput() {
	memset(commands, '\0', 10000);
	char line[10000];

	fgets(line, 10000, stdin);

	int sniff = 0;

	while (line[sniff] != '\0') {
		sniff++;
	}

	line[sniff] = '\n';

	if (line[0] != '#' && line[0] != '\n') {
		int paramScope = 0;
		int paramLength = 0;
		int charScope = 0;
		char str[200];

		while(line[charScope] != '\n' && line[charScope]!= '#' && paramScope<= 50 && charScope<= 200) {
			if (line[charScope] != '\t') {
				char c = line[charScope];

				if (c == ' ') {
					if (paramLength != 0) {
						commands[paramScope][paramLength] = '\0';
						paramLength = 0;
						paramScope++;
					}
				} else {
					commands[paramScope][paramLength] = c;
					paramLength++;
				}
			}

			charScope++;
		}

		if (line[charScope] == '#' && commands[0][0] == '\0') {
			commands[0][0] = '#';
		}

		if (paramScope > 50) {
			printf("Warning: Too many paramaters on line 1 (Max is 50)\n");
		}

		if (charScope > 200) {
			printf("Warning: Too many characters on line 1, paramater %d (Max is 200)\n", (paramScope + 1));
			printf("Be sure the last line in your script is empty!\n");
		}
	}

	execute();
	memset(line, '\0', 10000);
	acceptInput();
}

int main(void) {
	printf("Thank you for using Brainlet, enjoy.\n");
	acceptInput();
	return 0;
}
