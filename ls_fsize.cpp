#include "ls_fsize.h"
//======================New Defined for sorting technique============
//======================related to file==============================
infoFile::infoFile() : fileName(NULL), fileStat({}) 
{};

infoFile::~infoFile()
{};

void infoFile::addInfo(char *file) {
    fileName = file;
    lstat(file, &fileStat);
};

void infoFile::showInfo(int option) {
    //Show Name
    if ((strcmp(fileName, ".") == 0) || (strcmp(fileName, "..") == 0))
    {}
    else
        cout << "\t" << fileName<< "\t";
    // print file size and convert byte to kbyte
    if (option == KBYTE)
        cout << "\t" << fileStat.st_size/(float)1000 << "kbyte" << endl;
    else if (option == BYTE) 
        cout << "\t" << fileStat.st_size << "byte" << endl;
    else
        cout << "Command is not defined" << endl;
};
//======================related to directory==============================
infoDir::infoDir() : pD(NULL), pDir(NULL), iterDir(0), i(0), dirName(NULL), dirStat({}), pathName(""), currentPath(""), time(NULL), pwd(NULL), pgrgid(NULL)
{};

infoDir::~infoDir()
{};

void infoDir::showPermission(struct stat dir) {
    switch (dir.st_mode & S_IFMT) {
        case S_IFBLK: cout << "b"; break;
        case S_IFCHR: cout << "c"; break;
        case S_IFDIR: cout << "d"; break;
        case S_IFIFO: cout << "p"; break;
        case S_IFLNK: cout << "l"; break;
        case S_IFSOCK: cout << "s"; break;
        default:	cout << "-"; break;
    }
    //permission
    cout << ((dir.st_mode & S_IRUSR) ? "r" : "-")
         << ((dir.st_mode & S_IWUSR) ? "w" : "-")
         << ((dir.st_mode & S_IXUSR) ? "x" : "-")
         << ((dir.st_mode & S_IRGRP) ? "r" : "-")
         << ((dir.st_mode & S_IWGRP) ? "w" : "-")
         << ((dir.st_mode & S_IXGRP) ? "x" : "-")
         << ((dir.st_mode & S_IROTH) ? "r" : "-")
         << ((dir.st_mode & S_IWOTH) ? "w" : "-")
         << ((dir.st_mode & S_IXOTH) ? "x" : "-");
    //number of hard links
    cout << "\t" << dir.st_nlink;
    //User ID
    pwd = getpwuid(dir.st_uid);
    cout << "\t" << pwd->pw_name;
    //Group ID
    pgrgid = getgrgid(dir.st_gid);
    cout << "\t" << pgrgid->gr_name;
    //Time Spec
    time = ctime(&dir.st_mtime);
    strtok(time, "\n"); //eliminate "\n" from the string of time
    cout << "\t" << time << "\t";

};

void infoDir::addInfo(char *file) {
    if (file == NULL) {
        getcwd(currentPath, PATH_MAX);
        dirName = currentPath;
        iterDir = scandir(dirName, &pDir, NULL, alphasort);
    }
    else {
        dirName = file;
        iterDir = scandir(dirName, &pDir, NULL, alphasort);
    }
};

void infoDir::showInfo(int option) {
    // ls to a file
    if (pDir == NULL) {
        lstat(dirName, &dirStat);
        if (option == SIMPLE) 
            cout << dirName << endl;
        else if (option == DETAIL) {
            showPermission(dirStat);
            cout << dirStat.st_size << endl;
       }
    }
    // ls to a directory
    else {
        for (i = 2 ; i < iterDir ; ++i) {
            if (option == SIMPLE)
                cout << pDir[i]->d_name << endl;
            else if (option == DETAIL) {
                sprintf(pathName, "%s/%s", dirName, pDir[i]->d_name);
                lstat(pathName, &dirStat);
                showPermission(dirStat);
                cout.flags(ios::left);
                cout.width(35);
                cout << pDir[i]->d_name << "\t" << dirStat.st_size << endl;

            }
        }
    }
};

Info* Create::CreateInfo(int flag) {
    if (flag == FILE_OPT) return new infoFile;
    if (flag == FOLDER_OPT)  return new infoDir;
    else return NULL;
};

//======================Factory Class================================
