# 🐾 SMART PET CARE SYSTEM – HỆ THỐNG CHĂM SÓC THÚ CƯNG THÔNG MINH

## 📌 Mô tả đề tài
Trong cuộc sống hiện đại, thú cưng ngày càng được xem là một thành viên trong gia đình. Tuy nhiên, việc chăm sóc chúng đòi hỏi nhiều thời gian: cho ăn đúng giờ, theo dõi môi trường sống, đảm bảo an toàn…  
Hệ thống chăm sóc thú cưng thông minh được xây dựng nhằm giải quyết các vấn đề này thông qua IoT, cảm biến và điều khiển tự động.

---

## 📖 Mục lục
- 1. Problem Statement  
- 2. Main Content  
- 3. Block Diagram  
- 4. Pin Diagram  
- 5. Results  
- 6. Conclusion  

---

# 1. Problem Statement

### 🔍 Nhu cầu thực tế
- Chủ bận rộn → quên cho ăn hoặc thay nước.  
- Không thể theo dõi thú cưng khi đi làm hoặc đi xa.  
- Môi trường sống thay đổi (nhiệt độ, độ ẩm, khí gas) → gây nguy hiểm.  
- Không biết thú cưng đang có trong chuồng hay đã đi ra ngoài.

### 💡 Nguồn cảm hứng
- Nhiều thú cưng gặp nguy hiểm do môi trường sống không đảm bảo.  
- Mong muốn tạo ra một hệ thống giá rẻ, dễ triển khai.

---

# 2. Main Content

## 🧰 2.1. Hardware
- ESP32 DevKit V1  
- 4 × IR Sensor  
- 1 × Servo SG90  
- 1 × SHT30 / DHT22 (Temperature + Humidity)  
- 1 × MQ-2 gas sensor  
- 1 × LDR light sensor  
- Quạt mini  
- Đèn LED  

## 🖥 2.2. Software
- Node-RED Dashboard  
- MQTT Broker (EMQX)  
- PlatformIO (Arduino C++)  

## 🧠 2.3. Concept
- Giám sát vị trí thú cưng theo thời gian thực  
- Cho ăn tự động bằng servo  
- Theo dõi môi trường liên tục  
- Điều khiển quạt và đèn theo ngưỡng hoặc thủ công  

---

# 3. Block Diagram
*(Thay bằng ảnh thật)*  
![Block Diagram](./images/3.png)

---

# 4. Pin Diagram
![Pinout](./images/9.png)

| Thiết bị | Chân | ESP32 |
|---------|------|--------|
| Servo | PWM | 16 |
| IR Sensor 1 | OUT | 36 |
| IR Sensor 2 | OUT | 39 |
| IR Sensor 3 | OUT | 34 |
| IR Sensor 4 | OUT | 35 |
| SHT30 | SDA/SCL | 21 / 22 |
| MQ-2 | AOUT | 32 |
| LDR | AOUT | 33 |
| LED | OUT | 23 |
| Fan | OUT | 14 |

---

# 5. Results

## 5.1. Mô hình
![Model](./images/8.png)

## 5.2. Node-RED Dashboard
![Dash1](./images/IOT_Board.png)  
![Dash2](./images/h2.png)  
![Dash3](./images/h3.png)  
![Dash4](./images/5.png)  
![Dash5](./images/6.png)

---

# 6. Conclusion
- Theo dõi thú cưng theo thời gian thực  
- Tự động cho ăn  
- Giám sát môi trường đầy đủ  
- Điều khiển thiết bị theo ngưỡng hoặc thủ công  
- Dashboard dễ dùng và trực quan  
- Kết nối MQTT ổn định  

## Hướng phát triển:
- Camera livestream  
- Nhận diện thú cưng bằng AI  
- Lịch cho ăn tự động  
- Cảnh báo qua Zalo / Telegram  
