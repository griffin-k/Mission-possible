# Flood Relief Drone - Proof of Concept (POC)  

## Overview  
This project demonstrates a **Flood Relief Drone** designed to assist in disaster management. The UAV integrates multiple sensors and hardware components to gather and transmit real-time environmental data. A dashboard visualizes sensor data, enabling responders to make informed decisions during flood relief operations.  

## Features  
- **Real-time Data Display**:  
  - Temperature and humidity readings (DHT11 sensor).  
  - Gas detection (MQ2 sensor).  
  - Motion detection and object tracking (Radar and motion detector).  
  - Live video feed (FPV camera).  
- **Functional Hardware Integration**:  
  - Water pump for small-scale water removal demonstrations.  
  - Servo-controlled payload dropper for delivering essential supplies.  
- **Dashboard**: Displays live data fetched from the sensors using Firebase as the backend.  
- **Responsive Design**: Tailored for mobile and desktop devices using Tailwind CSS.  

## Technologies Used  

### Software  
- **Frontend**:  
  - HTML  
  - Tailwind CSS  
  - JavaScript  

- **Backend**:  
  - Firebase Realtime Database  

- **Hardware Code**:  
  - C++  

### Hardware Components  
- **Microcontroller**: ESP32  
- **Sensors**:  
  - DHT11 (Temperature and Humidity)  
  - MQ2 (Gas detection)  
  - Radar and motion detector  
- **Camera**: FPV Camera for live video streaming  
- **Actuators**:  
  - Water pump  
  - Servo motor for payload dropper  

## Installation  

### Prerequisites  
1. **Hardware Setup**:  
   - Assemble the sensors and actuators as per the drone design.  
   - Connect the ESP32 microcontroller and upload the C++ firmware.  

2. **Firebase Setup**:  
   - Go to the [Firebase Console](https://console.firebase.google.com/).  
   - Create a project and enable **Realtime Database**.  
   - Obtain the Firebase configuration keys and replace the placeholders in the project files.  

### Steps  
1. **Clone the Repository**  
   ```bash
   git clone https://github.com/griffin-k/flood-relief-drone.git
   cd flood-relief-drone

Set Up Firebase Configuration
Update the firebase-config.js file:

javascript
```
const firebaseConfig = {
  apiKey: "your-api-key",
  authDomain: "your-auth-domain",
  databaseURL: "your-database-url",
  projectId: "your-project-id",
  storageBucket: "your-storage-bucket",
  messagingSenderId: "your-messaging-sender-id",
  appId: "your-app-id"
};
firebase.initializeApp(firebaseConfig);
```

### Run the Dashboard

Open index.html in your browser to view the dashboard.

**Deploy Firmware**
Use the Arduino IDE to upload the C++ code to the ESP32.
