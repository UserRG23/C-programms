#include <stdio.h>

void print_c ( char c, int count ) {
	for ( int i = 0; i < count; i++ ) {
		printf( "%c", c );
	}
}
void line ( int size ) {
	printf( "+" );
	print_c( '-', size );
	printf( "+\n" );
}

int main ( void ) {
	int board, field;
	printf("Enter chessboard size:\n");
	if ( scanf("%d\n", &board) != 1 ) {
		printf("Invalid input.\n");
		return 0;
	}
	if ( board <= 0 ) {
		printf("Invalid input.\n");
		return 0;
	}
	printf("Enter field width:\n");
	if ( scanf("%d\n", &field) != 1 ) {
		printf("Invalid input.\n");
		return 0;
	}
	if ( field <= 0 ) {
		printf("Invalid input.\n");
		return 0;
	}

	int size = board * field;

	line ( size );

	for ( int i = 0; i < board; i ++ ) {

		for ( int r = 0; r < field; r ++ ) {
			printf ( "|" );
			for ( int j = 0; j < board; j ++ ) {
				if ( ( i + j ) % 2 == 0 ) print_c( ' ', field );
				else print_c( 'X', field );
			}
			printf ( "|\n" );
		}
	}

	line(size);

	return 0;
}
