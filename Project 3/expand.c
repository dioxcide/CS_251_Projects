#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hmap.h"

void copyName(char String1[], int i, char tempString[])     //Function that copies the file name between the quotes
{               //Gets string where the include statement was found. i is the position where the file name begins
                // and tempstring is the string used to store the file name
    i+=1;
    int j = 0;
    int k = 0;
    char c;
    while(i<256)            //While loop goes through essentially the whole line until it finds the 2nd quote or another char
    {
        c = String1[i];     //Assigns the current character in string1 to c
        if(c == '"')        //If C is the 2nd quote the loop breaks
        {
            break;
        }
        j++;                //Iterates j until the 2nd quote is found
        i++;
    }

    int a;
    for(a = i-j; a<i;a++)           //For loop that copies from position i of the array until j spots
    {
        tempString[k] = String1[a]; //Sets tempstring equal to string
        k++;
    }
    tempString[k] = '\0';           //Appends a null character at the end of it
}

int searchInclude(char String1[], char tempString[])   //Searches the file for a #include statment
{               //Takes the string read in from the file. Tempstring serves as the array storing the file name
    if (strncmp (String1,"#include ",9) == 0)   //If statement checking if there is a #include statement with at least one space at the beggining of the line
    {
        int i = 9;  //I is assigned 9 in order to start off the white space and search for the first quote
        while(i<256)
        {
            char c = String1[i];
            if(c == '"')            //If the first quote is found then copyName is ran
            {
                copyName(String1, i, tempString);
                return 1;
            }
            else if(isspace(c) == 0)    //If something other than a space or quote is found then an error is returned
            {
                fprintf(stderr,"Invalid include statement\n");
                exit(0);
            }
            i++;
        }
    }
    else    //If there isnt a #include statement it returns 0
    {
        return 0;
    }
}

void readText(char file[], HMAP_PTR includeFiles)//Function recursively searches through each file for #include and prints them out
{
    FILE *pFile;
    if(fopen(file, "r") == NULL)        //Checks if pFile is a valid file
    {
        fprintf(stderr, "FILE DOES NOT EXIST!\n");
        exit(0);
    }
    else
    {
        pFile = fopen(file, "r");   //Else is assigns the file to pFile
    }

    char String1[256];
    char tempString[256];
    while(fgets(String1, 256, pFile)!= NULL)    //Reads in the first line of the file
    {
        if(searchInclude(String1, tempString) == 1) //If statement that runs only if the #include statement is found
        {
            if(hmap_contains(includeFiles, tempString))     //If statement checking if there is a repeated file in the table
            {
                fprintf(stderr, "Infinite recursive loop!\n");
                exit(0);
            }
            hmap_set(includeFiles, file, tempString);   //Sets the file into the table

            readText(tempString, includeFiles); //Contiues to recursively read in the files until there are no more #include
        }
        else
        {
            fprintf(stdout, "%s", String1);
        }
    }
    fclose(pFile); //closes the stream
}

int main(int argc, char *argv[])
{
    char file[256];
    strcpy(file, argv[1]);  //Copies file name from command line argument
    HMAP_PTR includeFiles = hmap_create(0,1.0); //Sets the hashtable
    hmap_set(includeFiles, file, file);//Includes the first file being read in into the hash table
    readText(file, includeFiles);   //Starts the recursive function
}
