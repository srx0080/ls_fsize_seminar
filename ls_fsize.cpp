#include "ls_fsize.h"

//======================New Defined for sorting technique============
//======================related to file==============================
infoFile::infoFile() : fileName(NULL), time(NULL), fileStat({}), pwd(NULL), pgrgid(NULL)
{};

infoFile::~infoFile()
{};

void infoFile::addInfo(char * file) {
    fileName = file;
    lstat(file, &fileStat);
};

void infoFile::showName(const char *name) {
    if ((strcmp(name, ".") == 0) || (strcmp(name, "..") == 0))
    {}
    else
        cout << "\t" << name << "\t";
};

void infoFile::showInfo(const char *command) {
    showName(fileName);
    simpleInfo(command);
};
// print file size and convert byte to kbyte
void infoFile::simpleInfo(const char *command) {
    if ((command != NULL) && (strcmp(command, "h") == 0))
        cout << "\t" << fileStat.st_size/(float)1000 << "kbyte" << endl;
    else  
        cout << "\t" << fileStat.st_size << "byte" << endl;
};

void infoFile::detailInfo() {
    //To show detail Information about fileStat
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

void infoFile::detailShow(const char * file) {
                detailInfo();
                showName(file);
                simpleInfo(NULL); 
};

//=====================related to directory============

infoDir::infoDir() : pD(NULL), pDir(NULL), iterDir(0), i(0), dirName(NULL), pathName("")
{};

infoDir::~infoDir()
{};

void infoDir::addDirInfo(char *dir) {
    // add a dirctory information to pDir
    dirName = dir;
    iterDir = scandir(dir, &pDir, NULL, alphasort);
};

void infoDir::dirPathInfo(const char *path) {
    sprintf(pathName, "%s/%s", dirName, path);
};

void infoDir::showInfo(const char *command) {
    // ls to a file
    if (pDir == NULL) {
        addInfo(dirName);
        if (command == NULL)
            showName(dirName);
        else if (strcmp(command, "l") == 0)
            detailShow(dirName);
        else
            return;
    }
    // ls to a directory
    else {
        for (i = 2; i < iterDir ; ++i) {
            if (command == NULL)
                showName(pDir[i]->d_name);
            else if (strcmp(command, "l") == 0) {
                dirPathInfo(pDir[i]->d_name);
                addInfo(pathName);
                detailShow(pDir[i]->d_name);
            }
            else
                return;
        }
    }
}; 
