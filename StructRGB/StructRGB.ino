#define r_pin 6
#define g_pin 9
#define b_pin 11

struct rgb_led{
		uint8_t r_value;
		uint8_t g_value;
		uint8_t b_value;
};

rgb_led led = {0,0,0};
rgb_led led_1 = {5,5,6};

void setup(){
	Serial.begin(115200);
}

void loop(){
	if(Serial.available()){
		char buff[4];
		if(Serial.find("~")){
			Serial.readBytes(buff,4);
			if(buff[0] == 0x00){
				led.r_value = buff[1];
				led.g_value = buff[2];
				led.b_value = buff[3];
				writeLed(led.r_value,led.g_value,led.b_value);
			}
			if(buff[0] == 0x0A){
				led_1.r_value = buff[1];
				led_1.g_value = buff[2];
				led_1.b_value = buff[3];
				writeLed(led_1.r_value,led_1.g_value,led_1.b_value);
			}
			Serial.print(buff);
		}
		while(Serial.available()){
			Serial.read();
		}
	}
	
}

void writeLed(uint8_t r,uint8_t g, uint8_t b){
	analogWrite(r_pin,r);
	analogWrite(g_pin,g);
	analogWrite(b_pin,b);
}