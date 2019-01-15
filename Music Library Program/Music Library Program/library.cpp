//
//  library.cpp
//  Music Library Program
//
//  Created by Kim GT  on 14/01/2019.
//  Copyright © 2019 Kim GT . All rights reserved.
//

#include "library.hpp"


#define NUM_CHARS 256 //2^8
//노래들은 이중 연결리스트에 제목의 알파벳 순으로 저장한다.
//artist들을 이니셜에 따라 분류해서 각 그룹을 하나의 단방향 연결리스트로 저장한다.
Artist *artist_directory[NUM_CHARS];

void initialize()
{
    for(int i = 0 ; i<NUM_CHARS; i++)
        artist_directory[i] = NULL;
}

Artist *find_artist(char *name)
{
    Artist *p = artist_directory[(unsigned char)name[0]]; //first artist with initial name[0]
    //name[0] : 00000000 ~ 11111111 but 첫비트가 1인경우 정수로 변환하게 되면 부호가 있는 정수가 되는점이 있다.
    //int 형이면 110011 일때 앞이 다 1로 채워진다.
    while(p!= NULL && strcmp(p->name, name) < 0)
        p= p->next;
    
    if(p!=NULL && strcmp(p->name, name) ==0)
        return p;
    else
        return NULL;
}

Artist *create_artist_instance(char *name)
{
    Artist * ptr_artist = (Artist *)malloc(sizeof(Artist));
    ptr_artist->name = name;
    ptr_artist->head = NULL;
    ptr_artist->tail = NULL;
    ptr_artist->next = NULL;
    
    return ptr_artist;
}

Artist *add_artist(char *name)
{
    Artist * ptr_artist = create_artist_instance(name);
    
    Artist *p = artist_directory[(unsigned char)name[0]];
    Artist *q = NULL;
    
    while(p!=NULL && strcmp(p->name, name) < 0){
        q = p;
        p = p->next;
    }
    
    if(p==NULL && q==NULL){ //unique node
        artist_directory[(unsigned char)name[0]] = ptr_artist;
    }
    else if(q == NULL){ //add at the front
        ptr_artist->next = artist_directory[(unsigned char)name[0]];
        artist_directory[(unsigned char)name[0]] = ptr_artist;
    }
    else{//add_after(q)
        ptr_artist->next = p;
        q->next = ptr_artist;
    }
    
    return ptr_artist;
}

void add_song(char *artist, char *title, char *path)
{
    //find if the artist already exists
    Artist *ptr_artist = find_artist(artist); //return NULL if not
    if(ptr_artist == NULL){
        ptr_artist = add_artist(artist);
    }
    //add the song to the artist pointed by ptr_artist
    
}
