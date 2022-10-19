#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef unsigned char byte;

typedef struct codeword {
	int nbits;
	int nbytes;
	byte bytes[10];
} codeword;

struct node {
	int freq;
	char data;
	codeword cw;

	node* parent;
	node* left;
	node* right;
};

typedef struct minheap {
	int capacity;
	int size;
	node *arr;
} minheap;

typedef struct huffmanTree {
	node* nodes[100];
	int nnodes;
} huffmanTree;

// Insert element as last array element
// n is index of element to be inserted
node* minheap_insert(minheap *aa, node bb) {
	
	if(aa->size == aa->capacity){
		printf("Heap is at capacity (%d). Unable to insert element.\n", aa->capacity);
		return NULL;
	}
	
	if(aa == NULL){
		printf("Pointer to heap is NULL.\n");
		return NULL;
	}
	
	int i = aa->size+1;
	node tmp;
	node *a = aa->arr;
	a[i] = bb; 
	tmp = a[i];

	// loop until leaf is no longer less than its parent or until root node is reached
	while((i>1) && (tmp.freq < a[i/2].freq)){
		a[i] = a[i/2]; // overwrite leaf with parent value
		i = i/2; // update index to parent of leaf
	}
	a[i] = tmp; // insert added element 

	// increment heap size
	aa->size++;

	return &a[i];
}

minheap* create_minheap(int capacity, int *freq, char *data){

	minheap* aa = (minheap *)malloc(sizeof(minheap));
	if(aa == NULL){
		return NULL;
	}
	aa->arr = (node *)malloc(sizeof(node) * (capacity+1));
	if(aa->arr == NULL){
		return NULL;
	}	

	// set initial size and max capacity
	aa->size = 0;
	aa->capacity = capacity;

	// initialize nodes
	for (int i = 1; i <= capacity; i++){
		node h = (node){freq[i], data[i], (codeword){0,0,{}}, NULL, NULL, NULL};	
		minheap_insert(aa, h);
	}

	return aa;
}

void destroy_minheap(minheap* aa){

	if(aa->arr != NULL){
		free(aa->arr);
	}
	if(aa != NULL){
		free(aa);
	}
}


node* minheap_delete(minheap *aa) {

	// remove root, store last element in root
	node tmp;
	node *val = malloc(sizeof(node));
	if(val == NULL){
		return NULL;
	}
	node *a = aa->arr;
	int  i, j;
	int n = aa->size;

	*val = a[1]; // remember soon to be deleted root
	a[1] = a[n]; // set root to last value

	//a[n] = val; // store deleted value at index beyond heap 

	i = 1;
	j = 2*i;
	while (j < n) {

		// if right child is less than left child, update index of child
		// parent must actually have right leaf
		if((a[j+1].freq < a[j].freq) && (j + 1 < n)) {
			j++;
		}

		// check if child is less than parent
		if(a[i].freq > a[j].freq) {

			// swap values
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;

			// update index to child	
			i = j;
			j = 2*i;
		} else {
			break; // break if parent was not greater than children
		}
	}

	// decrement heap size
	aa->size--;

	return val;
}

void minheap_print(minheap *aa){
	
	for (int i = 1; i <= aa->size; i++){
		printf("%d %c\n", aa->arr[i].freq, aa->arr[i].data);
	}
}

huffmanTree* create_huffman_tree(minheap* heap){

	huffmanTree *tree = (huffmanTree*)malloc(sizeof(huffmanTree));
	if(tree == NULL){
		return NULL;
	}

	tree->nnodes = 0;

	int i = 0;
	while (heap->size > 1) {
		// two smallest nodes
		tree->nodes[2*i] = minheap_delete(heap);
		tree->nodes[2*i+1] = minheap_delete(heap);

		// increment number of nodes in huffman tree by 2		
		tree->nnodes += 2;	

		// sum of the two nodes
		node c = (node){tree->nodes[2*i]->freq + tree->nodes[2*i+1]->freq, (char)0, (codeword){0,0,{}}, NULL, 
							tree->nodes[2*i], tree->nodes[2*i+1]};

		// add node to heap and give child nodes a way to access parent 
		tree->nodes[2*i]->parent = minheap_insert(heap, c);
		tree->nodes[2*i+1]->parent = tree->nodes[2*i]->parent;

		i++;
	}
	// root node
	tree->nodes[2*i] = minheap_delete(heap);
	tree->nnodes++;

	return tree;
}

void destroy_huffman_tree(huffmanTree *tree) {

	for (int i = 0; i < tree->nnodes; i++){
		free(tree->nodes[i]);
	}

	if(tree != NULL)
		free(tree);
}

void traverse(node* root){

	if(root == NULL){
		return;
	}

	printf("left: %p\n", root->left);
	if(root->left != NULL){
		root->left->cw.bytes[root->left->cw.nbits] = '0';
		root->left->cw.nbits = root->cw.nbits;
		root->left->cw.nbits++;
		traverse(root->left);
	}

	printf("right: %p\n", root->right);
	if(root->right != NULL){
		root->right->cw.bytes[root->right->cw.nbits] = '1';
		root->right->cw.nbits = root->cw.nbits;
		root->right->cw.nbits++;
		traverse(root->right);
	}

}

void codeword_generate(node* root) {	

	traverse(root);

}

int main(int argc, char** argv){

	int freq[] = {0,5,9,12,13,16,45};
	char data[] = {'0','a','b','c','d','e','f'};
	int size = sizeof(freq)/sizeof(freq[0]);

	// create a min heap out of the two arrays
	minheap* heap = create_minheap(size-1, freq, data);

	// show the original array
	printf("------- Initial array -------\n");
	for (int i = 1; i <= size-1; i++){
		printf("%d %c\n", freq[i], data[i]);
	}

	// show the heap
	printf("------- After heap creation -------\n");
	minheap_print(heap);

	// create a huffman tree
	huffmanTree *tree = create_huffman_tree(heap);

	codeword_generate(tree->nodes[tree->nnodes-1]);

	// print the huffman tree node memory address relationships
	printf("------- Huffman Tree nodes -------\n");
	for (int i = 0; i < tree->nnodes; i++){
		printf("addr:%p freq:%d char:%c left:%p right:%p\n", tree->nodes[i], tree->nodes[i]->freq, 
			tree->nodes[i]->data, tree->nodes[i]->left, tree->nodes[i]->right);
		printf("codeword:");
		for(int j = 0; j < tree->nodes[i]->cw.nbits; j++){
			printf("%c", tree->nodes[i]->cw.bytes[j]);
		}
		printf("\n");
	} 


	// free the memory
	destroy_huffman_tree(tree);
	destroy_minheap(heap);

	return 0;
}
