//
//  library.hpp
//  Music Library Program
//
//  Created by Kim GT  on 14/01/2019.
//  Copyright © 2019 Kim GT . All rights reserved.
//

#ifndef library_hpp
#define library_hpp

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;//c컴파일러를 위한 타입 정의

struct song{
    Artist *artist;
    char *title;
    char *path;
    int index;//노래의 고유 번호
};

struct snode{
    struct snode *next,*prev;
    Song *song;
};

struct artist{
    char *name;
    struct artist *next;
    struct snode *head, *tail;
};

void initialize();
void add_song(char *artist, char *title, char *path);
void find_song();
void insert_node(Artist *ptr_artist, SNode *ptr_snode);
void status();

#endif /* library_hpp */
