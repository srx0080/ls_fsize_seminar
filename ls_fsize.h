#ifndef _LS_FSIZE_H_
#define _LS_FSIZE_H_

#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>
using namespace std;

class infoFile
{
	private:
        char *fileName;
		struct stat fileStat;

	public:
		infoFile(char *file);
		void showFile(char *convert);
			
};

class infoDir : public infoFile
{
	private:
		DIR *pD;
		struct dirent *pDir;
		struct passwd *pwd;
		struct group *pgrgid;
		char *dirName;
		char pathName[PATH_MAX];
		struct stat path;	
	public:
		infoDir(char *dir);
        void showDir(char *detail);
};	


#else
#endif

