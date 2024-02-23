#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s{
	NODE left;
	NODE right;
	int key;
	void *data;
}NODE_t[1];

typedef struct{
	NODE root;
}BST_t[1],*BST;

BST bst_init(){
	BST tree = (BST)malloc(sizeof(BST_t));
	tree->root = NULL;
	return tree;
}

NODE bst_init_node(int key,void *data){
	NODE node = (NODE)malloc(sizeof(NODE_t));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->data = data;
	return node;
}

bool bst_insert(BST tree,int key,void *data){
	if(tree == NULL){
		printf("Error: Your tree has not initialized.\n");
	}else if(tree->root == NULL){
		tree->root = bst_init_node(key,data);
	}else{
		NODE node = tree->root;
		while(node != NULL){
			if(key > node->key){
				if(node->right != NULL){
					node = node->right;
				}else{
					node->right = bst_init_node(key,data);
					node = NULL;
				}
			}else if(key < node->key){
				if(node->left != NULL){
					node = node->left;
				}else{
					node->left = bst_init_node(key,data);
					node = NULL;
				}
			}else{
				printf("Error: Duplicate number detected. No action is done.\n");
				return false;
			}
		}
	}
}

NODE bst_balanced_deletion_rec(NODE node,NODE parent,int key){
	if(node->key == key){
		NODE max = NULL;
		if((node->left == NULL)&&(node->right == NULL)){
			if(parent->left == node){
				parent->left = NULL;
			}else{
				parent->right = NULL;
			}
		}else if((node->left != NULL)&&(node->right == NULL)){
			max = node->left;
			while(max->right != NULL){
				max = max->right;
			}
			node->key = max->key;
			node->data = max->data;
			max = NULL;
		}else if((node->left == NULL)&&(node->right != NULL)){
			max = node->right;
			while(max->left != NULL){
				max = max->left;
			}
			node->key = max->key;
			node->data = max->data;
			max = NULL;
		}else{
			max = node->left;
			while(max->right != NULL){
				max = max->right;
			}
			node->key = max->key;
			node->data = max->data;
			max = NULL;
		}
		free(max);
	}else{
		if(key > node->key){
			bst_balanced_deletion_rec(node->right,node,key);
		}else{
			bst_balanced_deletion_rec(node->left,node,key);
		}
	}
	return node;
}

void bst_print_horizontal(NODE node,int l){
	int i;
	if(node != NULL){
		bst_print_horizontal(node->right,l+1);
		for(i=0;i<l;i++){
			printf("     ");
		}
		printf("%d\n",node->key);
		bst_print_horizontal(node->left,l+1);
	}
}

int main(){
	srand(time(NULL));
	int arr[20] = {23,54,35,12,87,99,13,32,4,7,86,73,69,27,43,11,36,45,88,2};
	BST tree = bst_init();
	int nodeNum = 20,i;
	for(i=0;i<nodeNum;i++){
		bst_insert(tree,arr[i],NULL);
	}
	bst_print_horizontal(tree->root,0);
	printf("\n ------------------ \n");
	bst_balanced_deletion_rec(tree->root,(NODE)tree,2);
	bst_print_horizontal(tree->root,0);
	printf("\n ------------------ \n");
	bst_balanced_deletion_rec(tree->root,(NODE)tree,32);
	bst_print_horizontal(tree->root,0);
	printf("\n ------------------ \n");
	bst_balanced_deletion_rec(tree->root,(NODE)tree,7);
	bst_print_horizontal(tree->root,0);
	printf("\n ------------------ \n");
	bst_balanced_deletion_rec(tree->root,(NODE)tree,12);
	bst_print_horizontal(tree->root,0);
	printf("\n ------------------ \n");
	
	return 0;
}
