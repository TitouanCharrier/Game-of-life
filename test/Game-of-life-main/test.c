#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int rows;
	int cols;

	if (isatty(STDIN_FILENO)) {
		printf("not pipe\n");
	}
	else printf("pipe\n");

	scanf("%d",&rows);
	scanf("%d",&cols);
	printf("Lignes : %d, Colonnes %d\n",rows,cols );
	return 0;
}