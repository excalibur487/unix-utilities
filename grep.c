#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(FILE *fp, char* term);

int main(int argc, char* argv[]) {
	FILE *fp = NULL;
	// No search term or file name provided
	if (argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			// Call grep on every file
			fp = fopen(argv[i], "r");
			if (fp == NULL) {
				printf("wgrep: cannot open file\n");
				exit(1);
			}
			grep(fp, argv[1]);
			fclose(fp);
		}
	// stdin is the input
	} else {
		grep(stdin, argv[1]);
	}
}


void grep(FILE *fp, char* term) {
	char* search = NULL;
	int slen;
	size_t len = 0;
	while ((slen = getline(&search, &len, fp)) != -1) {
		for (int i = 0; i < slen; i++) {
			if (!strncmp(term, search + i, strlen(term))) {
				printf("%s", search);
				break;
			}
		}
	}	
	free(search);
}
