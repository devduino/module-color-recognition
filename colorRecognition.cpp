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

#include <Arduino.h>
#include <Wire.h>
//#include <board.h>

#include "colorRecognition.h"

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
#define TSC34725_I2C_ADDRESS 0x29

#define TSC34725_COMMAND_SET_ENABLE_REGISTER 0xa0
#define TSC34725_COMMAND_GET_ID_REGISTER 0xb2
#define TSC34725_COMMAND_GET_RGBC_CHANNEL_DATA_REGISTER 0xb4

#define COLOR_RECOG_PIN_INT 1
#define COLOR_RECOG_PIN_SDA 2
#define COLOR_RECOG_PIN_SCL 3
#define COLOR_RECOG_PIN_WHITE 5
#define COLOR_RECOG_PIN_RED 9
#define COLOR_RECOG_PIN_GREEN 10
#define COLOR_RECOG_PIN_BLUE 11

namespace devduino {
	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//

	bool ColorRecognition::begin() {
		Wire.begin();
		pinMode(COLOR_RECOG_PIN_WHITE, OUTPUT);

		//Switch off light.
		digitalWrite(COLOR_RECOG_PIN_WHITE, LOW);

		bool found = getIdRegister() == 0x44;

		if (found) {
			powerOn();
		}

		//console.println(String(getIdRegister()));
		//console.println(String(getIdRegister() == (uint8_t) 0x44));
		return found;
	}

	void ColorRecognition::setLightingLevel(uint8_t level) {
		this->lightingLevel = lightingLevel;
	}

	void ColorRecognition::read() {
		//Switch on light.
		//TODO: Ajuster en fonction de l'attribut lightingLevel.
		digitalWrite(COLOR_RECOG_PIN_WHITE, lightingLevel);

		//Get color.
		getRGBC();

		//Switch off light.
		digitalWrite(COLOR_RECOG_PIN_WHITE, LOW);

		//TODO: Réduire en fonction du reemit level.
		analogWrite(COLOR_RECOG_PIN_RED, getRed());
		analogWrite(COLOR_RECOG_PIN_GREEN, getGreen());
		analogWrite(COLOR_RECOG_PIN_BLUE, getBlue());
	}

	uint16_t ColorRecognition::getRed() {
		return red;
	}

	uint16_t ColorRecognition::getGreen() {
		return green;
	}

	uint16_t ColorRecognition::getBlue() {
		return blue;
	}

	uint16_t ColorRecognition::getClear() {
		return clear;
	}

	void ColorRecognition::setReemitLevel(uint8_t reemitLevel) {
		this->reemitLevel = reemitLevel;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//
	uint8_t ColorRecognition::getIdRegister() {
		Wire.beginTransmission(TSC34725_I2C_ADDRESS);
		Wire.write(TSC34725_COMMAND_GET_ID_REGISTER);
		Wire.endTransmission();

		Wire.requestFrom(TSC34725_I2C_ADDRESS, 1);
		uint8_t buffer = Wire.read();
		Wire.endTransmission();

		return buffer;
	}

	void ColorRecognition::powerOn() {
		Wire.beginTransmission(TSC34725_I2C_ADDRESS);
		Wire.write(TSC34725_COMMAND_SET_ENABLE_REGISTER);
		Wire.write(0x03); //PON + AEN
		Wire.endTransmission();
	}

	uint16_t* ColorRecognition::getRGBC() {
		Wire.beginTransmission(TSC34725_I2C_ADDRESS);   // Write address of read to sensor
		Wire.write(TSC34725_COMMAND_GET_RGBC_CHANNEL_DATA_REGISTER);
		Wire.endTransmission();

		Wire.requestFrom(TSC34725_I2C_ADDRESS, 8);

		clear = Wire.read();
		clear |= (uint16_t) (Wire.read() << 8);
		red = Wire.read();
		red |= (uint16_t)(Wire.read() << 8);
		green = Wire.read();
		green |= (uint16_t)(Wire.read() << 8);
		blue = Wire.read();
		blue |= (uint16_t)(Wire.read() << 8);

		Wire.endTransmission();
	}
} // namespace devduino

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_COLOR_RECOGNITION)
devduino::ColorRecognition colorRecognition;
#endif