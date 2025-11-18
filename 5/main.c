#include <alloca.h>
#include <complex.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10001
#define MAX_UPDATES 300000
#define INVALID_INPUT { printf("Invalid input.\n"); \
					  return false; }

typedef struct {
	unsigned data [ MAX_SIZE ];
	unsigned size;
} Bypass;

Bypass bypass;

// Data structure for dates 
// Code from previous progtest
typedef struct TDate // dates valid from 1900-01-01
{
  unsigned       m_Year;
  unsigned short m_Month;
  unsigned short m_Day;
} TDATE;

// Create the date 
TDATE makeDate ( unsigned       y,
                 unsigned short m,
                 unsigned short d )
{
  TDATE res = { y, m, d };
  return res;
}

// Check date1 < date2 
bool lessDate ( const TDATE a, const TDATE b ) {
 if (a.m_Year != b.m_Year) return a.m_Year < b.m_Year;
    if (a.m_Month != b.m_Month) return a.m_Month < b.m_Month;
    return a.m_Day < b.m_Day;
}

// Chech date1 == date2
bool equalDate ( const TDATE a,
                  const TDATE b )
{
  return a . m_Year == b . m_Year
         && a . m_Month == b . m_Month
         && a . m_Day == b . m_Day;
}

// Check year is leap or not 
bool isLeap ( unsigned y ) {
  return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && y % 4000 != 0;
}

// Return max day in the month
int maxDay( const TDATE date )
{
  int day[] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ( isLeap( date.m_Year ) ) day[2] = 29;
  return day [ date.m_Month ];
}

// Check date
bool checkDate( const TDATE date )
{
	if (date.m_Year < 1900) return false;
    if (date.m_Month < 1 || date.m_Month > 12) return false;
    if (date.m_Day < 1 || date.m_Day > maxDay(date)) return false;
    return true;
}

// Date table
typedef struct {
	TDATE date;
	unsigned int value;
	unsigned int indx;
} ChangesCell;

typedef struct {
	ChangesCell data [ MAX_UPDATES ];
	unsigned int size;
} Changes;

Changes changes;

typedef struct {
	unsigned days;
	unsigned chVal;
	unsigned chIndx;
	unsigned elem;
} BufferCell;

BufferCell createBufferCell ( unsigned days, unsigned chVal, unsigned chIndx, unsigned elem ) {
	BufferCell tmp = { days, chVal, chIndx, elem };
	return tmp;
}

typedef struct {
	BufferCell * data;
	unsigned size;
} Buffer;

Buffer createBuffer ( unsigned start ) {
	Buffer result = {
	 ( BufferCell * ) malloc( sizeof ( BufferCell ) * ( ( changes . size - start ) + 1 ) ),
	 0
	};
	return result;
}

// Result intervals 
typedef struct {
	unsigned int value;
	unsigned int from, to;
} ResultCell;

typedef struct {
	ResultCell * data;
	unsigned int size;
} Result;

ResultCell createResult ( unsigned int value, 
					  unsigned int from,
					  unsigned int to ) {
	ResultCell tmp = { value, from, to };
	return tmp;
}

/*
 *  INVALID INPUT
 *  - missing curly braces or commas in the list of daily maintenance cost,
 *  - invalid daily maintenance cost (positive integer required),
 *  - less than 2 sections in the bypass,
 *  - more than 10000 sections in the bypass,
 *  - invalid format of the maintenance update (missing equality sign or colon),
 *  -? invalid date format (ISO format required),
 *  - invalid date (valid Gregorian date required),
 *  dates in maintenance updates must form an increasing sequence,
 *  invalid section in the maintenance cost update (0 or positive integer required, section number is limited by the bypass length),
 *  invalid daily maintenance cost (positive integer required),
 *  invalid format of the assignment command (missing question mark or dates),
 *  invalid date format (ISO format required),
 *  invalid date (valid Gregorian date required),
 *  invalid date interval in the assignment command (start date must be less than or equal to the end date).
*/

// --------------------------------------------------------------------------------------------------------
// UI section

int readArray () {
	bypass . data [ 0 ] = 0;
	bypass . size = 1;
	char sign;
	int curr_num;
	if ( scanf ( " %c ", &sign ) != 1 || sign != '{' ) INVALID_INPUT
	for ( int i = 1; i < MAX_SIZE; i ++ ) {
		// Check for invalid input
		if ( scanf ( " %d", &curr_num ) != 1 ) INVALID_INPUT 
		if ( curr_num < 0 ) INVALID_INPUT
		if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT
		if ( sign != ',' && sign != '}' ) INVALID_INPUT

		// Store specific data
		bypass . data [ i ] = bypass . data [ i - 1 ] + curr_num;
		bypass . size++;

		if ( sign == '}' ) {
			if ( bypass . size < 3 ) INVALID_INPUT 
			return true;
		}
	}
	INVALID_INPUT
}

