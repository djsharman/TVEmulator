

class pwmOutput {

    void outputCurrentTimeSlice() {


        int i;
        int z;

        while (1) {
            for (i = 0; i < 500; i++) {
                for (z = 0; z < 1; z++) {

                    digitalWrite(LED, HIGH); // On
                    delayMicroseconds(i * 10);
                    digitalWrite(LED, LOW); // Off
                    delayMicroseconds((500 - i) * 10);
                };
            };
            for (i = 500; i > 0; i--) {
                for (z = 0; z < 1; z++) {

                    digitalWrite(LED, HIGH); // On
                    delayMicroseconds(i * 10);
                    digitalWrite(LED, LOW); // Off
                    delayMicroseconds((500 - i) * 10);
                };
            };
        }
    }

}