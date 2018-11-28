#include <math.h>

#define true 1
#define false -1

#define set_declare(T)\
	typedef struct set_##T\
	{\
		struct rbnode_##T *root;\
		struct rbnode_##T *nil;\
		int (*comparator)(const T p1,const T p2);\
		void (*print_data)(const T data);\
		long unsigned int size;\
	}set_##T;\
	\
	typedef struct rbnode_##T\
	{\
		T data;\
		double nil_data;\
		char color;\
		struct rbnode_##T *left;\
		struct rbnode_##T *right;\
		struct rbnode_##T *parent;\
	}rbnode_##T;\
	\
	set_##T* create_set_##T(int (*comparator)(const T p1, const T p2), void (*print_data)(const T data));\
	void left_rotate_##T(set_##T *tree, rbnode_##T *x);\
	void right_rotate_##T(set_##T *tree, rbnode_##T *x);\
	void insert_##T(set_##T *tree, T key);\
	void rb_insert_##T(set_##T *tree, rbnode_##T *z);\
	void rb_insert_fixup_##T(set_##T *tree,rbnode_##T *z);\
	void inorder_##T(set_##T *tree);\
	void io_##T(set_##T* tree,rbnode_##T* n);\
	void postorder_##T(set_##T *tree);\
	void posto_##T(set_##T* tree,rbnode_##T* n);\
	void preorder_##T(set_##T *tree);\
	void preo_##T(set_##T* tree,rbnode_##T* n);\
	void rb_transplant_##T(set_##T *tree,rbnode_##T *u, rbnode_##T *v);\
	void rb_delete_##T(set_##T *tree,rbnode_##T *z);\
	void rb_delete_fixup_##T(set_##T *tree,rbnode_##T *x);\
	void delete_##T(set_##T *tree,T k);\
	rbnode_##T* rb_search_##T(set_##T *tree,rbnode_##T *x, T k);\
	int search_##T(set_##T *tree,T k);\
	rbnode_##T* rb_minimum_##T(set_##T *tree,rbnode_##T *x);\
	T min_##T(set_##T *tree);\
	rbnode_##T* rb_maximum_##T(set_##T *tree,rbnode_##T *x);\
	T max_##T(set_##T *tree);\
	rbnode_##T* rb_successor_##T(set_##T *tree,rbnode_##T *x);\
	T successor_##T(set_##T *tree, T k);\
	rbnode_##T* rb_predecessor_##T(set_##T *tree,rbnode_##T *x);\
	T predecessor_##T(set_##T *tree, T k);\
	int isEmpty_##T(set_##T* tree);\
	long unsigned int size_##T(set_##T* tree);\
	void clear_##T(set_##T* tree);\
	int issuperset_##T(set_##T* a,set_##T* b);\
	int issubset_##T(set_##T* a,set_##T* b);\
	set_##T* union_##T(set_##T* a,set_##T* b);\
	void rb_insertall_##T(set_##T* a,rbnode_##T* n,set_##T* res);\
	void insertall_##T(set_##T* a,set_##T* res);\
	void rb_deleteall_##T(set_##T* a,rbnode_##T* n,set_##T* res);\
	void deleteall_##T(set_##T* a,set_##T* res);\
	set_##T* difference_##T(set_##T* a,set_##T* b);\
	void rb_intersect_##T(set_##T *a,set_##T* b,set_##T* res,rbnode_##T* n);\
	set_##T* intersection_##T(set_##T* a,set_##T* b);\
	int isdisjoint_##T(set_##T* a,set_##T* b);\
	T* toArray_##T(set_##T* a);\
	int equals_##T(set_##T* a,set_##T* b);
	
	#define set_define(T)\
	set_##T* create_set_##T(int (*comparator)(const T p1, const T p2), void (*print_data)(const T data))\
	{\
		set_##T *tree=(set_##T*)malloc(sizeof(set_##T));\
		rbnode_##T *n=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		n->nil_data= -INFINITY;\
		n->left=n->right=n->parent=NULL;\
		n->color='B';\
		tree->nil=n;\
		tree->root=n;\
		tree->comparator=comparator;\
		tree->print_data=print_data;\
		tree->size=0;\
		return tree;\
	}\
	\
	void left_rotate_##T(set_##T *tree, rbnode_##T *x)\
	{\
		rbnode_##T *y=x->right;\
		x->right=y->left;\
		if(y->left!=tree->nil)\
			y->left->parent=x;\
		y->parent=x->parent;\
		if(x->parent==tree->nil)\
			tree->root=y;\
		else if(x==x->parent->left)\
			x->parent->left=y;\
		else x->parent->right=y;\
		y->left=x;\
		x->parent=y;\
	}\
	\
	void right_rotate_##T(set_##T *tree, rbnode_##T *x)\
	{\
		rbnode_##T *y=x->left;\
		x->left=y->right;\
		if(y->right!=tree->nil)\
			y->right->parent=x;\
		y->parent=x->parent;\
		if(x->parent==tree->nil)\
			tree->root=y;\
		else if(x==x->parent->right)\
			x->parent->right=y;\
		else x->parent->left=y;\
		y->right=x;\
		x->parent=y;\
	}\
	\
	void insert_##T(set_##T *tree, T key)\
	{\
		rbnode_##T *z=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		z->data=key;\
		z->left=z->right=z->parent=tree->nil;\
		if(search_##T(tree,key)==(-1))\
		{\
			rb_insert_##T(tree,z);\
			tree->size+=1;\
		}\
	}\
	\
	void rb_insert_##T(set_##T *tree, rbnode_##T *z)\
	{\
		rbnode_##T *y=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		y=tree->nil;\
		rbnode_##T *x=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		x=tree->root;\
		while(x!=tree->nil)\
		{\
			y=x;\
			if(tree->comparator(z->data,x->data)<0)\
				x=x->left;\
			else\
				x=x->right;\
		}\
		z->parent=y;\
		if(y==tree->nil)\
			tree->root=z;\
		else if(tree->comparator(z->data,y->data)<0)\
			y->left=z;\
		else\
			y->right=z;\
		z->left=tree->nil;\
		z->right=tree->nil;\
		z->color='R';\
		rb_insert_fixup_##T(tree,z);\
	}\
	\
	void rb_insert_fixup_##T(set_##T *tree,rbnode_##T *z)\
	{\
		while(z->parent->color=='R')\
		{\
			if(z->parent==z->parent->parent->left)\
			{\
				rbnode_##T *y=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
				y=z->parent->parent->right;\
				if(y->color=='R')\
				{\
					z->parent->color='B';\
					y->color='B';\
					z->parent->parent->color='R';\
					z=z->parent->parent;\
				}\
				else\
				{\
					if(z==z->parent->right)\
					{\
						z=z->parent;\
						left_rotate_##T(tree,z);\
					}\
					z->parent->color='B';\
					z->parent->parent->color='R';\
					right_rotate_##T(tree,z->parent->parent);\
				}\
			}\
			else\
			{\
				rbnode_##T *y=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
				y=z->parent->parent->left;\
				if(y->color=='R')\
				{\
					z->parent->color='B';\
					y->color='B';\
					z->parent->parent->color='R';\
					z=z->parent->parent;\
				}\
				else\
				{\
					if(z==z->parent->left)\
					{\
						z=z->parent;\
						right_rotate_##T(tree,z);\
					}\
					z->parent->color='B';\
					z->parent->parent->color='R';\
					left_rotate_##T(tree,z->parent->parent);\
				}\
			}\
		}\
		tree->root->color='B';\
	}\
	void inorder_##T(set_##T *tree)\
	{\
		io_##T(tree,tree->root);\
	}\
	void io_##T(set_##T* tree,rbnode_##T* n)\
	{\
		if(n != tree->nil)\
		{\
			io_##T(tree,n->left);\
			tree->print_data(n->data);\
			printf("%c " ,n->color);\
			io_##T(tree,n->right);\
		}\
	}\
	\
	void postorder_##T(set_##T *tree)\
	{\
		posto_##T(tree,tree->root);\
	}\
	void posto_##T(set_##T* tree,rbnode_##T* n)\
	{\
		if(n != tree->nil)\
		{\
			posto_##T(tree,n->left);\
			posto_##T(tree,n->right);\
			tree->print_data(n->data);\
			printf("%c\n" ,n->color);\
		}\
	}\
	\
	void preorder_##T(set_##T *tree)\
	{\
		preo_##T(tree,tree->root);\
	}\
	void preo_##T(set_##T* tree,rbnode_##T* n)\
	{\
		if(n != tree->nil)\
		{\
			tree->print_data(n->data);\
			printf("%c\n" ,n->color);\
			preo_##T(tree,n->left);\
			preo_##T(tree,n->right);\
		}\
	}\
	\
	void rb_transplant_##T(set_##T *tree,rbnode_##T *u, rbnode_##T *v)\
	{\
		if(u->parent==tree->nil)\
			tree->root=v;\
		else if(u==u->parent->left)\
			u->parent->left=v;\
		else\
			u->parent->right=v;\
		v->parent=u->parent;\
	}\
	\
	void rb_delete_##T(set_##T *tree,rbnode_##T *z)\
	{\
		rbnode_##T *y=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		rbnode_##T *x=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
		y=z;\
		char y_original_colour=y->color;\
		if(z->left==tree->nil)\
		{\
			x=z->right;\
			rb_transplant_##T(tree,z,z->right);\
		}\
		else if(z->right==tree->nil)\
		{\
			x=z->left;\
			rb_transplant_##T(tree,z,z->left);\
		}\
		else\
		{\
			y=rb_minimum_##T(tree,z->right);\
			y_original_colour=y->color;\
			x=y->right;\
			if(y->parent==z)\
				x->parent=y;\
			else\
			{\
				rb_transplant_##T(tree,y,y->right);\
				y->right=z->right;\
				y->right->parent=y;\
			}\
			rb_transplant_##T(tree,z,y);\
			y->left=z->left;\
			y->left->parent=y;\
			y->color=z->color;\
		}\
		if(y_original_colour=='B')\
			rb_delete_fixup_##T(tree,x);\
	}\
	void rb_delete_fixup_##T(set_##T *tree,rbnode_##T *x)\
	{\
		while(x!=tree->root && x->color=='B')\
		{\
			rbnode_##T *w=(rbnode_##T*)malloc(sizeof(rbnode_##T));\
			if(x==x->parent->left)\
			{\
				w=x->parent->right;\
				if(w->color=='R')\
				{\
					w->color='B';\
					x->parent->color='R';\
					left_rotate_##T(tree,x->parent);\
					w=x->parent->right;\
				}\
				if(w->left->color=='B' && w->right->color=='B')\
				{\
					w->color='R';\
					x=x->parent;\
				}\
				else\
				{\
					if(w->right->color=='B')\
					{\
						w->left->color='B';\
						w->color='R';\
						right_rotate_##T(tree,w);\
						w=x->parent->right;\
					}\
					w->color=x->parent->color;\
					x->parent->color='B';\
					w->right->color='B';\
					left_rotate_##T(tree,x->parent);\
					x=tree->root;\
				}\
			}\
			else\
			{\
				w=x->parent->left;\
				if(w->color=='R')\
				{\
					w->color='B';\
					x->parent->color='R';\
					right_rotate_##T(tree,x->parent);\
					w=x->parent->left;\
				}\
				if(w->right->color=='B' && w->left->color=='B')\
				{\
					w->color='R';\
					x=x->parent;\
				}\
				else\
				{\
					if(w->left->color=='B')\
					{\
						w->right->color='B';\
						w->color='R';\
						left_rotate_##T(tree,w);\
						w=x->parent->left;\
					}\
					w->color=x->parent->color;\
					x->parent->color='B';\
					w->left->color='B';\
					right_rotate_##T(tree,x->parent);\
					x=tree->root;\
				}\
			}\
		}\
		x->color='B';\
	}\
	void delete_##T(set_##T *tree,T k)\
	{\
		rbnode_##T *z=rb_search_##T(tree,tree->root,k);\
		if(z!=tree->nil)\
		{\
			rb_delete_##T(tree,z);\
			tree->size-=1;\
		}\
	}\
\
	rbnode_##T* rb_search_##T(set_##T *tree,rbnode_##T *x, T k)\
	{\
		if(x==tree->nil || tree->comparator(k,x->data)==0)\
			return x;\
		if(tree->comparator(k,x->data)<0)\
			return rb_search_##T(tree,x->left,k);\
		else \
			return rb_search_##T(tree,x->right,k);\
	}\
\
	int search_##T(set_##T *tree,T k)\
	{\
		rbnode_##T *z=rb_search_##T(tree,tree->root,k);\
		if(z==tree->nil)\
			return -1;\
		else return 1;\
	}\
	rbnode_##T* rb_minimum_##T(set_##T *tree,rbnode_##T *x)\
	{\
		while(x->left!=tree->nil)\
			x=x->left;\
		return x;\
	}\
\
	T min_##T(set_##T *tree)\
	{\
		return rb_minimum_##T(tree,tree->root)->data;\
	}\
\
	rbnode_##T* rb_maximum_##T(set_##T *tree,rbnode_##T *x)\
	{\
		while(x->right!=tree->nil)\
			x=x->right;\
		return x;\
	}\
\
	T max_##T(set_##T *tree)\
	{\
		return rb_maximum_##T(tree,tree->root)->data;\
	}\
\
	rbnode_##T* rb_successor_##T(set_##T *tree,rbnode_##T *x)\
	{\
		if(x->right!=tree->nil)\
			return rb_minimum_##T(tree,x->right);\
		rbnode_##T *y=(rbnode_##T* )malloc(sizeof(rbnode_##T));\
		y=x->parent;\
		while(y!=tree->nil && x==y->right)\
		{\
			x=y;\
			y=y->parent;\
		}\
		return y;\
	}\
\
	T successor_##T(set_##T *tree, T k)\
	{\
		rbnode_##T *z=rb_search_##T(tree,tree->root,k);\
		if(z!=tree->nil)\
		return rb_successor_##T(tree,z)->data;\
		else\
		return (T)NULL;\
	}\
\
	rbnode_##T* rb_predecessor_##T(set_##T *tree,rbnode_##T *x)\
	{\
		if(x->left!=tree->nil)\
			return rb_maximum_##T(tree,x->left);\
		rbnode_##T *y=(rbnode_##T* )malloc(sizeof(rbnode_##T));\
		y=x->parent;\
		while(y!=tree->nil && x==y->left)\
		{\
			x=y;\
			y=y->parent;\
		}\
		return y;\
	}\
\
	T predecessor_##T(set_##T *tree, T k)\
	{\
		rbnode_##T *z=rb_search_##T(tree,tree->root,k);\
		if(z!=tree->nil)\
		return rb_predecessor_##T(tree,z)->data;\
		else\
		return (T)NULL;\
	}\
	long unsigned int size_##T(set_##T* tree)\
	{\
		return tree->size;\
	}\
	int isEmpty_##T(set_##T* tree)\
	{\
		if(tree->size==0)\
			return true;\
		else\
			return false;\
	}\
	void clear_##T(set_##T* tree)\
	{\
		while(tree->size!=0)\
			delete_##T(tree,tree->root->data);\
	}\
	int issuperset_##T(set_##T* a,set_##T* b)\
	{\
		if((a->size)<(b->size))\
			return false;\
		else\
		{\
			int res=true;\
			rbnode_##T* curr=b->root;\
			rbnode_##T* pre;\
			while(curr!=b->nil)\
			{\
				if(curr->left==b->nil)\
				{\
					if(search_##T(a,curr->data)==false)\
						return false;\
					curr=curr->right;\
				}\
				else\
				{\
					pre=curr->left;\
					while(pre->right!=b->nil && pre->right!=curr)\
						pre=pre->right;\
					if(pre->right==b->nil)\
					{\
						pre->right=curr;\
						curr=curr->left;\
					}\
					else\
					{\
						pre->right=b->nil;\
						if(search_##T(a,curr->data)==false)\
							return false;\
						curr=curr->right;\
					}\
				}\
			}\
			return res;\
		}\
	}\
	int issubset_##T(set_##T* a,set_##T* b)\
	{\
		return issuperset_##T(b,a);\
	}\
	set_##T* union_##T(set_##T* a,set_##T* b)\
	{\
		set_##T* res = create_set_##T(a->comparator,a->print_data);\
		rb_insertall_##T(a,a->root,res);\
		rb_insertall_##T(b,b->root,res);\
		return res;\
	}\
	void rb_insertall_##T(set_##T* a,rbnode_##T* n,set_##T* res)\
	{\
		if(n != a->nil)\
		{\
			rb_insertall_##T(a,n->left,res);\
			insert_##T(res,n->data);\
			rb_insertall_##T(a,n->right,res);\
		}\
	}\
	void insertall_##T(set_##T* a,set_##T* res)\
	{\
		rb_insertall_##T(a,a->root,res);\
	}\
	set_##T* difference_##T(set_##T* a,set_##T* b)\
	{\
		set_##T* res = create_set_##T(a->comparator,a->print_data);\
		rb_insertall_##T(a,a->root,res);\
		rb_deleteall_##T(b,b->root,res);\
		return res;\
	}\
	void rb_deleteall_##T(set_##T* a,rbnode_##T* n,set_##T* res)\
	{\
		if(n != a->nil)\
		{\
			rb_deleteall_##T(a,n->left,res);\
			delete_##T(res,n->data);\
			rb_deleteall_##T(a,n->right,res);\
		}\
	}\
	void deleteall_##T(set_##T* a,set_##T* res)\
	{\
		rb_deleteall_##T(a,a->root,res);\
	}\
	set_##T* intersection_##T(set_##T* a,set_##T* b)\
	{\
		set_##T* res=create_set_##T(a->comparator,a->print_data);\
		if((a->size)<(b->size))\
			rb_intersect_##T(a,b,res,a->root);\
		else\
			rb_intersect_##T(b,a,res,b->root);\
		return res;\
	}\
	void rb_intersect_##T(set_##T *a,set_##T* b,set_##T* res,rbnode_##T* n)\
	{\
		if(n!=a->nil)\
		{\
			rb_intersect_##T(a,b,res,n->left);\
			if(search_##T(b,n->data)==1)\
				insert_##T(res,n->data);\
			rb_intersect_##T(a,b,res,n->right);\
		}\
	}\
	int isdisjoint_##T(set_##T* a,set_##T* b)\
	{\
		set_##T* res=intersection_##T(a,b);\
		if(res->root == res->nil)\
			return true;\
		else\
			return false;\
	}\
	T* toArray_##T(set_##T* a)\
	{\
		T* arr=(T*)malloc((a->size)*sizeof(T));\
		rbnode_##T* curr=a->root;\
		rbnode_##T* pre;\
		long unsigned int u=0;\
		while(curr!=a->nil)\
		{\
			if(curr->left==a->nil)\
			{\
				arr[u++]=curr->data;\
				curr=curr->right;\
			}\
			else\
			{\
				pre=curr->left;\
				while(pre->right!=a->nil && pre->right!=curr)\
					pre=pre->right;\
				if(pre->right==a->nil)\
				{\
					pre->right=curr;\
					curr=curr->left;\
				}\
				else\
				{\
					pre->right=a->nil;\
					arr[u++]=curr->data;\
					curr=curr->right;\
				}\
			}\
		}\
		return arr;\
	}\
	int equals_##T(set_##T* a,set_##T* b)\
	{\
		long unsigned int u=intersection_##T(a,b)->size;\
		if(u==a->size && u==b->size)\
			return true;\
		else return false;\
	}
