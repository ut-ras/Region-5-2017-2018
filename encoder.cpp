#include "../inc/encoder.h"

#define c_EncoderInterruptA 0
#define c_EncoderInterruptB 1
#define c_EncoderPinA 2
#define c_EncoderPinB 3
#define EncoderIsReversed

encoder::encoder(int _masterAddress, int _slaveAddress){
	Wire.begin(_slaveAddress);
	Wire.onRequest(requestEvent);

	pinMode(c_EncoderPinA, INPUT);      // sets pin A as input
	digitalWrite(c_EncoderPinA, HIGH);  // turn on pullup resistors
	pinMode(c_EncoderPinB, INPUT);      // sets pin B as input
	digitalWrite(c_EncoderPinB, HIGH);  // turn on pullup resistors
	attachInterrupt(c_EncoderInterruptA, HandleMotorInterruptA, CHANGE);
	attachInterrupt(c_EncoderInterruptB, HandleMotorInterruptB, CHANGE);
}

long encoder::getCurrentDistance(){
	return _EncoderTicks;
}

void encoder::resetEncoder(){
	data.dataLong = 0;
}

void encoder::HandleMotorInterruptA(){
  _EncoderBSet = digitalReadFast(c_EncoderPinB);
  _EncoderASet = digitalReadFast(c_EncoderPinA);

  _EncoderTicks+=ParseEncoder();

  _EncoderAPrev = _EncoderASet;
  _EncoderBPrev = _EncoderBSet;
}

void encoder::HandleMotorInterruptB(){
  // Test transition;
  _EncoderBSet = digitalReadFast(c_EncoderPinB);
  _EncoderASet = digitalReadFast(c_EncoderPinA);

  _EncoderTicks+=ParseEncoder();

  _EncoderAPrev = _EncoderASet;
  _EncoderBPrev = _EncoderBSet;
}

int encoder::ParseEncoder(){
  if(_EncoderAPrev && _EncoderBPrev){
    if(!_EncoderASet && _EncoderBSet) return 1;
    if(_EncoderASet && !_EncoderBSet) return -1;
  }else if(!_EncoderAPrev && _EncoderBPrev){
    if(!_EncoderASet && !_EncoderBSet) return 1;
    if(_EncoderASet && _EncoderBSet) return -1;
  }else if(!_EncoderAPrev && !_EncoderBPrev){
    if(_EncoderASet && !_EncoderBSet) return 1;
    if(!_EncoderASet && _EncoderBSet) return -1;
  }else if(_EncoderAPrev && !_EncoderBPrev){
    if(_EncoderASet && _EncoderBSet) return 1;
    if(!_EncoderASet && !_EncoderBSet) return -1;
  }
}

void encoder::requestEvent(){
  digitalWriteFast(LED_BUILTIN, HIGH);

  Wire.write((byte)((_EncoderTicks & 0xFF000000) >> 24));
  Wire.write((byte)((_EncoderTicks & 0x00FF0000) >> 16));
  Wire.write((byte)((_EncoderTicks & 0x0000FF00) >> 8));
  Wire.write((byte)((_EncoderTicks & 0x000000FF)));

  digitalWriteFast(LED_BUILTIN, LOW);
}
