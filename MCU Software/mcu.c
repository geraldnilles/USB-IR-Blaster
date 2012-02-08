// Easy way, copy most of the USB code from the LUFA program
// Hard way, read the USB spec and creat USB complient code from there

#include <avr/io.h>


enum next_out {
	LED_COMMAND,
	ENDPOINT_DESCRIPTOR,
	INTERFACE_DESCRIPTOR,
	STRING_DESCRIPTOR,
	ZERO_LENGTH_PACKET
}
enum next_in {
	GET_STATUS,
	ZERO_LENGTH_PACKET,
	ENDPOINT_DESCRIPTOR,
	INTERFACE_DESCRIPTOR,
	STRING_DESCRIPTOR
}

struct setup_packet{
	char bmRequestType;
	char bRequest;
	short wValue;
	short wIndex;
	short wLength;
}

// Return Data Here
char return_data[8];



int main(){
	// Setup Registers
	// Set USB Interrupts
	// Setup LED PWM output to be 32kHz at 50% duty cycle
}


void INTERRUPT_RXSTPI(){ // A SETUP Packet was received

	// There will be 8 bytes in the USB buffer
	// Each time the UEATX buffer is read, that byte is popped off the 
	char bmRequestType = UEDAT0;
	char bRequest = UEDAT0;
	short wValue = (UEDAT0 << 8) | UEDAT0;
	short wIndex = (UEDAT0 << 8) | UEDAT0;
	short wLength = (UEDAT0 << 8) | UEDAT0;
	
	// At this point, the USB Enpoint Byte counter should be zero UEBCLX

	switch(bRequest){ // TODO  THis will need to look at the Request type too
		case 0: // GET_STATUS
			// Set the IN packet data to 0x0000
			UEDAT0 = 0x00;
			UEDAT0 = 0x00;
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
			send_descriptor(wValue);
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
	
	// Clear the Interrupt
	RXSTPI = 0;
}


void interrupt_RXOUTI(){ // An Out packet was received
	// Look at the enum variables to see what we want to do with this info
	// Read Register and Do shit (probably with functions)
	// Clear the Interrupt
	RXOUTI = 0;
}

void interrupt_TXINI(){ // An IN packet was received
	// Look at the enum states to see what the host wants
	// Fill the DATA buffer with data we want to send
	// Clear the interrupt
	TXINI = 0;
}

