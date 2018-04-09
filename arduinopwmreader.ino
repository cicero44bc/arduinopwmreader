    // A *basic* sketch to read the pulse width of a PWM signal and print to serial.
    // Does not require a library.
    // Useful for reading PWM values from an R/C reciever
    // Signal is smoothed for legibility. It could be improved to utilise interrupts or low level operations.

    int pin = 2;  // PWM Pin
    int duration; // Duration of the pulse

    const int numReadings = 20; // Sample size for average.
    int readings[numReadings];
    int readIndex = 0;
    int total = 0;                  // Running total of sample
    int average = 0;                // Average from sample

    void setup(){
     
     Serial.begin(9600);
     pinMode(pin, INPUT);
     for (int thisReading = 0; thisReading < numReadings; thisReading++) {
       readings[thisReading] = 0; // Initialise sample array to 0.
     }
    }
     

    void loop(){

    duration = pulseIn(pin, HIGH);
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = duration;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    // if we're at the end of the array...
    if (readIndex >= numReadings) { // Print average when end of array reached.
      readIndex = 0;
      Serial.print("Av pulse width:");
      Serial.println(average);
    }

    // calculate the average:
    average = total / numReadings;
    delay(1);        // delay in between reads for stability

    }

