#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("zip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *uncomp;
	int32_t i = 1, counter = 1;
	char buf[2]; 
	uncomp = fopen(argv[i], "r");
	while ((buf[0] = fgetc(uncomp)) != EOF) {
		while (1) {
			buf[1] = fgetc(uncomp);
			if (buf[1] == EOF) {
				if (i >= argc - 1) {
					fwrite(&counter, 4, 1, stdout); 
					putc(buf[0], stdout);
					exit(0);
				} else {
					fclose(uncomp);
					uncomp = fopen(argv[++i], "r");
				}
			} else if (buf[0] != buf[1]) {
				fwrite(&counter, 4, 1, stdout);
				putc(buf[0], stdout);
				buf[0] = buf[1];
				counter = 1;
			} 
			else counter++;
		}
	}
}
