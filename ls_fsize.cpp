#include "ls_fsize.h"

infoFile::infoFile(char *file) {
	stat(file, &fileStat);
};

void infoFile::showFile() {
	cout << "File Size: \t" << fileStat.st_size << "byte" << "\n"
		<< "File Permissions: \t"
		<< (S_ISDIR(fileStat.st_mode) ? "d" : "-")
		<< ((fileStat.st_mode & S_IRUSR) ? "r" : "-")
		<< ((fileStat.st_mode & S_IWUSR) ? "w" : "-")
		<< ((fileStat.st_mode & S_IXUSR) ? "x" : "-")
		<< ((fileStat.st_mode & S_IRGRP) ? "r" : "-")
		<< ((fileStat.st_mode & S_IWGRP) ? "w" : "-")
		<< ((fileStat.st_mode & S_IXGRP) ? "x" : "-")
		<< ((fileStat.st_mode & S_IROTH) ? "r" : "-")
		<< ((fileStat.st_mode & S_IWOTH) ? "w" : "-")
		<< ((fileStat.st_mode & S_IXOTH) ? "x" : "-") 
		<< endl;
};

infoDir::infoDir(char *dir) 
	: pD(opendir(dir)), pDir(NULL), dirName(dir), infoFile(dir)
{};

void infoDir::showDir() {
	if (pD == NULL) {
		showFile();
	}
	else {
		while ((pDir = readdir(pD)) != NULL) {
			if ((strcmp(pDir->d_name, ".") == 0) || (strcmp(pDir->d_name, "..") == 0))
			{}
			else {
				sprintf(pathName, "%s%s", dirName, pDir->d_name);
				stat(pathName,&path);
				//file type
				switch (path.st_mode & S_IFMT) {
					case S_IFBLK: cout << "b"; break;
					case S_IFCHR: cout << "c"; break;
					case S_IFDIR: cout << "d"; break;
					case S_IFIFO: cout << "p"; break;
					case S_IFLNK: cout << "l"; break;
					case S_IFSOCK: cout << "s"; break;
					default:	cout << "-"; break;
				}

				//permission
				cout<< ((path.st_mode & S_IRUSR) ? "r" : "-")
					<< ((path.st_mode & S_IWUSR) ? "w" : "-")
					<< ((path.st_mode & S_IXUSR) ? "x" : "-")
					<< ((path.st_mode & S_IRGRP) ? "r" : "-")
					<< ((path.st_mode & S_IWGRP) ? "w" : "-")
					<< ((path.st_mode & S_IXGRP) ? "x" : "-")
					<< ((path.st_mode & S_IROTH) ? "r" : "-")
					<< ((path.st_mode & S_IWOTH) ? "w" : "-")
					<< ((path.st_mode & S_IXOTH) ? "x" : "-");
				//number of hard links
				cout << "\t" << path.st_nlink;
				//User ID
				pwd = getpwuid(path.st_uid);
				cout << "\t" << pwd->pw_name;
				//Group ID
				pgrgid = getgrgid(path.st_gid);
				cout << "\t" << pgrgid->gr_name;

				cout << "\t" << pDir->d_name
					<< "\t" << path.st_size << endl;
			}
//			if ((strcmp(pDir->d_name, ".") == 0) || (strcmp(pDir->d_name, "..") == 0))
//			{}
//
//			else
//				cout << pDir->d_name << endl;
		};
	}
};


