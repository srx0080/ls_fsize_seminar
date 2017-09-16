#include "ls_fsize.h"

infoFile::infoFile() : fileName(NULL), fileStat({}), pwd(NULL), pgrgid(NULL)
{};

infoFile::~infoFile() 
{};

void infoFile::addInfo(char *file) {
    fileName = file;
    stat(file, &fileStat);
};

void infoFile::simpleInfo(char *convert) {
    if ((convert != NULL) && !strcmp(convert, "h"))
        cout << "\t" << fileStat.st_size/(float)1000 << "kbyte" << endl;
    else  
        cout << "\t" << fileStat.st_size << "byte" << endl;
};

void infoFile::detailInfo() {
    //file type
    switch (fileStat.st_mode & S_IFMT) {
        case S_IFBLK: cout << "b"; break;
        case S_IFCHR: cout << "c"; break;
        case S_IFDIR: cout << "d"; break;
        case S_IFIFO: cout << "p"; break;
        case S_IFLNK: cout << "l"; break;
        case S_IFSOCK: cout << "s"; break;
        default:	cout << "-"; break;
    }
    //permission
    cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-")
         << ((fileStat.st_mode & S_IWUSR) ? "w" : "-")
         << ((fileStat.st_mode & S_IXUSR) ? "x" : "-")
         << ((fileStat.st_mode & S_IRGRP) ? "r" : "-")
         << ((fileStat.st_mode & S_IWGRP) ? "w" : "-")
         << ((fileStat.st_mode & S_IXGRP) ? "x" : "-")
         << ((fileStat.st_mode & S_IROTH) ? "r" : "-")
         << ((fileStat.st_mode & S_IWOTH) ? "w" : "-")
         << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    //number of hard links
    cout << "\t" << fileStat.st_nlink;
    //User ID
    pwd = getpwuid(fileStat.st_uid);
    cout << "\t" << pwd->pw_name;
    //Group ID
    pgrgid = getgrgid(fileStat.st_gid);
    cout << "\t" << pgrgid->gr_name;
    //Time Spec
    time = ctime(&fileStat.st_mtime);
    strtok(time, "\n"); //eliminate "\n" from the string of time
    cout << "\t" << time;
};

void infoFile::showName() {
    cout << "\t" << fileName << "\t";
};

void infoFile::showInfo(char *convert) {
    showName();
    simpleInfo(convert);
};
    

infoDir::infoDir() : infoFile(), pD(NULL), pDir(NULL), dirName(NULL), pathName("")
{};

infoDir::~infoDir() {
    closedir(pD);
};

void infoDir::addDir(char *dir) {
    pD = opendir(dir);
    pDir = readdir(pD);
    dirName = dir;
    addInfo(dir);
};

void infoDir::addPath(char *path) {
    sprintf(pathName, "%s%s", dirName, path);
};

void infoDir::showName() {
    if ((strcmp(pDir->d_name, ".") == 0) || (strcmp(pDir->d_name, "..") == 0))
    {}
    else
        cout << "\t" << pDir->d_name << "\t";
};


void infoDir::showInfo(char *convert) {
    if (pD == NULL) {
        simpleInfo(NULL);
    }
	else {
		while ((pDir = readdir(pD)) != NULL) {
            if (convert == NULL) {
                showName();
            }
            else if (strcmp(convert, "l") == 0) {
                addPath(pDir->d_name);
                addInfo(pathName);
                detailInfo();
                showName();
                simpleInfo(NULL);
            }
            else
                return;
        }
    }
};
