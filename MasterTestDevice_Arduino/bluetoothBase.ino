/**
 * bluetoothBase
 * the base functions used to run the bluetooth modules
 * 
 * @author Rijul Gupta <rijulg@gmail.com>
 * @since 22 April 2018
 */

#define bluetoothSerial Serial2
#define BLUETOOTH_BAUD 38400

#define MODE_SLAVE 0
#define MODE_MASTER 1

bool isConnected = false;
int numberRec = 0;
String str;
String masterName = "3asyMasterName";
String slaveName = "3asySlaveName";

void sendBluetoothCommand(String command){
  debug("Sending Command: "+command);
  bluetoothSerial.print("\r\n+"+command+"\r\n");
}

void talkToBluetooth(){
  if(bluetoothSerial.available()){ //check if there's any data sent from the remote bluetooth shield
      //numberRec = bluetoothSerial.parseInt();
      str = bluetoothSerial.readString();
      debug("Read from loop: "+str);
      numberRec = str.toInt();
      char s[100];
      sprintf(s, "Received: %d", numberRec);
      show(s);
      bluetoothSerial.print((numberRec+1));
  }
}

bool bluetoothConnected(){
  if(isConnected) return true;
  if(bluetoothSerial.available()){
    String str = bluetoothSerial.readString();
    debug(str);
    if(str.indexOf("CONNECT:OK") != -1){
      isConnected = true;
      return true;
    }
  }
}

void baseBluetoothSetup(int mode){
  bluetoothSerial.begin(38400);
  switch(mode){
    case 0:
      sendBluetoothCommand("STWMOD=0");
      sendBluetoothCommand("STNA="+slaveName);
    break;
    case 1:
      sendBluetoothCommand("STWMOD=1");
      sendBluetoothCommand("STNA="+masterName);
    break;
  }
  sendBluetoothCommand("STOAUT=1");
  sendBluetoothCommand("STAUTO=0");
  delay(2000);
  sendBluetoothCommand("INQ=1");
  switch(mode){
    case 0:
      show(slaveName+" is inquirable!");
    break;
    case 1:
      show(masterName+" is inquirable!");
    break;
  }
  delay(2000);
  bluetoothSerial.flush();
}

