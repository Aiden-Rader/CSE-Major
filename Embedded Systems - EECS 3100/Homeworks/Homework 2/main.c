 // Start of the program with main function
int main(void) {

	// Declare the two variables
	unsigned char ch1 = 0x34; // = 0011 0100
	unsigned char mask = 1;

	// Use a AND and a Bit Clear function to change ch1 variable
	ch1 = (ch1 & ~(mask<<2)); //ch1 = 0x30 = 0011 0000

	return 0;
}
