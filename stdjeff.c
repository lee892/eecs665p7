#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

void printBool(int64_t c){
	if (c == 0){
		fprintf(stdout, "false");
	} else{
		fprintf(stdout, "true");
	}
	fflush(stdout);
}

FILE * stdJeff_openFP(const char * s, int mode) {
	if (mode == 1) {
		fprintf("opening %s for writing\n", s);
		return fopen(s, "w");
	} else {
		fprintf("opening %s for reading\n", s);
		return fopen(s, "r");
	}
}

void stdJeff_closeFP(FILE* fp) {
	fclose(fp);
}

long int stdJeff_readInt(FILE* f) {
	char buffer[32];
	if (f == 1) {
		fgets(buffer, 32, stdin);
	} else {
		fgets(buffer, 32, f);
	}
	long int res = atol(buffer);
	return res;
}

void stdJeff_readString(FILE* in, FILE* out) {
	char* line = NULL;
	size_t len = 0;
	if (in == 1) {
		getline(&line, &len, stdin);
	} else {
		getline(&line, &len, in);
	}
	fprintf(out, "%s", line);
	fflush(out);
}

long int stdJeff_readBool(FILE* f) {
	char buffer[32];
	if (f == 1) {
		fgets(buffer, 32, stdin);
	} else {
		fgets(buffer, 32, f);
	}
	if (strcmp(buffer, "true")) {
		return 1;
	} else {
		return 0;
	}
}

void stdJeff_writeInt(long int num, FILE* f) {
	if (f == 0) {
		fprintf(stdout, "%ld", num);
		fflush(stdout);
	} else {
		fprintf(f, "%ld", num);
		fflush(f);
	}
}

void stdJeff_writeString(const char * s, FILE* f) {
	if (f == 0) {
		fprintf(stdout, "%s", s);
		fflush(stdout);
	} else {
		fprintf(f, "%s", s);
		fflush(f);
	}
}

void stdJeff_writeBool(long int b, FILE* f) {
	if (f == 0) {
		if (b == 0) {
			fprintf(stdout, "%s", "false");
			fflush(stdout);
		} else {
			fprintf(stdout, "%s", "true");
			fflush(stdout);
		}
	} else {
		if (b == 0) {
			fprintf(f, "%s", "false");
			fflush(f);
		} else {
			fprintf(f, "%s", "true");
			fflush(f);
		}
	}
}

void printInt(long int num){
	fprintf(stdout, "%ld", num);
	fflush(stdout);
}

void printString(const char * str){
	fprintf(stdout, "%s", str);
	fflush(stdout);
}

int64_t getBool(){
	char c;
	scanf("%c", &c);
	getchar(); // Consume trailing newline
	if (c == '0'){
		return 0;
	} else {
		return 1;
	}
}

int64_t getInt(){
	char buffer[32];
	fgets(buffer, 32, stdin);
	long int res = atol(buffer);
	return res;
}
