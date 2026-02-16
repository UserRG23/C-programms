#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_INPUT { printf("Invalid input.\n"); return 0; }
#define MAX_BUFF 1024

typedef struct {
	char * str;
	double frq;
} Cell;

typedef struct {
	Cell * cells;
	size_t size;
	size_t capacity;
} MainData;

MainData data;

bool insertStr ( char * input, Cell * curr, size_t len ) {
	size_t counter = 0;
	if ( len == 0 ) return false;
	curr -> str = ( char * ) malloc ( len );
	for ( size_t i = 0; i < len; i ++ ) {
		if ( input [ i ] == '\0' ) {
			curr -> str [ i ] = input [ i ]; 
			break;
		}
		if ( input [ i ] != 'A' && input [ i ] != 'G' && input [ i ] != 'C' && input [ i ] != 'T' ) return false;
		curr -> str [ i ] = input [ i ];
		counter ++;
	}
	if ( counter % 3 != 0 ) return false;
	return true;
}

bool check_dna ( char * input, size_t size ) {
	size_t counter = 0;
	for ( size_t i = 0; i < size; i ++ ) {
		if ( input [ i ] == '\0' ) break;
		if ( input [ i ] != 'A' && input [ i ] != 'G' && input [ i ] != 'C' && input [ i ] != 'T' ) return false;
		counter ++;
	}
	if ( counter % 3 != 0 ) return false;
	return true;
}

bool find ( const char *curr, const char *elem ) {
    size_t curr_len = strlen ( curr );
    size_t elem_len = strlen ( elem );

    if (elem_len > curr_len) return 0;

    for ( size_t i = 0; i + elem_len <= curr_len; i += 3 )
        if ( memcmp( curr + i, elem, elem_len ) == 0 )
            return true;
    return false;
}

void deleteAll () {
	for ( size_t i = 0; i < data . size; i ++ ) free ( data . cells [ i ] . str );
	free( data . cells );
}

int cmp ( const void *a, const void *b ) {
    const Cell *A = ( const Cell* ) a;
    const Cell *B = ( const Cell* ) b;
    if ( A -> frq > B -> frq ) return -1;
    if ( A -> frq < B -> frq ) return 1;
    return 0;
}

int main () {
	printf( "DNA database:\n" );
	size_t strcap = 0;
	size_t strlen;
    char *buff;

	data . size = 0;
	data . capacity = 0;

	char *rest;
	while ( ( strlen = getline ( &buff, &strcap, stdin ) ) != ( size_t ) EOF ) {
		if ( buff [ strlen - 1 ] == '\n' ) buff [ strlen - 1 ] = '\0';
		if ( buff [ 0 ] == '\0' ) break;

		double frq = strtod( buff, &rest );
		if ( buff == rest ) {
			free ( buff );
			deleteAll ();
			INVALID_INPUT;
		}
		if ( rest [ 0 ] != ':' ) {
			free ( buff );
			deleteAll();
			INVALID_INPUT;
		}
		if ( data . capacity == 0 ) {
			data . cells = ( Cell * ) malloc ( 4 * sizeof ( Cell )  );
			data . capacity = 4;
		}
		if ( data . capacity == data . size ) {
			data . capacity *= 2;
			Cell * tmp = ( Cell * ) realloc ( data . cells, data . capacity * sizeof ( Cell ) );
			data . cells = tmp;
		}
		data . cells [ data . size ++ ] . frq = frq;
		if ( !insertStr( rest + 1, &data . cells [ data . size - 1 ], strlen - ( rest - buff ) ) ) {
			free ( buff );
			INVALID_INPUT;
		}
	}

	if ( data . size == 0 ) {
		free ( buff );
		deleteAll ();
		INVALID_INPUT;
	}
	qsort( data . cells, data . size, sizeof ( Cell ), cmp );
	printf( "Searches:\n" );

	size_t resultSize = 0;
	Cell **result = ( Cell ** ) malloc ( 50 * sizeof ( Cell * ) );
	while ( ( strlen = getline ( &buff, &strcap, stdin ) ) != ( size_t ) EOF ) {
		if ( strlen > 0 && buff [ strlen - 1 ] == '\n' ) buff [ strlen - 1 ] = '\0';
		if ( buff [ 0 ] == '\0' ) {
			deleteAll ();
			free ( buff );
			free ( result );
			INVALID_INPUT;
		}
		if ( !check_dna( buff, strlen ) ) {
			free ( buff );
			free ( result );
			deleteAll ();
			INVALID_INPUT;
		}
		resultSize = 0;
        for ( size_t i = 0; i < data . size ; i++ ) {
            if ( find ( data . cells [ i ] . str, buff ) ) {
				if ( resultSize == 50 ) break;
                result [ resultSize++ ] = &data . cells [ i ] ;
            }
        }

		printf( "Found: %zu\n", resultSize );
        for ( size_t i = 0; i < resultSize; i ++ )
            printf ( "> %s\n", result [ i ] -> str );
	}

	free ( result );
	free ( buff );
	deleteAll ();

	return 0;
}
