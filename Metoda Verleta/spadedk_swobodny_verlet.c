// spadek swobodny w polu grawitacyjnym przy powierzchni Ziemi, gdzie F = (0, −mg)
// energia potencjalna Ep = mgy; warunki początkowe (WP)
// t0 = 0
// x0 = 0m
// y0 = 10m
// vx0 = 0 m/s
// vy0 = 0 m/s

#include <stdio.h>

#define N 2 // wymiar 2D x, y

// energia calkowita = Ek + Ep = 1/2*mv^2 + mgy
float Ec(float *r, float *v, float m, float g);


int main()
{
    FILE *plik=NULL;
    plik = fopen("spadek_swobodny_verlet.txt", "w");

    const float g=9.81f;             // przyspieszenie w m/s^2
    const float m = 5.0f;            // masa w kg

    // warunki poczatkowe

    float r[N] = {0.0f, 10.0f};      // polozenie w metrach
    float v[N] = {0.0f, 0.0f};       // predkosc m/s

    float rP[N], rW[N];              // polozenie w chwili wczesniejszej i pozniejszej
    float F[N] = {0.0f, -m*g};       // sila w newtonach

    float t = 0;                     // czas w sekundach
    float tN = 100;                  // czas koncowy w  sekundach
    float dt = 0.01;                 // krok czasowy w sekundach

    if(plik == NULL)
    {
        perror("blad w otwarciu pliku spadek_swobodny_verlet.txt");
        return 1;
    }

    // pierwszy krok czasowy
    // wzor na r1 = r0 + vo*dt + 1/2 F/m*dt^2
    rP[0] = r[0] + v[0]*dt + 0.5f*F[0]/m*(dt*dt);
    rP[1] = r[1] + v[1]*dt + 0.5f*F[1]/m*(dt*dt);

    printf("#    t            x            y            Vx          Vy           Ec\n");
    printf("% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

    fprintf(plik, "#    t            x            y            Vx          Vy           Ec\n");
    fprintf(plik, "% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

    while(r[1] >= 0.0f && t <= tN)
    {
        t += dt;

        // chwila wczesniejsza to teraz r0
        rW[0] = r[0];                                           // r(t - dt)
        rW[1] = r[1];               

        // r0 to teraz chwila pozniejsza r1
        r[0] = rP[0];                                           // r(t) x = 0 stale
        r[1] = rP[1];                                           // maleje kwadratem

        // chwila pozniejsza ze wzoru r2 = -r0 + 2*r1 + F/m*dt^2
        rP[0] = -rW[0] + 2*r[0] + F[0]/m*(dt*dt);               // rx(t+dt)
        rP[1] = -rW[1] + 2*r[1] + F[1]/m*(dt*dt);               // ry(t+dt)

        v[0] = (rP[0] - rW[0])/(2*dt);                          // v(t) zawsze 0, skladowa x sie nie zmienia
        v[1] = (rP[1] - rW[1])/(2*dt);

        printf("#    t            x            y            Vx          Vy           Ec\n");
        printf("% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0

        fprintf(plik, "#    t            x            y            Vx          Vy           Ec\n");
        fprintf(plik, "% f    % f    % f    % f    % f    % f\n", t, r[0], r[1], v[0], v[1], Ec(r, v, m, g));  // t0
    }

    fclose(plik);
    return 0;
}

float Ec(float *r, float *v, float m, float g)
{
    return m*((v[0]*v[0]) + (v[1]*v[1]))/2 + m*g*r[1];
}

// gnuplot
// plot "spadek_swobodny_verlet.txt u 1:3 w lp, -0.5*9.81*x**2+10