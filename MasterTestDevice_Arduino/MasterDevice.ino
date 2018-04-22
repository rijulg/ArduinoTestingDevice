/**
 * Combined Device code
 * 1. Manchester Decoder
 * 2. Manchester Sender
 * 3. Bluetooth Master
 * 4. Bluetooth Slave
 * 
 * @author Rijul Gupta <rijulg@gmail.com>
 * @since 22 April 2018
 */

#define DEBUG_ENABLED 1
#define SHOW_ENABLED 1
#define LED_BASE 10
#define FUNCTIONS 4
#define SERIAL_BAUD 9600

typedef enum
{
 BLUETOOTH_MASTER = 0,
 BLUETOOTH_SLAVE = 1,
 MANCHESTER_DECODER = 2,
 MANCHESTER_SENDER = 3,
} settingLED;


int setting = -1;

void setup() {

  Serial.begin(SERIAL_BAUD);
  
  for(int i=0; i<FUNCTIONS; i++){
    pinMode(LED_BASE+i, INPUT_PULLUP);
    switch(digitalRead(LED_BASE+i)){
      case LOW: 
        setting = i;
        i = FUNCTIONS;
      break;
    }
  }
  
  switch(setting){
    case BLUETOOTH_MASTER: 
      show("Setting up Bluetooth Master");
      delay(100); // so that we can print the show before setup changes
      setupBluetoothMaster();
    break;
    case BLUETOOTH_SLAVE: 
      show("Setting up Bluetooth Slave");
      delay(100); // so that we can print the show before setup changes
      setupBluetoothSlave();
    break;
    case MANCHESTER_DECODER:
      show("Setting up Manchester Decoder");
      delay(100); // so that we can print the show before setup changes
      setupManchesterDecoder();
    break;
    case MANCHESTER_SENDER:
      show("Setting up Manchester Sender");
      delay(100); // so that we can print the show before setup changes
      setupManchesterSender();
    break;
    default:
      show("No setting selected!");
  }

}

void loop() {

  switch(setting){
    case BLUETOOTH_MASTER: 
      loopBluetoothMaster();
    break;
    case BLUETOOTH_SLAVE: 
      loopBluetoothSlave();
    break;
    case MANCHESTER_DECODER:
      loopManchesterDecoder();
    break;
    case MANCHESTER_SENDER:
      loopManchesterSender();
    break;
  }

}

void debug(String str){
  if(DEBUG_ENABLED){
    Serial.println("Log/D: "+str+"\n"); 
  }
}

void show(String str){
  if(SHOW_ENABLED){
    Serial.println("Log/I: "+str+"\n"); 
  }
}
