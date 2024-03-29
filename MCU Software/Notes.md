This file will list all this shit my MCU code needs to support


## Transactions

USB Transactions will be documented as shown below

CAPITAL - Host side
lower - Device side
(In Parenthsis)* - Can happen multiple times
ZLP - Zero Length Data Packet

<pre>
SETUP - DATA - ack - (IN  - data)* - ACK - OUT - ZLP - ack
                   - (OUT - DATA)* - ack - IN  - zlp - ACK

OUT - DATA - ack

IN - data - ACK
</pre>

## Examples

Device - GET_STATUS
	SETUP Token
	DATA0 - 0x80 - 0x00 - 0x0000 - 0x0000 - 0x0002
		Request Type - Request - Value - Index - Return Data Length
	ack Token
	IN Token
	data0 - 0x0000
		bit 15-2 = Reserved - bit 1 = Remote Wakup - bit0 = Self Powered
	ACK Token
	OUT Token
	ZLP
	ack Token
	
DATA0 Packet
<table>
	<tr>
		<td>0x80</td> <td>0x00</td>
	</tr>
	<tr>
		<td>Request Type</td> <td>Request</td>
	</tr>
</table>

Device - CLEAR_FEATURE
	SETUP Token
	DATA0 - 0x00 - 0x01 - 0x???? - 0x0000 - 0x0000
		RequestType - Request - Feature - Index - Length
	ack Token

Device - SET_FEATURE
	SETUP Token
        DATA0 - 0x00 - 0x03 - 0x???? - 0x0000 - 0x0000
                RequestType - Request - Feature - Index - Length
        ack Token

Device - SET_ADDRESS
        SETUP Token
        DATA0 - 0x00 - 0x05 - 0x???? - 0x0000 - 0x0000
                RequestType - Request - Address - Index - Length
        ack Token

Device - GET_DESCRIPTOR - Device Descriptor
        SETUP Token
        DATA0 - 0x80 - 0x06 - 0x0100 - 0x0000 - 0x0012
                Request Type - Request - Descriptor Type and Index - Index - Length (18 bytes)
        ack Token
        IN Token
        data0
		0x12 - Length of Descriptor (18 bytes)
		0x01 - Descriptor TYpe (Device Descriptor)
		0x0110 - USB Spec Version (USB 1.1)
		0x00 - USB Deivce class (look up on USB.org)
		0x00 - USB Device SubClass (Look up on USB.org)
		0x00 - USB Protocol Code (Look up on USB.org)
		0x40 - Max Packet Size (64 bytes)
		0xBEAD - Vendor ID (Get a Unique one)
		0x0000 - Produce ID (ANything)
		0x0000 - Device Realease Number (Anything)
		0x00 - Manufacturer String Index
		0x01 - Product String Index
		0x02 - Serial Number Index
		0x01 - Number of Configurations ( 1)
        ACK Token
        OUT Token
        ZLP
        ack Token

Device - GET_DESCRIPTOR - Configuration Descriptor
        SETUP Token
        DATA0 - 0x80 - 0x06 - 0x0201 - 0x0000 - 0x0009
                Request Type - Request - Descriptor Type and Index - Index - Length (9 bytes)
        ack Token
        IN Token
        data0
		**** For configuration descriptrs, the entire heiarchy is returned
		*** Configuration 0 ***
                0x09 - Length of Descriptor (9? bytes)
                0x02 - Descriptor TYpe (Configuration Descriptor)
		0x0019 - Total Length (9+9+7?) so 25?
                0x01 - Number of Interfaces
		0x00 - Configuration Number
		0x03 - COnfiguration String Index
		0x00 - Attributes - Buss Powered and No remote wakeup
		0x00 - Max Power 0x32 -  (50)*(2mA) = 100 mA
		*** Interface 0 ***
		0x09 - Length of Descriptor (9 bytes)
		0x04 - Descriptor Type (Interface)
		0x00 - Interface Number
		0x00 - Alternate Settings
		0x01 - Number of Endpoints (Does not include Endpoint 0)
		0x00 - Interface Class (From USB.Org)
		0x00 - Interface SubClass (From USB.org)
		0x00 - Interface Protocol (From USB.org)
		0x04 - String Index
		*** Endpoint 1 *** // We do not describe the 0 endpoint
		0x07 - Length of Descriptor (7 bytes)
		0x05 - Descriptor type (Endpoint)
		0x01 - Endpoint Address (Out direction - 0 -  and Endpoint 1)
		0x03 - Attributes - Interrupt Endpoint
		0x0001 - Maximum Packet size the endpoint is capable of receiving (1 byte)? 
		0x01 - Interval for Polling - 1 frame count

        ACK Token
        OUT Token 
        ZLP 
        ack Token

Device - GET_DESCRIPTOR - String Descriptor 0
	SETUP Token
	DATA0
		0x80 - Request Type
		0x06 - Request (GET_Descriptor)
		0x0300 - Descriptor TYpe and Index (String and 0x00)
		0x0000 - Language Code (0)
		0x0000 - Length (0?)
	ack Token
	IN Token
	data0
		*** For index zero, return a list of languages ***
		0x04 - Lenght of return (4 bytes)
		0x03 - String Type - 0x03
		0x0409 - English USA
	ACK Token
	OUT Token
	ZLP
	ack Token

Device - GET_DESCRIPTOR - String Descriptor 1 to n
	SETUP Token
        DATA0
                0x80 - Request Type
                0x06 - Request (GET_Descriptor)
                0x03?? - Descriptor TYpe and Index (String and 1 to n)
                0x0409 - Language Code (0)
                0x0000 - Length (0?) // Check USB documentation
        ack Token
        IN Token
        data0
                *** For index zero, return a list of languages ***
                0x?? - Lenght of return + (number of chars + 1)*2 bytes
                0x03 - String Type - 0x03
                0x???? - Character 1 // Encoded in Unicode 16 so each character is 2 bytes
		0x???? - Character 2
		0x???? - Character 3
		--etc--
        ACK Token
        OUT Token
        ZLP
        ack Token
		 
Device - GET_CONFIGURATION
	SETUP Token
	DATA0
		0x80 - Request Type
		0x08 - Get Configuration REquest
		0x0000 - Zero
		0x0000 - Zero
		0x0001 - 1 Byte to be returned
	ack Token
	IN Token
	data0
		0x0? - Return 0 if the device is not configured.  Return 1 if the device is configured
	ACK Toekn
	OUT Token
	ZLP
	ack Token

Device - SET_Configuration
	SETUP Token
	DATA0
		0x00 - Request Type
		0x09 - Set Configuration Request
		0x0001 - Set Configuration 1 (the only one we support)
		0x0000 - Zero
		0x0000 - Zero
	ack Token

Device - SET_DESCRIPTOR is optional so lets ignore it
