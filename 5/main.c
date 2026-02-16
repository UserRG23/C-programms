#include <alloca.h>
#include <complex.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Maximum number of sections in bypass
#define MAX_BYPASS 10000 
// Maximum number of maintenance update
#define MAX_UPDATES 300000 
// Macro for invalid input
#define INVALID_INPUT { printf("Invalid input.\n"); \
					  return 0; } 

// Data structure for dates 
// Code from previous progtest
typedef struct TDate 
{
  unsigned       m_Year;
  unsigned short m_Month;
  unsigned short m_Day;
} TDATE;

TDATE makeDate ( unsigned       y,
                 unsigned short m,
                 unsigned short d )
{
  TDATE res = { y, m, d }; // Initialize date
  return res;
}

// ---------------------------------------------------------------------------
// Maintenance changes

typedef struct {
	TDATE date;
	unsigned int cost; // Maintenance cost
	unsigned int indx; // Index of bypass section affected
} ChangesCell;

typedef struct {
	ChangesCell data [ MAX_UPDATES ]; // All changes
	unsigned int size; // Number of changes stored
} Changes;

Changes changes;

// ---------------------------------------------------------------------------
// Result intervals 

typedef struct {
	unsigned int value;		// Difference value
	unsigned int from, to;  // Interval in bypass sections
} ResultCell;

typedef struct {
	ResultCell * data; // Dynamic array of results
	unsigned int size; // Number of results
} Result;

ResultCell createResult ( unsigned int value, 
						  unsigned int from,
						  unsigned int to ) {
	ResultCell tmp = { value, from, to }; // Initialize result interval
	return tmp;
}

// ---------------------------------------------------------------------------
// Bypass data

typedef struct {
	unsigned cost;       // Base daily cost
	unsigned changeSize; // Number of maintenance changes applied
	unsigned begin;      // Index in changes array where changes start
} Station;

Station createStation ( unsigned cost ) {
	Station result = { cost, 0, 0 }; // Initialize station with base cost
	return result;
}

typedef struct {
	Station data [ MAX_BYPASS ]; // Array of bypass sections
    unsigned size;				 // Number of sections used
    bool changed;				 // Flag if changes were applied
} Bypass;

Bypass bypass;

// ---------------------------------------------------------------------------------
// Date operations

// Compare if date a < b  
bool lessDate ( const TDATE a, const TDATE b ) {
 if (a.m_Year != b.m_Year) return a.m_Year < b.m_Year;
    if (a.m_Month != b.m_Month) return a.m_Month < b.m_Month;
    return a.m_Day < b.m_Day;
}

// Compare if date are equal
bool equalDate ( const TDATE a,
                  const TDATE b )
{
  return a . m_Year == b . m_Year
         && a . m_Month == b . m_Month
         && a . m_Day == b . m_Day;
}

// Check if year is leap or not 
bool isLeap ( unsigned y ) {
  return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && y % 4000 != 0;
}

// Max day in month
int maxDay( const TDATE date )
{
  const int day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ( isLeap( date.m_Year ) && date.m_Month == 2 ) return 29;
  return day [ date.m_Month - 1 ];
}

// Validate date
bool checkDate( const TDATE date )
{
	if (date.m_Year < 1900) return false;
    if (date.m_Month < 1 || date.m_Month > 12) return false;
    if (date.m_Day < 1 || date.m_Day > maxDay(date)) return false;
    return true;
}

// Count days between two dates inclusive
unsigned countDays ( TDATE from, TDATE to ) {
	if ( equalDate ( from, to ) ) return 1; // if dates are same 
	int days =  to . m_Day - from . m_Day; // Difference in days

	const unsigned short day [] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }; // Precalculated values for interval sum algorithm 
	from . m_Month --;
	to . m_Month --;
	// Check if month contains leap year February
	int leap1 = isLeap ( to . m_Year ) && to . m_Month >= 2 ? 1 : 0; 
	int leap2 = isLeap ( from . m_Year ) && from . m_Month >= 2 ? 1 : 0;
	// Interval sum algorithm from BIE-PA2
	int daysInMonths =  ( day [ to . m_Month ] + leap1 ) - ( day [ from . m_Month ] + leap2 );  

	unsigned yearDiff = to . m_Year - from . m_Year; // Difference in years
	from . m_Year --; 
	to . m_Year --; 
	// Amount of leap years
	unsigned leapYears = ( to . m_Year / 4 - from . m_Year / 4 ) - ( to . m_Year / 100 - from . m_Year / 100 ) 
					   + ( to . m_Year / 400 - from . m_Year / 400 ) - ( to . m_Year / 4000 - from . m_Year / 4000 );

	return days + daysInMonths + ( yearDiff * 365 ) + ( yearDiff == 0 ? 0 : leapYears )+ 1; // Total days
}

