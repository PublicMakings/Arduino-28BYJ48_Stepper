## Arduino-28BYJ48_Stepper
### *Arduino 28BYJ48 Stepper Motor .H and .CCP plus Sketch*

This is my first customizing of a header file for an arduino project. In it I have combined from a couple of sources to create a set of features which allow for moving the motor either continuously _Clockwise & AntiClockwise_, as well as moving by _incremented number of steps_.

These files are a combination of code found at **[4tronix][1] & [Engy Fun][2]**. This [Instrucable][3] covers a bit more detail from the Engy Fun post, and here is another [potential resource][4].

Eventually I would like to add in a *potentiometer*.method as well.

### *functions() & .methods*

Initialize the StepperMotor Object with default speed of 800ms for delay on the continuous motion. 
```arduino
StepperMotor(int In1, int In2, int In3, int In4, int motorTiming = 800)
```

```arduino
StepperMotor.go(bool direction)
StepperMotor.stop()
```

Set the duration for determined number of steps.
```arduino
StepperMotor.setStepDuration(int duration)
```
fixed number of steps
```arduino
StepperMotor.step(int noOfSteps)
```

### *Example sketch with three button functions:*  
* One button runs *Clockwise continuously*
* One button runs *Anticlockwise continuously*  
* One runs for a *predetermined fixed number of steps* 
  * I believe it is best if this number is divisible by 8 if looking for precision
```
#include "Stepper28BYJ48.h"

StepperMotor motor(8,9,10,11,1000); //function which takes pin inputs and motorspeed delay

int countpin = 4; // fixed step count
int cwpin = 2;   // input pin for clockwise switch
int acwpin = 3;  //anticlockwise switch

void setup(){
  motor.setStepDuration(100); //set dealy for fixed step count

  pinMode(countpin, INPUT);
  pinMode(cwpin, INPUT);   
  pinMode(acwpin, INPUT);  
  
}

void loop(){

  //if none of the buttons make sure none of the inputs are ON.
  
  while(digitalRead(cwpin) == LOW && digitalRead(acwpin) == LOW && digitalRead(countpin) == LOW){
    motor.turnOff();
    }
    
  if (digitalRead(cwpin) == HIGH){
    motor.go(false);
    }
  else if (digitalRead(acwpin) == HIGH){
    motor.go();
    }
  else if (digitalRead(countpin) == HIGH){
    motor.step(100);
    }

}
```
### *__Bonus__ notes*
```
//********************************************************
//
//code from http://4tronix.co.uk/arduino/Stepper-Motors.php
//
//more code http://4tronix.co.uk/arduino/Downloads.php
//
//table for 8 phase stepper sequence
//------------------------------------------------------------
// _________| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
// 4 orange |  *  |  *  |     |     |     |     |     |  *  |
// 3 yellow |     |  *  |  *  |  *  |     |     |     |     |
// 2 pink   |     |     |     |  *  |  *  |  *  |     |     |
// 1 blue   |     |     |     |     |     |  *  |  *  |  *  |
//------------------------------------------------------------
//*********************************************************
//
// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
////////////////////////////////////////////////
```

[1]: http://4tronix.co.uk/arduino/Stepper-Motors.php
[2]: http://engyfun.blogspot.com.au/2015/02/here-is-source-code-for-our-28byj48.html
[3]: http://www.instructables.com/id/Arduino-Library-for-28BYJ-48-Stepper-Motor-and-ULN/
[4]: http://forum.arduino.cc/index.php?topic=422336.0
