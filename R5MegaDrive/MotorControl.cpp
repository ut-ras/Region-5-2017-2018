    #include "MotorControl.h"

    #include <Arduino.h>
    #include <Adafruit_MotorShield.h>
    #include <PID_v1.h>
    #include "utility/Adafruit_MS_PWMServoDriver.h"

    MotorControl::MotorControl(int lA, int lB, int rA, int rB) {
      //Field Initializations

      l_Encoder = new encoder(lA, lB);
      r_Encoder = new encoder(rA, rB);

      //Serial.println("inside init");

      AFMS = new Adafruit_MotorShield();

      r_Motor = AFMS->getMotor(3);
      l_Motor = AFMS->getMotor(4);

      //Serial.println("AFMS init");

      l_correction = 0;
      r_correction = 0;

      l_EncoderSpeed = 0;
      r_EncoderSpeed = 0;

      prevTime = 0;

      leftKp = 0.25;
      leftKi = 15;
      leftKd = 0;
      l_PID = new PID(&l_EncoderSpeed, &l_PIDSpeed, &l_SetpointSpeed, leftKp, leftKi, leftKd, DIRECT);

      rightKp = 0.25;
      rightKi = 15;
      rightKd = 0;
      r_PID = new PID(&r_EncoderSpeed, &r_PIDSpeed, &r_SetpointSpeed, rightKp, rightKi, rightKd, DIRECT);

      //Serial.println("PID init");

      //Motor Initialization
      AFMS->begin();  // create with the default frequency 1.6KHz

      l_Motor->setSpeed(10);
      r_Motor->setSpeed(10);
      l_PIDSpeed = 10;
      r_PIDSpeed = 10;

      //PID Initialization
      l_PID->SetSampleTime(5);
      l_PID->SetMode(AUTOMATIC);
      l_PID->SetOutputLimits(0, 255);

      r_PID->SetSampleTime(5);
      r_PID->SetMode(AUTOMATIC);
      r_PID->SetOutputLimits(0, 255);


      lineSensorBack = new arrayline(LS_DIGITAL);
      lineSensorFront = new arrayline(LS_ANALOG);

      //delay for testing purposes
      delay(500);
      //Serial.println("Motor Control Initialized");

      currentCmd = STOP;
      useArray=false;
      startTicks = 0;

      l_SetpointSpeed = 0;
      r_SetpointSpeed = 0;
    }


    //Public Functions

    encoder* MotorControl::getLeftEncoder() {
      return l_Encoder;
    }

    encoder* MotorControl::getRightEncoder() {
      return r_Encoder;
    }

    void MotorControl::updateMotorControl() {      //update motor speeds with PID
      if(useArray==false  && (l_Encoder->getPos() > startTicks+80) )
      {
        useArray=true;
      }
      if (useArray && (currentCmd < FWDNOLINE)) {
        calculateLSCorrections();
        //l_SetpointSpeed += l_correction;
        //r_SetpointSpeed += r_correction;
      }
      if(useArray && FWDNOLINE)
      {

      }
      if (currentCmd != STOP) {
        calculateEncoderSpeeds();
        calculatePIDSpeeds();
        setMotorSpeeds(abs(l_PIDSpeed), abs(r_PIDSpeed));
      }
    }

    void MotorControl::turninPlace(int dir) {    //use Directions enum LEFT or RIGHT
      if (dir == RIGHT) {
        l_Motor->run(FORWARD);
        r_Motor->run(BACKWARD);
      }
      else if (dir == LEFT) {
        l_Motor->run(BACKWARD);
        r_Motor->run(FORWARD);
      }
    }

    void MotorControl::moveStraight(int dir) {              //use Directions enum FWD or BACK
      if (dir == BACK) {
        l_Motor->run(BACKWARD);
        r_Motor->run(BACKWARD);
      }
      else if (dir == FWD) {
        l_Motor->run(FORWARD);
        r_Motor->run(FORWARD);
      }
    }

    void MotorControl::stopMotors(int lastCmd) {
      setMotorSpeeds(0, 0);

      int waitTimeMs = 10;
      int r_pos_s = r_Encoder->getPos();
      int l_pos_s = l_Encoder->getPos();

      int r_pos_last = r_pos_s;
      int l_pos_last = l_pos_s;

      delay(waitTimeMs);
      int r_pos_current = r_Encoder->getPos();
      int l_pos_current = l_Encoder->getPos();

      int loopCount = 0;
      /*
      while ((r_pos_last != r_pos_current) || (l_pos_last != l_pos_current)) {
        r_pos_last = r_pos_current;
        l_pos_last = l_pos_current;
        r_pos_current = r_Encoder->getPos();
        l_pos_current = l_Encoder->getPos();
        delay(waitTimeMs);
      }

      int l_diff = abs(l_pos_current - l_pos_s);
      int r_diff = abs(r_pos_current - r_pos_s);

      Serial.println("encoder overshoot l:" + String(l_diff) + " r:" + String(r_diff) + " loopcount:" + String(loopCount));

      //correct motors
      if ((lastCmd == FWD1) || (lastCmd == FWD2) || (lastCmd == FWD3) || (lastCmd == FWDNOLINE)) {
        setMotorSpeeds(20, 20);
        moveStraight(BACK);

      }
      else if ((lastCmd == BACK1) || (lastCmd == BACK2) || (lastCmd == BACK3)) {
        setMotorSpeeds(20, 20);
        moveStraight(FWD);

      }
      //add if we want correction for the turn functions
      /*else if ((lastCmd == LEFTIP) || (lastCmd == LEFT45) || (lastCmd == LEFT90) || (lastCmd == LEFT135) || (lastCmd == LEFT180)) {

      }
      else if ((lastCmd == RIGHTIP) || (lastCmd == RIGHT45) || (lastCmd == RIGHT90) || (lastCmd == RIGHT135) || (lastCmd == RIGHT180) {

      }
      else {
        return;
        */
    /*  }

      //count encoder ticks for correction
      r_pos_s = r_Encoder->getPos();
      l_pos_s = l_Encoder->getPos();

      while ((abs(l_pos_s - l_pos_current) < l_diff) || (abs(r_pos_s - r_pos_current) < r_diff)) {
        r_pos_current = r_Encoder->getPos();
        l_pos_current = l_Encoder->getPos();

        if (abs(l_pos_s - l_pos_current) > l_diff) {
          l_Motor->setSpeed(0);
        }
        else if (abs(r_pos_s - r_pos_current) > r_diff) {
          r_Motor->setSpeed(0);
        }
        delay(5);
      }
      */

      setMotorSpeeds(0, 0);
    }



    //Private Functions
    //note: switched around corrections for testing while sensor is on rear, so we can move backwards and pretend its going fwd
    void MotorControl::calculateLSCorrections() {
      Serial.println("Line Sensor Corrections");

      //grab fwd vs back and move speed
      bool fwd = (currentCmd >= 0) && (currentCmd <= 2);
      int moveSpeed = 0;
      if (currentCmd % 3 == 0) { moveSpeed = LOW_SPEED; }
      else if (currentCmd % 3 == 1) { moveSpeed = MID_SPEED; }
      else { moveSpeed = HIGH_SPEED; }

      //get both line sensor positions -4000 is left, +4000 is right, 1000 for each sensor
      //int lineSensorWeightBack = lineSensorBack->getLinePosition();
      int lineSensorWeightBack = 0;
      int lineSensorWeightFront = lineSensorFront->getLinePosition();
      Serial.println("front weight: " + String(lineSensorWeightFront) + " / back weight: " + String(lineSensorWeightBack));

      //single sensor
      /*if(lineSensorWeightFront <= -1500) {
        turninPlace(fwd?LEFT:RIGHT);
      }
      else if(lineSensorWeightFront >= 1500) {
        turninPlace(fwd?RIGHT:LEFT);
      }
      else {
        moveStraight(fwd?FWD:BACK);
      }*/


      //calculate general position for each sensor. double sensors: -1 = left, 0 = middle, 1 = right
      int cutoff = 2000;
      //int backSection = (lineSensorWeightBack <= -1 *cutoff) ? (-1) : ((lineSensorWeightBack >= cutoff)?1:0);
      int backSection = 0;
      int frontSection = (lineSensorWeightFront <= -1 * cutoff) ? (-1) : ((lineSensorWeightFront >= cutoff)?1:0);
      Serial.println("front loc: " + String(frontSection) + " / back loc: " + String(backSection));

      boolean turnRight = ((frontSection == 0) && (backSection == -1)) || (frontSection == 1);
      boolean turnLeft = ((frontSection == 0) && (backSection == 1)) || (frontSection == -1);
      Serial.println("turn right: " + String(turnRight) + " / turn left: " + String(turnLeft));

      int rawWeighted = lineSensorFront->getWeightedValue();
      double correction = rawWeighted/12000.0;
      Serial.println("speed correction: " + String(correction));

      if(turnLeft) {
        l_SetpointSpeed = 0;
        r_SetpointSpeed = 90;
      }
      else if(turnRight) {
        r_SetpointSpeed = 0;
        l_SetpointSpeed = 90;
      }
      else {
        r_SetpointSpeed = moveSpeed - correction * moveSpeed;
        l_SetpointSpeed = moveSpeed + correction * moveSpeed;
      }
      moveStraight(fwd?FWD:BACK);

    }

    //set desired speeds
    void MotorControl::setSetpointSpeeds(int rotSpeed) {                      //deg / sec
      setSetpointSpeeds(rotSpeed, rotSpeed);
    }

    void MotorControl::setSetpointSpeeds(int l_rotSpeed, int r_rotSpeed) {    //deg / sec
      l_SetpointSpeed = l_rotSpeed;
      r_SetpointSpeed = r_rotSpeed;
    }

    //updateMotorSpeeds functions
    void MotorControl::calculateEncoderSpeeds() {
      if (vSampleCount < numVSamples) {
        unsigned long t = millis();

        //Serial.println("Left Encoder Diff " + String(l_Encoder->getPos() - l_PrevEncoderPos));
        //Serial.println("Time Diff " + String((t - prevTime)));

        leftVSampleSum += abs(2 * (l_Encoder->getPos() - l_PrevEncoderPos) / (.001 * double(t - prevTime)));
        l_PrevEncoderPos = l_Encoder->getPos();

        rightVSampleSum += abs(2 * (r_Encoder->getPos() - r_PrevEncoderPos) / (.001 * double(t - prevTime)));
        r_PrevEncoderPos = r_Encoder->getPos();

        prevTime = t;
        vSampleCount++;
      }
      if (vSampleCount == numVSamples) {
        //double lv = normalizeSpeedForAFMS(leftVSampleSum / numVSamples);
        //double rv = normalizeSpeedForAFMS(rightVSampleSum / numVSamples);
        double lv = (leftVSampleSum/ numVSamples);
        double rv = (rightVSampleSum/ numVSamples);

        l_EncoderSpeed = lv;
        r_EncoderSpeed = rv;

        leftVSampleSum = 0;
        rightVSampleSum = 0;
        vSampleCount = 0;

        //l_correction = 0;
        //r_correction = 0;
      }
    }
    void MotorControl::calculatePIDSpeeds() {
      l_PID->Compute();
      r_PID->Compute();
    }

    void MotorControl::setMotorSpeeds(int l_rotSpeed, int r_rotSpeed) {     //set actual speeds, direct output to AFMS motors
      l_Motor->setSpeed(l_rotSpeed);
      r_Motor->setSpeed(r_rotSpeed);
    }



    // ----------setMotorMode----------
    // Some sort of intermediary function
    // Calls setSetpointSpeeds and moveStraight
    // Input: Commands Enum
    //const uint8_t setMotorModeConstants[9] = {90, 135, 180, 90, 135, 180, 90, 90, 0};
    //const uint8_t setMotorDirectionConstants[9] = {FWD, FWD, FWD, BACK, BACK, BACK, LEFT, RIGHT, 0};
    void MotorControl::setMotorMode(int c) {
      Serial.println("Set Command: " + String(c));
      int lastCmd = currentCmd;
      currentCmd = c;
      switch (c) {
        case FWD1:
          setSetpointSpeeds(LOW_SPEED);
          moveStraight(FWD);
          useArray=false;
          startTicks=l_Encoder->getPos();
          break;
        case FWD2:
          setSetpointSpeeds(MID_SPEED);
          moveStraight(FWD);
          useArray=false;
          startTicks=l_Encoder->getPos();
          break;
        case FWD3:
          setSetpointSpeeds(HIGH_SPEED);
          moveStraight(FWD);
          useArray=false;
          startTicks=l_Encoder->getPos();
          break;
        case BACK1:
          setSetpointSpeeds(LOW_SPEED);
          moveStraight(BACK);
          break;
        case BACK2:
          setSetpointSpeeds(MID_SPEED);
          moveStraight(BACK);
          break;
        case BACK3:
          setSetpointSpeeds(HIGH_SPEED);
          moveStraight(BACK);
          break;
        case FWDNOLINE:
          setSetpointSpeeds(LOW_SPEED);
          moveStraight(FWD);
          break;
        case LEFTIP:
          setSetpointSpeeds(LOW_SPEED);
          turninPlace(LEFT);
          break;
        case RIGHTIP:
          setSetpointSpeeds(LOW_SPEED);
          turninPlace(RIGHT);
          break;
        case LEFT45:
          turnManeuver(LEFT, 1);
          break;
        case LEFT90:
          turnManeuver(LEFT, 2);
          break;
        case LEFT135:
          turnManeuver(LEFT, 3);
          break;
        case LEFT180:
          turnManeuver(LEFT, 4);
          break;
        case RIGHT45:
          turnManeuver(RIGHT, 1);
          break;
        case RIGHT90:
          turnManeuver(RIGHT, 2);
          break;
        case RIGHT135:
          turnManeuver(RIGHT, 3);
          break;
        case RIGHT180:
          turnManeuver(RIGHT, 4);
          break;
        case STOP:
          stopMotors(lastCmd);
          break;
        case RETURNWHITELEFT:
          forwardToWhite(LEFT);
          break;
        case RETURNWHITERIGHT:
          forwardToWhite(RIGHT);
          break;
        default:
          Serial.println("Undefined Command Error");
          stopMotors(lastCmd);
          break;
      }

      /*if(setMotorModeConstants[c] == 0) {
        stopMotors(lastCmd);
        return;
      }
      else {
        setSetpointSpeeds(setMotorModeConstants[c]);
        moveStraight(setMotorDirectionConstants[c]);
      }*/

    }

    void MotorControl::serialDebugOutput(boolean plotter) {
      if (plotter) {
        //Serial.println(int(l_EncoderSpeed));
        Serial.print(int(r_EncoderSpeed));
        Serial.print(",");
        Serial.println(int(l_EncoderSpeed));

      }
      else {
        //Serial.print("Line Sensor C: " + String(l_correction)+ " / " + String(r_correction));
        Serial.print(" Encoder: " +String(l_EncoderSpeed)+" / "+ String(r_EncoderSpeed));
        Serial.print(" Set: " + String(l_SetpointSpeed)+ "/ " + String(r_SetpointSpeed));
        Serial.print(" PID out: " + String(l_PIDSpeed)+ " / " + String(r_PIDSpeed) + "\n");
        Serial.println();
      }
    }

    //AUTOTUNING PID's (our version)

    void MotorControl::sweepPValues(double minP, double maxP, double stepP) {
      setIValues(0);

      double r_bestP = 0;
      double l_bestP = 0;

      double r_minDiff = 1000;
      double l_minDiff = 1000;

      for(double i = minP; i<maxP; i+=stepP) {
        Serial.println("P"+String(i));
        setPValues(i);

        double l_avgDiff = 0;
        double r_avgDiff = 0;

        for (int j =0; j<100; j++) {
          updateMotorControl();
          serialDebugOutput(false);
          l_avgDiff += abs(l_EncoderSpeed - l_SetpointSpeed);
          r_avgDiff += abs(r_EncoderSpeed - r_SetpointSpeed);
          delay(LOOP_DELAY);
        }

        l_avgDiff /= 100;
        r_avgDiff /= 100;

        if (l_avgDiff < l_minDiff) {
          l_minDiff = l_avgDiff;
          l_bestP = i;
        }
        if (r_avgDiff < r_minDiff) {
          r_minDiff = r_avgDiff;
          r_bestP = i;
        }
      }

      setMotorMode(STOP);
      while(1) {
        Serial.println("Best P vals: L=" + String(r_bestP) + " R=" + String(l_bestP));
        delay(3000);
      }
    }

    void MotorControl::sweepIValues(double minI, double maxI, double stepI) {
      double r_bestI = 0;
      double l_bestI = 0;

      double r_minDiff = 1000;
      double l_minDiff = 1000;

      for(double i = minI; i<maxI; i+=stepI) {
        Serial.println("I"+String(i));
        setIValues(i);

        double l_avgDiff = 0;
        double r_avgDiff = 0;

        for (int i =0; i<100; i++) {
          updateMotorControl();
          serialDebugOutput(false);
          l_avgDiff += abs(l_EncoderSpeed - l_SetpointSpeed);
          r_avgDiff += abs(r_EncoderSpeed - r_SetpointSpeed);
          delay(LOOP_DELAY);
        }

        l_avgDiff /= 100;
        r_avgDiff /= 100;

        if (l_avgDiff < l_minDiff) {
          l_minDiff = l_avgDiff;
          l_bestI = i;
        }
        if (r_avgDiff < r_minDiff) {
          r_minDiff = r_avgDiff;
          r_bestI = i;
        }

        setIValues(0);
        delay(100);
      }

      setMotorMode(STOP);
      while(1) {
        Serial.println("Best I vals: L=" + String(r_bestI) + " R=" + String(l_bestI));
        delay(3000);
      }
    }



    //Method Does not work properly because p values are not tuned by getting the error. We need to look at
    // The way to tune pid is to
    void MotorControl::setPValues(double p_val) {
      l_PID->SetTunings(p_val, 0, 0);
      r_PID->SetTunings(p_val, 0, 0);
    }

    void MotorControl::setIValues(double i_val)
    {
      l_PID->SetTunings(0.25, i_val, 0);
      r_PID->SetTunings(0.25, i_val, 0);
      leftKi = i_val;
      rightKi = i_val;
    }

    //Turn maneuver functions

    void MotorControl::turnManeuver(int dir, int num45Deg){
      //moveStraightEncoderTicks(FWD, 10);
      turnEncoderTicks(dir, num45Deg * 57);
    }