// --------------------------------------------------------------------------------
// Insert sort from BIE-PA1

void insertChanges ( ChangesCell cell ) {
	ChangesCell * data = changes . data;
	int i;
	for ( i = changes . size - 1; i >= 0 && data [ i ] . indx > cell . indx; i -- )
		data [ i + 1 ] = data [ i ]; // Shift right 
	data [ i + 1 ] = cell; // Insert new change
	changes . size ++;
}

// --------------------------------------------------------------------------------------------------------
// UI section

// Read array of daily costs for bypass sections
int readArray () {
	bypass . size = 0;
	char sign;
	int curr_cost; // Input cost
	if ( scanf ( " %c ", &sign ) != 1 || sign != '{' ) INVALID_INPUT; // Expect opening brace
	for ( int i = 0; i < MAX_BYPASS; i ++ ) {
		// Validate input
		if ( scanf ( " %d", &curr_cost ) != 1 ) INVALID_INPUT; // Read cost
		if ( curr_cost <= 0 ) INVALID_INPUT; // Must be positive 
		if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT; 
		if ( sign != ',' && sign != '}' ) INVALID_INPUT; // Expect comma or closing brace

		// Store data
		bypass . data [ i ] = createStation ( curr_cost );
		bypass . size++;

		if ( sign == '}' ) {
			if ( bypass . size < 2 ) INVALID_INPUT; // At least 2 sections required
			bypass . changed = false;
			return true;
		}
	}
	INVALID_INPUT
}

// Parse request command for interval  
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

	// Start date must be <= end date
	if ( lessDate ( *to, *from ) ) INVALID_INPUT;

	return true;
}

// Parse set command for maintenance update
bool parseSetCommand ( ChangesCell * cell ) {
	unsigned year;
	unsigned short day, month;
	if ( scanf ( " %u-%hu-%hu", &year, &month, &day ) != 3) INVALID_INPUT;
	cell -> date = makeDate( year, month, day );
	if ( !checkDate ( cell->date ) ) INVALID_INPUT; // Validate date

	if ( changes . size != 0 ) {
		// Dates must increase
		if ( lessDate( cell -> date, changes . data [ changes . size - 1 ] . date ) ) INVALID_INPUT;
		if ( equalDate( cell -> date, changes . data [ changes . size - 1 ] . date ) ) INVALID_INPUT;
	}

	int indx; // Section index
	if ( scanf ( " %d", &indx ) != 1 ) INVALID_INPUT; 
	if ( ( unsigned ) indx > bypass.size - 1 ) INVALID_INPUT; // Valid section index
	if ( indx < 0 ) INVALID_INPUT;;
	cell -> indx = indx;

	char sign; 
	if ( scanf ( " %c", &sign ) != 1 ) INVALID_INPUT; 
	if ( sign != ':' ) INVALID_INPUT; // Expect colon

	int value;
	if ( scanf ( " %d", &value ) != 1 ) INVALID_INPUT; 
	if ( value <= 0 ) INVALID_INPUT; // Cust must be positive
	cell -> cost = value;

	bypass . data [ indx ] . changeSize ++;
	bypass . changed = true;

	return true;
}

// Print result intervals
void resultOut ( const Result result ) {
	printf ( "Difference: %u, options: %u\n", result . data [0] . value, result . size );
	for ( unsigned i = 0; i < result . size; i ++ ) {
		printf ( "* %u - %u, ", result . data [ i ] . from, result . data [ i ] . to );
		unsigned restFrom = ( result . data [ i ] . to + 1 ) % ( bypass . size ); // Calculate where second interval starts
		unsigned restTo = result . data [ i ] . from; // Calculate where second interval ends
		restTo = restTo == 0 ? bypass . size - 1 : restTo - 1; // Wrap-around
		printf ( "%u - %u\n", restFrom, restTo );
	}
}
// --------------------------------------------------------------------------------------------------------
// Find result section

