// Ruch jednostajny prostoliniowy F = (0, 0)
// energia potencjalna ep = 0
// warunki początkowe (WP)
// t0 = 0
// x(0) = 2m
// y(0) = 3m
// vx(0) = 1m/s
// vy(0) = 4m/s

#include <stdio.h>
#define N 2                                         // 2 wymiary x, y

// funkcja wyliczajaca zachowanie energii calkowitej ukladu
float Ec(float *r, float *v, float m, float g);

int main()
{
    FILE *plik=NULL;

    plik = fopen("ruch_jednostajny.txt", "w");      // wypisywanie wynikow do pliku

    // ustalone stale fizyczne
    const float g = 9.81f;                          // przyspieszenie ziemskie g = 9.81 m/s^2
    const float m = 5.0f;                           // masa 5kg

    float r[N] = {2.0f, 3.0f};                      // poczatkowe polozenie x = 2m, y = 3m
    float v[N] = {1.0f, 4.0f};                      // poczatkowe skladowe predkosci vx = 1m/s, vy = 4m/s
    float F[N] = {0.0f, 0.0f};                      // sila "dzialajaca" w polu grawitacyjnym

    float t = 0.0f;                                 // czas poczatkowy t = 0s
    float dt = 1.0f;                                // krok czasowy
    float tN = 100.0f;                              // czas koncowy, warunek zakonczenia petli

    if(plik==NULL)
    {
        perror("blad w otwarciu 'ruch_jednostajny.txt'.");
        return 1;
    }

    // wypisanie poczatkowego stanu ukladu w kolumnach na standardowe wyjscie
    printf("t             x             y             vx            vy \n");
    printf("%f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1]);
    printf("energia potencjalna: %f \n", Ec(r, v, m, g));

    // wypisanie poczatkowego stanu ukladu w kolumnach do pliku
    fprintf(plik, "t                       x                     y                       vx                    vy \n");
    fprintf(plik, "%f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1]);
    fprintf(plik, "energia potencjalna: %f \n \n", Ec(r, v, m, g));

    // petla trwa dopoki czas nie zbiegnie sie z czasem koncowym
    while(t < tN)
    {
        t = t + dt;

        r[0] = r[0] + (v[0] * dt);
        r[1] = r[1] + (v[1] * dt);
        
        // wartosci skladowych predkosci nie ulegna zmianie (F(0, 0)), predkosc jest jednostajna
        v[0] = v[0] + (F[0]/m * dt);
        v[0] = v[0] + (F[0]/m * dt);
        
        // wypisanie poczatkowego stanu ukladu w kolumnach na standardowe wyjscie
        printf("t               x               y               vx            vy \n");
        printf("%f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1]);

        // wypisanie stanu ukladu w kolumnach do pliku
        fprintf(plik, "t                         x                          y                       vx                    vy                    ec \n");
        fprintf(plik, "%f      %f      %f      %f      %f      %f \n \n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));
    }

    printf("energia potencjalna: %f \n \n", Ec(r, v, m, g));
    fprintf(plik, "energia potencjalna: %f \n \n", Ec(r, v, m, g));

    fclose(plik);
    return 0;
}

// ec = 1/2*m*v**2 + m*g*y
// v = vx + vy
float Ec(float *r, float *v, float m, float g)
{
    return m*((v[0]*v[0]) + (v[1]*v[1]))/2.0f + m*g*r[1]; 
}

	// gnuplot:
	// set tics font "Helvetica,15" 
	// set ytics 10		odstep na osi y co 2 miejsca
	// set xtics 10		odstep na osi x co 2 miejsca
		
	// set key font "Helvetica,15"  
	// set tics font "Helvetica,15" 
	
	// plot "ruch_jednostajny.txt" u 1:2 t "x(t)" w lp 
	// plot "ruch_jednostajny.txt" u 1:2 t "x(t)" w lp, (x-2)+3  wynik scisly
	// set xzeroaxis      asymptota y = 0
	// set xlabel "t(s)"  legenda czas w sekundach
	// set ylabel "x(m)"  zmiana drogi w czasie