bool parseRequestCommand ( TDATE * from, TDATE * to ) {
	unsigned year;
	unsigned short day, month;
	// Parse first date
	if ( scanf ( " %u-%hu-%hu", &year, &month, &day ) != 3) INVALID_INPUT;
	*from = makeDate( year, month, day );
	if ( !checkDate ( *from ) ) INVALID_INPUT;

	// Parse second date
	if ( scanf ( " %u-%hu-%hu", &year, &month, &day ) != 3 ) INVALID_INPUT;
	*to = makeDate( year, month, day );
	if ( !checkDate ( *to ) ) INVALID_INPUT;

	// if from > to then invalid input
	if ( lessDate ( *to, *from ) ) INVALID_INPUT;

	return true;
}

bool parseSetCommand ( ChangesCell * cell ) {
	unsigned year;
	unsigned short day, month;
	if ( scanf ( " %u-%hu-%hu", &year, &month, &day ) != 3) INVALID_INPUT;;
	cell -> date = makeDate( year, month, day );
	if ( !checkDate ( cell->date ) ) INVALID_INPUT;;
	if ( changes . size != 0 ) {
		if ( lessDate( cell -> date, changes . data [ changes . size - 1 ] . date ) ) INVALID_INPUT;;
		if ( equalDate( cell -> date, changes . data [ changes . size - 1 ] . date ) ) INVALID_INPUT;;
	}

	int tmp;
	if ( scanf ( " %d", &tmp ) != 1 ) INVALID_INPUT;; 
	if ( ( unsigned ) tmp > bypass.size - 1 ) INVALID_INPUT;;
	if ( tmp < 0 ) INVALID_INPUT;;
	cell -> indx = tmp;

	char sign;
	if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT; 
	if ( sign != ':' ) INVALID_INPUT; 

	if ( scanf ( " %d", &tmp ) != 1 ) INVALID_INPUT; 
	if ( tmp < 0 ) INVALID_INPUT;
	cell -> value = tmp;

	return true;
}

void resultOut ( const Result result ) {
	printf ( "Difference: %u, options: %u\n", result . data [0] . value, result . size );
	for ( unsigned i = 0; i < result . size; i ++ ) {
		printf ( "* %u - %u, ", result . data [ i ] . from, result . data [ i ] . to );
		unsigned restFrom = ( result . data [ i ] . to + 1 ) % (bypass . size - 1); 
		unsigned restTo = result . data [ i ] . from; 
		restTo = restTo == 0 ? bypass . size - 2 : restTo - 1;
		printf ( "%u - %u\n", restFrom, restTo );
	}
}
// --------------------------------------------------------------------------------------------------------


unsigned countDays ( TDATE from, TDATE to ) {
	if ( equalDate ( from, to ) ) return 1;
	int days =  to . m_Day - from . m_Day;

	const unsigned short day [] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	from . m_Month --;
	to . m_Month --;
	int leap1 = isLeap ( to . m_Year ) && to . m_Month >= 2 ? 1 : 0; 
	int leap2 = isLeap ( from . m_Year ) && from . m_Month >= 2 ? 1 : 0;
	int daysInMonths =  ( day [ to . m_Month ] + leap1 ) - ( day [ from . m_Month ] + leap2 );  

	unsigned yearDiff = to . m_Year - from . m_Year;
	from . m_Year --; 
	unsigned leapYears = ( to . m_Year / 4 - from . m_Year / 4 ) - ( to . m_Year / 100 - from . m_Year / 100 ) 
					   + ( to . m_Year / 400 - from . m_Year / 400 ) - ( to . m_Year / 4000 - from . m_Year / 4000 );

	return days + daysInMonths + ( yearDiff * 365 ) + ( yearDiff == 0 ? 0 : leapYears )+ 1;
}

unsigned find ( Buffer * buff, unsigned chIndx ) {
	for ( int buffi = buff -> size - 1; buffi >= 0; buffi -- )
		if ( buff -> data [ buffi ] . chIndx == chIndx )  
			return buff -> data [ buffi ] . chVal; 
	return ( bypass . data [ chIndx + 1 ] - bypass . data [ chIndx ] );
}


