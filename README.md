# 📡 ESP32 Smart IR Signal Repeater & Amplifier



## 📖 Project Overview
This project is an **ESP32-based Infrared (IR) Signal Repeater** designed to solve the common issue of blocked or weak remote control signals. The system captures IR commands from a physical remote, decodes the protocol, and re-transmits the signal with **amplified power** using a transistor driver circuit.

It serves as a practical application of **Signals & Systems** theories, specifically **Sampling**, **Modulation**, and **Discrete-Time Processing**.

---

## ⚙️ Features
* **Signal Capture:** Real-time decoding of IR commands (NEC, Samsung, etc.).
* **Signal Amplification:** Uses a **2N2222 BJT Transistor** to boost the IR LED output current (approx. 100mA peak) for extended range.
* **Protocol Selectivity:** Filters specific protocols (e.g., Samsung) to prevent noise interference.
* **Non-Line-of-Sight Control:** Allows controlling devices hidden behind obstacles (cabinets, monitors).

---

## 🛠️ Hardware Components
| Component | Description | Function |
| :--- | :--- | :--- |
| **ESP32** | Microcontroller | Central processing unit for decoding and encoding signals. |
| **IR Receiver** | 38kHz Sensor | Demodulates the incoming IR carrier wave. |
| **IR LED** | 940nm Emitter | Transmits the regenerated signal. |
| **2N2222 Transistor** | NPN BJT | Acts as a high-current switch to drive the LED. |
| **330Ω Resistor** | Resistor | Limits base current to protect ESP32 GPIO pins. |

---


## 📊 Theoretical Background (Signals & Systems)
This project demonstrates the practical implementation of key engineering concepts:

### 1. Sampling & Nyquist Theorem
The remote control transmits data modulated on a 38 kHz carrier frequency. According to the Nyquist–Shannon Sampling Theorem, directly sampling this carrier signal would require a minimum sampling frequency of fs ≥ 76 kHz.

To optimize processing and reduce computational complexity, a TSOP infrared receiver is employed. The TSOP module acts as an analog band-pass filter and demodulator, removing the 38 kHz carrier and outputting the baseband digital signal. This baseband signal is then sampled by the ESP32 microcontroller using high-precision interrupt-based timing measurements, allowing accurate detection of pulse widths without the need for high-rate direct carrier sampling.

### 2. Modulation (ASK/PWM)
The logic "0" and "1" bits are encoded using pulse-distance modulation. The ESP32 regenerates this by modulating the 38 kHz carrier wave via software PWM (Pulse Width Modulation).

### 3. Transistor Switching
A **2N2222 NPN transistor** is used in saturation mode. A base resistor ($R_B = 330\Omega$) limits the base current ($I_B$) to approx. 8mA, allowing a collector current ($I_C$) sufficient to drive the IR LED at high intensity.

---

## 📂 Project Structure
* `src/`: Source code (Arduino/C++)
* `schematics/`: Circuit diagrams and images.
* `docs/`: Full Technical Project Report (PDF).

---

## 🚀 How to Run
1.  Install **Arduino IDE**.
2.  Install the `IRremoteESP8266` library via Library Manager.
3.  Connect the hardware as shown in the schematic.
4.  Upload the `.ino` code to your ESP32 board.
5.  Open Serial Monitor (115200 baud) to see decoded signals.

---

## 👨‍💻 Author
**Barış Erişen**
*Electrical & Electronics Engineering Student*
*Istanbul Kültür University*

[LinkedIn Profile](www.linkedin.com/in/barış-erişen-2140222a9)
