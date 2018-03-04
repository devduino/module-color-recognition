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

#ifndef DEVDUINO_MODULE_COLOR_RECOGNITION_H
#define DEVDUINO_MODULE_COLOR_RECOGNITION_H

#include <stdint.h>

/**
* Default namespace for devduino related code.
*/
namespace devduino {
	/**
	* \brief High level driver for COLOR_RECOGNITION of devduino.
	*
	* You must call "begin" method before being able to use it.
	*
	* For more information on internal behavior, the color sensor datasheet for AMS TSC34725 is available <a href="http://ams.com/eng/Products/Light-Sensors/Color-Sensors/TCS34725" target="_blank">here</a>.
	*/
	class ColorRecognition {
	public:
		/**
		 * \brief Initialize color sensor module of DevDuino.
		 *
		 * This method must be called before any other method of this class.
		 *
		 * \return true if color recognition module is found and started, false otherwise.
		 */
		bool begin();

		/**
		 * \brief Set the level of lighting while capturing color.
		 *
		 * Set the intensity of the diode lighting the element to capture color from.
		 * Intensity is comprised between 0 (off) and 255 (full power).
		 *
		 * \param level The intensity of diode.
		 */
		void setLightingLevel(uint8_t level);

		/**
		 * \brief Read the color from sensor.
		 * 
		 * After a read operation, color components can be got using getRed(), getGreen(), getBlue() or getClear() methods.
		 *
		 * \see getRed()
		 * \see getGreen()
		 * \see getBlue()
		 * \see getClear()
		 */
		void read();

		/**
		 * \brief Get the red component.
		 * 
		 * Get the red component of the latest color read from sensor.
		 *
		 * \see read()
		 *
		 * \return The latest red value or 0 if never read.
		 */
		uint16_t getRed();

		/**
		 * \brief Get the green component.
		 * 
		 * Get the green component of the latest color read from sensor.
		 *
		 * \see read()
		 *
		 * \return The latest green value or 0 if never read.
		 */
		uint16_t getGreen();

		/**
		 * \brief Get the blue component.
		 *
		 * Get the blue component of the latest color read from sensor.
		 *
		 * \see read()
		 *
		 * \return The latest blue value or 0 if never read.
		 */
		uint16_t getBlue();

		/**
		 * \brief Get the clear component.
		 *
		 * Get the clear component of the latest color read from sensor.
		 *
		 * \see read()
		 *
		 * \return The latest cleaar value or 0 if never read.
		 */
		uint16_t getClear();

		/**
		 * \brief Specify the reemit level of readed color.
		 *
		 * The reemission is done on LED using pins 9, 10 and 11.
		 *
		 * \param level The ratio of reemission compared to readed color.
		 */
		void setReemitLevel(uint8_t level);

	private:
		/**
		 * \brief The red component of latest color captured.
		 */
		uint16_t red = 0;
		/**
		 * \brief The green component of latest color captured.
		 */
		uint16_t green = 0;
		/**
		 * \brief The blue component of latest color captured.
		 */
		uint16_t blue = 0;
		/**
		 * \brief The clear component of latest color captured.
		 */
		uint16_t clear = 0;
		/**
		 * \brief The intensity of diode lighting the element to capture color from.
		 */
		uint8_t lightingLevel = 0;
		/**
		 * \brief Should color captured be reemited to module LED.
		 */
		float reemitLevel = 0;

		/**
		 * \brief Get the identifer of color sensor component.
		 */
		uint8_t getIdRegister();

		/**
		 * \brief power on sensor.
		 */
		void powerOn();

		/**
		 * \brief Get the color in front of sensor.
		 */
		uint16_t* getRGBC();

		/**
		 * \brief Reemit readed color on reemit led.
		 *
		 * \param red The red level to reemit.
		 * \param green The green level to reemit.
		 * \param blue The blue level to reemit.
		 */
		void reemit(uint8_t red, uint8_t green, uint8_t blue);
	};
} // namespace devduino

//Define global color sensor variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_COLOR_RECOGNITION)
extern devduino::ColorRecognition colorRecognition;
#endif

#endif //DEVDUINO_MODULE_COLOR_RECOGNITION_H