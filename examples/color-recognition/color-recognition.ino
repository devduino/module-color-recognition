/** MIT License
*
* Copyright(c) 2017 DevDuino
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

//Include board with DevDuino components.
#include <devduino.h>
#include <colorRecognition.h>
#include <Wire.h>
//DevDuino logo to display a splash screen before example.
#include "devduinoSprite.h"

ColorRecognition tcs = ColorRecognition();
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();


//Initialize program.
void setup()
{
  //First thing to do is to initialize DevDuino board.
  devduino.begin();
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoSprite, 37, 0);
  //Then transfer buffer to screen.
  display.flush();
  
  //Sleep for 1 second with splash screen displayed to be able to see it before continuing.
  delay(1000);

  console.clear();

  bool colorRecognitionState = tcs.begin();
  console.println(String("Color recognition module state: ") + colorRecognitionState);

  tcs.setLightingLevel(32);
  tcs.setReemitLevel(255);
}

//Loop over program execution.
void loop()
{
  tcs.read();
  
  //Get color from module.
  uint8_t red = tcs.getRed();
  uint8_t green = tcs.getGreen();
  uint8_t blue = tcs.getBlue();
  uint8_t clear = tcs.getClear();
  
  //Display color to console.
  console.println(String("Color: (Red/green/blue/clear) :") + red + "/" + green + "/" + blue + "/" + clear);

  if(red > green && red > blue) {
    console.println(String("Best match is RED."));
  } else if(green > red && green > blue) {
    console.println(String("Best match is GREEN."));
  } else {
    console.println(String("Best match is BLUE."));
  }
  
  //No need to refresh quickly.
  delay(1000);
}
