#include <Arduino.h>
#include <Stepper28BYJ48.h>
    //AO NOTES --> could add forward back options+motorknob

StepperMotor::StepperMotor(int In1, int In2, int In3, int In4, int motorTiming = 800){
    // Record pin numbers in the inputPins array
    this->inputPins[0] = In1;
    this->inputPins[1] = In2;
    this->inputPins[2] = In3;
    this->inputPins[3] = In4;

    // Iterate through the inputPins array, setting each one to output mode
    for(int inputCount = 0; inputCount < 4; inputCount++){
        pinMode(this->inputPins[inputCount], OUTPUT);
    }
     duration = 50;//this doesn't seem to do anything

     this -> motorSpeed = motorTiming;  //variable to set stepper speed

}

void StepperMotor::setStepDuration(int duration){
    this->duration = duration;
}

// functionReturnType FunctionName(optionalArgType optArg = defaultValue);



void StepperMotor::stopGo(bool direction = true){
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
  if(direction == true){
    for(int i = 0; i < 8; i++){
    for(int j = 0; j<4; j++){
       digitalWrite(inputPins[j], bitRead(lookup[i], j));
      }
      delayMicroseconds(motorSpeed);
    }
  }else{
    for(int i = 7; i >= 0; i--){
    for(int j = 0; j<4; j++){
       digitalWrite(inputPins[j], bitRead(lookup[i], j));
      }
      delayMicroseconds(motorSpeed);
    }
  }
}

void StepperMotor::turnOff(){
  for(int i = 0; i < 4; i++){
    digitalWrite(inputPins[i], bitRead(B00000,i));
    }
}


void StepperMotor::step(int noOfSteps){
    /*
        The following 2D array represents the sequence that must be
        used to acheive rotation. The rows correspond to each step, and
        the columns correspond to each input. L
    */
    bool sequence[][4] = {{LOW, LOW, LOW, HIGH },
                          {LOW, LOW, HIGH, HIGH},
                          {LOW, LOW, HIGH, LOW },
                          {LOW, HIGH, HIGH, LOW},
                          {LOW, HIGH, LOW, LOW },
                          {HIGH, HIGH, LOW, LOW},
                          {HIGH, LOW, LOW, LOW },
                          {HIGH, LOW, LOW, HIGH}};

    int factor = abs(noOfSteps) / noOfSteps;    // If noOfSteps is +, factor = 1. If noOfSteps is -, factor = -1
    noOfSteps = abs(noOfSteps);    // If noOfSteps was in fact negative, make positive for future operations

    /*
        The following algorithm runs through the sequence the specified number
        of times
    */
    for(int sequenceNum = 0;  sequenceNum <= noOfSteps/8; sequenceNum++){
        for(int position = 0; ( position < 8 ) && ( position < ( noOfSteps - sequenceNum*8 )); position++){
            delay(duration);
            for(int inputCount = 0; inputCount < 4; inputCount++){
                digitalWrite(this->inputPins[inputCount], sequence[(int)(3.5 - (3.5*factor) + (factor*position))][inputCount]);
            }
        }
    }
}
