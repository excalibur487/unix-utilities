#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *uncomp;
	int32_t counter = 1;
	char prev, curr;
	for (int i = 1; i < argc; i++) {
		uncomp = fopen(argv[i], "r");
		int32_t *temp = &counter;
		if ((prev = curr = fgetc(uncomp)) == EOF) {
			continue;
		}
		while(1) {
			curr = fgetc(uncomp);
			if (curr == EOF) {
				break;
			}
			//if (feof(uncomp))
			//	break;
			//printf("%d\n", curr);
			//printf("Count: %d\n", counter);
			if (curr == '\n') {
				curr = prev;
				curr = fgetc(uncomp);
				if (curr != EOF) {
					ungetc(curr, uncomp);
					printf("\n");
				}
				ungetc(curr, uncomp);
				curr = prev;
			}
			if (curr != prev) {
				//printf("%d", counter);
				fwrite(temp, 4, 1, stdout);
				printf("%c", prev);
				counter = 0;
				prev = curr;
			}
			counter++;
		}	
		//printf("Counter: %d\n", counter);
		if (i == argc - 1) {
			counter--;
			fwrite(temp, 4, 1, stdout);
			printf("%c", prev);
			counter = 0;
			prev = curr;
		}
		fclose(uncomp);
		//printf("ok\n");
	}
			
}
