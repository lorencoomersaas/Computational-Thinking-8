#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 100
#define HEIGHT 50
#define TWO_PI 6.28318530717958647692

int main() {
    double A = 0.0;
    double sin_A, cos_A;
    double x, y, z, ooz;
    char buffer[WIDTH * HEIGHT + 1];
    double zbuffer[WIDTH * HEIGHT];
    char donut[] = "abcdefghijkl";
    int luminance;

    double R = 2.5;
    double r = 1.25;

    while (1) {

        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            buffer[i] = ' ';
            zbuffer[i] = -1e9;
        }

        sin_A = sin(A);
        cos_A = cos(A);

        for (double theta = 0; theta < TWO_PI; theta += 0.01) {
            for (double phi = 0; phi < TWO_PI; phi += 0.005) {

                double circle_x = R + r * cos(phi);
                double circle_y = r * sin(phi);

                x = circle_x * cos(theta);
                y = circle_y * cos_A - (circle_x * sin(theta) * sin_A);
                z = circle_y * sin_A + (circle_x * sin(theta) * cos_A);

                ooz = 1 / (z + 5);
                int px = (int)(WIDTH / 2 + (WIDTH / 3.0) * x * ooz);
                int py = (int)(HEIGHT / 2 - (HEIGHT / 3.0) * y * ooz);

                double L = cos(phi) * cos(theta) * sin_A - sin_A * cos(theta) * sin(phi) +
                           cos_A * sin(theta) + 1;
                luminance = (int)(L * 5.5);

                int idx = py * WIDTH + px;
                if (py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH && ooz > zbuffer[idx]) {
                    zbuffer[idx] = ooz;
                    buffer[idx] = donut[(luminance > 0 ? luminance : 0)];
                }
            }
        }

        printf("\x1b[H");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                putchar(buffer[i * WIDTH + j]);
            }
            putchar('\n');
        }

        A += 0.05;
        usleep(1000);
    }

    return 0;
}
