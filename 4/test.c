#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
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
  TDATE res = { y, m, d };
  return res;
}
bool  equalDate ( TDATE a,
                  TDATE b )
{
  return a . m_Year == b . m_Year
         && a . m_Month == b . m_Month
         && a . m_Day == b . m_Day;
}
#endif /* __PROGTEST__ */


bool lessDate ( TDATE a, TDATE b ) {
 if (a.m_Year != b.m_Year) return a.m_Year < b.m_Year;
    if (a.m_Month != b.m_Month) return a.m_Month < b.m_Month;
    return a.m_Day < b.m_Day;
}

// ------------------------------------------------------------------------

void nextMonth ( TDATE * date ) {
	date->m_Month++;
    if (date->m_Month > 12) {
        date->m_Month = 1;
        date->m_Year++;
    }
}

// ------------------------------------------------------------------------

void prevMonth ( TDATE * date ) {
	date->m_Month --;
	if ( date->m_Month == 0 ) {
		date->m_Month = 12;
		date->m_Year --;
	}
}

// ------------------------------------------------------------------------

void nearest13 ( TDATE * date ) {
	if (date->m_Day > 13)
        nextMonth(date);
    date->m_Day = 13;
}

// ------------------------------------------------------------------------

bool isLeap ( int y ) {
  return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && y % 4000 != 0;
}

// ---------------------------------------------------------------------------

int maxDay( const TDATE * date )
{
  int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (isLeap( date->m_Year )) day[1] = 29;

  return day[date->m_Month - 1];
}

//------------------------------------------------------------

bool checkDate( TDATE * date )
{
	if (date->m_Year < 1900) return false;
    if (date->m_Month < 1 || date->m_Month > 12) return false;
    if (date->m_Day < 1 || date->m_Day > maxDay(date)) return false;
    return true;
}

//------------------------------------------------------------

short dayOfWeek ( TDATE date ) {
	unsigned long long y = date.m_Year;
    unsigned long long m = date.m_Month;
    unsigned long long d = date.m_Day;

    if (m < 3) {
        m += 12;
        y--;
    }

    unsigned long long k = y % 100;
    unsigned long long j = y / 100;

    unsigned long long int h = (d + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) + 5 * j) % 7;
    return (h + 6) % 7; 
}

// -------------------------------------------------

bool countFriday13 ( TDATE from, TDATE to, long long int * cnt )
{
	/* Formula to compute the day of the week:
	*    (q + ((13 * (m + 1)) / 5) + K + (K/4) + (J/4) + 5*J )%7 -> day of the week
	*
	*    q -> day of the month 
	*    m -> month ( January = 13, February = 14, everything else is the same ) 
	*    K -> century 
	*    J -> year of the century
	*/
	
	// Validate date
	if ( !checkDate ( &from ) 
	  || !checkDate( &to ) 
	  || lessDate( to, from ) )
		return false;

	// nearest 13th day of the month
	nearest13 ( &from );

	// Find 13th day of the month for every month on the interval
	*cnt = 0;
	for (; lessDate( from, to ) || equalDate(from, to); nextMonth( &from ) ) {
		short weekday = dayOfWeek( from );
		// Check is this date is Friday
		if ( weekday == 5 ) {
			*cnt += 1;
			printf("%d/%.2d/%d\n", from.m_Day, from.m_Month, from.m_Year);
			printf("%lld\n", *cnt);
		}
	}
	return true;
}

bool prevFriday13 ( TDATE * date )
{
	if ( !checkDate( date ) ) return false; 

	nearest13( date );
	prevMonth( date );

	TDATE lowerbound = makeDate( 1900, 1, 1);

	for (; lessDate( lowerbound, *date ); prevMonth( date ) ) {
		short weekday = dayOfWeek( *date );
		// Check is this date is Friday
		if ( weekday == 5 ) return true;
	}
	return false;
}

bool nextFriday13 ( TDATE * date )
{
	if ( !checkDate( date ) ) return false; 

	if ( date->m_Day == 13 ) nextMonth( date );
	nearest13( date );

	for (;; nextMonth( date ) ) {
		short weekday = dayOfWeek( *date );
		// Check is this date is Friday
		if ( weekday == 5 ) return true;
	}
	return false;
}

