function donut() {
    let A = 0, B = 0;  // Angles for rotation
    const width = 80;
    const height = 24;
    const K2 = 5;  // Constant for zooming
    const K1 = width * K2 * 3 / (8 * (2 + 1));  // Constant for scaling
    
    setInterval(() => {
        // Create the 2D donut
        let output = Array(height).fill('').map(() => Array(width).fill(' '));
        
        for (let i = 0; i < 6.28; i += 0.07) {  // Loop over latitude
            for (let j = 0; j < 6.28; j += 0.02) {  // Loop over longitude
                let sinA = Math.sin(A);
                let cosA = Math.cos(A);
                let sinB = Math.sin(B);
                let cosB = Math.cos(B);
                let sinI = Math.sin(i);
                let cosI = Math.cos(i);
                let sinJ = Math.sin(j);
                let cosJ = Math.cos(j);

                // 3D parametric equations for the donut shape
                let x = cosA * (22 + 10 * cosI) * cosJ - sinA * sinJ;
                let y = sinA * (22 + 10 * cosI) * cosJ + cosA * sinJ;
                let z = 10 * sinI + 15;
                let ooz = 1 / z;  // Perspective division
                
                // Calculate screen position
                let X = Math.floor(width / 2 + K1 * x * ooz);
                let Y = Math.floor(height / 2 - K1 * y * ooz);
                
                // Calculate brightness based on z value for better visualization
                let L = Math.floor(8 * ((cosB * sinA * sinI - cosA * sinB * cosI) * cosJ - cosA * sinB * cosI - sinA * sinB * cosJ));
                if (Y >= 0 && Y < height && X >= 0 && X < width && ooz > 0) {
                    // Map L value to ASCII brightness (32 is space, 46 is dot, 48 is zero, etc.)
                    const chars = ".,-~:;=!*#$@";
                    const char = chars[Math.max(L, 0)];
                    output[Y][X] = char;
                }
            }
        }
        
        // Print the donut in the console
        console.clear();
        output.forEach(row => console.log(row.join('')));

        // Increment rotation angles for the donut
        A += 0.04;
        B += 0.02;

    }, 50);
}

// Start the donut animation
donut();
