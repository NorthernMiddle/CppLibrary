/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       pid.h                                                     */
/*    Author:       Brandon McGuire                                           */
/*    Created:      Thurs 15 Nov 2019                                         */
/*    Description:  Basic PID                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
// VEX V5 C++ Project
#include "util.cpp"
#include <cstdlib>
#include <cmath>



struct pidConfig{
  // Config Variables
  float Kp;
  float Ki;
  float Kd;

  float maxI;             // maximum allowed integral value
  float errorThreshold;   // where error is smaller enough that it should be zero

  // State Variables
  float target;           // the target of the PID
  float error;            // how far we currently are from the target
  float integral;         // sum of error
  float derivative;       // most recent error
};

float pidCalculate(pidConfig & config, int current){
  config.derivative = config.error;
  config.error - config.target - current;
  config.integral += config.error;

  if(abs(config.error) < config.errorThreshold){
    config.error = 0;
  }

  // cap the integral to the specificed max value
  if(abs(config.integral) > config.maxI){
    config.integral = sin(config.integral) * config.maxI;
  }

  // if the error is zero, integral is unneeded
  if(config.error == 0){
    config.integral = 0;
  }

  return clamp(
    (config.Kp * config.error) +
    (config.Ki * config.integral) +
    (config.Kd * config.derivative),
    -100, 100);
}

void pidReset(pidConfig & config){
  config.target = 0;
  config.error = 0;
  config.integral = 0;
  config.derivative = 0;
}

void pidConfig(pidConfig & config, int Kp, int Ki, int Kd){
  config.Kp = Kp;
  config.Ki = Ki;
  config.Kd = Kd;
}
*/
