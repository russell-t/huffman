#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int capacity;
	int size;
	int *arr;
} minheap;

minheap* create_minheap(int capacity, int *arr){

	minheap* mh = (minheap *)malloc(sizeof(minheap));
	if(mh == NULL){
		return NULL;
	}

	mh->size = 0;
	mh->capacity = capacity;
	mh->arr = arr;

	return mh;
}

void destroy_minheap(minheap* aa){
	free(aa);
}

// Insert element as last array element
// n is index of element to be inserted
void minheap_insert(minheap *aa) {
	
	if(aa->size == aa->capacity){
		printf("Heap is at capacity (%d). Unable to insert element.\n", aa->capacity);
		return;
	}
	
	if(aa == NULL){
		printf("Pointer to heap is NULL.\n");
		return;
	}
	
	int tmp, i = aa->size+1;
	int *a = aa->arr;
	tmp = a[i];

	// loop until leaf is no longer less than its parent or until root node is reached
	while((i>1) && (tmp < a[i/2])){
		a[i] = a[i/2]; // overwrite leaf with parent value
		i = i/2; // update index to parent of leaf
	}
	a[i] = tmp; // insert added element 

	// increment heap size
	aa->size++;
}

int minheap_delete(minheap *aa) {

	// remove root, store last element in root
	int val, i, j, tmp;
	int *a = aa->arr;
	int n = aa->size;

	val = a[1]; // remember soon to be deleted root
	a[1] = a[n]; // set root to last value

	a[n] = val; // store deleted value at index beyond heap 

	i = 1;
	j = 2*i;
	while (j < n) {

		// if right child is less than left child, update index of child
		// parent must actually have right leaf
		if((a[j+1] < a[j]) && (j + 1 < n)) {
			j++;
		}

		// check if child is less than parent
		if(a[i] > a[j]) {

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

void minheap_sort(minheap *aa){

	for (int i = aa->size; i > 0; i--){
		minheap_delete(aa);
	}
}

void minheap_print_array(minheap *aa){
	
	for (int i = 1; i <= aa->capacity; i++){
		printf("%d\n", aa->arr[i]);
	}
}

int main(int argc, char** argv){

	int arr[] = {0,10,20,30,25,5,40,35,18,9,98,7,4,230,891,17};
	int val = 0;
	int size = sizeof(arr)/sizeof(arr[0]);

	minheap* heap = create_minheap(size-1, arr);

	printf("------- Initial array -------\n");
	minheap_print_array(heap);
	for (int i = 1; i <= size-1; i++){
		minheap_insert(heap);
	}
	printf("-------\n");
	printf("After heap creation:\n");
	for(int i = 1; i <= size-1; i++){
		printf("%d\n", heap->arr[i]);
	}

	minheap_sort(heap);
	printf("------- After heap sort -------\n");
	minheap_print_array(heap);

	free(heap);

	return 0;
}