#ifndef __PROGTEST__
int main ()
{
  long long int cnt;
  TDATE x;
   assert ( countFriday13 ( makeDate ( 1900,  1,  1 ), makeDate ( 2025,  5,  1 ), &cnt )
            && cnt == 215LL );
   assert ( countFriday13 ( makeDate ( 1900,  1,  1 ), makeDate ( 2025,  6,  1 ), &cnt )
            && cnt == 215LL );
   assert ( countFriday13 ( makeDate ( 1900,  1,  1 ), makeDate ( 2025,  5, 13 ), &cnt )
            && cnt == 215LL );
   assert ( countFriday13 ( makeDate ( 1900,  1,  1 ), makeDate ( 2025,  6, 13 ), &cnt )
            && cnt == 216LL );
   assert ( countFriday13 ( makeDate ( 1904,  1,  1 ), makeDate ( 2025,  5,  1 ), &cnt )
            && cnt == 207LL );
   assert ( countFriday13 ( makeDate ( 1904,  1,  1 ), makeDate ( 2025,  6,  1 ), &cnt )
            && cnt == 207LL );
   assert ( countFriday13 ( makeDate ( 1904,  1,  1 ), makeDate ( 2025,  5, 13 ), &cnt )
            && cnt == 207LL );
   assert ( countFriday13 ( makeDate ( 1904,  1,  1 ), makeDate ( 2025,  6, 13 ), &cnt )
            && cnt == 208LL );
   assert ( countFriday13 ( makeDate ( 1905,  2, 13 ), makeDate ( 2025,  5,  1 ), &cnt )
            && cnt == 205LL );
   assert ( countFriday13 ( makeDate ( 1905,  2, 13 ), makeDate ( 2025,  6,  1 ), &cnt )
            && cnt == 205LL );
   assert ( countFriday13 ( makeDate ( 1905,  2, 13 ), makeDate ( 2025,  5, 13 ), &cnt )
            && cnt == 205LL );
   assert ( countFriday13 ( makeDate ( 1905,  2, 13 ), makeDate ( 2025,  6, 13 ), &cnt )
            && cnt == 206LL );
   assert ( countFriday13 ( makeDate ( 1905,  1, 13 ), makeDate ( 2025,  5,  1 ), &cnt )
            && cnt == 206LL );
   assert ( countFriday13 ( makeDate ( 1905,  1, 13 ), makeDate ( 2025,  6,  1 ), &cnt )
            && cnt == 206LL );
   assert ( countFriday13 ( makeDate ( 1905,  1, 13 ), makeDate ( 2025,  5, 13 ), &cnt )
            && cnt == 206LL );
   assert ( countFriday13 ( makeDate ( 1905,  1, 13 ), makeDate ( 2025,  6, 13 ), &cnt )
            && cnt == 207LL );
   assert ( countFriday13 ( makeDate ( 2025,  5, 13 ), makeDate ( 2025,  5, 13 ), &cnt )
            && cnt == 0LL );
   assert ( countFriday13 ( makeDate ( 2025,  6, 13 ), makeDate ( 2025,  6, 13 ), &cnt )
            && cnt == 1LL );
   assert ( ! countFriday13 ( makeDate ( 2025, 11,  1 ), makeDate ( 2025, 10,  1 ), &cnt ) );
   assert ( ! countFriday13 ( makeDate ( 2025, 10, 32 ), makeDate ( 2025, 11, 10 ), &cnt ) );
   assert ( ! countFriday13 ( makeDate ( 2090,  2, 29 ), makeDate ( 2090,  2, 29 ), &cnt ) );
   assert ( countFriday13 ( makeDate ( 2096,  2, 29 ), makeDate ( 2096,  2, 29 ), &cnt )
            && cnt == 0LL );
   assert ( ! countFriday13 ( makeDate ( 2100,  2, 29 ), makeDate ( 2100,  2, 29 ), &cnt ) );
   assert ( countFriday13 ( makeDate ( 2000,  2, 29 ), makeDate ( 2000,  2, 29 ), &cnt )
            && cnt == 0LL );
   x = makeDate ( 2025, 6, 12 );
   assert ( prevFriday13 ( &x )
            && equalDate ( x, makeDate ( 2024, 12, 13 ) ) );
   x = makeDate ( 2025, 6, 12 );
   assert ( nextFriday13 ( &x )
            && equalDate ( x, makeDate ( 2025, 6, 13 ) ) );
   x = makeDate ( 2025, 6, 13 );
   assert ( prevFriday13 ( &x )
            && equalDate ( x, makeDate ( 2024, 12, 13 ) ) );
   x = makeDate ( 2025, 6, 13 );
   assert ( nextFriday13 ( &x )
            && equalDate ( x, makeDate ( 2026, 2, 13 ) ) );
   x = makeDate ( 2025, 6, 14 );
   assert ( prevFriday13 ( &x )
            && equalDate ( x, makeDate ( 2025, 6, 13 ) ) );
   x = makeDate ( 2025, 6, 14 );
   assert ( nextFriday13 ( &x )
            && equalDate ( x, makeDate ( 2026, 2, 13 ) ) );
   x = makeDate ( 2025, 2, 29 );
   assert ( ! prevFriday13 ( &x ) );
   x = makeDate ( 2025, 2, 29 );
   assert ( ! nextFriday13 ( &x ) );
   x = makeDate ( 1900, 3, 18 );
   assert ( ! prevFriday13 ( &x ) );
   x = makeDate ( 1900, 3, 18 );
   assert ( nextFriday13 ( &x )
            && equalDate ( x, makeDate ( 1900, 4, 13 ) ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
