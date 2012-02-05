
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <sys/types.h>


// set_led
// THis function sets the LED either on or off
//
// dev - USB device handle pointer
// mode - false --> Turn LED off | true --> Turn LED on
void set_led(libusb_device_handle *dev,bool mode){

	unsigned char data[] = {0,0,0,0};
	int * transferred;

	if(mode){
		printf("LED On!\n");
		// Set data to 1
		data[0] = 0xff;
	} else {
		printf("LED Off!\n");
		// Set data to 0
		data[0] = 0x00;

	}

	libusb_interrupt_transfer(dev,1,data,8,transferred,10);

}


// Initializes the libraries
int main (int argc,char **argv){

	// Welcome Message
        printf("Gerald's USB IR Blaster v0.1\n");

	// Setup Working Variables
	libusb_device_handle *handle;
	libusb_device **list;
	libusb_device *found = NULL;

	// Initialize the libusb library.  This must be done before all calling any functions
	libusb_init(NULL);

	ssize_t cnt = libusb_get_device_list(NULL, &list);
	ssize_t i = 0;
	if (cnt < 0){
		return (int) cnt;
	}
	
	for (i=0; i < cnt; i++){
		libusb_device *device = list[i];
		struct libusb_device_descriptor d;
		libusb_get_device_descriptor(device,&d);
		unsigned short VenID = d.idVendor;
		if (VenID == 0x1b4f){
			printf("Device Found!\n");
			found = device;
		}
	}	
	
	libusb_free_device_list(list, 1);

	// Send 'ON' or 'OFF' commands


	libusb_exit(NULL);
	return 0;

}
