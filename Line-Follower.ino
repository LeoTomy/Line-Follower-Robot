#include <avr/io.h>
#include <EEPROM.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000UL  // Define the microcontroller clock speed

// Function to initialize the ADC (Analog-to-Digital Converter)
void initADC() {
    ADMUX |= (1 << REFS0);  // Set reference voltage
    ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);  // Enable ADC with prescaler 128
}

// Function to read ADC value from a specified channel
int16_t adcval(uint8_t ch) {
    ADMUX = (ADMUX & 0b11111000) | (ch & 0b00000111);  // Select ADC channel
    ADCSRA |= (1 << ADSC);  // Start ADC conversion
    while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
    return ADC;  // Return the ADC result
}

// Function to initialize Timer1 for PWM (Pulse Width Modulation) control
void initTimer() {
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);  // Configure Timer1 for Fast PWM mode
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Set prescaler 8 and mode
    ICR1 = 15999;  // Define the TOP value for PWM cycle
}

// Function to set motor speed for Motor 1 using PWM
void setM1Speed(float speed) {
    OCR1A = speed;  // Set PWM duty cycle for Motor 1
}

// Function to set motor speed for Motor 2 using PWM
void setM2Speed(float speed) {
    OCR1B = speed;  // Set PWM duty cycle for Motor 2
}

int main() {
    initADC();  // Initialize ADC on channels 0 and 1
    initTimer();  // Initialize PWM time
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3)| (1 << PB5);  // Set motor control pins and On-Board Led as output
    DDRD &= ~(1 << PD4);  // Set PD4 as input for sensors
    PORTD = (1 << PD4);  // Enable pull-up resistor for PD4
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
    int T ;
   uint16_t* eeprom_address = (uint16_t*)0x10;
    while (1) {  // Infinite loop for continuous operation
    float battery=(float(adcval(6))/1023)*5;
    if(battery<4)
        PORTB|=(1 << PB5); // Indication for insufficient Battery Voltage
    else
     PORTB&=~(1 << PB5);
    T = eeprom_read_word(eeprom_address); 
  if (T== 255) {
    T = 600; // Default if EEPROM is empty
    eeprom_write_word(eeprom_address,T); 
  }  
    int sensorReading = adcval(7);  // Read sensor value from ADC channel 7
            float speed_right = (sensorReading << 4);  // Convert sensor reading to speed value
            float speed_left = (sensorReading << 4) * 0.93;  // Apply correction factor

            int sensorR = adcval(0);  // Read right sensor value
            int sensorL = adcval(1);  // Read left sensor value
           
if (!(PIND & (1 << PD2))) { // Calibrate threshold
 PORTB&=~(1 << PB5);
    T = (sensorL+ sensorR) / 2;
     eeprom_write_word(eeprom_address,T);
     _delay_ms(2000);
    PORTB|=(1 << PB5);
        _delay_ms(2000);
    }
        if (!(PIND & (1 << PD4))) {  // Check if PD4 low
        
            int error = sensorR - sensorL;  // Calculate error for movement adjustment
            float Kp = 1.0 /370;  // Proportional control gain
            float offset = Kp * static_cast<float>(error);  // Compute offset for speed adjustment

            if (sensorR >= T || sensorL >= T) {  // If either sensor detects a high value
                PORTB |= (1 << PB3);  // Activate Motor 2 forward
                PORTB |= (1 << PB0);  // Activate Motor 1 forward
                setM1Speed((1.0 - offset) * speed_right);  // Adjust speed based on error
                setM2Speed((1.0 + offset) * speed_left);  // Adjust speed based on error
                _delay_ms(20);
                
                
}
else if (sensorR < T && sensorL < T) {  // If both sensors read below threshold
                PORTB &= ~(1 << PB0);  // Activate Motor 1 backward
                PORTB &= ~(1 << PB3);  // Activate Motor 1 backward
                setM1Speed(speed_right);  // Maintain normal speed
                setM2Speed(speed_left);  // Maintain normal speed  
                _delay_ms(20);
                } 
              else {  // unxpected situation
                setM1Speed(0);  // Stop Motor 1
                setM2Speed(0);  // Stop Motor 2
            }
        }
        else {
if ( sensorR > T && sensorL > T ) { // straight
PORTB |= (1 << PB3);
PORTB |= (1 << PB0);
setM1Speed(speed_right);
setM2Speed(speed_left);
_delay_ms(10);
} else if ( sensorL < T && sensorR > T) { // right
PORTB |= (1 << PB3);
PORTB |= (1 << PB0);
setM1Speed(0); // right motor stopped
setM2Speed(speed_left);
_delay_ms(10);
} else if ( sensorR < T && sensorL > T) { // left
PORTB |= (1 << PB3);
PORTB |= (1 << PB0);
setM1Speed(speed_right);
setM2Speed(0); // left motor stopped
_delay_ms(10);
} else { // reverse
PORTB &= ~(1 << PB0);  
PORTB &= ~(1 << PB3);
setM1Speed(speed_right);
setM2Speed(speed_left);
_delay_ms(10);
} 
        }
        }
    
    return 0;  // End of program
}