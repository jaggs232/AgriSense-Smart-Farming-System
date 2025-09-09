# AgriSense-Smart-Farming-System


AgriSense is an IoT-powered smart farming solution that automates precision agriculture tasks like soil moisture, gas (CO₂) detection, and water level management using Arduino, sensors, relay control, and an LCD display for real-time feedback.


Features:

~ Soil Moisture Monitoring & Automated Irrigation
The system measures soil moisture and automatically turns the water pump (via relay) ON/OFF when levels fall below or above set thresholds.

~ CO₂ (Gas) Sensing
Continuously tracks and displays CO₂ (gas sensor) readings on the LCD screen in ppm.

~ Water Level Detection
Detects water tank levels to prevent pump dry-run and conserve water.

~ DHT11 Temperature & Humidity Sensor Ready
Code includes DHT11 setup for future temperature/humidity monitoring.

~ User Feedback & Rotating Display
LCD cycles through soil moisture, CO₂, project info, and team credits for clear visibility.




Hardware Required:

* Arduino board (Uno, Nano, etc.)

* DHT11 sensor (temperature & humidity)

* Soil moisture sensor (analog)

* Gas/CO₂ sensor (analog)

* Water level sensor (digital)

* Relay module (to control pump)

* LCD I2C display (16x2)

* Wires, breadboard



How It Works:

--Startup & Initialization: LCD displays status while system prepares sensors.


Continuous Monitoring:

--Reads values from all sensors.

--Controls the relay/pump based on soil moisture and water tank levels.


Rotating LCD Display:

--Shows soil moisture %, CO₂ ppm, project name, and team credits in cycles every 1.5s.


Serial Output:

--Prints real-time data to Arduino Serial Monitor for debugging.



Credits:

~ Jaganathan V

~ Mrithula R

~ Lacshan KK

~ Keerthivasan A
