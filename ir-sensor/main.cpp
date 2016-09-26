// simple IR signal detector

#include "hwlib.hpp"
#define MAXPULSE 1000
int MAX = 100;
#define RESOLUTION 20
int pulses[100][2];
int currentpulse = 0;

void printpulses(void)
{
	hwlib::cout << "\n\r\n\rReceived: \n\rOFF \tON\n";
	for(int i = 0; i < currentpulse; i++) {
		hwlib::cout << pulses[i][0] * RESOLUTION;  //verwissel deze 0 en 1 om positie van high and low te wissellen
		hwlib::cout << " usec, ";
		hwlib::cout << pulses[i][1] * RESOLUTION;
		hwlib::cout << " usec\n";
	}
	/*
    // print it in a 'array' format
    hwlib::cout <<"int IRsignal[] = {";
    hwlib::cout <<"// ON, OFF (in 10's of microseconds)";
    for (int  i = 0; i < currentpulse-1; i++) {
      hwlib::cout <<"\t"; // tab
      hwlib::cout <<pulses[i][1] * RESOLUTION / 10;
      hwlib::cout <<", ";
      hwlib::cout <<pulses[i+1][0] * RESOLUTION / 10;
      hwlib::cout <<",";
    }
    hwlib::cout <<"\t"; // tab
    hwlib::cout <<pulses[currentpulse-1][1] * RESOLUTION / 10;
    hwlib::cout <<", 0};";
     * */
}

//void readIr(auto tsop_signal)
//{
//    int highpulse, lowpulse;
//    highpulse = lowpulse = 0;
//
//    while(1) {
//	highpulse = lowpulse = 0;
//	while(tsop_signal.get() == 0) {
//
//	    highpulse++;
//	    hwlib::wait_us(RESOLUTION);
//
//	    if((highpulse >= MAX) && (currentpulse != 0)) {
//		printpulses();
//		currentpulse = 0;
//		return;
//	    }
//	}
//
//	pulses[currentpulse][0] = highpulse;
//
//	while(tsop_signal.get() == 1) {
//	    lowpulse++;
//	    hwlib::wait_us(RESOLUTION);
//	    if((lowpulse >= MAX) && (currentpulse != 0)) {
//		printpulses();
//		currentpulse = 0;
//		return;
//	    }
//	}
//
//	pulses[currentpulse][1] = lowpulse;
//	currentpulse++;
//    }
//}

int main(void)
{

	hwlib::wait_ms(50);
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;

	auto tsop_signal = target::pin_in(target::pins::d8);
	auto tsop_gnd = target::pin_out(target::pins::d9);
	auto tsop_vdd = target::pin_out(target::pins::d10);

	// auto ir = hwlib::target::d2_36kHz();
	tsop_gnd.set(0);
	tsop_vdd.set(1);
	// ir.set(1);
	// test
	// while(1) {
	//	hwlib::cout<< "reading\n";
	// readIr(tsop_signal);
	// hwlib::cout<< "stash";
	//}

	int highpulse, lowpulse;
	highpulse = lowpulse = 0;

	while(currentpulse < 100) {
		// zet de timing variabelen op 0
		highpulse = lowpulse = 0;
		// terwijl het signaal uit de decoder laag is
		while(tsop_signal.get() == 1) {
			// verhoog tijd variabele en wacht aantal us
			highpulse++;
			hwlib::wait_us(RESOLUTION);
			// als deze pulse langer duurd dan time out en er is 1 pulse gezien
			// print de pulsen en return
			//			if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
			if((highpulse >= MAXPULSE)) {
				printpulses();
				currentpulse = 0;
				return 0;
			}
			//hwlib::cout << currentpulse << "1\n";
		}
		// sla de pulse op in het pulse array
		pulses[currentpulse][0] = highpulse;
		// terwijl het signaal uit de decoder hoog is
		while(tsop_signal.get() == 0) {
			// verhoog tijd variabele en wacht aantal us
			lowpulse++;
			hwlib::wait_us(RESOLUTION);
			// als deze pulse langer duurd dan time out en er is 1 pulse gezien
			// print de pulsen en return
			//			if ((lowpulse >= MAXPULSE) && (currentpulse != 0)) {
			if((lowpulse >= MAXPULSE)) {

				printpulses();
				currentpulse = 0;
				return 0;
			}
			//hwlib::cout << currentpulse << "0\n";
		}
		// sla de pulse op in het pulse array
		pulses[currentpulse][1] = lowpulse;
		// verhoog positie in pulse array
		currentpulse++;
	}
	printpulses();
}
