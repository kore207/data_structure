#include <stdio.h>
#include <stdlib.h>

#define MAX_POLYS 10

struct term {
	int coef;
	int expo;
	struct term *next;
};

typedef struct term Term;

typedef struct polynomial {
	char name;
	Term *first;
	int size = 0;
}Polynomial;

Polynomial *polys[MAX_POLYS];
int n = 0;

Term *create_term_instance() {
	Term *t = (Term *)malloc(sizeof(Term));
	t->coef = 0;
	t->expo = 0;
	return t;
}

Polynomial *create_polynomial__instance(char name) {//�������� ������ ��ü�� �ʱ�ȭ
	Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}//��ü�� �����ϰ� �⺻������ �ʱ�ȭ���ִ� �Լ��� ���� ����� ����ϴ� �͵� ����.

void add_term(int c, int e, Polynomial *poly) {
	if (c == 0)
		return;
	Term *p = poly->first, *q = NULL;
	while (p != NULL && p->expo == e) //���� ���� �� �ִ� ���
	{
		p->coef += c;
		if (q == NULL)
			poly->first = p->next;
		else
			q->next = p->next;
		poly->size--;
		free(p);
	}

	Term *term = create_term_instance();
	term->coef = c;
	term->expo = e;

	if (q == NULL) {
		term->next = poly->first;
		poly->first = term;
	}
	else {
		term->next = p;
		q->next = term;
	}
	poly->size++;
	return;
}

int eval(Polynomial *poly, int x) {
	int result = 0;
	Term *t = poly->first;
	while (t != NULL) {
		result += eval(t, x);
		t = t->next;
	}
	return result;
}

int eval(Term *term, int x) {
	int result = term->coef;
	for (int i = 0; i < term->expo; i++) {
		result *= x;
	}
	return result;
}

void print_poly(Polynomial *p)
{
	printf("%c=", p->name);
	Term *t = p->first;
	while (t != NULL) {
		print_term(t);
		printf("+");
		t = t->next;
	}
}

void print_term(Term *pTerm) {
	printf("%dx^%d", pTerm->coef, pTerm->expo);
}