## 큐의 개념과 구현

> 선형 자료구조의 일종으로 First In First Out(FIFO). 즉 먼저 들어간 놈이 먼저 나온다. 

* 큐(queue) 역시 스택과 마찬가지로 일종의 리스트 
* 단 데이터의 삽입은 한쪽 끝에서, 삭제는 반대쪽 끝에서만 일어남
* 삽입이 일어나는 쪽을 rear, 삭제가 일어나는 쪽을 front 라고 부름
* FIFO(First-In, FIrst- Out)라고 불림
* ex) Printer queue,
* insert, enqueue, offer, push: 큐의 rear 에 새로운 원소를 삽입하는 연산
* remove, dequeue, poll, pop: 큐의 front에 있는 원소를 큐로부터 삭제하고 반환하는 연산
* peek, element,fornt : 큐의 front 에 있는 원소를 제거하지 않고 반환하는 연산
* is_empty : 비어있는지

### Linked List 로 구현

* 큐의 rear에서는 삽입, front 에서는 삭제가 일어남. 따라서 연결리스트의 앞쪽을 front, 뒤졲을 rear로 하는 것이 유리함
* 삽입을 하기 위해서는 마지막 노드의 주소를 항상 기억해야함
* 큐는 현재 몇개의 데이터가 있는지 알아야 할 상황이 자주 있기 때문에 get_size(Queue q); 와같은 함수가 필요하다.

```c
struct queue_type{
    struct node *front;
    struct node *rear;
    int size;
};
int get_size(Queue q)
{
    return q->size;
} 
Queue create()
{
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    if(q==NULL)
        printf("Error in create: queue could not be created.");
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;        
}
void destroy(Queue q)
{
    make_empty(q);
    free(q);
}
void make_empty(Queue q)
{
    while(!is_empty(q))
        dequeue(q);
    q->size = 0;
}
bool is_empty(Queue q)
{
    return q->front == NULL; //or return q->size == 0;
}

void enqueue(Queue q, Item i)
{
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
        printf("Error in push: queue is full.");
    new_node->data = i;
    new_node->next = NULL;
    if(q->front == NULL){//현재 큐가 비어있는 상태
        q->front = new_node;
        q->rear = new_node;
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}
Item dequeue(Queue q)
{
    struct node *old_front;
    Item i;
    if(is_empty(q))
        printf("Error in dequeue: queue is empty.");
    old_front = q->front; 
    i=old_front->data;
    q->front = old_front->next;
    if(q->front == NULL)//유일한 노드인경우
        q->rear = NULL;
    free(old_front);   
    q->size--;
    return i;
}
Item peek(Queue q)
{
    if(is)empty(q))
        printf("Error in peek : queue is empty.");
    return q->front->data;
}
    

```

### 환형 배열을 이용한 구현

- Rear 와 front가 변하며 원형처럼 데이터를 추가 및 삭제 가능

  

