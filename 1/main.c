#include <stdio.h>

int main () {
	int input;
	const char output [][ 87 ] = {
		"noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.",
		"bortaS bIr jablu'DI' reH QaQqu' nay'.",
		"Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.",
		"bISeH'eghlaH'be'chugh latlh Dara'laH'be'.",
		"qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.",
		"Suvlu'taHvIS yapbe' HoS neH.",
		"Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.",
		"Heghlu'meH QaQ jajvam.",
		"leghlaHchu'be'chugh mIn lo'laHbe' taj jej." 
	};

	printf("ml' nob:\n");

	if (scanf ( "%d ", &input ) != 1) {
		printf ( "Neh mi'\n" );
	} else if ( input >= 0 && input <= 8 ) {
		printf ( "Qapla'\n" );
		printf ( "%s\n", output [ input ] );
	} else {
		printf ( "Qih mi' %d\n", input );
	}
	return 0;
}
