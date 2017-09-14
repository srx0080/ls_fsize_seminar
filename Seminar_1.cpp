#include "ls_fsize.h"

int main (int argc, char **argv)
{
    if(argc == 0) {
        cout << "not enough command" << endl;
        return 0;
    }
    
	if(!strcmp(argv[1], "ls")) {
        if(argc == 3) {
            infoDir infodir(argv[2]);
            infodir.showDir(NULL);	
        }
        else if(argc == 4) {
            infoDir infodir(argv[3]);
            infodir.showDir(argv[2]);
        }
    }
	else if (!strcmp(argv[1], "fsize")) {
        if(argc == 3) {
            infoFile infofile(argv[2]);
            infofile.showFile(NULL);
		}
        else if(argc == 4) {
            infoFile infofile(argv[3]);
            infofile.showFile(argv[2]);
        }
        else {
            return 0;
        }
    }
}
