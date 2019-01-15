//
//  main.cpp
//  Music Library Program
//
//  Created by Kim GT  on 14/01/2019.
//  Copyright © 2019 Kim GT . All rights reserved.
//

#include <iostream>
#include "library.hpp"
#include "string_tools.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define BUFFER_LENGTH 200

void handle_add();
void process_command();

int main(int argc, const char * argv[]) {
    
    initialize();
    process_command();
    return 0;
}

void process_command()
{
    char command_line[BUFFER_LENGTH];
    char *command;
    while(1){//infinite loop
        printf("$ ");//prompt
        
        if(read_line(stdin, command_line, BUFFER_LENGTH) <= 0 )
            continue;
        
        command =strtok(command_line, " ");
        if(strcmp(command, "add")==0)
            handle_add();
//        else if(strcmp(command, "search
//            handle_search();
//        else if(strcmp(command, "remove")==0)
//            handle_remove();
//        else if(strcmp(command, "status")==0)
//            handle_status();
//        else if(strcmp(command, "play")==0)
//            handle_play();
//        else if(strcmp(command, "save")==0)
//            handle_save();
        else if(strcmp(command, "exit")==0)
            break;
    }
}

void handle_add()
{
    char buffer[BUFFER_LENGTH];
    char *artist = NULL, *title = NULL, * path = NULL;
    printf("    Artist: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        artist =strdup(buffer);
    
    printf("    Tilte: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        title =strdup(buffer);
    
    printf("    Path: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        path =strdup(buffer);
    
    printf("%s %s %s\n", artist, title, path);
    //add to the music library
    
    add_song(artist, title, path);
}
