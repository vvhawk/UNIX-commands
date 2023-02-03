#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>


//FROM find.c
typedef struct dirent dirent;
void find(char*, DIR*);
void findh(char*, char*);


// FROM ls.c
// typedef struct dirent dirent;
char** changesize(char**, int);
void shortsort(char**, int);

char spacer[1000] = "";
void listFiles(char* dirname);
void addSpaces(char *dest, int num_of_spaces);

bool inDir = false;
int format;
int level = 0;



int main(int argc, char **argv)
{
    if(argc > 1) // Only want to run tree program, 1 arguement = arg[0]
    {
        printf("Too many arguments\n");
        return 1;
    }

    printf(".\n");
    listFiles(".");
    
    return 0;

}

void listFiles(char* dirname)
{
    DIR* current = opendir(dirname);
    if (current == NULL)
    {
        printf("%d", 2);
        return;
    }

    dirent* move = readdir(current);

    int size = 0; //Array last index
    char** names = malloc(sizeof(char*));
    while(move != NULL)
    {
        if(move->d_name[0] != '.') 
        {
            names[size] = malloc((strlen(move->d_name) + 1) * sizeof(char));
            strncpy(names[size], move->d_name, strlen(move->d_name) + 1);
            names = changesize(names, size + 1);
            size++; 
        }
        move = readdir(current);

    }

    // struct stat buff; //store stat of files
    shortsort(names, size);
    for(int i = 0; i < size; i++)
    {
        
        struct stat info; // place declaration inside so we avoid the . and .. hidden directories
        char* path = malloc(sizeof(char) * (strlen(dirname) + strlen("/") + strlen(names[i]) + 1)); //Alloctae for path
        //copy file of path
        strncpy(path, dirname, strlen(dirname) + 1);
        strncat(path, "/", 2);
        strncat(path, names[i], strlen(names[i]) + 1);
        stat(path, &info);
        if (level != 0)
        {
            for (int i = 1; i <= level; i++)
            {
                    printf("  ");
            }
        }
        printf("-%s\n", names[i]);
        if (S_ISDIR(info.st_mode))
        {
            
            level++;
            listFiles(path);
            format+= 2;
            
            level--;
                 
        }
        free(path);
           
           
    }
    closedir(current);
    
    //Free array of strings  
    for(int i = 0; i < size; i++)
    {
        free(names[i]);
    }

    format = 0;
    free(names);


}


// Following methods are from list.c and find.c

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
