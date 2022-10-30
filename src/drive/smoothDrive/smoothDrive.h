/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       smoothDrive.h                                             */
/*    Author:       NMS_RP                                                    */
/*    Date:         01 Oct 2022                                               */
/*    Description:  header file for driver operations functions               */
/*                    for Spin Up                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef DRIVE_H
#define DRIVE_H

// acceleration smoothing function
double motorVelocitySmoothValue(double ceil_JoyStickInputValue, int expValue);

// tank drive func
int tankDrive_f();


#endif // DRIVE_H
