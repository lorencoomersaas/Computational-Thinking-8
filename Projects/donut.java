public class Donut {
    public static void main(String[] args) {
        double A = 0, B = 0;  // Angles for rotation
        double i, j;
        
        while (true) {
            // Clear the screen
            System.out.print("\u001b[H");

            // Create 3D donut shape using ASCII characters
            for (i = 0; i < 6.28; i += 0.07) {  // Loop over latitude
                for (j = 0; j < 6.28; j += 0.02) {  // Loop over longitude
                    double sinA = Math.sin(A);
                    double cosA = Math.cos(A);
                    double sinB = Math.sin(B);
                    double cosB = Math.cos(B);
                    double sinI = Math.sin(i);
                    double cosI = Math.cos(i);
                    double sinJ = Math.sin(j);
                    double cosJ = Math.cos(j);

                    // 3D parametric equations for the donut shape
                    double x = cosA * (22 + 10 * cosI) * cosJ - sinA * sinJ;
                    double y = sinA * (22 + 10 * cosI) * cosJ + cosA * sinJ;
                    double z = 10 * sinI + 15;
                    double ooz = 1 / z;  // Perspective division

                    // Calculate screen position
                    int X = (int) (40 + 30 * x * ooz);
                    int Y = (int) (12 + 12 * y * ooz);

                    // Use brightness based on z value for better visualization
                    int L = (int) (8 * ((cosB * sinA * sinI - cosA * sinB * cosI) * cosJ - cosA * sinB * cosI - sinA * sinB * cosJ));
                    if (Y >= 0 && Y < 24 && X >= 0 && X < 80 && ooz > 0) {
                        // Map L value to ASCII brightness (32 is space, 46 is dot, 48 is zero, etc.)
                        char c = ".,-~:;=!*#$@"[Math.max(L, 0)];
                        System.out.print(c);
                    } else {
                        System.out.print(" ");
                    }
                }
                System.out.println();
            }

            // Increment rotation angles for the donut
            A += 0.04;
            B += 0.02;

            // Pause to simulate animation
            try {
                Thread.sleep(50);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
