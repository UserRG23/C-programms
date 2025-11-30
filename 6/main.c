#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 1001
#define INVALID_INPUT { printf("Invalid input.\n"); \
						return 0; }

typedef struct 
{
  unsigned short m_Month;
  unsigned short m_Day;
  unsigned short m_Hour;
  unsigned short m_Minute;
} TTime;

bool  equalDate ( TTime a,
                  TTime b )
{
  return a . m_Month == b . m_Month
         && a . m_Day == b . m_Day 
		 && a . m_Hour == b . m_Hour
		 && a . m_Minute == b . m_Minute;
}

bool lessDate ( TTime a, TTime b ) {
    if (a.m_Month != b.m_Month) return a.m_Month < b.m_Month;
    if ( a . m_Day != b . m_Day ) return a.m_Day < b.m_Day;
    if ( a . m_Hour != b . m_Hour ) return a.m_Hour < b.m_Hour;
    return a.m_Minute < b.m_Minute;
}

int maxDay( const unsigned short m_Month )
{
  int day[] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return day [ m_Month ];
}

bool checkDay( unsigned short m_Month, unsigned short m_Day )
{
    if (m_Day < 1 || m_Day > maxDay ( m_Month ) )return false;
    return true;
}

bool makeDate ( int m, int d, int h, int min,
				TTime * date )
{
  if ( d < 1 || d > maxDay ( m ) ) return false;
  if ( h < 0 || h > 23 ) return false;
  if ( min < 0 || min > 59 ) return false;
  date -> m_Day = d;
  date -> m_Month = m;
  date -> m_Hour = h;
  date -> m_Minute = min;
  return true;
}

typedef struct {
	int* camera_id;
	unsigned capacity;
	unsigned size;
	TTime date;
} Spoted;

// Car rz with Spoted
typedef struct {
	char rz [ MAX_STR ];
	Spoted * spoted;
	unsigned cap;
	unsigned size;
} TCar;

// 2d array 
typedef struct {
	TCar * cars;
	unsigned size;
	unsigned cap;
} MainData;

MainData data;

static char decoder [][ 4 ] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
int decode_month ( char * str ) {
	for ( int i = 0; i < 12; i ++ ) {
		if ( strcmp ( str, decoder [ i ] ) == 0 ) return i + 1;
	}
	return 13;
}

char * incode_month ( int month ) { return decoder [ month - 1 ]; }

int parse_date ( TTime * date ) {
	static char month [ 4 ];
	int day;
	int hour;
	int minute;
	char sign;
	if ( scanf ( " %3s ", month ) != 1 ) return 0;
	int month_num = decode_month( month );
	if ( month_num == 13 ) return 0;
	if ( scanf ( " %d", &day ) != 1 ) return 0;
	if ( scanf ( " %d", &hour ) != 1 ) return 0;
	if ( scanf ( " %c", &sign ) != 1 ) return 0;
	if ( sign != ':' ) return 0;
	if ( scanf ( " %d", &minute ) != 1 ) return 0;
	if ( !makeDate( month_num, day, hour, minute, date ) ) return 0;
	return true;
}

// -------------------------------------------------------------

typedef struct NODE {
	TCar value;
	struct NODE * left;
	struct NODE * right;
	int leftCount;
	int rightCount;
} Node;

Node * first;

int max ( const int a, const int b ) {
	return a > b ? a : b;
}

void calculateRight ( Node * root ) {
	if ( root -> right == NULL ) root -> rightCount = 0;
	else root -> rightCount = max ( root -> right -> leftCount, root -> right -> rightCount ) + 1;
}

void calculateLeft ( Node * root ) {
	if ( root -> left == NULL ) root -> leftCount = 0;
	else root -> leftCount = max ( root -> left -> leftCount, root -> left -> rightCount ) + 1; 
}

Node* rotateRight ( Node * r ) {
	Node * tmp = r -> left;
	r -> left = tmp -> right;
	calculateLeft ( r );
	tmp -> right = r;
	calculateRight( tmp );
	return tmp;
}

Node* rotateLeft ( Node * r ) {
	Node * tmp = r -> right;
	r -> right = tmp -> left;
	calculateRight( r );
	tmp -> left = r;
	calculateLeft( tmp );
	return tmp;
}


