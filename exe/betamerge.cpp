#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "EUAnaBeta.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please type 'betamerge #run'." << endl;
		return 0;
	}

	int runB = atoi(argv[1]);
	EUAnaBeta beta;
	beta.BetaGammaMerge(runB);
}	
