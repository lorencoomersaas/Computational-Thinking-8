#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 40
#define TWO_PI 6.28318530717958647692

int main() {
    double A = 0.0;  // Rotation angle for flipping motion
    double sin_A, cos_A;
    double x, y, z, ooz;       // 3D coordinates and projection
    char buffer[WIDTH * HEIGHT + 1];
    double zbuffer[WIDTH * HEIGHT]; // Depth buffer
    char donut[] = ".,-~:;=!*#$@";  // Donut surface characters
    int luminance;

    // Radii of the donut
    double R = 2.0;  // Major radius
    double r = 1.0;  // Minor radius

    while (1) {
        // Clear the buffers
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            buffer[i] = ' ';
            zbuffer[i] = -1e9;  // Very small number for depth initialization
        }

        // Precompute sine and cosine for the flipping rotation
        sin_A = sin(A);
        cos_A = cos(A);

        // Loop through the donut surface points
        for (double theta = 0; theta < TWO_PI; theta += 0.02) {  // Smaller step for denser rendering
            for (double phi = 0; phi < TWO_PI; phi += 0.01) {    // Smaller step for denser rendering
                // Parametric equations for the donut
                double circle_x = R + r * cos(phi);  // Donut's "circle" in 3D
                double circle_y = r * sin(phi);

                // Rotate the 3D point around the X-axis (flipping motion)
                x = circle_x * cos(theta);
                y = circle_y * cos_A - (circle_x * sin(theta) * sin_A);
                z = circle_y * sin_A + (circle_x * sin(theta) * cos_A);

                // Perspective projection
                ooz = 1 / (z + 5);  // Adjust depth for perspective
                int px = (int)(WIDTH / 2 + (WIDTH / 3.5) * x * ooz);   // Horizontal scaling
                int py = (int)(HEIGHT / 2 - (HEIGHT / 3.5) * y * ooz);  // Vertical scaling

                // Luminance calculation for shading
                double L = cos(phi) * cos(theta) * sin_A - sin_A * cos(theta) * sin(phi) +
                           cos_A * sin(theta) + 1;  // Simplified shading formula
                luminance = (int)(L * 5.5);  // Map luminance to character range

                // Update buffer only if the point is closer than the previous depth
                int idx = py * WIDTH + px;
                if (py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH && ooz > zbuffer[idx]) {
                    zbuffer[idx] = ooz;  // Update depth buffer
                    buffer[idx] = donut[(luminance > 0 ? luminance : 0)];
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

        // Increment angle for flipping
        A += 0.05;  // Smooth flipping motion

        usleep(20000);  // Adjust speed of rotation (20ms per frame)
    }

    return 0;
}