Node* balance ( Node * r ) {
	if ( r -> rightCount - r -> leftCount < -1 ) {
		if ( r -> left == NULL ) r = rotateRight( r );
		else if ( r -> left -> rightCount - r -> left -> leftCount <= 0 ) r = rotateRight( r );
		else {
			r -> left = rotateLeft( r -> left );
			r = rotateRight( r );
		}
	}
	if ( r -> rightCount - r -> leftCount > 1 ) {
		if ( r -> right == NULL ) r = rotateLeft( r );
		else if ( r -> right -> rightCount - r -> right -> leftCount >= 0 ) r = rotateLeft( r );
		else {
			r -> right = rotateRight( r -> right );
			r = rotateLeft( r );
		}
	}
	return r;
}


Node * createNode ( const char * str ) {
	Node * newNode = ( Node * ) malloc ( sizeof ( Node ) );
	unsigned copysize = strlen( str ) + 1;
	strncpy ( newNode -> value . rz, str, copysize );
	newNode -> value . cap = 1;
	newNode ->  value . size = 0;
	newNode ->  value . spoted = ( Spoted * ) malloc( sizeof ( Spoted ) );

	newNode ->  left = NULL;
	newNode ->  right = NULL;
	newNode ->  leftCount = 0;
	newNode ->  rightCount = 0;
	return newNode;
}

Node * insertAVL ( Node * r, const char * value, Node ** result ) {
	if ( r == NULL ) {
		*result = createNode ( value );
		return *result;
	}
	unsigned cmp = strcmp( value, r -> value . rz ); 
	if ( cmp < 0) {
		r -> left = insertAVL( r -> left, value, result );
		calculateLeft( r );
	} else if ( cmp > 0 ) {
		r -> right = insertAVL( r  -> right, value, result ); 
		calculateRight( r );
	} else *result = r; 
	r = balance( r );
	return r;
}

Node * findAVL ( Node * r, const char * value ) {
	if ( r == NULL ) return NULL;
	unsigned cmp = strcmp( value, r -> value . rz ); 
	if ( cmp < 0 ) return findAVL( r -> left, value );
	if ( cmp > 0 ) return findAVL( r -> right, value );
	return r;
}

void deleteSpoted ( Node * root ) {
	for ( unsigned i = 0; i < root -> value . size; i ++ )
		free ( root -> value . spoted [ i ] . camera_id );
	free (root -> value . spoted);
}

void deleteAVL ( Node * root ) {
	if ( root == NULL ) return;
	deleteAVL( root -> left );
	deleteAVL( root -> right );
	deleteSpoted( root );
	free (root );
}

// -----------------------------------------------------------------

unsigned binarySearch ( const TCar * curr, const TTime date ) {
	int lo = 0;
	int hi = curr -> size - 1;
	unsigned mid = 0;
	while ( lo <= hi ) {
		mid = lo + ( hi - lo ) / 2;
		if ( lessDate( date, curr -> spoted [ mid ].date ) ) hi = mid - 1;
		else if ( lessDate(  curr -> spoted [ mid ].date, date ) ) lo = mid + 1;
		else return mid;
	}
	return mid;
}

void insertSort ( Spoted * cell, int indx, TCar * curr ) {
	int i = curr -> size == 0 ? -1 : curr -> size - 1;
	for ( ; i >= 0 && i >= indx; i -- ) 
		curr -> spoted [ i + 1 ] = curr -> spoted [ i ];
	curr -> spoted [ i + 1 ] = *cell;
	curr -> size ++;
}

void insertCam ( int cell, Spoted * curr ) {
	int i = curr -> size == 0 ? -1 : curr -> size - 1;
	for ( ; i >= 0 && curr -> camera_id [ i ] > cell; i -- ) 
		curr -> camera_id [ i + 1 ] = curr -> camera_id [ i ];
	curr -> camera_id [ i + 1 ] = cell;
	curr -> size ++;
}

