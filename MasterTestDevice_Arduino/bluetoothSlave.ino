/**
 * bluetoothSlave
 * majority of the functions are implemented in bluetoothBase
 * this class is to initialize the device as a slave and do some
 * predefined work.
 * 
 * @author Rijul Gupta <rijulg@gmail.com>
 * @since 22 April 2018
 */

void setupBluetoothSlave(){
  getSlaveName();
  baseBluetoothSetup(MODE_SLAVE);
}

void loopBluetoothSlave(){
  if(bluetoothConnected()){
    talkToBluetooth();
  }
  delay(100);
}
