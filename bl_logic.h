#ifndef BL_LOGIC_H_
#define BL_LOGIC_H_

extern int ignoreBLCode;

int logicDepth = 0;
int logicStarts[256];
int loopCounter[256];
int loopCounterInverse[256];
int loopDeepest = 0;

long anchors[256];

extern int line;

void routeLogic(char c[50][200]) {
	printf("Logic has been disabled for the shell version of Brainlet\n");
}

#endif
