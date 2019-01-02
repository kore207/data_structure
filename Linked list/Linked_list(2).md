# 연결리스트

---

### 개념과 기본 동작들 (2)

+ 연결리스트의 맨 앞에 새로운 노드 삽입하기
  1. 새로운 노드를 만들고 추가할 데이터를 저장한다.
  2. 새로운 노드의 next 필드가 현재의 head 노드를 가리키도록 한다.새로운 노드를 새로운 head 노드로 한다.
  3. 새로운 노드를 새로운 head 노드로 한다.

```c
Node *tmp = (Node *)malloc(sizeof(Node));
tmp->data = "Ann";
tmp->next = head;
head = tmp;
```

> 연결 리스트를 다루는 프로그램에서 가장 주의할 점은 내가 작성한 코드가 일반적인 경우만이 아니라
>
> 특수한 경우에도 문제 없이 작동하는지 확인하는 것이다. 이 경웨는 기존의 연결리스트의 길이가 0
>
> 인경우, 즉 head가 NULL 인 경우에도 문제가 없는지 확인해야 한다.

-첫번째 노드를 가리키는 포인터 **head가 전역변수**인 경우

```c
void add_first(char *item)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    head = temp;
}
```

-첫번째 노드를 가리키는 포인터 head가 전역변수가 **아닌** 경우

```c
void add_first(Node **ptr_head, char *item)//포인터 변수 head의 주소를 매개변수로 받는다.
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = *ptr_head;
    *prt_head = temp ;
}

//or

Node *add_first(Node *head, char * item)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    return temp;
}
//호출은 다음과 같이한다 add_first(&head, item_to_store); or head = add_first(headm ,item)
```

* 어떤 노드 뒤에 새로운 노드 삽입하기

  1. 새로운 노드를 만들고 데이터를 저장한다.

  2. 새로운 노드의 next 필드가 prev의 다음 노드를 가리키도록 한다.

  3. 새로운 노드를 prev의 다음 노드로 만든다.

     ```ㅊ
     Node *tmp = (Node *)malloc(sizeof(Node));
     tmp->data = data_to_store;
     tmp->next = prev->next;
     prev->next =tmp;
     ```

  > 연결리스트에 새로운 노드를 삽입할 때 삽입할 위치의 바로 앞 노드의 주소가 필요하다.
  >
  > 즉 어떤 노드의 뒤에 삽입하는 것은 간단하지만, 반대로 어떤 노드의 앞에 삽입하는 것은 간단하지 않다.
  >
  > (만들지 않는게 좋다.)

* 첫번째 노드의 삭제

  1. head 가 현재 head 노드의 다음 노드를 가리키게 만든다.

     ```ㅊ
     head = head->next;
     ```

* 어떤 노드의 다음 노드 삭제하기(삭제하고자 하는 노드보다 그 전의 주소를 알아야하기 때문)

  ```ㅊ
  if(prev->next != NULL)
  	prev->next = prev->next->next;
  ```

* 연결리스트 순회하기(traverse)

  (연결리스트의 노드들을 처음부터 순서대로 방분하는 것을 순회 한다고 말한다. ex)fine, search ... )

  ```c
  Node *find(char *word){
      Node *p = head;
      while(p != NULL){
          if(strcmp(p->data, word)==0)
              return p;
          p= p->next;
      }
      return NULL;
  }
  
  Node *get_node(int index){// 연결리스트의 index번째 노드의 주소를 반환
      if(index < 0) //index 칸 이동한뒤 반환한다. 
          return NULL;
      Node *p = head;
      for(int i=0; i<index && p!=NULL; i++)
          p = p->next;
      return p;
  }
  
  int add(int index, char *item){//연결리스트의 index번째 위치에 새로운 노드를 만들어서 삽입
      if(index<0)
          return 0;
             
      if(index == 0){
          add_first(item);
          return 1;
      }             
      
      Node *prev = get_node(index-1);
      if(prev != NULL){
          add_after(prev, item);
          return 1;
      }
      return 0;
  }
  
  Node *remove(int index){//index번째 노드를 삭제하고 , 그 노드에 저장된 데이터를 반환
      if(index < 0)
          return NULL;
      
      if(index==0)
          return remove_first();
      
      Node *prev = get_node(index-1);
      if(prev==NULL)
          return NULL;
      else
          return remove_after(prev);
  }
  
  Node *remove(char *item){//입력된 데이터를 저장한 노드를 찾아 삭제
      Node *p = head;
      while(p!=NULL && strcmp(p->data, item)!=0)
          p=p->next;
      //while문은 빠져나오지만 그 앞의 주소를 알아야한다.
      //연결리스트를 사용할때의 전형적인 상황
  }
  
  Node *remove(char *item){
      Node *p = head;
      Node *q = NULL;
      while(p!=NULL && strcmp(p->data, item)!=0){
          q = p; //q는 항상 p보다 한칸 앞을 가리킨다.
          p=p->next;
      }
      if(p==NULL)
          return NULL;
      if(q==NULL)
          return remove_first();
      else
          return remove_afrer(q);
  }
  ```
