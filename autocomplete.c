#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6386)
#pragma warning(disable : 6385)
#pragma warning(disable : 6011)


//Part 1
void read_in_terms(struct term** terms, int* pnterms, char* filename) {
	char line[200];
	printf("FILENAME: %s\n", filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error opening file");
		return;
	}
	fgets(line, sizeof(line), fp);
	int N = atoi(line);

	*pnterms = N;
	//allocate memory
	struct term* term_ptr = (struct term*)malloc(sizeof(struct term) * N);
	*terms = term_ptr;
	for (int i = 0; i < N; i++) {
		//inputs line
		fgets(line, sizeof(line), fp);

		//processes line
		//get weight first
		int idx = -1;
		while (line[++idx] == ' ');
		char string_weight[50];
		int og_idx = idx;
		while (line[idx] != '\t') {
			string_weight[idx - og_idx] = line[idx++];
		}
		string_weight[idx - og_idx] = '\0';
		double weight = atof(string_weight);
		idx++;

		//get term
		og_idx = idx;
		char string_term[200];
		while (line[idx] != '\0' && line[idx] != '\n') {
			string_term[idx - og_idx] = line[idx++];
		}
		string_term[idx - og_idx] = '\0';

		//malloc bitches
		strcpy(term_ptr[i].term, string_term);
		term_ptr[i].weight = weight;
	}

}

//Part 2 helper function
int my_strcmp(char* substr, char* str) {
	if (*substr == '\0') {
		return 0;
	}
	else if (*str == '\0' && *substr != '\0') {
		return 1;
	}
	else if (*substr != *str) {
		return *substr - *str;
	}
	else {
		return my_strcmp(substr + 1, str + 1);
	}
}

//Part 2 (a)
int lowest_match(struct term* terms, int nterms, char* substr) {
	int l = 0, r = nterms - 1;
	while (l != r || !my_strcmp(substr, terms[l].term)) {
		//printf("L: %d R: %d\n", l, r);
		int mid_point = (l + r) / 2;
		int dif = my_strcmp(substr, terms[mid_point].term);
		//printf("DIF: %d\n", dif);
		if (!dif) {
			while (--mid_point >= 0 && !my_strcmp(substr, terms[mid_point].term));
			return mid_point + 1;
		}
		else if (dif > 0) {
			l = mid_point + 1;
		}
		else {
			r = mid_point - 1;
		}
	}
	return -1;
}

//Part 2 (b)
int highest_match(struct term* terms, int nterms, char* substr) {
	int l = 0, r = nterms - 1;
	while (l != r || !my_strcmp(substr, terms[l].term)) {
		//printf("L: %d R: %d\n", l, r);
		int mid_point = (l + r) / 2;
		int dif = my_strcmp(substr, terms[mid_point].term);
		//printf("DIF: %d\n", dif);
		if (!dif) {
			while (++mid_point < nterms && !my_strcmp(substr, terms[mid_point].term));
			return mid_point - 1;
		}
		else if (dif > 0) {
			l = mid_point + 1;
		}
		else {
			r = mid_point - 1;
		}
	}
	return -1;
}

//quicksort for struct
void swap(struct term* term1, struct term* term2) {
	struct term temp_term = *term1;
	*term1 = *term2;
	*term2 = temp_term;
}

void q_sort(struct term* terms, int L, int R) {
	if (L < R) {
		double pivot_num = terms[R].weight;
		int pivot_idx = 0;
		for (int x = L; x < R; x++) {
			if (terms[x].weight >= pivot_num) {
				if (terms + x != terms + L + pivot_idx) {
					swap(terms + x, terms + L + pivot_idx);
				}
				pivot_idx += 1;
			}
		}
		swap(terms + L + pivot_idx, terms + R);
		q_sort(terms, L, L + pivot_idx - 1);
		q_sort(terms, L + pivot_idx + 1, R);
	}
}

void print_terms(struct term* arr_ptr, int N) {
	for (int x = 0; x < N; x++) {
		printf("TERM: %s | WEIGHT: %f \n", arr_ptr[x].term, arr_ptr[x].weight);
	}
	printf("\n");
}

//Part 3
void autocomplete(struct term** answer, int* n_answer, struct term* terms, int nterms, char* substr){
	int lower_idx = lowest_match(terms, nterms, substr);
	int upper_idx = highest_match(terms, nterms, substr);
	printf("LOWER: %d UPPER: %d\n", lower_idx, upper_idx);
	*n_answer = (upper_idx - lower_idx) + 1;
	*answer = (struct term*)malloc(sizeof(struct term) * *n_answer);
	memcpy(*answer, terms + lower_idx, sizeof(struct term) * *n_answer);
	q_sort(*answer, 0, *n_answer - 1);
}