#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

int main (int argc, char** argv){


    const char* homePath;
    if ((homePath = getenv("HOME")) == NULL) {
        homePath = getpwuid(getuid())->pw_dir;
    }

    const char* toodooDir = "/.toodoo";
    const char* configFile = "/toodoo.cfg";
    const char* todolistFile = "/list.toodoo";

    std::string configFilePath = std::string(homePath) + std::string(toodooDir) + std::string(configFile);
    std::string listFilePath = std::string(homePath) + std::string(toodooDir) + std::string(todolistFile);; 

    //NO ARG
    if(argc == 1){
        //default
        std::cout << "===== WELCOME TO TOODOO =====" << std::endl;
        std::cout << "version indev 0.1            " << std::endl;
        std::cout << "Use \"todo h\" to get a list " << std::endl;
        std::cout << "of all existing commands.    " << std::endl;
        std::cout << "=============================" << std::endl;
        return 0;
    }

    //HELP
    if(strcmp(argv[1], "h") == 0 || strcmp(argv[1], "help") == 0){
        if (argc > 2){
            std::cout << "Too many arguments." << std::endl;
        }

        std::cout << "====== TOODOO COMMANDS ======" << std::endl;
        std::cout << "h|help : get list of toodoo parameters" << std::endl;
        std::cout << "a|add \"Do stuff\" : Adds \"Do stuff\" to the todolist" << std::endl;
        std::cout << "d|done X : Marks the task with the id X as done" << std::endl;
        std::cout << "l|list : returns the list of current tasks to be done" << std::endl;
        std::cout << "conky : returns the list formated for conky" << std::endl;
        std::cout << "=============================" << std::endl;
        return 0;
    }

    //ADD
    if(strcmp(argv[1], "a") == 0 || strcmp(argv[1], "add") == 0){
        if(argc < 3){
            std::cout << "Too few arguments." << std::endl;
        } else if (argc < 3){
            std::cout << "Too many arguments." << std::endl;
        }

        FILE* f = fopen(listFilePath.c_str(), "a");
        if(f == NULL){
            std::cout << "Could not open " << listFilePath << std::endl;
            return -1;
        }

        fprintf(f, "%s\n", argv[2]);

        std::cout << "\"" << argv[2] << "\" added to the list" << std::endl;
        return 0;
    }

    //DONE
    if(strcmp(argv[1], "d") == 0 || strcmp(argv[1], "done") == 0){
        if(argc < 3){
            std::cout << "Too few arguments." << std::endl;
        } else if (argc < 3){
            std::cout << "Too many arguments." << std::endl;
        }

        
        std::cout << "Item n°" << argv[2] << " marked as done." << std::endl;
        return 0;
    }

    //LIST
    if(strcmp(argv[1], "l") == 0 || strcmp(argv[1], "list") == 0){
        if (argc > 2){
            std::cout << "Too many arguments." << std::endl;
        }

        FILE* f = fopen(listFilePath.c_str(), "r");
        if(f == NULL){
            std::cout << "Could not open " << listFilePath << std::endl;
            return -1;
        }

        char buffer[1000];
        std::cout << "============ TODO ===========" << std::endl;
        while(fgets(buffer, 1000, f) != NULL){
            if(buffer[0] != '#'){
                std::cout << buffer;
            }
        }
        std::cout << "=============================" << std::endl;

        return 0;
    }

    //CONKY
    if(strcmp(argv[1], "conky") == 0 || strcmp(argv[1], "conky") == 0){
        if (argc > 2){
            std::cout << "Too many arguments." << std::endl;
        }

        return 0;
    }

    std::cout << "Unknown command." << std::endl;

    return 0;
}