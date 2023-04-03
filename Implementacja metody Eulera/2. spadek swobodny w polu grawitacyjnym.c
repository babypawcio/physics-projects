// 4.1 example 2

// spadek swobodny w polu grawitacyjnym ziemii gdzie F = (0, -mg)
// energia poten-cjalna Ep = mgy; warunki początkowe (WP)
// t0 = 0
// x(0) = 0m
// y(0) = 10m
// vx(0) = 0m/s
// vy(0) = 0m/s

#include <stdio.h>

#define N 2                 // 2 wymiary x, y

// metoda eulera
// r = r + v * dt
// v = v + a * dt           a = F/m 

// funkcja wyliczajaca zachowanie energii calkowitej ukladu
// ec = 1/2*mv^2 + mgy;
float Ec(float *r, float *v, float m, float g);

int main()
{
    FILE *plik = NULL;
    plik = fopen("spadek_swobodny.txt", "w");           // wypisywanie wynikow do pliku

    // ustalone stale fizyczne

    const float g = 9.81f;                              // przyspieszenie ziemskie g = 9.81 m/s^2
    const float m = 5.0f;                               // masa = 5kg

    // warunki poczatkowe

    float r[N] = {0.0f, 10.0f};                         // polozenie 2D x, y
    float v[N] = {0.0f, 0.0f};                          // predkosc vx i vy
    float F[N] = {0.0f, -m*g};                          // sila w polu grawitacyjnym

    float t = 0.0f;                                     // czas t0 = 0s
    float dt = 0.01f;                                   // krok czasowy dt

    float tN = 100;                                     // czas koncowy, warunek zakonczenia petli


    // sprawdzenie czy plik jest poprawnie otwarty

    if(plik == NULL)
    {
        perror("blad w otwarciu pliku: 'spadek_swobodny.txt'. ");
        return 1;
    }

    // wypisanie poczatkowego stanu ukladu w kolumnach na standardowe wyjscie
    printf("t             x             y              vx            vy \n");
    printf("%f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1]);

    printf("energia calkowita: %f \n \n", Ec(r, v, m, g));

    // wypisanie poczatkowego stanu ukladu w kolumnach do pliku
    fprintf(plik, "t                       x                      y                        vx                    vy                     Ec \n");
    fprintf(plik, "%f      %f      %f      %f      %f       %f \n \n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));

    fprintf(plik, "energia calkowita: %f \n \n", Ec(r, v, m, g));

    // dopoki wysokosc jest wieksza od 0 i czas jest mniejszy niz ustalony czas koncowy
    while(r[1] >= 0 && t < tN)
    {
        t = t + dt;

        r[0] = r[0] + (v[0] * dt);                  // zawsze 0. bo x = 0, vx = 0 i fx = 0
        r[1] = r[1] + (v[1] * dt);

        v[0] = v[0] + (F[0]/m * dt);                // zawsze 0, bo vx = 0 i fx = 0
        v[1] = v[1] + (F[1]/m * dt);

        // wypisanie stanu ukladu w kolumnach na standardowe wyjscie
        printf("t             x             y              vx            vy \n");
        printf("%f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1]);

        // wypisanie stanu ukladu w kolumnach do pliku
        fprintf(plik, "t                       x                      y                        vx                    vy                     Ec \n");
        fprintf(plik, "%f      %f      %f      %f      %f       %f \n \n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));


    }

    printf("energia calkowita: %f \n \n", Ec(r, v, m, g));
    fprintf(plik, "energia calkowita: %f \n \n", Ec(r, v, m, g));


    fclose(plik);
    return 0;

}

// ec = 1/2*m*v**2 + m*g*y
// v = vy + vx
float Ec(float *r, float *v, float m, float g)
{
	return m/2.0f * ((v[0]*v[0]) + (v[1]*v[1])) + m*g*r[1];
	
}

	// gnuplot:
	// set tics font "Helvetica,15" 
	// set ytics 5		odstep na osi y co 5 miejsc
	// set xtics 5		odstep na osi x co 5 miejsc
		
	// set key font "Helvetica,15"  
	// set tics font "Helvetica,15" 
	
	// plot "wyniki.txt" u 1:3 t "y(t)" w lp 
	// plot "wyniki.txt" u 1:3 t "y(t)" w lp, -9.81/2*x**2+10  wynik scisly
	// set xzeroaxis      asymptota y = 0
	// set xlabel "t(s)"  legenda czas w sekundach
	// set ylabel "y(m)"