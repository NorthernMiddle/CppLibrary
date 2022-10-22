#pragma config(UART_Usage, UART1, VEX_2x16_LCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, dgtl1,  encA,                sensorQuadEncoder)
#pragma config(Motor,  port1,           MotorP1,       tmotorNormal, openLoop)
#pragma config(Motor,  port10,          MotorP2,       tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*        Module:     	JSrecord.c                                             */
/*        Author:     	James Pearman                                          */
/*        Created:    	29 Oct 2011                                            */
/*        Description:  Joy Stick Record                                       */
/*			Example code to show use of joystick recording and     */
/*			playback. Simple arcade control is implemented on      */
/*			right joystick. Button 8U starts/stops recording.      */
/*        		Button 8D starts/stops playback                        */
/*        Revisions:  	V0.1                                                   */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

// delay in mS between sampling the joystick data
#define RECORD_PRECISION    100

// Maximum number of events we can store
#define MAX_EVENTS          999

// Structure to hold event data - 8 bytes per event
struct {
    int      deltaTime;
    char     JoyStick[4];
    int      buttons;
} REvent;

// Globals to hold number of stored events and current playback
// event
int     MyEventNumber = 0;
int     currentEvent = 0;

// Idle, recording or playback modes.
typedef enum {
    IsIdle = 0,
    IsRecording,
    IsPlayback
    } ControlMode;

ControlMode MyControlMode;

// temporary storage for joystick data during playback
int     vexRT_Resampled[4];

// The array holding all our event data
REvent  MyEvents[MAX_EVENTS];

