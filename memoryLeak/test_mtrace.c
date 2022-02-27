#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>

int main()
{
	setenv("MALLOC_TRACE", "output", 1);
	mtrace();
	char* p = (char*)malloc(sizeof(char) * 10);

	return 0;
}
