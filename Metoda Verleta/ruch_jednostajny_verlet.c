// Ruch jednostajny prostoliniowy F = (0, 0) N
//energia potencjalna ep = 0; warunki początkowe (WP)
// t0 = 0
// x0 = 2m
// y0 = 3m
// vx0 = 1 m/s
// vy0 = 4 m/s

#include <stdio.h>

#define N 2 // wymiar 2D x, y

// energia calkowita = Ek + Ep = 1/2*mv^2 + mgy(=0)
float Ec(float *r, float *v, float m, float g); 

int main()
{
    FILE *plik = NULL;

    plik = fopen("ruch_jednostajny_verlet.txt", "w");

    const float g = 9.81f;             // przyspieszenie w m/s^2
    const float m = 5.0f;            // masa w kg

    // warunki poczatkowe

    float r[N] = {2.0f, 3.0f};       // polozenie w metrach
    float v[N] = {1.0f, 4.0f};       // predkosc m/s

    float rP[N], rW[N];              // polozenie w chwili wczesniejszej i pozniejszej
    float F[N] = {0.0f, 0.0f};       // sila w newtonach

    float t = 0;                     // czas w sekundach
    float tN = 100;                  // czas koncowy w  sekundach
    float dt = 0.1;                 // krok czasowy w sekundach
    float energia;

    if(plik == NULL)
    {
        perror("blad w otwarciu pliku ruch_jednostajny_verlet.txt");
        return 1;
    }

    // pierwszy krok czasowy
    // wzor na r1 = r0 + vo*dt + 1/2 F/m*dt^2
    rP[0] = r[0] + v[0]*dt + 0.5f*F[0]/m*(dt*dt);           // sila = 0, wiec krok pierwszy wyniesie r[i] + v[i]8dt
    rP[1] = r[1] + v[1]*dt + 0.5f*F[1]/m*(dt*dt);           // np dla d[1] rP[1] = 3m + 4m/s*1/100s = 3.04m

    printf("#    t            x            y            Vx          Vy           Ec\n");
    printf("% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

    fprintf(plik, "#    t            x            y            Vx          Vy           Ec\n");
    fprintf(plik, "% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

    while(t <= tN)
    {
        t += dt;

        // chwila wczesniejsza to teraz r0
        rW[0] = r[0];                                           // r(t - dt)
        rW[1] = r[1];               

        // r0 to teraz chwila pozniejsza r1
        r[0] = rP[0];                                           // r(t), zmiana drogi w czasie jednostajnie
        r[1] = rP[1];                                           // zmiana drogi w czasie jednostajnie

        // chwila pozniejsza ze wzoru r2 = -r0 + 2*r1 + F/m*dt^2
        rP[0] = -rW[0] + 2*r[0] + F[0]/m*(dt*dt);               // rx(t+dt)
        rP[1] = -rW[1] + 2*r[1] + F[1]/m*(dt*dt);               // ry(t+dt)

        v[0] = (rP[0] - rW[0])/(2*dt);                          // v(t) predkosc x jak i y jest praktyccznie niezmienna
        v[1] = (rP[1] - rW[1])/(2*dt);

        printf("#    t            x            y            Vx          Vy           Ec\n");
        printf("% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

        fprintf(plik, "#    t            x            y            Vx          Vy           Ec\n");
        fprintf(plik, "% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

        // energia calkowita jest zachowana (EP = 0)
    }

    fclose(plik);
    return 0;
}

float Ec(float *r, float *v, float m, float g)
{
    return m*((v[0]*v[0]) + (v[1]*v[1]))/2 + 0;
}

// gnuplot
// plot "ruch_jednostajny_verlet.txt" u 1:3 w lp, 1*(x-2)+3