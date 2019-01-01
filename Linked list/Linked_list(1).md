# 연결리스트

### 개념과 기본 동작들

* 리스트

  -기본적인 연산: 삽입, 삭제, 검색 등,

  -리스트를 구현하는 대표적인 두 가지 방법: 배열, 연결리스트

* 배열의 단점

  -크기가 고정 - reallocation 이 필요

  -리스트의 중간에 원소를 삽입하거나 삭제할 경우 다수의 데이터를 옮겨야함

* 연결리스트

  -다른 데이터의 이동없이 중간에 삽입이나 삭제가 가능

  -길이의 제한이 없음

  -하지만 랜덤 엑세스가 불가능

### 연결리스트란?

+ 메모리에 연속된 공간에 저장된 배열과 달리 순서대로 저장할 필요가 없다.

+ 다만 첫번째 데이터에 두번째 데이터의 주소를 함께 저장한다.![Alt text](https://github.com/kore207/data_structure/blob/master/Linked%20list/linked_list_1.JPG)

  -각 연결되는 부분을 노드라고한다. ( 첫번째 노드는 따로 저장해야한다.)

  + 각각의 노드는 필요한 데이터 필드와 하나 혹은 그 이상의 링크 필드로 구성
  + 링크 필드는 다음 노드의 주소를 저장
  + **첫 번째 노드**의 주소는 따로 저장해야(절대 잊어서는 안됨)
  + 마지막 노드엔 NULL을 저장

  ```c
  struct node{
      char *data;
      struct node *next; //다음 노드의 주소를 저장할 필드.
      //(자기와 동일한 구조체에 대한 포인터를 메버로 가진다는 의미에서 " 자기참조형 구조체" 라고 부르기도 한다,)
  }
  
  typedef struct nod Node;
  Node *head = NULL; //연결리스트의 첫 번째 노드의 주소를 저장할 포인터
  ```

  ---

  #### 예제 코드

  ```c
  int main()
  {
      head = (Node *)malloc(sizeof(Node));
      head->data = "Tuesday";
      head->next = NULL;
      
      Node *q = (Node *)malloc(sizeof(Node));
      q->data = "Thursday";
      q->next = NULL;
      head = q;
      
      Node *p = head; 
      while(p!=NULL){
          printf("%s\n", p->data);
          p = p->next;
      }
  }
  ```

  ---
