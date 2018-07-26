#define F_CPU	16000000
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM OCR1B = OCR1A 

double myrand(int *x)
{
	/*linear congruential generator*/
	const int m = 100;
	const int a = 8;
	const int inc = 65;
	*x = ((a * (*x)) + inc) % m ;
	return (*x / (double)m) * 65535;
}

void timer1_init(void) {
	/*initializing the timer*/
	
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);		/* It is reset to "0" in the live count, when TCNT1 = OCR1A (/1024)	*/						
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10) | (1 << CS12);		/* CTC (Reset on coincidence)						*/
	TCNT1 = 0x00;									/* timer state (initialization)						*/
	
	ICR1 = 0xFF;									/* Pulse repetition period (max value)					*/
		
	OCR1A=0x00;									/* duty ratio								*/
	OCR1B=0x00;									/*									*/
	
}

int main(void)
{
	/* Configure GPIO */
	DDRB |= 0XE;									/* set PB3, PB2, PB1 to output						 */
	PORTB |= 0xE;									/* set output to 1							 */
	volatile uint16_t  res;								/* random result							 */
	int x0 = 2;									/* start value								*/
	timer1_init();
		
	while(1) {
				
		// generate random number from 0 to 65536
		res = myrand(&x0);
		// imitate probability density
		if (res >= 65536) {
			PWM = 2;  // maximum pwm level
			} else if (res > 50000) {
			PWM = 3;
			} else if (res > 40078) {
			PWM = 5;
			} else if (res > 30801) {
			PWM = 7;
			} else if (res > 27524) {
			PWM = 10;
			} else if (res > 24247) {
			PWM = 15;
			} else if (res > 20971) {
			PWM = 20;
			} else if (res > 17694) {
			PWM = 25;
			} else if (res > 14417) {
			PWM = 30;
			} else if (res > 11140) {
			PWM = 35;
			} else if (res > 7863) {
			PWM = 40;
			} else if (res > 4587) {
			PWM = 45;
			} else if (res > 1965) {
			PWM = 50;
			} else if (res > 1310) {
			PWM = 55;
			} else if (res > 654) {
			PWM = 60;
			} else {
			PWM = 0;  // logical 0
		}
	}
	return 0;
}