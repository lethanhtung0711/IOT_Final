# Bảng điều khiển IoT bằng Dashboard UI trong Node-RED 

Các dự án thực hành, học tập việc tạo bảng điều khiển và giám sát cho các dự án IoT bằng Dashboard UI trên Node-RED 

## Dự án 1: Đồng hồ đo và Đồ thị 

- Sử dụng Gauge node (đồng hồ đo) và Chart node (đồ thị) để hiển thị các thông số nhiệt độ và độ ẩm
- Nhiệt độ và độ ẩm được mô phỏng bằng hàm Math.random trong function nodes
- Các thao tác học tập trong dự án này:
    + Cài đặt `node-red-dash-board` Palette (một bảng các node để tạo giao diện bảng điều khiển)
    + Thiết kế một bảng điều khiển đơn giản từ thiết kế flow với các nodes
    + Các thành phần cơ bản của dashboard: Layout >> Tabs >> Groups >> Widget 
    + Một số cách tùy biến hiển thị trên dashboard ... 
- [Kho mã dự án](./TempGaugeChartUI/)

## Dự án 2: Thanh điều khiển slider 

- Dashboard ngoài chức năng hiển thị (giám sát thông số) còn có chức năng điều khiển 
- Dự án này sử dụng một thanh điều khiển (slider) để điều khiển tham số hiện lên đồ thị 
- Một số node điều khiển khác như nút bấm, bạn có thể tự khám phá 
- [Kho mã dự án](./TempGaugeChartUI/)

## Dự án 3: Giao tiếp hiển thị số liệu qua MQTT Broker 

Dự án này bao gồm hai kho mã nguồn 
1. Dashboard cho hiển thị nhiệt độ, độ ẩm, và thanh điều khiển độ sáng trên Node-RED. [Link](./DHT22_LED_Dashboard/) 
2. Mã nguồn firmware trên ESP32, kèm các file thiết lập mô phỏng Wokwi trên VS-Code. [Link](./DHT22_MQTT_LED_ESP32/)

## Hướng dẫn sử dụng Wokwi trên VS Code
Wokwi là một trình mô phỏng phần cứng như ESP32 và các ngoại vi khác trên nền web. Gần đây đã có thể cài phần mở rộng để chạy trực tiếp trên VS Code giúp rút ngắn thời gian biên dịch code (ở trên web sẽ lâu và phụ thuộc vào tải của server wokwi hiện tại) và thời gian để thử nghiệm code trên phần cứng. Tất nhiên cuối cùng các bạn vẫn nên nạp code vào phần cứng thật. 

1. Cài Wokwi extension (bấm vào nut extension trên vscode tìm Wokwi --> cài đặt)
2. Thêm file `diagram.json` vào thư mục dự án pio (cùng mức với file platformio.ini) để hiển thị sơ đồ dự án. Sơ đồ này hiện chỉ có thể biên soạn và copy từ web wokwi.com
3. Thêm file `wokwi.toml` để chỉ đường dẫn đến các file firmware biên dịch ra từ pio. Ví dụ: https://github.com/wokwi/esp32-ntp-clock/blob/main/wokwi.toml 

Tham khảo thêm: https://docs.wokwi.com/vscode/getting-started 