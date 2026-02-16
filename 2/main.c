#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Circle {
	double x, y;
	double radius;
};

// x == y
int equal ( double x, double y ) { return fabs ( x - y ) <= 1000 * DBL_EPSILON * ( fabs(x) + fabs(y) ); }

// normalize 
double normalize ( double x, double lower_bound, double upper_bound ) {
	if ( x < lower_bound ) return lower_bound;
	else if ( x > upper_bound ) return upper_bound;
	return x;
}

int main () {
	struct Circle circle1, circle2;

	printf("Enter circle #1 parameters:\n");
	if ( scanf ( "%lf %lf %lf", &circle1 . x, &circle1 . y, &circle1 . radius ) < 3 ) {
		printf("Invalid input.\n");
		return EXIT_SUCCESS;
	}
	if ( circle1 . radius < 0 ) {
		printf("Invalid input.\n");
		return EXIT_SUCCESS;
	}

	printf("Enter circle #2 parameters:\n");
	if ( scanf ( "%lf %lf %lf", &circle2 . x, &circle2 . y, &circle2 . radius ) < 3 ) {
		printf("Invalid input.\n");
		return EXIT_SUCCESS;
	}

	if ( circle2 . radius < 0 ) {
		printf("Invalid input.\n");
		return EXIT_SUCCESS;
	}


	double distance_x = circle1 . x - circle2 . x;
	double distance_y = circle1 . y - circle2 . y;
	double distance = sqrt ( 
				pow ( distance_x, 2 ) 
				+ pow ( distance_y, 2 ) 
			);


	// External touch, no overlap.
	if ( equal (  circle1 . radius + circle2 . radius, distance ) ) { 
		printf( "External touch, no overlap.\n" );
		return EXIT_SUCCESS;
	}

	// Circles are identical
	if ( equal ( distance, 0.0 ) && equal ( circle1 . radius, circle2 . radius ) ) {
		printf ( "The circles are identical, " );
		printf( "overlap: %lf\n", M_PI * pow ( circle1 . radius, 2 ) );
		return EXIT_SUCCESS;
	}

	if ( equal (  distance, fabs ( circle1 . radius - circle2 . radius ) ) ) {
		printf ( "Internal touch, " );
		if ( circle1 . radius > circle2 . radius ) {
			printf ( "circle #2 lies inside circle #1, overlap: %lf\n", M_PI * circle2 . radius * circle2 . radius );
			return EXIT_SUCCESS;
		}
		if ( circle2 . radius > circle1 . radius ) {
			printf ( "circle #1 lies inside circle #2, overlap: %lf\n", M_PI * circle1 . radius * circle1 . radius );
			return EXIT_SUCCESS;
		}
	}

	if ( distance + circle1 . radius < circle2 . radius ) {
			printf ( "Circle #1 lies inside circle #2, overlap: %lf\n", M_PI * circle1 . radius * circle1 . radius );
			return EXIT_SUCCESS;
	}

	if ( distance + circle2 . radius < circle1 . radius ) {
			printf ( "Circle #2 lies inside circle #1, overlap: %lf\n", M_PI * circle2 . radius * circle2 . radius );
			return EXIT_SUCCESS;
	}

	// one cicle inside another
	if ( distance < circle1 . radius + circle2 . radius ) {
		double area1 =  ( pow( distance, 2 ) + pow( circle1 . radius, 2 ) - pow( circle2 . radius, 2 ) )  / ( 2 * distance * circle1 . radius );
		area1 = normalize( area1, -1.0, 1.0 );

		double area2 = ( pow( distance, 2 ) + pow( circle2 . radius, 2 ) - pow( circle1 . radius, 2 ) ) / ( 2 * distance * circle2 . radius ); 
		area2 = normalize( area2, -1.0, 1.0 );

		double tmp =  ( - distance + circle1 . radius + circle2 . radius ) * ( distance + circle1 . radius - circle2 . radius ) * ( distance - circle1 . radius + circle2 . radius ) * ( distance + circle1 . radius + circle2 . radius ); 
		tmp = tmp < 0 ? 0.0 : tmp;

		double result_area = pow ( circle1 . radius, 2 ) * acos ( area1 ) + pow ( circle2 . radius, 2 ) * acos ( area2 ) - sqrt ( tmp ) / 2;
		if ( equal( result_area, 0.0 ) ) {
			printf ( "The circles lie outside each other, no overlap.\n" );
			return EXIT_SUCCESS;
		}

		printf ( "The circles intersect, overlap: %lf\n", result_area );
		return EXIT_SUCCESS;
	}

	// one cicle is outsed from another
	if ( circle1 . radius + circle2 . radius < distance ) {
		printf ( "The circles lie outside each other, no overlap.\n" );
	}

	return EXIT_SUCCESS;
}
