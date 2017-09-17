#ifndef _LS_FSIZE_H_
#define _LS_FSIZE_H_

#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> //To Use POSIX Units
#include <limits.h> //To Use Other Limit Units
#include <grp.h>
#include <pwd.h>
using namespace std;

class infoFile
{
	private:
        char *fileName;
        char *time; //to eliminate "\n" from the string of modification time
		struct stat fileStat;
        struct passwd *pwd;
        struct group *pgrgid;

	public:
		infoFile();
        ~infoFile();
        void addInfo(char *file);
        void simpleInfo(char *command);
        void detailInfo();
        void showName(char *name);
		virtual void showInfo(char *command);
			
};

class infoDir : public infoFile
{
	private:
		DIR *pD;
		struct dirent **pDir;
        int iterDir;
        int i;
        char *dirName;
        char pathName[PATH_MAX];
	public:
		infoDir();
        ~infoDir();
        void addDirInfo(char *dir);
        void pathDirInfo(char *path);
        virtual void showInfo(char *command);
};	


#else
#endif

