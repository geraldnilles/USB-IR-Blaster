// Easy way, copy most of the USB code from the LUFA program
// Hard way, read the USB spec and creat USB complient code from there

#include <avr/atmega8u2.h>

int main(){
	// Setup Registers
	// Set USB Interrupts
	// Setup LED PWM output to be 32kHz at 50% duty cycle
}

void USB_interrupt(){

}

void setup_packet(char * data){
	unsigned char bmRequestType = data[0];
	unsigned char bRequest = data[1];
	unsigned short wValue = data[2:3];
	unsigned short wIndex = data[4:5];
	unsigned short wLength = data[6:7];

	switch(bRequest){
		case 0: // GET_STATUS
			// Set the IN packet data to 0x0000
			// THis means the device is bus-powered and does not wakeup the computer
			break;
		case 1: // CLEAR_FEATURE
			// No data is returned
			break;
		case 3: // SET_FEATURE
			// No data is returned
			break;
		case 5:	// SET_ADDRESS ... i think this is handled in hardware...
			// No data is returned
			break;		
		case 6: // GET_Descriptor ... Request a descriptor
			// Type and Index are in wValue
			// Set the In Packet to the requested descriptor
			break;
		case 7: // SET_DESCRIPTOR ... Descriptor is being sent to device
			// Prepare for next OUT packet to describe the descriptor described here
			break;
		case 8: // GET_CONFIGURATION
			// Set the IN packet to be the Configuration Value
			break;
		case 9: // SET_CONFIGURATION
			// Prepare for an OUT packet with the COnfiguration Value
			break;
		default:
			// Sent a 0 length packet if an in packet is requested
	}
}
