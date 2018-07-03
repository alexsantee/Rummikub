#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para função usleep

void clear();

int main()
{
    const char *frame0 = "\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n    _______                                      _       \n   (  ____ )                                    | \\    /\\\n   | (    )|                                    |  \\  / /\n   | (____)|                                    |  (_/ / \n   |     __)                                    |   _ (  \n   | (\\ (                                       |  ( \\ \\ \n   | ) \\ \\__                                    |  /  \\ \\\n   |/   \\__/                                    |_/    \\/\n                                                         \n\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n";
    const char *frame1 = "===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n\n    _______                                      _       \n   (  ____ )                                    | \\    /\\\n   | (    )|                                    |  \\  / /\n   | (____)|                                    |  (_/ / \n   |     __)                                    |   _ (  \n   | (\\ (                                       |  ( \\ \\ \n   | ) \\ \\__                                    |  /  \\ \\\n   |/   \\__/                                    |_/    \\/\n                                                         \n\n\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n";
    const char *frame2 = "###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################";
    const char *frame3 = "X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n\n    _______           _______  _______ _________ _                 ______  \n   (  ____ )|\\     /|(       )(       )\\__   __/| \\    /\\|\\     /|(  ___ \\ \n   | (    )|| )   ( || () () || () () |   ) (   |  \\  / /| )   ( || (   ) )\n   | (____)|| |   | || || || || || || |   | |   |  (_/ / | |   | || (__/ / \n   |     __)| |   | || |(_)| || |(_)| |   | |   |   _ (  | |   | ||  __ (  \n   | (\\ (   | |   | || |   | || |   | |   | |   |  ( \\ \\ | |   | || (  \\ \\ \n   | ) \\ \\__| (___) || )   ( || )   ( |___) (___|  /  \\ \\| (___) || )___) )\n   |/   \\__/(_______)|/     \\||/     \\|\\_______/|_/    \\/(_______)|/ \\___/ \n                                                                           \n\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +";
    const char *frame4 = "+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n\n    _______           _______  _______ _________ _                 ______  \n   (  ____ )|\\     /|(       )(       )\\__   __/| \\    /\\|\\     /|(  ___ \\ \n   | (    )|| )   ( || () () || () () |   ) (   |  \\  / /| )   ( || (   ) )\n   | (____)|| |   | || || || || || || |   | |   |  (_/ / | |   | || (__/ / \n   |     __)| |   | || |(_)| || |(_)| |   | |   |   _ (  | |   | ||  __ (  \n   | (\\ (   | |   | || |   | || |   | |   | |   |  ( \\ \\ | |   | || (  \\ \\ \n   | ) \\ \\__| (___) || )   ( || )   ( |___) (___|  /  \\ \\| (___) || )___) )\n   |/   \\__/(_______)|/     \\||/     \\|\\_______/|_/    \\/(_______)|/ \\___/ \n                                                                           \n\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X";

    const char *frames[5];
    frames[0] = frame0;
    frames[1] = frame1;
    frames[2] = frame2;
    frames[3] = frame3;
    frames[4] = frame4;

    int i;
    for(i=0; i<30; i++)
    {
        putchar('\n');
        clear();
        printf("%s", frames[(i%2)]);
        usleep(100000);
    }
    
        putchar('\n');
        clear();
        printf("%s", frames[2]);
        usleep(400000);
        
        for(i=0; i<30; i++)
    {
        putchar('\n');
        clear();
        printf("%s", frames[(i%2)+3]);
        usleep(200000);
    }    

    putchar('\n');
    clear();
}

void clear()
{
	#ifdef WIN32 //para Windows
   		system("CLS");
	#else //para outro, seja MacOS ou Linux
        system("clear");
	#endif
}
