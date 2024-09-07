# ESP32 Firebase Sensor Registration

This project registers an ESP32 device with Firebase using user-provided credentials and sensor information. The device connects to a Wi-Fi network, gets the device ID from the user, and uploads it to the Firebase Realtime Database.

## Features

- Connects the ESP32 to a Wi-Fi network using user-provided SSID and password.
- Prompts the user to enter a sensor ID and validates the format.
- Registers the device to Firebase with a unique ID.
- Uses the `Firebase_ESP_Client` library to interact with the Firebase Realtime Database.

## Requirements

- **Hardware:**
  - An ESP32 development board.

- **Software:**
  - Arduino IDE or PlatformIO (in Visual Studio Code).
  - [Firebase Arduino Client Library for ESP8266 and ESP32](https://github.com/mobizt/Firebase-ESP-Client) (`mobizt/Firebase Arduino Client Library for ESP8266 and ESP32` version `^4.4.14`).
  - Properly set up Firebase project with Realtime Database enabled.

## Setup Instructions

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/esp32-firebase-sensor-registration.git
   cd esp32-firebase-sensor-registration
   ```

2. **Install Dependencies:**
   - Ensure you have the `Firebase_ESP_Client` library installed. You can install it via the Arduino Library Manager or PlatformIO.

3. **Configure Firebase:**
   - Update the `API_KEY` and `DATABASE_URL` in the code with your Firebase project details.

4. **Upload Code to ESP32:**
   - Connect your ESP32 board to your computer.
   - Open the project in your Arduino IDE or PlatformIO and upload the code to the ESP32.

5. **Run the Program:**
   - Open the Serial Monitor at `115200` baud rate.
   - Follow the prompts to enter the Wi-Fi SSID, password, and sensor ID.

## Usage

- **Wi-Fi Connection:**
  - When the program starts, it asks for the Wi-Fi SSID and password.
  - It connects to the provided network.

- **Sensor ID Registration:**
  - The program prompts the user to enter a sensor ID.
  - The ID is validated based on a specific format.
  - If valid, the device ID is sent to the Firebase Realtime Database.

## Example Output

```
Enter WiFi SSID: 
YourSSID
Enter WiFi Password: 
********
Connecting to Wi-Fi
Connected to [YourSSID]

SensorID for single slots: SM-yyy (yyy -> unique 3-digit ID)
SensorID for 1/3/6/8/9/12 slots: SMx-yy (x -> # of slots (1/3/6/8/9/12), (yyy -> unique 3-digit ID)
Enter Sensor ID:
SM1-001
It is Valid ID
Device Registered Successfully!
```

## Troubleshooting

- **Cannot Connect to Wi-Fi:**
  - Double-check the SSID and password.
  - Make sure the ESP32 is within range of the Wi-Fi router.
  
- **Invalid Sensor ID Format:**
  - Make sure the ID starts with `SM` and follows the proper format as described in the prompt.

- **Failed to Write Data to Firebase:**
  - Ensure that the Firebase URL and API key are correctly set.
  - Check your internet connection.

## License

This project is open source and available under the [MIT License](LICENSE).

## Contributing

Feel free to open an issue or submit a pull request if you find any bugs or want to add features.

## Acknowledgments

- [Firebase Arduino Client Library](https://github.com/mobizt/Firebase-ESP-Client) by Mobizt

---

Feel free to adjust the URLs and specific project details to match your actual repository.
