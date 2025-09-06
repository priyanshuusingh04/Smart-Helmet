# 🪖 Smart Helmet – Accident Detection & Alert System  

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)  
[![Arduino](https://img.shields.io/badge/Made%20with-Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)  
[![GSM](https://img.shields.io/badge/Module-SIM900A-orange)]()  
[![GPS](https://img.shields.io/badge/Module-NEO--6M-blue)]()  

---

## 🔹 Project Overview  
The **Smart Helmet** is an IoT-based safety system designed to **detect accidents and notify emergency contacts**—without requiring internet connectivity, smartphones, or mobile apps.  

Unlike existing solutions that depend on cloud services or costly setups, this project is:  
- ✅ **Standalone** – Works without internet  
- ✅ **Low-cost** – Affordable for real-world deployment  
- ✅ **Reliable** – Uses GSM & GPS modules for emergency alerts  

When an accident occurs, the helmet automatically:  
1. Detects impact using the **ADXL345 accelerometer**  
2. Captures real-time **GPS location** with the **NEO-6M module**  
3. Sends an **SMS with location link** via the **SIM900A GSM module**  
4. Initiates a **phone call** to emergency contacts  

This ensures **faster response times**, especially in rural/semi-urban areas with limited connectivity.  

---

## 🔹 Features  
- 🚨 Automatic crash detection  
- 📍 Real-time GPS tracking  
- 📲 SMS alerts with Google Maps link  
- 📞 Emergency call to saved contacts  
- 🔋 12V battery for portable operation  
- 🌐 Works **without internet or smartphone apps**  

---

## 🔹 Components Used  
- **Arduino Uno** → Central microcontroller  
- **ADXL345 Accelerometer** → Detects abnormal motion & impact  
- **NEO-6M GPS Module** → Captures accident location  
- **SIM900A GSM Module** → Sends SMS & makes emergency calls  
- **12V Battery & Power Switch** → Portable power supply  
- **Breadboard & Jumper Wires** → Circuit connections  
- *(Optional)* MQ-3 Alcohol Sensor → Detects rider alcohol levels  

---

## 🔹 System Architecture  

### ⚙️ Working Principle  
1. Accelerometer records **real-time helmet motion (X, Y, Z axes)**  
2. Sudden abnormal change → **interpreted as crash**  
3. Arduino triggers **GSM module** → Sends **SMS + call**  
4. GPS adds **live coordinates** in the alert  

```plaintext
Helmet (ADXL345) → Arduino UNO → GPS (NEO-6M) → GSM (SIM900A) → Emergency Contacts
```

## 📂 Repository Structure  
```plaintext
Smart-Helmet/  
│── code/            # Arduino source code  
│── report/          # Detailed project report (PDF/DOCX)  
│── circuit/         # Circuit diagrams & connection files  
│── images/          # Photos of hardware & prototype  
│── README.md        # Documentation  
```

## 🔹 Tools & Technologies  
- **Arduino IDE** (programming & debugging)  
- **Embedded C / Arduino C++** (firmware)  
- **Circuito.io / Fritzing** (circuit design)  
- **GPS & GSM libraries** (location + SMS handling)  

---

## 🔹 Future Scope  
- ⚡ Upgrade accelerometer (e.g., ADXL377) for higher impact detection  
- 🔋 Add solar charging & smart power management  
- 📡 Migrate to **ESP32** for Wi-Fi/Bluetooth integration  
- 📱 Develop a **companion smartphone app**  
- 🧪 Use **AI/ML models** to reduce false positives  
- 🚦 Integrate with traffic management systems  

---

## 🚀 Getting Started  

### 🔧 Requirements  
- Arduino IDE installed  
- GSM SIM card (2G supported)  
- Clear GPS antenna access
- 
---
## 📸 Demonstration  

### System Setup  
![IMG20250429201157](https://github.com/user-attachments/assets/7b611e92-45b7-4d3a-a308-28382323b285)

---
## 🔹 Author  
👤 **Priyanshu Singh**  
- 🎓 IIT Ropar | Mechanical Engineering  
- 🔧 Skills: Abaqus, SolidWorks, OpenFOAM, Fusion, Ansys, Arduino IDE, Linux  
- 📧 Email: priyanshusingh04112003@gmail.com  
- 🌐 [LinkedIn](https://www.linkedin.com/in/priyanshu-singh-a47033265) | [YouTube](https://youtube.com/@theunfilteredguyy)  

---
⭐ If you like this project, don’t forget to **star the repo**!
