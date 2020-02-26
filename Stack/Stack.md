## 스택(Stack) 개념과 구현

---

### 개념

> 선형 자료구조의 일족으로 Last In First Out(LIFO). 즉, 나중에 들어간 원소가 먼저 나온다. 이것은 Stack의 가장 큰 특징이다.

- 스택은 일종의 리스트
- 단, 데이터의 삽입과 삭제가 한쪽 끝에서만 이루어짐
- LIFO(Last -In, First-Out)
  
  * 프링글스와도 같다 가장 나중에 들어온 과자가 가장 먼저 나간다. 
- 삽입/삭제가 일어나는 쪽을 스택의 top이라고 부름
- 스택이 지원하는 연산

  * Push: 스택에 새로운 원소를 삽입하는 연산

  * Pop: 스택의 top에 있는 원소를 스택에서 제거하고 반환
  * Peek: 스택 top의 원소를 제거하지 않고 반환
  * Empty: 스택이 비었는지 검사  
>https://gurumee92.tistory.com/110

### 구현

<stack.c>

```c
#include "stack.h"
#define MAX_CAPACITY 100

char stack[MAX+CAPACITY];//스택에 저장되는 데이터의 타입을 문자(char)라고 가정
int top = -1;//index of the top element

void push(char ch){
    if(is_full())//스택이 가득차면 더이상 push 할수 없다
        return; //간단하게 표시 한것
    top++;
    stack[top] = ch;
}

char pop(){//pop을 호출하기 전에 먼저 empty인지 검사해야 한다.
    char tmp = stack[top];
    top--;
    return tmp;
}

char peek(){ 
    return stack[top]
}

int is_empty(){
    return top == -1;
}

int is_full(){
    return top == MAX_CAPACITY-1;
}
```

- 연결리스트에선 맨 앞이 노드를 삽입/삭제하기에 편하다. 따라서 맨 앞을 stack의 top으로 한다.

~~~c 
struct node{
    char *data;//문자열들을 저장하는 스택
    struct node *next;
};
typedef struct node Node;

Node *top = NULL;

void push(char *item){
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = item;
    p->next = top;
    top = p;
}

char *pop(){
    if(is_empty())
        return NULL;//좋은 방법은 아님(여기선 대충처리)
    char *result = top->data;
    top = top->next;//free 가 있어야하긴 함
    return result;
}

char *peek(){
    if(is_empty())
        return NULL;
    return top->data;
}

int is_empty(){
    return top == NULL;
}
~~~

### 문제점

- 스택이 2개가 필요한 경우 ->push 같은 함수를 각각에 만들어줘야하고있음(Top 변수)
- 서로 다른 탑입의 데이터를 저장할 스택이 필요한 경우

### 보완

- 배열로 구현

- ~~~ C
  void push(Stack s, Item i) //Item 은 Typedef 한것 
  {
      if(is_full(s))
          reallocats(s);
      s->top++;
      s->contents[s->top] = i;
  }
  
  Item pop(Stack s)
  {
      if(is_empty(s))
          terminate("Error in pop: stack is empty.");
      s->top--;
      return s->contents[s->top+1];
  }
  
  Item peek(Stack s)
  {
      if(is_empty(s))
          terminate("Error in peek: stack is empty.");
      return s->contents[s->top];        
  }
  ~~~

- 연결리스트로 구현


-> 1가지 타입의 데이터만을 저장할 수 있는것은 여전함

* * * Generic Programming	-> 로직은 같은데 타입만 다른 경우 
    * c언어는 적절하게 제공하지 못함 (void * 타입을 사용하여 generic 한 스택을 구현 할 수 있으나 단점이 있음)
    * 객체지향 프로그래밍 언어
