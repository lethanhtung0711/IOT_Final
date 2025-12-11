# 🐾 Smart Pet Care System
### Hệ thống chăm sóc thú cưng thông minh sử dụng ESP32, MQTT và Node-RED

---

## 📌 Giới thiệu

Trong cuộc sống hiện đại, nhiều người nuôi thú cưng như chó, mèo nhưng không phải lúc nào cũng có thời gian để chăm sóc đầy đủ. Các vấn đề thường gặp:

- Bận rộn, quên cho ăn đúng giờ  
- Không theo dõi được môi trường sống của thú cưng  
- Không biết thú cưng đang ở trong chuồng hay đi ra ngoài  
- Không phát hiện kịp các vấn đề nguy hiểm như nóng quá mức, ẩm cao hoặc khí độc  

**Smart Pet Care System** được thiết kế để giải quyết những vấn đề đó bằng cách giám sát hoàn toàn tự động và có thể điều khiển từ xa.

---

## 🚗 Problem Statement — Vấn đề thực tiễn

### Nhu cầu thực tế
- Thú cưng cần ăn uống đúng giờ và đúng lượng.  
- Môi trường chuồng nuôi phải an toàn và thoải mái.  
- Chủ nuôi cần giám sát từ xa khi đi làm hoặc đi du lịch.  
- Hệ thống cần hoạt động ổn định và tự động hóa tối đa.

### Những hạn chế hiện tại
- Cho ăn thủ công dễ bị bỏ quên  
- Môi trường thay đổi nguy hiểm nhưng không được phát hiện kịp thời  
- Không thể biết thú cưng ra/vào chuồng  
- Công chăm sóc lớn khi chủ bận rộn  

---

## 🌟 Real-World Demand — Tính cấp thiết

Một hệ thống chăm sóc thú cưng thông minh giúp:

- Tự động hóa chăm sóc thường ngày  
- Tăng an toàn nhờ theo dõi môi trường  
- Điều khiển và giám sát từ xa  
- Giảm công sức chăm sóc  
- Nâng cao chất lượng sống cho thú cưng  

Giải pháp chi phí thấp, dễ triển khai cho các hộ gia đình.

---

## 💡 Inspiration — Ý tưởng phát triển

Dự án được phát triển từ nhu cầu thực tế:

- Chủ nuôi thường bận rộn không thể chăm sóc đầy đủ  
- Buồng chuồng kín có thể quá nóng hoặc thiếu thoáng khí  
- Thú cưng hay chạy ra ngoài mà chủ không biết  
- Mong muốn tự động hóa để giảm tải công việc  

Mục tiêu: **đơn giản – rẻ – thông minh – dễ mở rộng**.

---

## 🔧 Hardware — Phần cứng sử dụng

### **Bộ điều khiển**
- ESP32 DevKit V1 — trung tâm xử lý và giao tiếp MQTT

### **Hệ thống chăm sóc thú cưng**
- Servo SG90 → mở nắp khay thức ăn  
- Cảm biến hồng ngoại IR → phát hiện thú cưng đến gần  
- Cảm biến mức nước → kiểm tra nước uống  

### **Hệ thống môi trường**
- SHT30 / DHT22 → đo nhiệt độ và độ ẩm  
- MQ-2 → phát hiện khói / khí gas  
- LDR → đo ánh sáng môi trường  
- LED → chiếu sáng khi trời tối  
- Quạt mini → làm mát chuồng khi nhiệt độ cao  

### **Nguồn**
- Adapter 5V–2A

---

## 🧠 Software — Phần mềm sử dụng

### **Node-RED Dashboard**
- Hiển thị trạng thái chuồng (có thú / trống)  
- Điều khiển quạt, đèn, servo  
- Biểu đồ nhiệt độ – độ ẩm  
- Cảnh báo thời gian thực qua MQTT  

### **MQTT Broker**
- EMQX Cloud  
- Ổn định, dễ dùng, tốc độ nhanh  

### **PlatformIO**
- Lập trình ESP32  
- Tổ chức code module, dễ bảo trì  

---

## 🏗️ Concept — Nguyên lý hoạt động

### **1️⃣ Cho ăn tự động**
- IR phát hiện thú cưng → mở nắp thức ăn bằng servo  
- Có chế độ điều khiển từ dashboard  

### **2️⃣ Theo dõi hoạt động**
- IR nhận biết thú cưng đang ở trong chuồng hay không  
- Dashboard hiển thị: **OCCUPIED / EMPTY**  

### **3️⃣ Giám sát môi trường**
- Gửi dữ liệu nhiệt độ – độ ẩm liên tục  
- Nếu quá nóng → bật quạt  
- Nếu trời tối → bật đèn  

### **4️⃣ Theo dõi nước uống**
- Cảm biến mức nước cảnh báo khi sắp hết  

### **5️⃣ Điều khiển từ xa**
Qua MQTT, có thể điều khiển:

- Quạt  
- Đèn  
- Servo thức ăn  
- Chế độ tự động  

---

## 📊 Dashboard Features

- Trạng thái thú cưng theo thời gian thực  
- Biểu đồ nhiệt độ – độ ẩm  
- Điều khiển toàn bộ thiết bị trong chuồng  
- Màu sắc trực quan: ĐỎ (có thú), XANH (trống)  

---

## 🎯 Kết luận

Hệ thống Smart Pet Care System mang lại:

- Tự động hóa quá trình chăm sóc  
- Giám sát an toàn và cảnh báo tức thời  
- Giảm công việc cho người nuôi  
- Tăng sự thoải mái và an toàn cho thú cưng  

### Khả năng mở rộng:
- Camera livestream  
- Nhận diện khuôn mặt thú cưng bằng AI  
- Theo dõi sức khỏe (chuyển động, nhịp tim)  
- Gửi thông báo về điện thoại  

---

## 👤 Tác giả

**Ngọc Mũm Mĩm 💖**  
Hệ thống được xây dựng với sự đam mê IoT và tình yêu dành cho thú cưng.

