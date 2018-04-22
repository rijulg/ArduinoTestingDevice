/*
BluetoothShield Demo Code Master.pde.This sketch could be used with
Slave.pde to establish connection between two Arduino.
2011 Copyright (c) Seeed Technology Inc. All right reserved.
Author: Steve Chang
This demo code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
For more details about the product please check http://www.seeedstudio.com/depot/
*/
/* Upload this sketch into Seeeduino and press reset*/

String slaveAddr;

void setupBluetoothMaster(){

  getSlaveName();
  
  baseBluetoothSetup(MODE_MASTER);
  
  getSlaveAddress();
  connectToSlave();
  //wait 1s and flush the serial buffer
  delay(1000);
  bluetoothSerial.print(0);
  bluetoothSerial.flush();
}

void loopBluetoothMaster(){
  talkToBluetooth();
}

void getSlaveName(){
  bool found = false;
  while(!found){
    if(Serial.available()){
      String name = Serial.readString();
      if(name.length() > 0){
        slaveName = name; 
      }
      found = true;
    }
  }
}

void getSlaveAddress(){
  //find the target slave
  int nameIndex = 0;
  int addrIndex = 0;
  String retSymb = "+RTINQ="; // start symble when there's any return
  String recvBuf;

  show("Searching for slave ("+slaveName+")");
  
  while(1){
    if(bluetoothSerial.available()){
      recvBuf = bluetoothSerial.readString();
      debug(recvBuf);
      nameIndex = recvBuf.indexOf(";"+slaveName); //get the position of slave name
      
      //nameIndex -= 1;
      //decrease the ';' in front of the slave name, to get the position of the end of the slave address
      if ( nameIndex != -1 ){
        //Serial.print(recvBuf);
        addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());//get the start position of slave address
        slaveAddr = recvBuf.substring(addrIndex, nameIndex);//get the string of slave address
        break;
      }
    }
  }
}

void connectToSlave(){
  //form the full connection command
  int connectOK = 0;
  String recvBuf = "";
  show("Connecting to slave: "+slaveName+"("+slaveAddr+")");
  //connecting the slave till they are connected
  do{
    sendBluetoothCommand("CONN="+slaveAddr);//send connection command
    while(1){
      if(bluetoothSerial.available()){
        recvBuf = bluetoothSerial.readString();
        debug(recvBuf);
        if(recvBuf.indexOf("CONNECT:OK") != -1){
          connectOK = 1;
          show("Connected!");
          break;
        }
        else if(recvBuf.indexOf("CONNECT:FAIL") != -1){
          show("Connect again!");
          break;
        }
      }
    }
  }while(0 == connectOK);
}

