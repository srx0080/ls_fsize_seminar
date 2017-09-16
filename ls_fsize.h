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
        virtual void showName();
		virtual void showInfo(char *convert);
			
};

class infoDir : public infoFile
{
	private:
		DIR *pD;
		struct dirent *pDir;
        char *dirName;
        char pathName[PATH_MAX];
	public:
		infoDir();
        ~infoDir();
        void addDir(char *dir);
        void addPath(char *path);
        virtual void showName();
        virtual void showInfo(char *convert);
};	


#else
#endif