void insertSpoted ( TCar * curr, TTime date, unsigned camera_id ) {
	
	if ( curr -> cap <= curr -> size ) {
		curr -> cap *= 2;
		curr -> spoted = ( Spoted * ) realloc ( curr -> spoted, curr -> cap * sizeof ( Spoted ) );
	}

	unsigned indx = binarySearch ( curr, date );
	Spoted * spoted = &curr -> spoted [ indx ];
	if ( equalDate ( spoted -> date, date ) ) {
		if ( spoted -> capacity == spoted -> size ) {
			spoted -> capacity *= 2;
			spoted -> camera_id = ( int * ) realloc ( spoted -> camera_id, spoted -> capacity * sizeof ( int ) );
		}
		spoted -> camera_id [ spoted -> size ++ ] = camera_id;
	} else {
		Spoted cell;
		cell . camera_id = ( int * ) malloc ( sizeof ( int ) );
		cell . camera_id [ 0 ] = camera_id;
		cell . capacity = 1;
		cell . size = 1;
		cell  . date = date;
		insertSort ( &cell, indx, curr );
	}
}

void insertRZ ( char * rz, TTime date, int camera_id ) {
	Node * curr;
	first = insertAVL ( first, rz, &curr );
	insertSpoted( &curr -> value, date, camera_id );
}

// -------------------------------------------------------------------

void result_out ( Spoted * spoted ) {
	printf ( "%s ", incode_month( spoted -> date .  m_Month  ) );
	printf ( "%d ", spoted -> date . m_Day );
	printf ( "%d:%d, ", spoted -> date . m_Hour, spoted -> date . m_Minute );

	printf( "%dx [", spoted -> size );
	for ( unsigned i = 0; i < spoted -> size; i ++ ) {
		printf( "%d", spoted -> camera_id [ i ] );
		if ( i != spoted -> size - 1 ) 
			printf(", ");
	}
	printf( "]\n" );
}

void findResult ( TTime date, char * rz ) {
	Node * curr = findAVL ( first, rz );
	if ( curr == NULL ) {
		printf( "> Car not found.\n" );
		return;
	}
	unsigned result = binarySearch( &curr -> value, date );
	
	if ( equalDate ( curr -> value . spoted [ result ] . date, date ) ) {
		printf ( "> Exact: " );
		result_out ( &curr -> value . spoted [ result ] );
		return;
	}

	printf( "> Previous: " );
	if ( result == 0 && lessDate ( date, curr -> value . spoted [ result ] . date ) ) {
		printf( "N/A\n" );
	} else {
		result_out ( &curr -> value . spoted [ result - 1 ] );
	}

	printf("> Next: ");
	if ( result == curr -> value . size - 1 && 
		 lessDate ( curr -> value . spoted [ result ] . date, date ) ) {
		printf( "N/A\n" );
	} else {
		result_out ( &curr -> value . spoted [ result ] );
	}
}

// --------------------------------------------------------------------

int parse_reports () {
	data . size = 0;
	data . cap = 2;
	data . cars = ( TCar * ) malloc ( sizeof ( TCar ) * data . cap );
	char sign;
	char rz [ MAX_STR ];
	TTime date;
	int camera_id;
	if ( scanf ( " %c ", &sign ) != 1 || sign != '{' ) INVALID_INPUT;
	while ( sign != '}' ) {
		// Check for invalid input
		if ( scanf ( " %d", &camera_id ) != 1 ) INVALID_INPUT;
		if ( camera_id <= 0 ) INVALID_INPUT;
		if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT;
		if ( sign != ':' ) INVALID_INPUT;

		if ( scanf ( " %1000s ", rz ) != 1 ) INVALID_INPUT;
		if ( !parse_date( &date ) ) INVALID_INPUT;

		if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT;
		if ( sign != ',' && sign != '}' ) INVALID_INPUT;
		insertRZ( rz, date, camera_id );
	}
	return 1;
}

int parse_search_command ( char * str, TTime * date ) {
	if ( scanf ( " %1000s ", str ) != 1 ) INVALID_INPUT;
	if ( !parse_date( date ) ) INVALID_INPUT;
	return 1;
}


int main () {
	printf( "Camera reports:\n");
	if ( !parse_reports() ) return 0;
	printf( "Search:\n");
	TTime input_date;
	char input_string [ MAX_STR ];
	while ( !feof ( stdin ) ) {
		if ( !parse_search_command( input_string, &input_date ) ) {
			deleteAVL(first);
			return 0;
		}
		findResult ( input_date, input_string );
	}
	return 0;
}
