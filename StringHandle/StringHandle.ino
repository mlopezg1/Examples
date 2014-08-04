#include "RGB.h"

#define red 0x0A
#define	green 0x0B
#define blue 0x0C

// ----- RGB Led -------------------

// class rgb_led{
// 	public:
// 		rgb_led(uint8_t,uint8_t,uint8_t,bool);
// 		uint8_t r_value;
// 		uint8_t g_value;
// 		uint8_t b_value;
// 		void setColor(uint8_t,uint8_t,uint8_t);
// 		void setColor();
// 		void setRandom();
// 		uint8_t getColor(uint8_t);
// 	private:
// 		void writeOutput(uint8_t,uint8_t,uint8_t);
// 		bool mode;
// 		uint8_t r_pin;
// 		uint8_t g_pin;
// 		uint8_t b_pin;
// };

// rgb_led::rgb_led(uint8_t r,uint8_t g,uint8_t b, bool mod){
// 	mode = mod;
// 	r_pin = r;
// 	g_pin = g;
// 	b_pin = b;
// 	pinMode(r_pin, OUTPUT);
// 	pinMode(g_pin, OUTPUT);
// 	pinMode(b_pin, OUTPUT);
// }

// void rgb_led::writeOutput(uint8_t r_out, uint8_t g_out, uint8_t b_out){
// 	if(!mode){
// 		r_out = 255 - r_out;
// 		g_out = 255 - g_out;
// 		b_out = 255 - b_out;
// 	}
// 	analogWrite(r_pin, r_out);
// 	analogWrite(g_pin, g_out);
// 	analogWrite(b_pin, b_out);
// }

// void rgb_led::setColor(){
// 	writeOutput(r_value,g_value,b_value);
// }

// void rgb_led::setColor(uint8_t r, uint8_t g, uint8_t b){
// 	r_value = r;
// 	g_value = g;
// 	b_value = b;
// 	writeOutput(r_value,g_value,b_value);
// }

// void rgb_led::setRandom(){
// 	r_value = random(0,255);
// 	g_value = random(0,255);
// 	b_value = random(0,255);
// 	writeOutput(r_value,g_value,b_value);
// }

// ----------------------------------------

rgb_led output(7,8,9,true);

void setup(){
	Serial.begin(115200);
}

void loop(){
	String Command = readString();
	if(Command == "Red"){
		output.r_value = askForColor(Command);
		output.setColor();
	}
	else if(Command == "Green"){
		output.g_value = askForColor(Command);
		output.setColor();
	}
	else if(Command == "Blue"){
		output.b_value = askForColor(Command);
		output.setColor();
	}
	else if(Command == "Random"){
		output.setRandom();
		char out_buffer[128];
		sprintf(out_buffer,"New Values! \n Red = %u \n Green = %u \n Blue = %u;");
		Serial.println(out_buffer);
	}
	else if(Command == "Status"){
		char out_buffer[128];
		sprintf(out_buffer,"Status \n Red = %u \n Green = %u \n Blue = %u;");
		Serial.println(out_buffer);
	}
	else{
		Serial.println(Command + " is not a Valid Command");
	}
}

uint8_t askForColor(String Com){

	Serial.println("What's the Value for " + Com +"?");
	String inp = "";
	while(inp == "")
	{
		inp = readString();
	}
	return uint8_t(inp.toInt());
}

String readString()
{
	String output="";
	while(Serial.available())
	{
	  	output.concat(char(Serial.read()));
	  	delay(10);
	}
	return output;
}

