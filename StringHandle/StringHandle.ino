//#include "RGB.h"

#define red 0x0A
#define	green 0x0B
#define blue 0x0C

// ----- RGB Led -------------------

class rgb_led{
	public:
		rgb_led(uint8_t,uint8_t,uint8_t,bool);
		uint8_t r_value;
		uint8_t g_value;
		uint8_t b_value;
		void setColor(uint8_t,uint8_t,uint8_t);
		void setColor();
		void setRandom();
		uint8_t getColor(uint8_t);
	private:
		void writeOutput(uint8_t,uint8_t,uint8_t);
		bool mode;
		uint8_t r_pin;
		uint8_t g_pin;
		uint8_t b_pin;
};

rgb_led::rgb_led(uint8_t r,uint8_t g,uint8_t b, bool mod){
	mode = mod;
	r_pin = r;
	g_pin = g;
	b_pin = b;
	r_value = 0;
	g_value = 0;
	b_value = 0;
	pinMode(r_pin, OUTPUT);
	pinMode(g_pin, OUTPUT);
	pinMode(b_pin, OUTPUT);
	digitalWrite(r_pin,1);
	digitalWrite(g_pin,1);
	digitalWrite(b_pin,1);
}

void rgb_led::writeOutput(uint8_t r_out, uint8_t g_out, uint8_t b_out){
	if(!mode){
		r_out = 255 - r_out;
		g_out = 255 - g_out;
		b_out = 255 - b_out;
	}
	analogWrite(r_pin, r_out);
	analogWrite(g_pin, g_out);
	analogWrite(b_pin, b_out);
}

void rgb_led::setColor(){
	writeOutput(r_value,g_value,b_value);
}

void rgb_led::setColor(uint8_t r, uint8_t g, uint8_t b){
	r_value = r;
	g_value = g;
	b_value = b;
	writeOutput(r_value,g_value,b_value);
}

void rgb_led::setRandom(){
	r_value = uint8_t(random(255));
	g_value = uint8_t(random(255));
	b_value = uint8_t(random(255));
	writeOutput(r_value,g_value,b_value);
}

// ----------------------------------------

rgb_led output(6,9,11,false);

void setup(){
	Serial.begin(115200);
	Serial.println("--- Begin ---");
}

void loop(){
	if(Serial.available()){
		String Command = readString();
		if(Command == "Red"){
			output.r_value = askForColor(Command);
			output.setColor();
			Serial.println("The new value for " + Command +" is " + String(output.r_value));
		}
		else if(Command == "Green"){
			output.g_value = askForColor(Command);
			output.setColor();
			Serial.println("The new value for " + Command +" is " + String(output.g_value));
		}
		else if(Command == "Blue"){
			output.b_value = askForColor(Command);
			output.setColor();
			Serial.println("The new value for " + Command +" is " + String(output.b_value));
		}
		else if(Command == "Random"){
			output.setRandom();
			char out_buffer[128];
			sprintf(out_buffer,"New Values! \n Red = %u \n Green = %u \n Blue = %u",output.r_value,output.b_value,output.g_value);
			Serial.println(out_buffer);
		}
		else if(Command == "Status"){
			char out_buffer[128];
			sprintf(out_buffer,"Status \n Red = %u \n Green = %u \n Blue = %u",output.r_value,output.b_value,output.g_value);
			Serial.println(out_buffer);
		}
		else{
			Serial.println(Command + " is not a Valid Command");
		}
		Serial.println("--- --- ---");
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