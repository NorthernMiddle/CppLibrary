/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       util.h                                                    */
/*    Author:       NMS_RP                                                    */
/*    Created:      Mon 18 Nov 2019                                           */
/*    Description:  Utility Function File                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define PI 3.1415926535

/*
 * Clamps a value to a maximum and minimum
 * @param float val The value to clamp
 * @param float min The minimum value for the value
 * @param float max The maximum value for the value
 * @return float The clamped value
 */
float clamp(float val, float min, float max) {
  return val > max ? max : val < min ? min : val;
}

/**
 * Performs modulus for floats
 * @param float x The numerator
 * @param float y The demominator
 * @return float The remainder of x / y
 */
/* float fmodf(float x, float y) {
    return (x - y * floor(x / y));
}*/



/*
#define TURBO 6           // 600 rpm output speed --> V5 Smartmotor Blue Motor Cartridge
#define HIGHSPEED 2       // 200 rpm output speed --> V5 Smartmotor Green Motor Cartridge
#define TORQUE 1          // 100 rpm output speed --> V5 Smartmotor Red Motor Cartridge
*/

 /** Converts inches to encoder ticks, for the purpose of setting targets in PIDs
 *  Usage:
 *  inchesToTicks(10, 3.25, 1, HIGHSPEED);
 *
 * @param float unit The number inches to convert to ticks
 * @param float wheelDiameter The diameter of the wheel, in inches
 * @param float gearing The external gear ration (Speed Up => x, Torque Up => 1/x)
 * @param float motorGear The internal gear ratio of the motor (constants TURBO, HIGHSPEED, and TORQUE have been specified)
 */

/*
float inchesToTicks(float unit, float wheelDiameter, float gearing, float motorGear) {
    return (
        (unit / (motorGear * gearing)) /  // Cancel out gear ratio
        (wheelDiameter * PI)              // Divide by circumfrence to solve for rotations
    ) * 360;                              // 360 ticks in a rotation
}
 
//1800 ticks/rev for  36:1  gears Red Motor Gear Cartridge
//900 ticks/rev  for  18.1  gears Green Motor Gear Cartridge
//300 ticks/rev  for   6:1  gears Blue Motor Gear Cartridge




#define STRTOK_MAX_TOKEN_SIZE 20
#define STRTOK_MAX_BUFFER_SIZE 50
*/

/**
 * Tokenise an array of chars, using a seperator
 * @param buffer pointer to buffer we're parsing
 * @param token pointer to buffer to hold the tokens as we find them
 * @param seperator the seperator used between tokens
 * @return true if there are still tokens left, false if we're done
 */
 
 /*
bool strtok(char *buffer, char *token, char *seperator)
{
  int pos = stringFind(buffer, seperator);
  char t_buff[STRTOK_MAX_BUFFER_SIZE];
  // Make sure we zero out the buffer and token
  memset(token, 0, STRTOK_MAX_TOKEN_SIZE);
  memset(&t_buff[0], 0, STRTOK_MAX_BUFFER_SIZE);
  // Looks like we found a seperator
  if (pos >= 0)
  {
    // Copy the first token into the token buffer, only if the token is
    // not an empty one
    if (pos > 0)
      memcpy(token, buffer, pos);
    // Now copy characters -after- the seperator into the temp buffer
    memcpy(&t_buff[0], buffer+(pos+1), strlen(buffer) - pos);
    // Zero out the real buffer
    memset(buffer, 0, strlen(buffer) + 1);
    // Copy the temp buffer, which now only contains everything after the previous
    // token into the buffer for the next round.
    memcpy(buffer, &t_buff[0], strlen(&t_buff[0]));
    return true;
  }
  // We found no seperator but the buffer still contains a string
  // This can happen when there is no trailing seperator
  else if(strlen(buffer) > 0)
  {
    // Copy the token into the token buffer
    memcpy(token, buffer, strlen(buffer));
    // Zero out the remainder of the buffer
    memset(buffer, 0, strlen(buffer) + 1);
    return true;
  }
  return false;
}
*/
