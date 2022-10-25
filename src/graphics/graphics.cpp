#include "robot-config.h"

#include <stdlib.h>

#define  random( t )    ( ((double)rand() / RAND_MAX) * (t) )

using namespace vex;

int
main() {
    // Simple graphics demo.
    //
    
    // The default monospace text is drawn on a grid with 12 rows of 48 characters.
    // The cursor is set to the text location and text printed to the screen.
    // The top left hand corner is cursor location row 1 column 1.
    //
    Brain.Screen.print("Hello World, I am a V5 Brain ...");
    //
    // If the font is changed the grid adjusts accordingly
    // The default font is called "mono20", that means monospace with a line that is 20 pixels high.
    // Other monospace fonts available are
    // mono30
    // mono40
    // mono60
    // Here is some larger text
    //
    Brain.Screen.setFont( prop60 );
    Brain.Screen.setCursor( 2, 1 );
    Brain.Screen.print("This is prop60");
    //
    // There are also some proportional fonts available, these are called prop20, prop30, prop40 and prop60
    //
    
    // We can also draw lines
    // a line is given an x,y coordinate as the start point and an x,y coordinate as the end point
    // The useable area of the V5 screen under the menubar is 480 pixels wide and 240 pixels high
    // drawLine( xstart, ystart, xend, yend )
    Brain.Screen.drawLine( 100, 100, 200, 100 );
    //
    // and change the color used to draw the line
    Brain.Screen.setPenColor( vex::color::red );
    Brain.Screen.drawLine( 100, 110, 200, 110 );
    //
    // and make it wider
    Brain.Screen.setPenWidth( 4 );
    Brain.Screen.drawLine( 100, 120, 200, 120 );
    //
    // We can also change the color in different ways
    // we can use a named color.
    Brain.Screen.setPenColor( vex::color::yellow );
    Brain.Screen.drawLine( 100, 130, 200, 130 );
    //
    // using a hue in the range 0 to 360 degrees
    Brain.Screen.setPenColor( 240 );
    Brain.Screen.drawLine( 100, 140, 200, 140 );
    //
    // or using a string with a hexadecimal rgb value a bit like that used in html
    Brain.Screen.setPenColor( "#00FF00" );
    Brain.Screen.drawLine( 100, 150, 200, 150 );
    //
    // an alternative using a shorter string
    Brain.Screen.setPenColor( "#F0F" );
    Brain.Screen.drawLine( 100, 160, 200, 160 );
  
    //
    // We can draw rectangles
    // A rectangle is given the x,y coordinate of the top left corner, a width and height
    // drawRectangle( x, y, width, height )
    Brain.Screen.drawRectangle( 200, 100, 100, 30 );
    //
    // A rectangle uses the pen color and width for the outline and a fill color
    // for the interior.
    Brain.Screen.setFillColor( vex::color::orange );
    Brain.Screen.drawRectangle( 200, 140, 100, 30 );
    //
    // we can specify a color for the interior of the rectangle as part of the function call
    Brain.Screen.drawRectangle( 240, 160, 100, 30, vex::color::green );
    //
    // There is a special color called TRANSPARENT that does not erase what is inside the rectangle
    // (note. current firmware has a bug and sometimes the fill color is not correctly set after using transparent)
    //
    Brain.Screen.setPenColor( vex::color::red );
    Brain.Screen.setPenWidth( 2 );
    Brain.Screen.setFillColor( vex::color::transparent );
    Brain.Screen.drawRectangle( 260, 120, 100, 30 );
    //
            
    //
    // We can draw circles
    // A circle is given the x,y coordinate of the center and a radius
    // drawCircle( xc, yc, radius )
    Brain.Screen.setFillColor( vex::color::blue );
    Brain.Screen.drawCircle( 390, 70, 40 );
    //
    // The same functionality is available for circles as rectangles.
    // here we specify the fill color
    Brain.Screen.drawCircle( 390, 70, 20, "#F00" );
    // A circle with no fill
    Brain.Screen.setPenColor( vex::color::cyan );
    Brain.Screen.setPenWidth( 10 );
    Brain.Screen.setFillColor( vex::color::transparent );
    Brain.Screen.drawCircle( 390, 70, 80 );

    //
    // This will pause the code for 2 seconds (2000mS)
    this_thread::sleep_for( 2000 );
    
    // We can draw single pixels
    // lets draw 5000 randomly placed green pixels
    Brain.Screen.setPenColor( vex::color::green );
    for( int i=0;i<5000;i++ ) {
        int x = random( 480 );
        int y = random( 240 );
        Brain.Screen.drawPixel( x, y );
        
        // small delay so we can see them drawing
        this_thread::sleep_for( 1 );
    }

    //
    // This will pause the code for 5 seconds (5000mS)
    this_thread::sleep_for( 5000 );
  
    // This will clear everything on the screen.
    Brain.Screen.clearScreen();

	// another short delay
    this_thread::sleep_for( 1000 );
    
    // This will clear the screen to red.
    Brain.Screen.clearScreen( vex::color::red );

    this_thread::sleep_for( 1000 );
    Brain.Screen.setFont( prop60 );
    Brain.Screen.setCursor( 2, 2 );
    Brain.Screen.print("Happy coding !");

    return 0;
}
