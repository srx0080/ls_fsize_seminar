#include "ls_fsize.h"

int main (int argc, char **argv)
{
	if(!strcmp(argv[1], "ls")) {
		infoDir infodir(argv[2]);
		infodir.showInfo();	
		}
	else if (!strcmp(argv[1], "fsize")) {
		infoFile infofile(argv[2]);
		infofile.showInfo();
		}
	else {
		return 0;
	}
}
