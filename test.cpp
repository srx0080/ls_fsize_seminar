#include <dirent.h>
#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) 
{
    struct dirent **pDir;
    int iterDir = 0;
    int i = 0;

    iterDir = scandir(argv[1], &pDir, NULL, alphasort);

    while(i < iterDir) {
        cout << pDir[i]->d_name << endl;
        i++;
    }
}