// Link each section to its first change in changes array
void findBegins () {
	Station * stations = bypass . data; // Copy pointer to array for easier usage
	ChangesCell * chCells = changes . data; // Copy pointer to array for easier usage

	for ( unsigned i = 0, curr = chCells [ i ] . indx; i < changes . size; i += stations [ curr ] . changeSize ) {
		curr = chCells [ i ] . indx;
		stations [ curr ] . begin = i;
	}
	bypass . changed = false;
}

// Binary search in changes array for a date 
unsigned binarySearch ( const TDATE date, int lo, int hi ) {
	unsigned mid = 0;
	while ( lo <= hi ) {
		mid = lo + ( hi - lo ) / 2;
		if ( lessDate( date, changes.data [ mid ].date ) ) hi = mid - 1;
		else if ( lessDate(  changes.data [ mid ].date, date ) ) lo = mid + 1;
		else return mid; // Match
	}
	return mid;
}

// Compute sum of daily costs for a section over interval
long unsigned sumDays ( unsigned indx, TDATE from, TDATE to ) {
	Station * sections = bypass . data;
	if ( sections [ indx ] . changeSize == 0 ) return sections [ indx ] . cost * countDays ( from, to );

	unsigned begin = sections [ indx ] . begin;
	unsigned end = sections [ indx ] . changeSize - 1 + begin;
	unsigned start = binarySearch ( from, begin, end );
	unsigned chVal = sections [ indx ] . cost;
	long unsigned result = 0;

	if ( begin < start ) start --;

	for ( unsigned int i = start; i <= end; i ++ ) {
		TDATE tmp = changes . data [ i ] . date;
		if ( lessDate ( tmp, from ) || equalDate ( tmp, from ) ) {
			chVal = changes . data [ i ] . cost; // Update cost at current date
			continue;
		}
		if ( lessDate ( to, tmp ) )  break; // Beyond interval
		result += chVal * ( countDays( from, tmp ) - 1 ); // Partial sum
		chVal = changes . data [ i ] . cost;
		from = tmp;
	}
	result += chVal * countDays ( from, to ); // Add remaining days
	return result;
}

// Sliding window to find intervals with minimal difference
void findIntervals ( const TDATE from, const TDATE to, Result * result ) {
	long int diff = 0;
	long unsigned sum, minDiff = INT_MAX, abs_diff;
	unsigned left = 0, right = 0;
	long unsigned total = 0;

	if ( bypass . changed ) findBegins(); // Recumpute begin indices

	for ( unsigned i = 0; i < bypass . size; i ++ ) 
		total += sumDays ( i, from, to); // Total sum

	sum = sumDays( left, from, to);
	while ( right < bypass . size - 1 ) {
		diff = sum - ( total - sum );
		abs_diff = labs ( diff );
		if ( abs_diff == minDiff ) 
			result -> data [ result -> size ++ ] = createResult( abs_diff, left, right ); // Another optimal interval
		if ( abs_diff < minDiff ) {
			result -> size = 0;
			result -> data [ result -> size ++ ] = createResult( abs_diff, left, right ); // New best interval
			minDiff = abs_diff;
		}
		if ( diff <= 0 ) sum += sumDays( ++right, from, to); 
		else sum -= sumDays( left++, from, to); 
		if ( left == right ) sum += sumDays( ++right, from, to); // Ensure window size > 0
	}
}

int main () {
	printf("Daily cost:\n");
	if ( !readArray() ) return 0; // Read bypass costs
	Result result;
	// Allocate result array
	result . data = (ResultCell*) malloc( sizeof( ResultCell ) * ( ( bypass . size / 2 ) * bypass . size) );
	TDATE from, to;
	ChangesCell cell;
	changes.size = 0;

	char sign;
	scanf ( " %c", &sign );
	for (; !feof(stdin); scanf ( " %c", &sign ) ) {
		switch ( sign ) { // Define type of the inserted command
			case '?':
				if ( !parseRequestCommand( &from, &to ) ) {
					free ( result . data );
					return 0;
				}
				findIntervals ( from, to, &result ); // Compute intervals
				resultOut ( result ); // Print intervals
				break;
			case '=':
				if ( !parseSetCommand ( &cell ) ) {
					free ( result . data );
					return 0;
				}
				insertChanges ( cell ); // Store new change
				break;
			default:
				free ( result . data );
				INVALID_INPUT;
				return 0;
		}
	}
	free ( result . data ); // Clean up
	return 0;
}
