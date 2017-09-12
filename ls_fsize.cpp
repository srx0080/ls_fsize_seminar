#include "ls_fsize.h"

infoFile::infoFile(char *file) {
	stat(file, &fileStat);
};

void infoFile::showInfo() {
	cout << "File Size : " << fileStat.st_size << "byte" << endl;
};

infoDir::infoDir(char *dir) 
	: dp(opendir(dir)), dirp(NULL), infoFile(dir)
{};

void infoDir::showInfo() {
	while ((dirp = readdir(dp)) != NULL)
			cout << dirp->d_name << endl;
};