long    currentEventTime;

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Initialize the array with pre ecorded data                                 */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
void initData(){
    // Paste data here cut from the debug Stream window.

}


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Convert the joystick buttons into a bitfield (well sort of)                */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
int GetButtons(){
    int buttons = 0;
    
    buttons |= (vexRT[ Btn7U ] == 1) ? 0x01  : 0;
    buttons |= (vexRT[ Btn7D ] == 1) ? 0x02  : 0;
    buttons |= (vexRT[ Btn7L ] == 1) ? 0x04  : 0;
    buttons |= (vexRT[ Btn7R ] == 1) ? 0x08  : 0;

    buttons |= (vexRT[ Btn8U ] == 1) ? 0x10  : 0;
    buttons |= (vexRT[ Btn8D ] == 1) ? 0x20  : 0;
    buttons |= (vexRT[ Btn8L ] == 1) ? 0x40  : 0;
    buttons |= (vexRT[ Btn8R ] == 1) ? 0x80  : 0;

    buttons |= (vexRT[ Btn5U ] == 1) ? 0x100 : 0;
    buttons |= (vexRT[ Btn5D ] == 1) ? 0x200 : 0;

    buttons |= (vexRT[ Btn6U ] == 1) ? 0x400 : 0;
    buttons |= (vexRT[ Btn6D ] == 1) ? 0x800 : 0;

    return( buttons );
}
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Routine to add a new event to the event array                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
void AddEvent(){
	static long     lastEventTime;
	       int      deltaTime;

    if(MyEventNumber < MAX_EVENTS)
        {
        deltaTime = currentEventTime - lastEventTime;

        if( MyEventNumber > 0 )
            MyEvents[ MyEventNumber ].deltaTime = deltaTime;
        else
            MyEvents[ MyEventNumber ].deltaTime = 0;

        lastEventTime = currentEventTime;

        MyEvents[ MyEventNumber ].JoyStick[ Ch1 ] = vexRT[ Ch1 ];
        MyEvents[ MyEventNumber ].JoyStick[ Ch2 ] = vexRT[ Ch2 ];
        MyEvents[ MyEventNumber ].JoyStick[ Ch3 ] = vexRT[ Ch3 ];
        MyEvents[ MyEventNumber ].JoyStick[ Ch4 ] = vexRT[ Ch4 ];

        MyEvents[ MyEventNumber ].buttons = GetButtons();

        vexRT_Resampled[ Ch1 ] = MyEvents[ MyEventNumber ].JoyStick[ Ch1 ];
        vexRT_Resampled[ Ch2 ] = MyEvents[ MyEventNumber ].JoyStick[ Ch2 ];
        vexRT_Resampled[ Ch3 ] = MyEvents[ MyEventNumber ].JoyStick[ Ch3 ];
        vexRT_Resampled[ Ch4 ] = MyEvents[ MyEventNumber ].JoyStick[ Ch4 ];

        MyEventNumber++;
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*      Recoding task                                                          */
/*      Monitor joystick for changes and store event data                      */
/*      Max of 10 events per second                                            */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
task RecordMonitor(){
    int loopCount = 0;

    // Use timer 1 to track time
    currentEventTime = time1[ T1 ] = 0;

    // The first Event always at 0
    MyEventNumber = 0;
    AddEvent();

    while( true )
        {
        currentEventTime = time1[T1];
        currentEvent = MyEventNumber-1;

        // look for change in JoyStick position
        if( vexRT[ Ch1 ] != MyEvents[ currentEvent ].JoyStick[ Ch1 ] )
            {
            AddEvent();
            loopCount = 0;
            }
        else
        if( vexRT[ Ch2 ] != MyEvents[ currentEvent ].JoyStick[ Ch2 ] )
            {
            AddEvent();
            loopCount = 0;
            }
        else
        if( vexRT[ Ch3 ] != MyEvents[ currentEvent ].JoyStick[ Ch3 ] )
            {
            AddEvent();
            loopCount = 0;
            }
        else
        if( vexRT[ Ch4 ] != MyEvents[ currentEvent ].JoyStick[ Ch4 ] )
            {
            AddEvent();
            loopCount = 0;
            }
        else
        if( GetButtons() != MyEvents[ currentEvent ].buttons )
            {
            AddEvent();
            loopCount = 0;
            }

        // add event at least every 2 seconds
        if( ++loopCount == 20 )
            {
            AddEvent();
            loopCount = 0;
            }

        wait1Msec( RECORD_PRECISION );
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*      Playback task                                                          */
/*                                                                             */
/*      As the name implies, use the recorded information to drive the robot.  */
/*	The time for the next event is calculated and compared to the current  */
/*	time, when the time for the next event is reached the variables        */
/*	actually driving the motors are updated. This is repeated for every    */
/*	event until the end of the recorded data is reached.		       */
/*-----------------------------------------------------------------------------*/

task Playback(){
    long    EventTime;

    currentEventTime = time1[ T1 ] = 0;

    currentEvent = 0;
    EventTime    = 0;

    while( currentEvent < MyEventNumber )
        {
        EventTime = EventTime + MyEvents[ currentEvent ].deltaTime;

        do
            {
            wait1Msec(10);
            currentEventTime = time1[ T1 ];
            } while( currentEventTime < EventTime );

        vexRT_Resampled[ Ch1 ] = MyEvents[ currentEvent ].JoyStick[ Ch1 ];
        vexRT_Resampled[ Ch2 ] = MyEvents[ currentEvent ].JoyStick[ Ch2 ];
        vexRT_Resampled[ Ch3 ] = MyEvents[ currentEvent ].JoyStick[ Ch3 ];
        vexRT_Resampled[ Ch4 ] = MyEvents[ currentEvent ].JoyStick[ Ch4 ];

        // Not doing anything with the buttons yet

        currentEvent++;
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*      Task to display status on the LCD                                      */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task 
LcdStatus(){
    string str;
    float  timer;

    bLCDBacklight = true;

    while( true )
        {
        setLCDPosition(0, 0);

        if( MyControlMode == IsRecording )
            sprintf(str,"Record   %3d/%3d", MyEventNumber, MAX_EVENTS );
        else
        if( MyControlMode == IsPlayback )
            sprintf(str,"Play     %3d/%3d", currentEvent, MyEventNumber );
        else
            sprintf(str,"Idle     %3d/%3d", MyEventNumber, MAX_EVENTS );

        displayNextLCDString(str);

        setLCDPosition(1, 0);
        timer = currentEventTime/1000.0;
        sprintf(str,"%04d %04d  %5.1f", motor[ MotorP1 ], motor[ MotorP2 ], timer );
        displayNextLCDString(str);

        wait1Msec(100);
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*      Demo - control 2 motors using playback or record data                  */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task driveMotor(){
    int drive1, drive2;

    while( true )
        {
        if( MyControlMode == IsRecording )
            {
            drive1 = vexRT_Resampled[ Ch1 ];
            drive2 = vexRT_Resampled[ Ch2 ];
            }
        else
        if( MyControlMode == IsPlayback )
            {
            drive1 = vexRT_Resampled[ Ch1 ];
            drive2 = vexRT_Resampled[ Ch2 ];
            }
        else
            {
            // change this if you still want to drive
            // when not recording
            drive1 = 0;
            drive2 = 0;
            }

        // arcade drive
        motor[ MotorP1 ] = (drive2 + drive1) / 2;
        motor[ MotorP2 ] = (drive2 - drive1) / 2;

        wait1Msec( 10 );
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Dump contents of the event data array to the debug stream                  */
/*  code is awkward as we are limited hy the 20 char limit on strings          */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

void dumpData(){
    int     i;
    string str;

    for(i=0;i<MyEventNumber;i++)
        {
        // string support sucks
        // 20 char limit is really annoying

        sprintf(str, "// Event %d",i);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        sprintf(str, "deltaTime = %d;",MyEvents[i].deltaTime);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        writeDebugStream("JoyStick[Ch1] = ");
        sprintf(str, "%d;",MyEvents[i].JoyStick[ Ch1 ]);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        writeDebugStream("JoyStick[Ch2] = ");
        sprintf(str, "%d;",MyEvents[i].JoyStick[ Ch2 ]);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        writeDebugStream("JoyStick[Ch3] = ");
        sprintf(str, "%d;",MyEvents[i].JoyStick[ Ch3 ]);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        writeDebugStream("JoyStick[Ch4] = ");
        sprintf(str, "%d;",(long)MyEvents[i].JoyStick[ Ch4 ]);
        writeDebugStreamLine(str);

        sprintf(str,"MyEvents[%d].", i);
        writeDebugStream(str);
        sprintf(str, "buttons = %d;",MyEvents[i].buttons);
        writeDebugStreamLine(str);

        // Wait for while if the debug stream is nearly full
        if( getAvailSpaceInDebugStream() < 256 )
            wait1Msec( 2000 );

        wait1Msec(50);
        }

    writeDebugStream("MyEventNumber = ");
    sprintf(str, "%d;",MyEventNumber);
    writeDebugStreamLine(str);
}


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*      Main task                                                              */
/*      Monitor buttons to start and stop recording                            */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task main()
{
    // start persistant tasks
    StartTask( driveMotor );
    StartTask( LcdStatus );

    initData();

    while( true )
        {
        // Button 8 UP  - start/stop recording
        if( ((vexRT[ Btn8U ] == 1) || (nLCDButtons & kButtonRight)) && (MyControlMode != IsPlayback) )
            {
            // set mode on button press
            MyControlMode = (MyControlMode == IsIdle) ? IsRecording : IsIdle;

            // start or stop record task
            if( MyControlMode == IsRecording )
                StartTask( RecordMonitor, 10 );
            else
                StopTask( RecordMonitor );

            // wait for button release
            while( ( vexRT[ Btn8U ] == 1 ) || (nLCDButtons & kButtonRight ))
                wait1Msec( 50 );
            }


        // Button 8 DOWN - start/stop playback
        if( ((vexRT[ Btn8D ] == 1) || (nLCDButtons & kButtonLeft)) && (MyControlMode != IsRecording) )
            {
            // set mode on button press
            MyControlMode = (MyControlMode == IsIdle) ? IsPlayback : IsIdle;

            // Start or stop playback task
            if( MyControlMode == IsPlayback )
                StartTask( Playback, 10 );
            else
                StopTask( Playback );

            // wait for button release
            while( ( vexRT[ Btn8D ] == 1 ) || (nLCDButtons & kButtonLeft))
                wait1Msec( 50 );
            }

        // center button dumps the event array
        if( nLCDButtons & kButtonCenter )
            {
            // dump event array
            dumpData();

            // wait for button release
            while( nLCDButtons & kButtonCenter )
                wait1Msec( 50 );
            }

        // Wait for playback task to end
        if( (MyControlMode == IsPlayback) && (getTaskState( Playback ) == taskStateStopped ) )
            {
            wait1Msec(100);
            MyControlMode = IsIdle;
            }

        // dont hog cpu
        wait1Msec( 50 );
        }
}