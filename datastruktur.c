
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char const *argv[])

{
	int antall = 10;

	
	
	/*
	array = malloc(sizeof(int) * antall);
	printf("%zu\n", numberofelements );*/

	int *enemies = malloc(antall * sizeof(int));
	size_t numberofelements = sizeof(enemies)/sizeof(enemies[0]);
	printf("%zu\n", numberofelements );

	// You can index pointers just like arrays.

	// Make the array bigger

	int *more_enemies = realloc(enemies, (antall*20) * sizeof(int));
	enemies = more_enemies;
	printf("%zu\n", numberofelements );

	// Clean up when you're done.
}