// Amount of days between two dates
unsigned totalSumDays ( TDATE from,
		   TDATE to,
		   unsigned indx,
		   Buffer * buff,
		   unsigned sum ) {

	unsigned * sections = bypass . data;
	unsigned result = 0;
	unsigned chVal = sections [ 1 ] - sections [ 0 ], chIndx = 0, elem = chVal;
	unsigned daysAmount;

	if ( indx > 0 ) indx --;
	for ( unsigned i = indx; i < changes . size; i ++ ) {
		TDATE tmp = changes . data [ i ] . date;
		if ( lessDate ( tmp, from ) || equalDate ( tmp, from ) ) {
			chIndx = changes . data [ indx ] . indx;
			chVal = changes . data [ indx ] . value;
			elem = ( sections [ chIndx + 1 ] - sections [ chIndx ] );
			sum = sum - elem + chVal;
			result += sum;
			buff -> data [ buff -> size ++ ] = createBufferCell ( daysAmount, chVal, chIndx, elem );
			continue;
		}

		if ( lessDate ( to, tmp ) ) break;

		daysAmount = countDays( from, tmp ) - 1;
		sum = sum - elem + chVal;
		result += sum * daysAmount;
		buff -> data [ buff -> size ++ ] = createBufferCell ( daysAmount, chVal, chIndx, elem );


		chIndx = changes . data [ i ] . indx;
		chVal = changes . data [ i ] . value;
		elem = find ( buff, chIndx );
		from = tmp;
	}

	daysAmount = countDays( from, to );
	sum = sum - elem + chVal;
	result += sum * daysAmount;
	buff -> data [ buff -> size ++ ] = createBufferCell ( daysAmount, chVal, chIndx, elem );
	return result;
}


void sumDays ( unsigned * sum,
			   unsigned left, 
			   unsigned right,
			   Buffer buff ) {
	unsigned result = 0;
	BufferCell * cell;
	for ( unsigned i = 0; i < buff . size; i ++ ) {
		cell = &buff . data [ i ];
		if ( cell -> chIndx >= left && cell -> chIndx <= right - 1 ) 
			*sum = *sum - cell -> elem + cell -> chVal;
		result += *sum * cell -> days;
	}
	*sum = result;
}

unsigned binarySearch ( const TDATE date ) {
	unsigned lo = 0, hi = changes.size - 1, mid;
	while ( lo <= hi ) {
		mid = lo + ( hi - lo ) / 2;
		if ( hi == 0 ) return 0;
		if ( lessDate( date, changes.data [ mid ].date ) ) hi = mid - 1;
		else if ( lessDate(  changes.data [ mid ].date, date ) ) lo = mid + 1;
		else return mid;
	}
	return mid;
}

void findIntervals ( const TDATE from, const TDATE to, Result * result ) {
	int diff = 0;
	unsigned sum = 0;
	unsigned left = 0, right = 1, minDiff = INT_MAX, abs_diff;
	unsigned startDate = 0;

	if ( changes . size != 0 ) startDate = binarySearch( from );
	Buffer buff = createBuffer ( startDate );

	unsigned total = totalSumDays ( from, to, startDate, &buff, bypass . data [ bypass . size - 1 ] );

	while ( right < bypass . size - 1 ) {
		sum = bypass . data [ right ] - bypass . data [ left ];
		sumDays ( &sum, left, right, buff );

		diff = sum - ( total - sum );
		abs_diff = abs ( diff );
		if ( abs_diff == minDiff ) {
			result -> data [ result -> size ++ ] = createResult( abs_diff, left, right - 1 );
		}
		if ( abs_diff < minDiff ) {
			result -> size = 0;
			result -> data [ result -> size ++ ] = createResult( abs_diff, left, right - 1 );
			minDiff = abs_diff;
		}
		if ( diff <= 0 ) right ++;
		if ( diff > 0 ) left ++; 
		if ( left == right ) right ++;
	}
	free ( buff.data );
}

void addDate ( const ChangesCell cell ) { changes . data [ changes . size ++ ] = cell; }

int main () {
	printf("Daily cost:\n");
	if ( !readArray() ) return 0;
	Result result;
	result . data = (ResultCell*) malloc( sizeof( ResultCell ) * ( ( bypass . size / 2 ) * bypass . size) );
	TDATE from, to;
	ChangesCell cell;
	changes.size = 0;

	char sign;
	scanf ( " %c", &sign );
	for (; !feof(stdin); scanf ( " %c", &sign ) ) {
		switch ( sign ) {
			case '?':
				if ( !parseRequestCommand( &from, &to ) ) {
					free ( result . data );
					return 0;
				}
				findIntervals ( from, to, &result );
				resultOut ( result );
				break;
			case '=':
				if ( !parseSetCommand ( &cell ) ) {
					free ( result . data );
					return 0;
				}
				addDate ( cell );
				break;
			default:
				INVALID_INPUT;
				free ( result . data );
				return 0;
		}
	}
	free ( result . data );
	return 0;
}
