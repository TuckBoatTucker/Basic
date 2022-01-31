#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int** searchWord(char** arr, char* word, int i, int j, int k, int jLow, int jHigh, int kLow, int kHigh, int size, int** path, int n);
int** searchParam(char** arr, char* word, int i, int j, int k, int s, int** path, int n);
int zeroArr(int** arr);

// Main function	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);

    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

int** searchParam(char** arr, char* word, int i, int j, int k, int s, int** p, int n){


//	printf("%d, %d\n",j+1,k+1);
	if (j==0&&k==0) return searchWord(arr, word, i, j, k, j, j+1, k, k+1, s, p, n);
	else if (j==bSize-1&&k==0) return searchWord(arr, word, i, j, k, j-1, j, k, k+1, s, p, n);
	else if (j==0&&k==bSize-1) return searchWord(arr, word, i, j, k, j, j+1, k-1, k, s, p, n);
	else if (j==bSize-1&&k==bSize-1) return searchWord(arr, word, i, j, k, j-1, j, k-1, k, s, p, n);
	else if (j==0&&k<bSize-1&&k>0) return searchWord(arr, word, i, j, k, j, j+1, k-1, k+1, s, p, n);
	else if (j==bSize-1&&k>0&&k<bSize-1) return searchWord(arr, word, i, j, k, j-1, j, k-1, k+1, s, p, n);
	else if (k==0&&j<bSize-1&&j>0) return searchWord(arr, word, i, j, k, j-1, j+1, k, k+1, s, p, n);
	else if (k==bSize-1&&j>0&&j<bSize-1) return searchWord(arr, word, i, j, k, j-1, j+1, k-1, k, s, p, n);
	else return searchWord(arr, word, i, j, k, j-1, j+1, k-1, k+1, s, p, n);
}

int** searchWord(char** arr, char* word, int i, int oriJ, int oriK, int jLow, int jHigh, int kLow, int kHigh, int size, int** path, int n){

	int o, m, t=1,j,k,x;

	for (j=jLow; j<=jHigh; j++){
		for (k=kLow; k<=kHigh; k++){
			if ((j!=oriJ || k!=oriK) && *(word+i+1) == *(*(arr+j)+k)){
				if (i+1==size-1){

					if (*(*(path+j)+k)!=i+2&&*(*(path+j)+k)<=t){
						m=i+2;
						t=*(*(path+j)+k);

						while (t!=0){
							m*=10;
							t/=10;
						}
						*(*(path+j)+k) += m;
					}
					if (*(*(path+oriJ)+oriK)!=i+1&&*(*(path+oriJ)+oriK)<=t){
						m=i+1;
						t=*(*(path+oriJ)+oriK);
						while (t!=0){
							m*=10;
							t/=10;
						}
						*(*(path+oriJ)+oriK) += m;
					}
					return path;
				}
				if (zeroArr(searchParam(arr, word, i+1, j, k, size, path, n))!=1){

					if (*(*(path+oriJ)+oriK)!=i+1&&*(*(path+oriJ)+oriK)<=t*10){
						m=i+1;
						t=*(*(path+oriJ)+oriK);
						while (t*10!=0){
							m*=10;
							t/=10;
						}
						*(*(path+oriJ)+oriK) += m;}
					return searchParam(arr, word, i+1, j, k, size, path,n);
				}
			}
		}
	}
	int **zero = (int**)malloc(bSize*sizeof(int*));

	for (i=0;i<bSize;i++){
		*(zero+i) = (int*)malloc(bSize*sizeof(int));
		for (int j=0;j<bSize;j++){
			*(*(zero+i)+j) = 0;
		}
	}
	return zero;
}


int zeroArr(int** arr){

	int x=1;
	for (int i=0;i<bSize;i++){
		for (int j=0;j<bSize;j++){
			if (*(*(arr+i)+j)!=0) x=0;
		}
	}
	return x;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
    // Your implementation here...

	for (int i=0;i<bSize;i++) {
		for (int j=0;j<bSize; j++){
			printf("%c ", *(*(arr+i)+j));
		}

		printf("\n");
	}

	printf("\n");
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the word appears in arr, it will print out a message and the path as shown in 
    // the sample runs. If not found, it will print a different message as shown in the sample runs.
    // Your implementation here...

	int a,i,j,k,n=0,m,t,x=0,s=0;

	//transform input into all uppercase letters
	for (i=0;*(word+i)!=0;i++){
		a = (int) *(word+i);	//a stores the ASCII value of each letter
		if (a>96){
			a -= 32;
		}
		*(word+i) = (char) a;
	}

	//initialize search path all to 0
	int **path = (int**)malloc(bSize*sizeof(int*));

	for (i=0;i<bSize;i++){
		*(path+i) = (int*)malloc(bSize*sizeof(int));
		for (j=0;j<bSize;j++){
			*(*(path+i)+j) = 0;
		}
	}

	while (*(word+s)){
		s++;
	}

	
	for (j=0;j<bSize;j++){
		for (k=0;k<bSize;k++){
			if (*(word)==*(*(arr+j)+k)){
				path = searchParam(arr, word, 0, j, k, s, path, 0);
			}
			if (zeroArr(path)==0) break;
		}
		if (zeroArr(path)==0){
			break;
		}
	}
	if (zeroArr(path)==1){
		printf("Word not found!\n");
	}
	else{
		printf("Word found!\nPrinting the search path:\n");
	//print search path
		for (i=0;i<bSize;i++){
			for (j=0;j<bSize;j++){
				printf("%d\t",*(*(path+i)+j));
			}
			printf("\n");
		}
	}

}