void MotorControl::moveStraightEncoderTicks(int dir, int encoderTicks){
  int initLTicks = l_Encoder->getPos();
  int initRTicks = r_Encoder->getPos();

  setSetpointSpeeds(LOW_SPEED, LOW_SPEED);

  moveStraight(dir);

  while((abs(initRTicks - r_Encoder->getPos()) < encoderTicks) && (abs(initLTicks - l_Encoder->getPos()) < encoderTicks)){
    calculateEncoderSpeeds();
    calculatePIDSpeeds();
    setMotorSpeeds(abs(l_PIDSpeed), abs(r_PIDSpeed));

    delay(LOOP_DELAY);
  }
  setMotorMode(STOP);
}

void MotorControl::forwardToWhite(int dir){
  moveStraightEncoderTicks(FWD, 535);
  turnEncoderTicks(dir, 238);;
  moveStraightEncoderTicks(FWD, 227);
}

void MotorControl::turnEncoderTicks(int dir, int encoderTicks){
  int initLTicks = l_Encoder->getPos();
  int initRTicks = r_Encoder->getPos();

  setSetpointSpeeds(LOW_SPEED, LOW_SPEED);

  turninPlace(dir);

  Serial.println("Starting the turn");

  while((abs(initRTicks-r_Encoder->getPos()) < encoderTicks) && (abs(initLTicks-l_Encoder->getPos()) < encoderTicks)){
    calculateEncoderSpeeds();
    calculatePIDSpeeds();
    setMotorSpeeds(abs(l_PIDSpeed), abs(r_PIDSpeed));

    Serial.println("Turning");
    delay(LOOP_DELAY);
  }
  Serial.println("Stopping");
  setMotorMode(STOP);
}
