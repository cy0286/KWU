///////////////////////////////////////////////////////////////////////////////									     
// File Name : 20212058_simple_ls.c  					     //
// Date : 2023/03/29							     //	
// Os : Ubuntu 16.04 LTS 64bits 		    			     //
// Author : Song ChaeYoung					             //	
// Student ID : 2021202058						     //	
// ------------------------------------------------------------------------- //	
// Title : System Programming Assignment #1-1       			     //
// Description : Code for outputting file names to a single file path.       //
// If the file path is not specified as a factor, the current directory      //
// results are printed by default. 					     //
// File names should be alphabetically, case-insensitive.		     //
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////////////									     
// stricmp					     			     //
// ========================================================================= //	
// s1 : First string to compare		    			   	     //
// s2 : Second string to compare				             //	
// The function compares the two strings case-insensitive, returning a       //
// negative number if s1 is less than s2, if it is equal to 0, and    	     //
// a positive number if it is large. The length of a string causes a longer  //
// string to follow						     	     //
// Purpose: Function that compares strings case-insensitive		     //
///////////////////////////////////////////////////////////////////////////////
//String comparison function
int stricmp(const char *s1, const char *s2) 
{
    for (size_t i = 0; s1[i] && s2[i]; ++i) 
    {
        int j = tolower(s1[i]) - tolower(s2[i]); //Case sensitive x
        if (j != 0) return j; //Returns the difference value if two characters are different
    }
    return strlen(s1) - strlen(s2); //Longer string must follow
}

int main(int argc, char *argv[]) 
{
    DIR *dir;
    struct dirent *dirp;

    //Receive file path as command line factor
    const char *path = (argc > 1) ? argv[1] : ".";
    if(argc > 2) //Check the number of command line factors
    {  
        printf("simple_ls : only one directory path can be processed\n");
        return 1;
    }
    else if(argc == 1) //Process the current directory if there are no factors
    {
        dir = opendir(".");
    }
    else //Processing directory paths received as factors
    {
        dir = opendir(argv[1]);
    }

    if(dir == NULL) //Error handling
    {
        printf("simple_ls : cannot access '%s' : No such directory\n", argv[1]);
        return 1;
    }

    if ((dir = opendir(path)) != NULL) 
    {
        //Read File List
        char **files = malloc(sizeof(char*) * 1000); //Dynamic allocation of arrays to store file lists
        int files1 = 0;
        while ((dirp = readdir(dir)) != NULL) 
        {
            //Exclude hidden files
            if (dirp->d_name[0] == '.') continue;

            //Save File Name
            files[files1++] = strdup(dirp->d_name);
        }
        closedir(dir);

        //Sort file names
        for (int i = 0; i < files1 - 1; i++) 
        {
            for (int j = i + 1; j < files1; j++) 
            {
                if (stricmp(files[i], files[j]) > 0) 
                {
                    char *tmp = files[i];
                    files[i] = files[j];
                    files[j] = tmp;
                }
            }
        }

        //File Name Output & deallocate memory
        for (int i = 0; i < files1; i++) 
        {
            printf("%s\n", files[i]);
            free(files[i]);
        }
        free(files);

        return 0;
    } 
}
