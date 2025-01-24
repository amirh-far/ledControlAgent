# LED Control AI Agent Based on Telegram Bot  

An AI-powered agent designed to manage an ESP32 module for precise control of LED devices. This agent enables dynamic lighting effects, remote management, and intelligent behavior integration for a wide range of applications. Based on Telegram Bot, Completely Remote Access. ESP32 on Station Mode in Wifi configuration.

## Features

- **AI-Driven Control**: Adaptive decision-making to dynamically adjust LED states based on predefined or learned patterns.
- **ESP32 Integration**: Seamless communication with ESP32 modules via Wi-Fi or Bluetooth.
- **Remote Control**: API endpoints for managing LEDs from external systems or IoT platforms.
- **Customizable and Extendable**: Add or modify effects and behaviors for specific use cases.
- **Efficient Communication**: Optimized for low-latency and reliable data exchange with ESP32.



## Installation

### Prerequisites

Ensure you have the following:
- **Python 3.8 or later** for running the AI agent
- **ESP32 module** with LED strips (e.g., WS2812, APA102)
- **Arduino IDE or PlatformIO** to flash the ESP32 firmware
- **Dependencies** installed via `requirements.txt`

### Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/amirh-far/ledControlAgent.git
   cd ledControlAgent
   ```

2. **Install Python Dependencies**
   ```bash
   pip install -r requirements.txt
   ```
   - install espressif module for ESP32-CAM.
   - create an .env file and pass your telegram token as ```BOT_TOKEN=```
   - add your OpenAI API Token to your terminal profile. Tutorial in this [link](https://help.openai.com/en/articles/5112595-best-practices-for-api-key-safety)

3. **Flash the ESP32 Firmware & Run the arduino code**
   - Navigate to the `firmware/` directory.
   - Open the firmware project in the Arduino IDE or PlatformIO.
   - Flash the ESP32 module.
   - in /arduino folder find the ```arduino.ino``` file using an arduino IDE and update the code:
     - Set your server IP in the strings corresponding to your IP
     - Set your SSID and Password in the corresponding variables.
     - Run the ```arduino.ino``` file using an arduino IDE, allowing to communicate to server.

4. **Run the Server and Telegram Bot**
   - Run the server:
   ```bash
   python server.py
   ```
   - Run the Telegram bot 
    ```bash
   python bot.py
   ```


## Usage

### ESP32 Setup

1. Connect the ESP32 module to your LED strip.
2. Ensure the ESP32 is powered and connected to the same network with the AI agent.
3. The ESP32 will communicate with the agent via HTTP API requests.


#### Example Outputs

<p>
   <img src=
</p>


## Contributing

We welcome contributions! Follow these steps:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add feature-name"
   ```
4. Push the branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.


## License

This project is licensed under the MIT License. Bro change it however you want!

