#include "robot-config.h"

/**
  * button.cpp
  * program to setup buttons on a V5 Brain display
  * author: jpearman
  * source: https://www.vexforum.com/index.php/34682-how-do-you-make-buttons-on-the-brain-screen/0
  *
  */

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
  {   30,  30, 60, 60,  false, 0x800000 },
  {  150,  30, 60, 60,  false, 0x008000 },
  {  270,  30, 60, 60,  false, 0x000080 },
  {  390,  30, 60, 60,  false, 0x808000 },
  {   30, 150, 60, 60,  false, 0x800080 },
  {  150, 150, 60, 60,  false, 0x804040 },
  {  270, 150, 60, 60,  false, 0x008080 },
  {  390, 150, 60, 60,  false, 0x808080 }
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
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

    for( int index=0;index < nButtons;index++) {
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

      if( buttons[i].state )
        c = buttons[i].color;
      else
        c = vex::color::black;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        c = c + 0x404040;
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );
    }
}

int main() {
    // register events
    Brain.Screen.pressed( userTouchCallbackPressed );
    Brain.Screen.released( userTouchCallbackReleased );

    // initial display
    displayButtonControls( 0, false );

    Brain.Screen.printAt(155, 125, "Touch the squares");
    while(1) {
      // Allow other tasks to run
      vex::this_thread::sleep_for(10);
    }
}
