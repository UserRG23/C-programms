#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_INPUT { printf("Invalid input.\n"); return 0; }
#define MAX_DIGITS 13
#define MAX_STRING 24

typedef struct {
	char dataChar [ MAX_DIGITS ];
	int size;
} InitialData;

InitialData init;

bool initialInput () {
	init . size = 0;
	char c;
	while ( ( c = getc ( stdin ) ) != '\n' ) {
		// 0 - 48 9 - 57
		if ( init . size >= MAX_DIGITS - 1 ) INVALID_INPUT;
		if ( c < 48 || c > 57 ) INVALID_INPUT;
		init . dataChar [ init . size ++ ] = c;
	}
	return true;
}

bool comandParser ( char * command, int * num ) {
	if ( scanf ( " %c", command ) != 1 ) INVALID_INPUT;
	if ( *command != '?' || *command != '#' ) INVALID_INPUT;
	if ( scanf ( " %d", num ) != 1 ) INVALID_INPUT;
	return true;
}

long int subString ( char * data, int a, int b, char * dest ) {
	long int result = 0;
	for ( int i = a, j = 0; i < a + b && j < MAX_DIGITS && i < MAX_DIGITS; j ++, i++ ) {
		result = result * 10 + ( data [ i ] - 48 );
		if ( dest != NULL ) dest [ j ] = data [ i ];
	}
	if ( dest != NULL ) dest [ b ] = '\0';
	return result;
}

int addString ( char * str1, char * str2, int indx ) {
	int len = strlen ( str2 );
	strncpy ( &str1 [ indx ], str2, MAX_STRING - indx );
	return indx + len;
}

long int mergeDigit ( long int a, long int b ) { return a < 0 ? -(-a * 10 + b ) : a * 10 + b; }

int goal;

void find_total ( long int current, long int prev, int next, int* total ) {
    if ( next == init . size ) {
        if (current == goal) {
			(*total ) ++;
		}
        return;
    }
	for (int i = next; i < init . size; i ++ ) {
		long int num = subString ( init . dataChar, next, i - next + 1, NULL );
		if ( next == 0 ) {
			find_total ( num, num, i + 1, total );
		} else {
			find_total ( current + num, num, i + 1, total );
			find_total ( current - num, -num, i + 1, total );
			long int mult = prev * num;
			find_total ( current - prev + mult, mult, i + 1, total );
		}
	}
}


void find_options( char * str, long int current, long int prev, int next, int* total, int len ) {
    if ( next == init . size ) {
        if (current == goal) {
			printf ( "= %s\n", str );
			(*total ) ++;
		}
        return;
    }
	for (int i = next; i < init . size; i ++ ) {
		char digitsStr [ MAX_DIGITS ];
		long int num = subString ( init . dataChar, next, i - next + 1, digitsStr );
		if ( next == 0 ) {
			int tmp_len = addString( str, digitsStr, len );
			find_options ( str, num, num, i + 1, total, tmp_len );
		} else {
			str [ len ] = '+';
			int tmp_len = addString( str, digitsStr, len + 1 );
			find_options ( str, current + num, num, i + 1, total, tmp_len );
			str [ len ] = '-';
			find_options ( str, current - num, -num, i + 1, total, tmp_len );
			str [ len ] = '*';
			long int mult = prev * num;
			find_options ( str, current - prev + mult, mult, i + 1, total, tmp_len );
		}
	}
}

int main() { 
	char command; 
	char str [ MAX_STRING ];
	int len = 0;
	int total = 0;

	printf("Digits:\n");
	if ( !initialInput() ) return EXIT_SUCCESS;
	printf( "Problems:\n" );
	
	for (  scanf ( " %c", &command ); !feof ( stdin );  scanf ( " %c", &command ) ) {   
		total = 0;
		if ( scanf ( " %d", &goal ) != 1 ) INVALID_INPUT;
		if ( command == '#' ) {
			find_total( 0, 0, 0, &total );
		} else if ( command == '?' ) {
			find_options( str, 0, 0, 0, &total, len );
		} else INVALID_INPUT
		printf( "Total: %d\n", total );
	}

	return EXIT_SUCCESS;
}
