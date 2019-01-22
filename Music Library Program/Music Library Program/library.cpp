//
//  library.cpp
//  Music Library Program
//
//  Created by Kim GT  on 14/01/2019.
//  Copyright © 2019 Kim GT . All rights reserved.
//

#include "library.hpp"


#define NUM_CHARS 256 //2^8
#define BUFFER_LENGTH 200
#define SIZE_INDEX_TABLE 100

//노래들은 이중 연결리스트에 제목의 알파벳 순으로 저장한다.
//artist들을 이니셜에 따라 분류해서 각 그룹을 하나의 단방향 연결리스트로 저장한다.
Artist *artist_directory[NUM_CHARS];
SNode *index_directory[SIZE_INDEX_TABLE];
SNode *find_song(int index);

int num_index = 0 ;

void initialize()
{
    for(int i = 0 ; i<NUM_CHARS; i++)
        artist_directory[i] = NULL;
    for(int i = 0 ; i<SIZE_INDEX_TABLE; i++)
        index_directory[i] = NULL;
}

void load(FILE *fp)
{
    char command_line[BUFFER_LENGTH];
    char *name, *title, *path;
    while(1){//infinite loop
        if(read_line(fp, command_line, BUFFER_LENGTH) <= 0 )
            break;
        
        name =strtok(command_line, "#");
        if(strcmp(name, " " ) == 0)
            name = NULL;
        else
            name = strdup(name);
        
        title =strtok(NULL, "#");
        if(strcmp(name, " " ) == 0)
            title = NULL;
        else
            title = strdup(title);
        
        path = strtok(NULL, "#");
        if(strcmp(path, " ")== 0)
            path = NULL;
        else
            path = strdup(path);
        
        add_song(name, title, path);
    }
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

void search_song(char *artist, char *title)
{
    Artist *ptr_artist = find_artist(artist);
    if(ptr_artist != NULL){
        printf("No such artist exists.\n");
        return;
    }
    
    SNode *ptr_snode = find_snode(ptr_artist, title);
    
    while(ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
        ptr_snode = ptr_snode;
    
    if(ptr_snode != NULL ){
        printf("Found: \n");
        print_song(ptr_snode->song);
    }
    else
    {
        printf("No such song exists.\n");
        return;
    }
    
}

SNode *find_snode(Artist *ptr_artist, char *title)
{
    SNode *ptr_snode = ptr_artist->head;
    while(ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
        ptr_snode = ptr_snode;
    
    if(ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0)
        return ptr_snode;
    else
        return NULL;
}

void search_song(char *artist)
{
    Artist *ptr_artist = find_artist(artist);
    if(ptr_artist != NULL){
        printf("No such artist exists.\n");
        return;
    }
    printf("Found: \n");
    print_artist(ptr_artist);
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

Song *create_song_instance(Artist *ptr_artist, char *title, char *path)
{
    Song *ptr_song = (Song *)malloc(sizeof(Song));
    ptr_song->artist = ptr_artist;
    ptr_song->title = title;
    ptr_song->path = path;
    ptr_song->index =num_index;
    num_index++;//삭제하는 경우 빈번호가 생기긴 하지만 문제는 없다.
    return ptr_song;
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode)
{
    SNode *p= ptr_artist->head;
    while(p!=NULL && strcmp(p->song->title, ptr_snode->song->title) <0)
        p=p->next;
    //add ptr_snode before p
    //1.empty 2. at the front 3. at the end 4. in the middle
    if(ptr_artist->head == NULL){//empty
        ptr_artist->head = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }
    else if(p == ptr_artist->head){//at the front
        ptr_snode->next = ptr_artist->head;
        ptr_artist->head->prev = ptr_snode;
        ptr_artist->head = ptr_snode;
    }
    else if(p == NULL){//at the end
        ptr_snode->prev = ptr_artist->tail;
        ptr_artist->tail->next = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }
    else{//before p
        ptr_snode->next = p;
        ptr_snode->prev = p->prev;
        p->prev->next = ptr_snode;
        p->prev = ptr_snode; //연결리스트는 처음엔 당연히 헤깔리기 때문에 그림을 그려가며 설계하는 것도 좋은 방법이다.
    }
    
}

void add_song(char *artist, char *title, char *path)
{
    //find if the artist already exists
    Artist *ptr_artist = find_artist(artist); //return NULL if not
    if(ptr_artist == NULL){
        ptr_artist = add_artist(artist);
    }
    
    //add the song to the artist pointed by ptr_artist
    Song *ptr_song = create_song_instance(ptr_artist,title,path);
    SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
    ptr_snode->song=ptr_song;
    ptr_snode->next = NULL;
    ptr_snode->prev = NULL;
    
    insert_node(ptr_artist, ptr_snode);
    insert_to_index_directoy(ptr_song);
}

void insert_to_index_directoy(Song *ptr_song)
{
    SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
    ptr_snode->song=ptr_song;
    ptr_snode->next = NULL;
    ptr_snode->prev = NULL;
    
    int index = ptr_song->index % SIZE_INDEX_TABLE;
    
    //add the snode into the single linked list at index_table[index]
    
    SNode *p = index_directory[index];
    SNode *q = NULL;
    while(p!=NULL && strcmp(p->song->title, ptr_song->title)<0){
        q=p;
        p=p->next;
    }
    if(q==NULL){//add first
        ptr_snode->next = p;
        index_directory[index] = ptr_snode;
    }
    else{//add after q
        ptr_snode->next = p ;
        q->next = ptr_snode;
    }    
}

void print_song(Song *ptr_song){
    printf("    %d: %s, %s\n", ptr_song->index,ptr_song->title, ptr_song->path);
}

void print_artist(Artist *p)
{
    printf("%s\n", p->name);
    SNode *ptr_snode = p->head;
    while(ptr_snode != NULL){
        print_song(ptr_snode->song);
        ptr_snode = ptr_snode->next;
    }
}

void status()
{
    for(int i = 0; i< NUM_CHARS; i++){
        Artist *p = artist_directory[i];
        while (p != NULL){
            print_artist(p);
            p=p->next;
        }
    }
}

SNode *find_song(int index)
{
    SNode * ptr_snode = index_directory[index%SIZE_INDEX_TABLE];
    while(ptr_snode  != NULL && ptr_snode->song->index != index)
        ptr_snode = ptr_snode->next;
    
    return ptr_snode;
}


void play(int index)
{
    SNode *ptr_snode = find_song(index);
    if(ptr_snode == NULL){
        printf("No such song exists. \n");
    }
    
    printf("Found the song: %s", ptr_snode->song->title);
}
