#include "ls_fsize.h"


int main(int argc, char **argv)
{
    int flag= 0;
    int option_flag = 0;
    int option_command = 0;
    int opt_short;
    Create createInfo;
// Command parsing
    while((opt_short = getopt(argc,argv, "c:hl"))!=-1) {
        switch (opt_short) {
            case 'c':
                // parsing suboption of -c
                if (strcmp(optarg, "fsize") == 0) {
                    flag = FILE_OPT;
                    option_flag = BYTE;
                    break;
                }
                else if(strcmp(optarg, "ls") == 0) {
                    flag = FOLDER_OPT;
                    option_flag = SIMPLE;
                    break;
                }
                else
                    break;

            // conversion information of directory
            case 'h':
                option_flag = KBYTE;
                break;

            case 'l':
                option_flag = DETAIL;
                break;

            case '?':
                option_command = NO_OPT;
                break;
            default:
                cout << "default" << endl;
                break;
        }
    }
    // Show Information about directory or file
    if (option_command == NO_OPT)
        cout << "Command is not defined" << endl;
    else {
        Info* infor = createInfo.CreateInfo(flag);
        infor->addInfo(argv[optind]);
        infor->showInfo(option_flag);
    }
 
}
