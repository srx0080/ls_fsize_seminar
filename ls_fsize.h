#ifndef _LS_FSIZE_H_
#define _LS_FSIZE_H_

// #include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

class infoFile
{
	private:
		struct stat fileStat;

	public:
		infoFile(char *file);
		virtual void showInfo();
			
};

class infoDir : public infoFile
{
	private:
		DIR *dp;
		struct dirent *dirp;
			
	public:
		infoDir(char *dir);
		virtual void showInfo();
};	


#else
#endif

