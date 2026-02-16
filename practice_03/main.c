#include <stdio.h>
#include <string.h>

int main ( void ) {
	int x, y, z;
	char rgb [ 4 ];
	char b1, b2, c1, c2;
	printf ( "Type color in RGB format:\n" );
	if ( scanf ( " %3s %c %d %c %d %c %d %c", rgb, &b1, &x, &c1, &y, &c2, &z, &b2 ) < 4 ) {
		printf ( "Invalid input.\n" );
		return 0;
	}
	if ( b1 != '(' || c1 != ',' || c2 != ',' || b2 != ')' ) {
		printf ( "Invalid input.\n" );
		return 0;
	}

	if ( strcmp ( rgb, "rgb" ) != 0 ) {
		printf ( "Invalid input.\n" );
		return 0;
	}

	if ( ( x > 255 || x < 0 ) ||
	     ( y > 255 || y < 0 ) ||
	     ( z > 255 || z < 0 ) ) {
		printf ( "Invalid input.\n" );
		return 0;
	}
		 

	printf ( "#%.2X%.2X%.2X\n", x, y, z );
	// printf ( "x=%d, y=%d, z=%d, result=%d\n", x, y, z, result );

	return 0;
}
