#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
typedef struct dirent dirent;
void find(char*, DIR*);
void findh(char*, char*);
int main(int argc, char** argv)
{
    if(argc == 1) //argv[1] = NULL
    {
        printf("Too little arguments\n");   
        return 1;
    }
    DIR* current = NULL;
    find(argv[1], current);
    return 0;
}

void find(char* find, DIR* current)
{
    current = opendir("."); //open current directory
    char* path = malloc(3 * sizeof(char)); //diretory path
    char* temppath = malloc(3* sizeof(char)); //same as path
    strcpy(path, "./"); //Add root path
    strncpy(temppath, path, 3); //temppath = path
    dirent* move = readdir(current);
    while(move != NULL)
    {
        if(move->d_name[0] != '.')
        {
        
            if(strstr(move->d_name, find) != NULL) //print if name matches pattern
            {
                printf("./%s\n", move->d_name); //print path
            }
            struct stat info;
            stat(move->d_name, &info); //get file info 
            if(S_ISDIR(info.st_mode)) //Search through directory 
            {
                char* temp = realloc(path, (strlen(move->d_name) + strlen(path) + 2) * sizeof(char));
                path = temp; //Add name of directory to path
                findh(find, strncat(path, move->d_name, strlen(move->d_name) + 1)); //recusive function to search through directory
                strncpy(path, temppath, strlen(temppath) + 1); //path = temppath, strncat adds name to path
            }
        }
        move = readdir(current);
    }
    closedir(current);
    free(path);
    free(temppath);
}
void findh(char* find, char* path)
{
    char* temppath = malloc((strlen(path) + 3) * sizeof(char)); //enough for path and / and /0
    DIR* current = opendir(path);
    strncat(path, "/", 2); //path ends with /
    strncpy(temppath, path, strlen(path) + 1); //newpath = path
    char* temp; //temp pointer for realloc
    dirent* move = readdir(current);
    while(move != NULL)
    {
        if(move->d_name[0] != '.')
        {
        
            if(strstr(move->d_name, find) != NULL) //print if found
            {
                printf("%s%s\n", path, move->d_name);
            }

            temp = realloc(temppath, (strlen(move->d_name) + strlen(path) + 3) * sizeof(char)); //Increase array size 
            temppath = temp;
            struct stat info;
            stat(strncat(temppath, move->d_name, strlen(move->d_name) + 1), &info); //Get file info, need added path
            if(S_ISDIR(info.st_mode))
            {
                findh(find, temppath);
            }
            strncpy(temppath, path, strlen(temppath) + 1); //temppath = path, remove added name of file
        }
        move = readdir(current);
    }
    free(temppath);
    closedir(current);
}

