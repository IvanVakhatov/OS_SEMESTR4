#include "main_header.h"

int main(int argc, char* argv[], char* envp[]) {
	while (*envp != NULL) {
		printf("%s\n", *envp);
		envp++;
	}
	return 0;
}