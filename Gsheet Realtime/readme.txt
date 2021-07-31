Cài đặt python 1 trong các phiên bản: 3.6, 3.7, 3.8 
	https://www.python.org/downloads/

Mở CMD (Win+R gõ cmd)
paste các lệnh sau

	py -m ensurepip --upgrade
	pip install pandas

Bấm chuột phải vào file main.py chọn edit with notepad
Sửa các đường dẫn tới thư mục gồm
- Thư mục film
- Thư mục để lưu các file excels
- Sửa thời gian cập nhật

mở CMD với thư mục chứa file main.py
(mở thư mục chứa file main.py, đưa chuột vào thanh địa chỉ, xoá hết, gõ cmd rồi enter)

sau đó nhập lệnh:

	python main.py

Để dừng việc cập nhật thì đóng cmd. 
Sau khi chạy thử thành công (cmd hiện 0,1,2,3... tương ứng số lần cập nhật)
Edit file main và xoá dòng lệnh print(i) ở cuối file