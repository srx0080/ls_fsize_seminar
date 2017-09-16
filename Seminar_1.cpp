#include "ls_fsize.h"

int main (int argc, char **argv)
{
    if(argc == 0) {
        cout << "not enough command" << endl;
        return 0;
    }
    
	if(!strcmp(argv[1], "ls")) {
        if(argc == 3) {
            infoDir infodir;
            infodir.addDir(argv[2]);
            infodir.showInfo(NULL);	
        }
        else if(argc == 4) {
            infoDir infodir;
            infodir.addDir(argv[3]);
            infodir.showInfo(argv[2]);
        }
    }
	else if (!strcmp(argv[1], "fsize")) {
        if(argc == 3) {
            infoFile infofile;
            infofile.addInfo(argv[2]);
            infofile.showInfo(NULL);
		}
        else if(argc == 4) {
            infoFile infofile;
            infofile.addInfo(argv[3]);
            infofile.showInfo(argv[2]);
        }
        else {
            return 0;
        }
    }
    return 0;
}
