//http://fizyka.umk.pl/~tecumseh/EDU/FdI2/FdI2_l3.pdf

// 4.1 example 3

// rzut ukosny w polu grawitacyjnym przy powierzchni Ziemi, gdzie F = (0, −mg)
// energia potencjalna ep = mgy; warunki początkowe (WP):
// t0 = 0
// x(0) = 0m
// y(0) = 0m
// vx(0) = 5m/s
// vy(0) = 4m/s

#include <stdio.h>

// dwa wymiary x, y
#define N 2	

// funkcja obliczajaca zachowanie energii calkowitej ukladu
float Ec(float *r, float *v, float m, float g);

int main()
{
	FILE *plik = fopen("rzut_ukosny.txt", "w");	// wypisywanie wynikow do pliku
	
	const float g = 9.81f;     		// przyspieszenie ziemskie m/s^2
	const float m = 5.0f;     		// masa w kg 
	
	// warunki poczatkowe
	
	float r[N] = {0.0f, 0.0f};    	// polozenie w 2D
	float v[N] = {5.0f, 4.0f};		// predkosc m/s
	float F[N] = {0, -m*g};			// sila w Newtonach
	float t = 0.0f;					// czas w sekundach
	float dt = 0.01f;				// krok czasowy w sekundach
									// krok czasowy zmniejszony 10 krotnie - blad tez zmniejszony 10 krotnie, np w zachowaniu energii calkowitej
									
	float tN = 100;					// ostatne ograniczenie czasowe 100 sekund
	
	if(plik == NULL)
	{
		perror("blad w otwarciu pliku");
		return 11;
	}
	
	// drukowanie poszczegolnych wartosci poczatkowych w kolumnach
	printf("t			x			y			Vx			Vy \n");
	printf("%f		%f		%f		%f		%f \n \n \n",t, r[0], r[1], v[0], v[1] );
	
	fprintf(plik, "t			x			y			Vx			Vy \n");
	fprintf(plik, "%f		%f		%f		%f		%f \n \n \n",t, r[0], r[1], v[0], v[1] );
	
	printf("energia calkowita : %f J \n \n", Ec(r, v, m, g));
	fprintf(plik, "energia calkowita : %f J \n \n", Ec(r, v, m, g));
	
	// dopoki wysokosc jest wieksza niz 0 i czas jest mniejszy niz ustalony czas koncowy
	while(r[1] >= 0 && t < tN)
	{
		// zmiana w czasie
		t = t + dt;						
		r[0] = r[0] + v[0] * dt;		// pierwszy wzor z metody eulera na polozenie
		r[1] = r[1] + v[1] * dt;
	
		v[0] = v[0] + F[0]/m * dt;		// drugi wzor na predkosc
		v[1] = v[1] + F[1]/m * dt;

		// drukowanie poszczegolnych wartosci w kolumnach na standardowe wyjscie
		printf("t			x			y			Vx			Vy \n");
		printf("%f		%f		%f		%f		%f \n",t, r[0], r[1], v[0], v[1] );
		
		// drukowanie poszczegolnych wartosci w kolumnach do pliku
		fprintf(plik, "t			x			y			Vx			Vy \n");
		fprintf(plik, "%f		%f		%f		%f		%f \n",t, r[0], r[1], v[0], v[1] );

	}
	
	printf(plik, "\nenergia calkowita : %f J \n", Ec(r, v, m, g));
	fprintf(plik,"\nenergia calkowita : %f J \n", Ec(r, v, m, g));

	fclose(plik);
	
	// gnuplot:
	// set tics font "Helvetica,15" 
	// set ytics 5		odstep na osi y co 2 miejsca
	// set xtics 5		odstep na osi x co 2 miejsca
		
	// set key font "Helvetica,15"  
	// set tics font "Helvetica,15" 
	
	// plot "wyniki.txt" u 1:3 t "y(t)" w lp 
	// plot "wyniki.txt" u 1:3 t "y(t)" w lp, 4*x-9.81/2*x**2   wynik scisly
											  // vy * t -1/2*g*t**2
	// set xzeroaxis      asymptota y = 0
	// set xlabel "t(s)"  legenda czas w sekundach
	// set ylabel "y(m)"

	return 0;
}

// Ec = Ek + Ep  =  mv^2/2 + mgy
// v^2 = vox^2 + voy^2

float Ec(float *r, float *v, float m, float g)
{
	return m/2.0f * ((v[0]*v[0]) + (v[1]*v[1])) + m*g*r[1];
	
}