#include <stdlib.h>
#include <stdio.h>
#include "autocomplete.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6386)
#pragma warning(disable : 6385)
#pragma warning(disable : 6011)


int main(void) {
	struct term* test_ptr;
	int num_of_terms;
	read_in_terms(&test_ptr, &num_of_terms, "cities.txt");

	for (int x = 0; x < 5; x++) {
		printf("%s %lf\n", test_ptr[x].term, test_ptr[x].weight);
	}
	struct term* test_ptr2;
	int N2;
	read_in_terms(&test_ptr2, &N2, "./fuck_praxis/fuck_praxis1.txt");
	printf("INDEX: %d\n", lowest_match(test_ptr2, N2, "a"));

	struct term* sorted_ptr;
	int answer_n;
	autocomplete(&sorted_ptr, &answer_n, test_ptr2, N2, "d");

	print_terms(sorted_ptr, answer_n);

	free(test_ptr);
	free(test_ptr2);
}