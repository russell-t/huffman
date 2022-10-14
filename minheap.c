#include <stdio.h>

// Insert element as last array element
// n is index of element to be inserted
void minheap_insert(int *a, int n) {

	int tmp, i = n;
	tmp = a[n];

	// loop until leaf is no longer less than its parent or until root node is reached
	while((i>1) && (tmp<a[i/2])){
		a[i] = a[i/2]; // overwrite leaf with parent value
		i = i/2; // update index to parent of leaf
	}
	a[i] = tmp; // insert added element 
}

int minheap_delete(int *a, int n) {

	// remove root, store last element in root
	int val, i, j, tmp;
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
	return val;
}

int main(int argc, char** argv){

	int arr[] = {0,10,20,30,25,5,40,35,18,9,98,7,4};
	int val = 0;
	int size = sizeof(arr)/sizeof(arr[0]);

	for (int i = 1; i <= size-1; i++){
		minheap_insert(arr, i);
	}
	printf("After heap creation:\n");
	for(int i = 1; i <= size-1; i++){
		printf("%d\n", arr[i]);
	}
	printf("-------\n");
	for (int i = size-1; i > 1; i--){
		val = minheap_delete(arr, i);
		printf("deleted %d\n", val);
		for(int j = 1; j <= size-1; j++){
			printf("%d\n", arr[j]);
		}
		printf("-------\n");
	}

	return 0;
}
