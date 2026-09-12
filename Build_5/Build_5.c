// Define necessary libraries
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"


// Define Pico's Wireless chip library
#include "pico/cyw43_arch.h"


// Define the Wireless chip pin connected to the on board LED
#define WIRELESS_ON_BOARD_LED_PIN 0


//Define the Trigger and Echo pins as GPIO 12 and GPIO 13 respectively
#define TRIG_PIN 12
#define ECHO_PIN 13

// Define the Green, Yellow, Red LED driving pins as GPIO 4, GPIO 5, GPIO 6 respectively
#define GREEN_LED_PIN 4
#define YELLOW_LED_PIN 5
#define RED_LED_PIN 6

// Define the Buzzer signal pin as GPIO15
#define BUZZER_PIN 15


// Function to use the ultrasonic sensor to measure distance
float DISTANCE_SENSOR_OUTPUT(){

    // Initialise the variable storing the total distance recorder per run 
    float distance_sum = 0;

    // Define the number of readings the sensor takes per run
    int test_size = 3;

    // Run the sensor a set amout of times and sum the measured distances
    for (int count=0;count<test_size;count++){
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

        // Record the time at which the Echo pulse begins
        uint64_t end = time_us_64();

        // Calculate the Echo pulse duration in microseconds
        float duration = end - start;

        // Calculate distance in cm using the data sheet defined formula.
        float current_distance = (duration*34)/(1000*2);

        // Add the distance to the previously measured distances
        distance_sum = distance_sum + current_distance;

        sleep_ms(10);
    }

    // Calculate the average distance the sensor measured in this run
    float final_distance = distance_sum/test_size;

    // Return the measured distance 
    return final_distance;
}

// Function to create the LED response
void LED_RESPONSE(float distance){

    // Initially, have all the LEDs OFF
    gpio_put(GREEN_LED_PIN,0);
    gpio_put(YELLOW_LED_PIN,0);
    gpio_put(RED_LED_PIN,0);

    // If distance is less than 25cm, turn all 3 LEDs on
    if (distance<25){
        gpio_put(GREEN_LED_PIN,1);
        gpio_put(YELLOW_LED_PIN,1);
        gpio_put(RED_LED_PIN,1);
    }

    // If distance is between 25 and 40cm, turn the green and yellow LEDs on
    else if (distance < 40){
        gpio_put(GREEN_LED_PIN,1);
        gpio_put(YELLOW_LED_PIN,1);
    }

    /// If distance is between 40 and 60 cm, turn the green LED on
    else if (distance < 60)
        gpio_put(GREEN_LED_PIN,1);

}

// Function to create the Buzzer response
void BUZZER_RESPONSE(float distance){

    // If distance is less than 25cm, output a conitnuous tone
    if (distance<25){
        gpio_put(BUZZER_PIN,1);
        sleep_ms(75);
    }

    // If distance is between 25 and 40cm, output a fast beeping tone
    else if (distance<40){ 
        gpio_put(BUZZER_PIN,1);
        sleep_ms(75);
        gpio_put(BUZZER_PIN,0);
        sleep_ms(75);
    }

    // If distance is between 40 and 60cm, output a slow beeping tone
    else if (distance<60){
        gpio_put(BUZZER_PIN,1);
        sleep_ms(100);
        gpio_put(BUZZER_PIN,0);
        sleep_ms(200);
    }
    
    // Otherwise turn the buzzer off (necessary here and not for LED response 
    // because Buzzer signal is not reset to 0 by default for every iteration)
    else
        gpio_put(BUZZER_PIN,0);
}

int main() {
    // Initialise the Pico's standard I/O interface
    stdio_init_all();

    // Initialise Pico W's wireless architecture
    cyw43_arch_init();

    // Turn on board LED on while program is running
    cyw43_arch_gpio_put(WIRELESS_ON_BOARD_LED_PIN,1);

    // Initialise the Trigger pin as an output
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    
    // Initialise the Echo pin as an input
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);

    // Initialise the LED pins as output
        // Green
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

        // Yellow
    gpio_init(YELLOW_LED_PIN);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);

        // Red
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    // Initialise the Buzzer pin as output
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Initially, set the Buzzer signal to LOW
    gpio_put(BUZZER_PIN,0);

    // Initially, set the Trigger signal to LOW
    gpio_put(TRIG_PIN,0);

    // Initialise the distance variable to be used within the while loop as float
    float distance;

    // Continuously take distance measurements and output response
    while(true){

        // Use the ultrasonic sensor to measure distance 
        distance = DISTANCE_SENSOR_OUTPUT();

        // Use the measured distance to output an appropriate LED response
        LED_RESPONSE(distance);

        // Use the measured distance to output an appropriate Buzzer response
        BUZZER_RESPONSE(distance);

    }  
}  
