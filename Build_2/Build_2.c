// Define necessary libraries
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

//Define the Trigger and Echo pins as GPIO 12 and GPIO 13 respectively
#define TRIG_PIN 12
#define ECHO_PIN 13


// Function to use the ultrasonic sensor to measure distance
void DISTANCE_SENSOR_OUTPUT(){
    
    // Send a 10 us HIGH pulse through the Trigger pin to trigger the ultrasonic sensor
    gpio_put(TRIG_PIN,1);
    sleep_us(10);
    gpio_put(TRIG_PIN,0);
                    
    // Wait for the Echo signal to go HIGH
    while (gpio_get(ECHO_PIN) == 0);

    // Record the time at which the Echo pulse begins
    uint64_t start = time_us_64();

    // Wait for the Echo signal to go LOW
    while (gpio_get(ECHO_PIN) == 1);

    // Record the time at which the Echo pulse ends
    uint64_t end = time_us_64();

    // Calculate the Echo pulse duration in microseconds
    float duration = end - start;

    // Calculate distance in cm using the data sheet defined formula.
    float current_distance = (duration*34)/(1000*2);

    // Output the measured distance using the Pico's USB connection
    printf("Distance: %f \n", current_distance);

}


int main() {
    // Initialise the Pico's standard I/O interface
    stdio_init_all();

    // Initialise the Trigger pin as an output
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    
    // Initialise the Echo pin as an input
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);


    // Initially, set the Trigger signal to LOW
    gpio_put(TRIG_PIN,0);

    // Continuously take distance measurements
    while(true){

        // Use the ultrasonic sensor to measure distance 
        DISTANCE_SENSOR_OUTPUT();

        // Wait for 20 ms
        sleep_ms(20);

    }  
}  

