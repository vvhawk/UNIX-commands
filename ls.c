#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
typedef struct dirent dirent;
char** changesize(char**, int);
void sort(char**, char**, int);
void shortsort(char**, int);
int main(int argc, char** argv)
{
    if(argc == 2 && (strncmp(argv[1], "-l", 3) != 0))
    {
        printf("Wrong command\n");
        return 1;
    }
    struct stat buff; //store stat of files
    struct tm* tmp = NULL; //to format dates
    dirent* move;
    DIR* current = opendir(".");
    move = readdir(current); //Pointer to files in directory
    int size = 0; //Array last index
    char** names = malloc(sizeof(char*)); //String array
    char** times = malloc(sizeof(char*)); //Time array
    uid_t* ids = malloc(sizeof(uid_t));
    int modes[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH}; //Excecution permissions
    while(move != NULL)
    {
        if(move->d_name[0] != '.') 
        {
            names[size] = malloc((strlen(move->d_name) + 1) * sizeof(char));
            strncpy(names[size], move->d_name, strlen(move->d_name) + 1);
            names = changesize(names, size + 1);
            if(argc == 2)
            {
                //Formatting the times
                times[size] = malloc(15 * sizeof(char));
                stat(move->d_name, &buff); //Put stats of file in buff
                tmp = localtime(&(buff.st_atime)); //Format time in tmp
                strftime(times[size], 14, "%b %d %H:%M", tmp); //Get proper time format 
                times = changesize(times, size + 1);
                ids[size] = buff.st_uid;
                uid_t *temp = realloc(ids, (size + 2) * sizeof(uid_t));
                ids = temp;
            }
            size++; 
        }
        move = readdir(current);
    }
    closedir(current);

    
    if(argc == 2)
    {
        sort(names, times, size);
        for(int i = 0; i < size; i++)
        {
            struct stat info;
            stat(names[i], &info);
            printf((S_ISDIR(info.st_mode)) ? "d" : "-"); //Check if directory
            for(int j = 0; j < 9; j++) //Print file permissions
            {
                if(info.st_mode & modes[j])
                {
                    if(j % 3 == 0)
                    {
                        printf("r");
                    }
                    else if(j % 3 == 1)
                    {
                        printf("w");
                    }
                    else
                    {
                        printf("x"); 
                    }
                }
                else
                {
                    printf("-");
                }
            }
            printf(" %s %s %ld %s %s \n", getpwuid(ids[i])->pw_name, getgrgid(getpwuid(ids[i])->pw_gid)->gr_name, info.st_size, times[i], names[i]);
        }
    }
    else
    {
        shortsort(names, size);
        for(int i = 0; i < size; i++)
        {
            printf("%s\n", names[i]);
        }
    }
    for(int i = 0; i < size; i++)
    {
        free(names[i]);
    }

    free(names);
    if(argc == 2)
    {
        for(int i = 0; i < size; i++)
        {
            free(times[i]);
        }   
    }
    free(times);
    free(ids);

    return 0;
}

void sort(char** sort, char** sort2, int size)
{
    char* temp;
    
    int swapin = 0;

    //Selection sort
    for(int i = 0; i < size; i++)
    {
        swapin = i;
        for(int j = i + 1; j < size; j++)
        {
            if(strcasecmp(sort[swapin], sort[j]) > 0)
            {
                swapin = j;
            }
        }
        temp = sort[i];
        sort[i] = sort[swapin];
        sort[swapin] = temp;
        temp = sort2[i];
        sort2[i] = sort2[swapin];
        sort2[swapin] = temp;
    }
    
}
char** changesize(char** change, int size)
{
    char** temp = realloc(change, (size + 1) * sizeof(char*));
    if(temp == NULL)
    {
        printf("Failed");
        return NULL;
    }
    return temp;
}

void shortsort(char** sort, int size)
{
    char* temp;
    
    int swapin = 0;

    //Selection sort
    for(int i = 0; i < size; i++)
    {
        swapin = i;
        for(int j = i + 1; j < size; j++)
        {
            if(strcasecmp(sort[swapin], sort[j]) > 0)
            {
                swapin = j;
            }
        }
        temp = sort[i];
        sort[i] = sort[swapin];
        sort[swapin] = temp;
        
    }
}