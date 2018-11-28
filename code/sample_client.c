#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

set_declare(int);
set_define(int);

typedef char* string;
set_declare(string);
set_define(string);

void print_string(const string a)
{
	printf("%s",a);
}
int comparator_string(const string a, const string b)
{
		if(strcmp(a,b)==0)
			return 0;
		else if(strcmp(a,b)>0)
			return 1;
		else
			return -1;
}

int comparator_int(const int a, const int b)
{
		if(a==b)
			return 0;
		else if(a>b)
			return 1;
		else
			return -1;
}
void print_int(const int a)
{
	printf("%d",a);
}

int main()
{
	/*Creating two sets*/
	set_int *a=create_set_int(comparator_int,print_int);
	set_int *b=create_set_int(comparator_int,print_int);
	
	int i=0;
	int arr_a[5]={50,25,75,42,63};
	int arr_b[10]={7,50,35,42,10,90,63,25,5,75};
	
	/*Inserting elements into the sets*/
	for(i=0;i<5;++i)
		insert_int(a,arr_a[i]);
	for(i=0;i<10;++i)
		insert_int(b,arr_b[i]);
	
	/*Displaying sets in ascending order*/
	printf("\nSet a in ascending order:\n");
	inorder_int(a);
	printf("\n\nSet b in ascending order:\n");
	inorder_int(b);
	
	/*Size & isEmpty*/
	printf("\n\nSet a is empty: %s\n",isEmpty_int(a)==1?"True":"False");
	printf("\nSize of set a: %lu\n",size_int(a));
	
	/*Union of sets a & b*/
	set_int* c=union_int(a,b);
	printf("\nUnion of sets a and b:\n");
	inorder_int(c);
	
	/*Intersection of sets a & b*/
	c=intersection_int(a,b);
	printf("\n\nIntersection of sets a and b:\n");
	inorder_int(c);

	/*Difference a-b*/
	c=difference_int(b,a);
	printf("\n\nSet difference a-b:\n");
	inorder_int(c);
	
	/*superset, subset, disjoint*/
	printf("\n\na is a superset of b: %s\n",issuperset_int(a,b)==1?"True":"False");
	printf("a is a subset of b: %s\n",issubset_int(a,b)==1?"True":"False");
	printf("a and b are disjoint: %s\n",isdisjoint_int(a,b)==1?"True":"False");
	printf("a equals b: %s\n",equals_int(a,b)==1?"True":"False");
	
	/*min,max*/
	printf("\nSmallest element in a: %d\n",min_int(a));
	printf("Largest element in a: %d\n",max_int(a));
	
	/*successor,predecessor*/
	printf("\nPredecessor of 63 in set b: %d\n",predecessor_int(b,63));
	printf("\nSuccessor of 63 in set b: %d\n",successor_int(b,63));
	
	/* insert everything from a into b*/
	printf("\nAfter inserting everything from a into b: \n");
	insertall_int(a,b);
	inorder_int(b);
	
	/*Deletion from a*/
	delete_int(a,75);
	printf("\nSize after deleting 75 from a: %lu\n",size_int(a));
	
	/*Deleting everything in a from b*/
	deleteall_int(a,b);
	printf("\nDeleting everything in a from b: \n");
	inorder_int(b);
	
	/*Clear a*/
	clear_int(a);
	printf("\n\na is empty after deleting everything from a: %s\n",isEmpty_int(a)==1?"True":"False");
	
	/*creating a set of strings*/
	set_string* s=create_set_string(comparator_string,print_string);
	
	string arr_s[5]={"abc","bca","cab","dfa","cbe"};
	for(i=0;i<5;++i)
		insert_string(s,arr_s[i]);
	printf("\nSet of strings: \n");
	inorder_string(s);
	printf("\nSize of set s: %lu\n",size_string(s));
	delete_string(s,"cab");
	printf("Size after deleting cab from s: %lu\n",size_string(s));
	return 0;
}
