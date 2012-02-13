// Easy way, copy most of the USB code from the LUFA program
// Hard way, read the USB spec and creat USB complient code from there

#include <avr/io.h>


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
			// THis is not required so we will just ignore the next outpacket
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
	// Check Endpoint Number requested
	// Look at the enum variables to see what we want to do with this info
	// Read Register and Do shit (probably with functions)
	// Clear the Interrupt
	RXOUTI = 0;
}

void interrupt_TXINI(){ // An IN packet was received
	if(ENDPOINT == 0){ // Control Endpoint Selected
		switch(next_in){
			case GET_STATUS_DEVICE:
				UEADAT0 = 0x00;
				UEADAT0 = 0x00;
			case GET_STATUS_INTERFACE:
				UEADAT0 = 0x00;
				UEADAT0 = 0x00;
			case ZERO_LENGTH_PACKET:
				break
			case CONFIGURATION_DESCRIPTOR:
				UEADAT0 = 0x00;
				///... 
			case STRING_DESCRIPTOR_0:
				UEADAT0 = 0x04; // THis Packet will be 4 bytes
				UEADAT0 = 0x03; // This is a String Descriptor
				UEADAT0 = 0x04; // THis string is english (pt 1)
				UEADAT0 = 0x09; // THis string is english (pt 2)
				break;
			case STRING_DESCRIPTOR_1:
				UEADAT0 = 0x07; // This packet will be 7 bytes long
				UEADAT0 = 0x03; // THis is a string descriptor
				UEADAT0 = u'U'; // Seind string in UNICODE
				UEADAT0 = u'S';
				UEADAT0 = u'B';
				UEADAT0 = u'I';
				UEADAT0 = u'R';
			default:
				// ZLP

		}
	} else { // LED Endpoint Selected
		// THere are no IN commands for the LED drive so return ZLP
	}
	// Look at the enum states to see what the host wants
	// Fill the DATA buffer with data we want to send
	// Clear the interrupt
	TXINI = 0;
}

