#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 40
#define TWO_PI 6.28318530717958647692

int main() {
    double A = 0.0, B = 0.0;   // Rotation angles
    double sin_A, cos_A, sin_B, cos_B;
    double x, y, z, ooz;       // 3D coordinates and projection
    char buffer[WIDTH * HEIGHT + 1];
    char donut[] = ".,-~:;=!*#$@";  // Donut surface characters
    int luminance;

    // Radii of the donut
    double R = 2.0;  // Major radius
    double r = 1.0;  // Minor radius

    while (1) {
        // Clear the buffer
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            buffer[i] = ' ';
        }

        // Calculate sine and cosine for the angles
        sin_A = sin(A);
        cos_A = cos(A);
        sin_B = sin(B);
        cos_B = cos(B);

        // Loop through the donut surface points
        for (double theta = 0; theta < TWO_PI; theta += 0.03) {  // Smaller step for density
            for (double phi = 0; phi < TWO_PI; phi += 0.01) {    // Smaller step for density
                // Parametric equations for the donut
                double circle_x = R + r * cos(phi);
                double circle_y = r * sin(phi);

                // 3D coordinates before rotation
                x = circle_x * cos(theta);
                y = circle_y;
                z = circle_x * sin(theta);

                // Apply rotations
                double x_rot = x * cos_B + z * sin_B;
                double z_rot = z * cos_B - x * sin_B;
                double y_rot = y * cos_A - z_rot * sin_A;
                z = y * sin_A + z_rot * cos_A;
                x = x_rot;

                // Perspective projection
                ooz = 1 / (z + 5);  // Adjust depth scaling
                int px = (int)(WIDTH / 2 + (WIDTH / 3.5) * x * ooz);   // Scale horizontally
                int py = (int)(HEIGHT / 2 - (HEIGHT / 3.5) * y_rot * ooz);  // Scale vertically

                // Luminance calculation for shading
                double L = cos(phi) * cos(theta) * sin_B - sin_A * cos(theta) * sin(phi) +
                           cos_A * sin(theta) + cos_B * (cos_A * cos(theta) - sin_A * sin(phi));
                luminance = (int)((L + 1) * 5.5);

                if (py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH && ooz > 0) {
                    buffer[py * WIDTH + px] = donut[(luminance > 0 ? luminance : 0)];
                }
            }
        }

        // Print the buffer
        printf("\x1b[H");  // Reset cursor position
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                putchar(buffer[i * WIDTH + j]);
            }
            putchar('\n');
        }

        // Increment angles for rotation (flipping effect)
        A += 0.05;  // Dominant X-axis rotation (flipping)
        B += 0.01;  // Minimal Y-axis rotation to avoid wobble

        usleep(30000);  // Adjust speed of rotation
    }

    return 0;
}
