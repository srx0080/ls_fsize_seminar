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
#include <getopt.h>
using namespace std;

class Info 
{
    public:
        virtual void addInfo(char *file) = 0;
        virtual void showInfo(const char *command) = 0;
};

class infoFile : public Info
{
	private:
        char *fileName;
		struct stat fileStat;

	public:
		infoFile();
        ~infoFile();
        virtual void addInfo(char *file);
		virtual void showInfo(const char *command);
};

class infoDir : public Info 
{
	private:
		DIR *pD;
		struct dirent **pDir;
        int iterDir;
        int i;
        char *dirName;
        struct stat dirStat;
        char pathName[PATH_MAX];
        char *time; // to eliminate "\n" from the string of modification time
        struct passwd *pwd;
        struct group *pgrgid;
	public:
		infoDir();
        ~infoDir();
        void showPermission(struct stat dir);
        virtual void addInfo(char *dir);
        virtual void showInfo(const char *command);
};	

class Create
{
    public:
        virtual Info* CreateInfo(string file);
};
#else
#endif
