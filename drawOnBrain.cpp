/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\reece.turner                                     */
/*    Created:      Fri Dec 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// collect data for on screen button
typedef struct _button {                               
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color color;
} button;

// Button definitions
button buttons[] = {                                      
  {   5,  7, 230, 105,  false, vex::red },
  {  150,  30, 60, 60,  false, vex::blue },
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */            
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0; index < nButtons; index++) {
      button *pButton = &buttons index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;
      
      return(index);
    }
    return (-1);
}
/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0; index < nButtons; index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();
    
    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }
    
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();
    
    if( (index = findButton( xpos, ypos )) >= 0 ) {
      buttons[index].state = !buttons[index].state;
      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {
      
      if( buttons*.state )
        c = buttons*.color;
      else
        c = vex::color::black;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        c = c + 0x404040;
        Brain.Screen.drawRectangle( buttons*.xpos, buttons*.ypos, buttons*.width, buttons*.height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons*.xpos, buttons*.ypos, buttons*.width, buttons*.height );
  
      // outline
      Brain.Screen.drawRectangle( buttons*.xpos, buttons*.ypos, buttons*.width, buttons*.height, vex::color::transparent );
    }
}

/*
void drawRedAutonBtn(){
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(3);

  Brain.Screen.setFillColor("#E11218"); // RED
  Brain.Screen.drawRectangle( 5, 7, 230, 105 );

  Brain.Screen.setCursor( 2, 4 );  // ROW, COLUMN
  Brain.Screen.setFont(propL);
  Brain.Screen.print( "RED" );

  Brain.Screen.setCursor( 3, 4 ); // ROW, COLUMN
  Brain.Screen.setFont(propL);
  Brain.Screen.print( "ALLIANCE" );

}

void drawBlueAutonBtn(){
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(3);

  Brain.Screen.setFillColor("#1870d5"); // BLUE
  Brain.Screen.drawRectangle( 245, 7, 230, 105 );

  Brain.Screen.setCursor( 2, 21 );  // ROW, COLUMN
  Brain.Screen.setFont(propL);
  Brain.Screen.print( "BLUE" );

  Brain.Screen.setCursor( 3, 21 ); // ROW, COLUMN
  Brain.Screen.setFont(propL);
  Brain.Screen.print( "ALLIANCE" );

}

void drawImgAutonBlock(){
  
  Brain.Screen.setPenWidth(3);

  vex::color maroon = vex::color( 128, 0, 0 );
  Brain.Screen.setPenColor( maroon ); // MAROON
  vex::color gold = vex::color( 212, 175, 55 );
  Brain.Screen.setFillColor( gold ); // GOLD
  Brain.Screen.drawRectangle( 15, 190, 450, 40 );

  Brain.Screen.setFont(propM);
  Brain.Screen.setPenColor( maroon ); // MAROON
  Brain.Screen.setCursor( 11, 7 ); // ROW, COLUMN
  Brain.Screen.print( "Northern Middle School Robotics Program" );


  Brain.Screen.setFont(monoM);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setPenWidth( 5 );
  Brain.Screen.setCursor( 8, 10 );
  Brain.Screen.print(" ** Auton Alliance Selection ** ");
  Brain.Screen.setCursor( 9, 5 );
  Brain.Screen.print(" ** Press Either Red or Blue to Select ** ");

}
*/

int main() {
  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
/*
  Brain.Screen.render(true,false);  // set VSync (vertical sync) on, automatic refresh to off
    // When we call Brain.Screen.render() with no arguments, it will force a redraw of the screen.
    // With the previous command here we turned off automatic redraws, so the LCD will only redraw
    // when we tell it to, which means we can guarantee it won't redraw in the middle of one of our
    // other drawing commands and give a partial picture. Getting partial pictures on redraws is
    // what causes flickering when drawing without this buffering scheme.
  Brain.Screen.clearScreen();             // clears the back buffer for drawing, default clear color is black
  drawRedAutonBtn();
  drawBlueAutonBtn();
  drawImgAutonBlock();
  Brain.Screen.render();                // flips the back buffer to the screen all at once, preventing flickering
*/

  // initial display
  displayButtonControls( 0, false );
  
  Brain.Screen.printAt(155, 125, "Touch the squares");

  while(1) {

    // Allow other tasks to run
    vex::this_thread::sleep_for(10);

  }
  
}
