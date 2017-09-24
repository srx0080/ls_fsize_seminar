#ifndef _LS_FSIZE_H_
#define _LS_FSIZE_H_
//#define FILE_OPT 0
//#define FOLDER_OPT 1
//#define NO_OPT 2
//#define DETAIL 0
//#define SIMPLE 1
//#define BYTE 0
enum {
    FILE_OPT = 0,
    FOLDER_OPT,
    NO_OPT,
    DETAIL, 
    SIMPLE, 
    BYTE, 
    KBYTE 
};

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
        virtual void showInfo(int option) = 0;
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
		virtual void showInfo(int option);
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
        char currentPath[PATH_MAX];
        char *time; // to eliminate "\n" from the string of modification time
        struct passwd *pwd;
        struct group *pgrgid;
        void showPermission(struct stat dir);
	public:
		infoDir();
        ~infoDir();
        virtual void addInfo(char *file);
        virtual void showInfo(int option);
};	

class Create
{
    public:
        virtual Info* CreateInfo(int flag);
};
#else
#endif
