## 이중연결리스트

---

* 단방향 연결 리스트(single linked list)의 한계
  - 어떤 노드의 앞에 새로운 노드를 삽입하기 어려움
  - 삭제의 경우에 항상 삭제할 노드의 앞 노드가 필요
  - 단방향 순회만이 가능
* 이중 연결 리스트
  * 각각의 노드가 다음 노드와 이전 노드의 주소를 가지는 연결 리스트
  * 양방향 순회가 가능
  * head 와 tail 을 두는것이 좋다.
  * ex)

``` c
struct node{
    char *data
    struct node next;
    struct node prev;
}

typedef struct node Node;

Node *head;
Node *tail;
int size=0;
```

---

### 삽입

```C 
Node *new_node = (Node *)malloc(sizeof(Node));
new_node->data = "Sharon";
new_node->next = p;
new_node->prev = p-<prev;
p->prev->next = new_node;
p->prev = new_node;
```

### 삭제

```c
p->prev->next = p->next;//헤드나 테일이 아닌 일반 적인 경우
p->next->prev = p->prev;
```

---

#### ADD  (or REMOVE )

```c 
void add_after(Node *pre, char *item)
{
    Node *new_node = (Node *)malloc(sizeof(Node)); //유일한 노드
    new_node->data = item;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    if(pre == NULL && head == NULL){//add_after (to empty list)
        head = node_node;//헤드와 테일 모두 하나의 노드가 된다.
        tail = node_node;
    } 
    else if(pre==NULL){//head != NULL //add_after (at the head) 
        new_node->next = head; 
        head->prev = new_node;
        head =new_node;
    }
    else if(pre==tail){//add_after (at the tail) 
        new_node->prev=tail;
        tail->next = new_node;
        tail = new_node;
    }
    else{//add_after (in the middle) 
        new_node->prev = pre;
        new_node->next = pre->next;
        pre->next->prev = new_node;
        pre->next = new_node;
    }
    size++;
}
```

---

#### 정렬

```c
void add_ordered_list(char *item){
    Node *p = tail; //empty 면 p 가 null 이기 때문에 while 문 즉각 빠져나옴
    while(p!=NULL && strcmp(item, p->data) <0)
        p = p->prev;
    add_after(p,item);
}
```

---

### 원형 연결리스트

* 마지막 노드의 다음 노드가 첫번째 노드가 되는 단순 연결리스트

#### 

