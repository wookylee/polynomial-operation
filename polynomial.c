#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define DATEFILE "C://datastructure01.txt"
Polynomial poly[2] = { NULL };
Polynomial Zero();
Boolean IsZero(Polynomial poly);
int Coef(Polynomial poly, int expon);
int LeadExp(Polynomial poly);
typedef struct polyNode* Polynomial;
typedef struct polyNode{
	int coef;
	int expon;
	Polynomial link; //다음 링크로 연결
	Polynomial mullink; // 곱셈에서 사용될 링크
}polyNode;
Polynomial poly[2] = { NULL };
void printPoly(Polynomial poly);
void getPoly(FILE *);
Polynomial Attach(Polynomial poly, int coef, int expon);
Polynomial Remove(Polynomial poly);
Polynomial SingleMut(Polynomial poly, int coef, int expon);
Polynomial Add(Polynomial poly1, Polynomial poly2);
Polynomial Mult(Polynomial poly1, Polynomial poly2);

Polynomial Zero() {
	Polynomial poly = (Polynomial)malloc(sizeof(polyNode));
	Polynomial zero = (Polynomial)malloc(sizeof(polyNode));
	zero ->expon = 0;
	zero->coef = 0;
	zero->link = NULL;
	poly->link = zero;
	return poly;
}

Boolean IsZero(Polynomial poly) {
	if (poly->link->coef == 0 && poly->link->expon == 0)
		return true;
	else
		return false;
}

int Coef(Polynomial poly, int expon) {
	Polynomial new;
	int a;
	for (new = poly->link; new != NULL; new = new->link) {
		if (new->expon == expon)
			return new->coef; a++;
	}
	if (a == 0) {
		printf("The exponetn %d not found", expon);
		return;
	}
}

int LeadExp(Polynomial poly) {
	return poly->link->coef;
}


Polynomial getNode() {
	Polynomial node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else
		node = (Polynomial)malloc(sizeof(polyNode));
	return node;
}
void getPoly(FILE *fp) {

	int line; 
	int coef,expon=0;
	char *poly1, *poly2;
	Polynomial two[2];
	for (line; line < 2; line++) {
		poly[line] = get_node();
	}
}

void Attach(Polynomial poly, int coef, int expon) {
	Polynomial temp; 
	temp = getNode();
	temp->coef = coef;
	temp->expon = expon;
	poly->link = temp;
	poly = temp;

}
Polynomial Remove(Polynomial poly) {
	Polynomial temp;
	if (poly) {
		temp = poly->link;
		poly->link = avail;
		avail = temp;
		poly = NULL;
	}
}

Polynomial SingleMut(Polynomial poly, int coef, int expon) {
	Polynomial temp;
	Polynomial add = Copy(poly);
	for (temp = add; temp != NULL; temp = temp->link) {
		temp->coef *= coef;
		temp->expon += expon;
	}
	return add;
}

Polynomial Add(Polynomial poly1, Polynomial poly2) {
	int temp2 = 0;
	Polynomial a, b;
	Polynomial temp = Copy(poly1);
	for (a = poly2->link; a != NULL; a = a->link) {
		for (b = temp->link; b != NULL; b = b->link) {
			if (b->expon == a->expon) {
				b->coef += a->coef;
				temp2++;
				break;
			}
		}
		if (temp2 == 0)
			Attach(temp, a->coef, b->coef);
	}
	return temp;
}

Polynomial Mult(Polynomial poly1, Polynomial poly2) {

}

void printPoly(Polynomial poly)
{
	int i = 0;
	Polynomial temp;
	temp = getNode();
	temp = poly->link;
	while (temp->link != poly) {
		if ((temp->coef < 0) && !(poly->link==temp)) {
			i = -1 * (temp->coef);
			printf("%dx", i);
		}
		else
			printf("%dx", temp->coef);
	
		printf("%d", temp->expon);
		if (temp->link->coef < 0)
			printf("-");
		else
			printf("+");
	temp = temp->link;
	}

	printf("%d", abs(temp->coef));
	if (temp->expon != 0)
		printf("x%d", temp->expon);
		printf("\n");

}


int main () {

	FILE *fp;
	int i = 0;
	Polynomial temp;
	if ((fp = fopen(DATAFILE, "a")) == NULL) {
		printf("Error in file open");
		exit(0);
	}

	getPoly(fp);
	for (i = 0; i < 2; i++) {
		printf("Polynomial %d:", i + 1);
		printPoly(poly[i]);
	}
	printf("Polynomial1: ");
	printPoly(poly[0]);
	printf("\n");
	printf("Polynomial2: ");
	printPoly(poly[1]);
	printf("\n");


	printf("Add polynomial1 and polynomial2");
	temp = Add(poly[0], poly[1]);
	printf("Result of Add: ");
	printPoly(temp);
	printf("\n");
	Remove(temp);

	pritnf("Multiply polynomial1 and polynomial2");
	temp = Mult(poly[0], poly[1]);
	printf("Result of Multiply: ");
	printPoly(temp);
	printf("\n");
	Remove(temp);

	return 0;

}