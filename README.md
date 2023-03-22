# Air Quality Monitoring System
<h2>Description</h2>
This code is used to monitor air quality with a four-sensor system that measures the concentration of gases such as CO, CO2, and NH3. The system also measures temperature and humidity using a BME280 sensor.<br>
<b>2020</b>

<h2>Hardware Required</h2>
- Arduino board <br>
- 4 x Gas sensors<br>
- BME280 Sensor<br>

<h2>Prerequisites</h2>
Before using this program, make sure you have the following libraries installed:<br><br>

- Wire.h - included with Arduino IDE<br>
- SPI.h - included with Arduino IDE<br>
- Adafruit_Sensor.h - install from the Arduino Library Manage<br>
- Adafruit_BME280.h - install from the Arduino Library Manage<br>

<h2>Setup</h2>
The ESP32 is connected to four gas sensors and a BME280 sensor. The BME280 sensor is connected using the I2C protocol. The four gas sensors are connected to the four analog input pins A0, A1, A2, and A3.

In the <b>'setup()'</b> function, the BME280 sensor is initialized and a test message is printed on the serial monitor. The first line of data is printed to the serial monitor, which contains the labels of the columns of the data table.

The <b>'loop()'</b> function starts by checking if <b>'runs'</b> is equal to zero. If <b>'runs
</b> is zero, the system starts measuring data from the four gas sensors and the BME280 sensor. The measurement values are stored in an array named <b>'data'</b>.

If <b>'runs'</b> is not zero, the system enters a regression analysis function. The regression function calculates the regression line for each gas sensor using the measured data from the four gas sensors and a calibration dataset. After the regression analysis, the system enters a mode where it can calculate the gas concentration of each sensor using the regression lines.

If there is input data available on the serial monitor, the system reads it and stores it in a variable called <b>'key'</b>. If <b>'key'</b> is equal to "300", "200", "100", or "0", the system sets the variable <B>'j'</B>to the appropriate value. If <b>'key'</b> is equal to "G", the system prints the measured data to the serial monitor and enters the regression analysis mode. If <b>'key'</b> is equal to "C", the system calculates and prints the gas concentration of each sensor using the regression lines.

<h2>Variables</h2>
- <b>'key'</b>: A variable that stores the input data from the serial monitor<br>
- <b>'runs'</b>: A counter variable used to keep track of the number of measurements<br>
- <b>'i</b>, <b>'j'</b>, and o: Counter variables used in the regression analysis<br>
- <b>'data[4][4]'</b>: An array used to store the measured data<br>
- <b>'sigmaX[4]'</b>, <b>'sigmaXY[4]'</b>, <b>'sigmaX2[4]'</b>, <b>'b[4]'</b>, <b>'a[4]'</b>, <b>'Xbar[4]'</b>, and <b>'Ybar'</b>: Variables used in the regression analysis<br>
- <b>'Sen1'</b>, <b>'Sen2'</b>, <b>'Sen3'</b>, and <b>'Sen4'</b>: Variables used to control the timing of the sensor readings<br>

<h2>Functions</h2>
- <b>'setup()'</b>: Initializes the BME280 sensor and prints a test message to the serial monitor.<br>
- <b>'loop()'</b>: Reads the sensor data, performs regression analysis, and calculates the gas concentration of each sensor.<br>
- <b>'regression()'</b>: Calculates the regression line for each gas sensor using the measured data from the four gas sensors and a calibration dataset.<br>

## Example Chamber 

[Excel auto graph](https://www.youtube.com/watch?v=n86BISk9gv4)

<p align="center">
<img src="https://user-images.githubusercontent.com/77733903/226969550-c57abcc8-f801-402d-8713-8824cc9c3cee.JPG" width="500"><img src="https://user-images.githubusercontent.com/77733903/226969593-e0617e17-bb66-4cc8-a402-5d49bc5b16fa.JPG" width="500">
</p>

<h2>License</h2>

This program is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
