#include <stdio.h>

struct Time {
	int h, m, s, ms;
};

int main ( void ) {
	struct Time t1, t2;
	struct Time result;
	
	printf ( "Enter time t1:\n" );

	if ( 4 != scanf ( " %d : %d : %d , %d ", &t1 . h, &t1 . m, &t1 . s, &t1 . ms ) ) {
		printf ( "Invalid input.\n" );
		return 0;
	}
	

	if ( t1 . ms >= 1000 || t1 . ms < 0 ||
		 t1 . s >= 60 || t1 . s < 0 ||
		 t1 . m >= 60 || t1 . m < 0 ||
		 t1 . h >= 24 || t1 . h < 0 ) {
		printf ( "Invalid input.\n" );
		return 0;
	}

	printf ( "Enter time t2:\n" );
	if ( 4 != scanf ( " %d : %d : %d , %d ", &t2 . h, &t2 . m, &t2 . s, &t2 . ms ) ) {
		printf ( "Invalid input.\n" );
		return 0;
	}

	if ( t2 . ms >= 1000 || t2 . ms < 0 ||
		 t2 . s >= 60 || t2 . s < 0 ||
		 t2 . m >= 60 || t2 . m < 0 ||
		 t2 . h >= 24 || t2 . h < 0 ) {
		printf ( "Invalid input.\n" );
		return 0;
	}

	
	if ( t1 . ms > t2 . ms ) {
		result . ms = 1000 + t2 . ms - t1 . ms;
		t2 . s --;
	} else {
		result . ms = t2 . ms - t1 . ms;
	}

	if ( t1 . s > t2 . s ) {
		result . s = 60 + t2 . s - t1 . s;
		t2 . m --;
	} else {
		result . s = t2 . s - t1 . s;
	}

	if ( t1 . m > t2 . m ) {
		result . m = 60 + t2 . m - t1 . m;
		t2 . h --;
	} else {
		result . m = t2 . m - t1 . m;
	}

	if ( t1 . h > t2 . h ) {
		printf ( "Invalid input.\n" );
		return 0;
	} else {
		result . h = t2 . h - t1 . h;
	}

	printf ( "Duration: %2.1d:%.2d:%.2d,%.3d\n", result . h, result . m, result . s, result . ms );

	return 0;
}
