#include "ls_fsize.h"

int main (int argc, char **argv)
{
	if(!strcmp(argv[1], "ls")) {
		infoDir infodir(argv[2]);
		infodir.showDir();	
		}
	else if (!strcmp(argv[1], "fsize")) {
		infoFile infofile(argv[2]);
		infofile.showFile();
		}
	else {
		return 0;
	}
}
