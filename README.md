# Assignment8_Embedded_System
# STM32F103 - Đọc giá trị ADC và gửi qua UART

## 📌 Giới thiệu
Project này sử dụng **STM32F103C8T6** để đọc giá trị điện áp từ chân **PA0 (ADC Channel 0)**, sau đó gửi dữ liệu qua **UART1** để hiển thị trên máy tính hoặc thiết bị giám sát.  

Chức năng chính:
- Đọc tín hiệu analog từ PA0.
- Chuyển đổi sang giá trị ADC (12-bit, 0–4095).
- Tính toán điện áp dựa trên Vref = 3.3V.
- Gửi giá trị ADC và điện áp (mV) qua UART1 với baudrate 9600.

---

## ⚙️ Cấu hình phần cứng
- **MCU:** STM32F103C8T6 (hoặc dòng STM32F1 tương thích).
- **Chân sử dụng:**
  - `PA0` → Ngõ vào ADC (tín hiệu analog cần đo).
  - `PA9` → UART1 TX.
  - `PA10` → UART1 RX.
- **Nguồn tham chiếu (Vref):** 3.3V.
- Kết nối UART với máy tính qua **USB-TTL** để quan sát dữ liệu.

---

## 🛠️ Cấu hình phần mềm
- **Ngôn ngữ:** C.
- **IDE:** Keil uVision / STM32CubeIDE.
- **Thư viện:** Standard Peripheral Library (SPL).

---
