#include<iostream>
#include<CoreWindow.h> //window.h hàm này dùng để build hàm gotoxy()
#include<conio.h> // xài cho hàm _getch() dùng để clear thông báo. Và xài cho hàm _khbit() để kiểm tra phát hiện sự kiện "nhấn phím"
#include<cmath>
#define MAX  100
int toa_do_x[MAX] = {}; // 100 tọa độ x đc khởi tạo có giá trị là 0
int toa_do_y[MAX] = {}; // 100 tọa độ y đc khởi tạo có giá trị là 0

int sl = 5; // Snake's lenght
int const FOOD_NUM = 5;
int xqua = -1;
int yqua = -1;

using namespace std;
char mssv[8] = { '2','3','1','2','0','2','4','2' };
void play();
void gotoxy(int x, int y);
void ve_tuong();
void khoi_tao_ran(); // 
void ve_ran();
void di_chuyen_ran(int x, int y);
void xoa_doan_duoi();
void ShowCur(bool CursorVisibility);// hàm này dùng để tắt cái nhấp nháy của con trỏ :D
bool game_over();
bool ktra_ran_de_qua();
void tao_qua();
void ve_qua();
bool ktra_ran_an_qua();
void xu_ly_ran_an_qua();





int main() {
	srand(time(NULL)); // tạo hạt giống cho rand();
	play();

	_getch(); // hàm này để delay in ra màn hình dòng thông báo của chương trình ở đoạn cuối ctrinh
	gotoxy(100, 25); // này là để đẩy cái thông báo console xuống dưới màn hình ( ngoài khoảng tường) (chủ yếu mang tính thẩm mỹ)
	return 0;


}












void play() {
	//				Build game - setting -
	ShowCur(0); // tắt nháy chuột: nhìn mượt hơn
	ve_tuong();
	khoi_tao_ran(); // dùng hàm khởi tạo rắn để tạo tọa độ đầu tiên của con rắn ( sau đó con rắn sẽ đc vẽ bằng hàm ve_ran)
	int x = toa_do_x[0];
	int y = toa_do_y[0];
	//create_food();
	int check = 2; // biến này dùng để kiểm tra cho các nút điều khiển: xuống - lên - trái - phải của rắn
	// 0: xuống
	// 1: lên
	// 2: phải
	// 3: trái

   //					 ----- PLAY ----
	tao_qua();
	ve_qua();
	while (true) {

		// clear data cũ
		xoa_doan_duoi();

		// in
			 if (check == 2) { ++x; }// sang phải thì tọa độ x + 1 
		else if (check == 1) { --y; }// lên thì tọa độ y - 1 
		else if (check == 0) { ++y; }// xuống thì tọa độ y + 1 
		else if (check == 3) { --x; }// trái thì tọa độ x - 1 
		di_chuyen_ran(x, y); // hàm này sẽ xử lý tọa độ của rắn
	
		// ve ran
		ve_ran();



		// điều khiển(
		if (_kbhit() == true) { // có thể viết (_kbhit()) thì cũng trả về true (phát hiện nhấn phím)
			char c = _getch();
			if (c == -32) { // kiểm tra xem có phải là phím mũi tên ko? 


				c = _getch();

				if ((c == 72) && (check != 0)) { // phím mũi tên đi lên. c == 72 và check trước đó phải khác 0. để tránh trg hợp cho con rắn đang đi xuống mà có thể đi lên

					check = 1; // lên

				}
				else if ((c == 80) && (check != 1)) {// c == 80 và check trước đó phải khác 1. Để tránh trg hợp cho con rắn đang đi lên mà có thể đi xuống
					check = 0; // xuống

				}
				else if ((c == 75) && (check != 2)) {// c == 75 và check trước đó phải khác 2. để tránh trg hợp cho con rắn đang sang phải mà có thể sang trái
					check = 3; // trái

				}
				else if ((c == 77) && (check != 3)) { // c == 75 và check trước đó phải khác 3. để tránh trg hợp cho con rắn đang sang trái mà có thể sang phải5
					check = 2; // phải

				}
			}
		}
		if (game_over() == true) break; // thoát khỏi vòng while
		xu_ly_ran_an_qua();
		Sleep(100);
	}
}
bool ktra_ran_de_qua() {
	for (int i = 0; i < sl; ++i) {
		if ((xqua == toa_do_x[i]) && yqua == toa_do_y[i]) {
			return true;
		}
	}
	return false;
}
void tao_qua() {
	do {
		xqua = rand() % (109 - 11 + 1) + 11;
		yqua = rand() % (23 - 2 + 1) + 2;
	} while (ktra_ran_de_qua());
}
void ve_qua() {

	gotoxy(xqua, yqua); cout << "*";
}
bool ktra_ran_an_qua() {

	/* có thể viết là
	 return ( (toa_do_x[0] == xqua) && (toa_do_y[0] == yqua) )
	*/
	if ((toa_do_x[0] == xqua) && (toa_do_y[0] == yqua)) {
		return true;
	}
	return false;
}
void xu_ly_ran_an_qua() {
	if (ktra_ran_an_qua()) {
		if (sl < 8) {
			sl++;
		}
		tao_qua(); // tạo quả mới
		ve_qua();

	}
}
bool game_over() {
	if (toa_do_x[0] == 10 || toa_do_x[0] == 110 || toa_do_y[0] == 1 || toa_do_y[0] == 25) // chạm tường
	{
		return true;
	}
	if (sl >= 5) { // trường hợp rắn cắn phải thân điều kiện cần là sl >= 5)
		for (int i = 4; i < sl; ++i) { // khởi tạo từ i = 4 vì, trường hợp rắn cắn phải thân chỉ xảy ra khi đầu rắn chạm vào đốt thứ 4 trở lên ( số thứ tự = 0 tính từ đầu rắn)
			if ((toa_do_x[0] == toa_do_x[i]) && (toa_do_y[0] == toa_do_y[i])) {
				return true;
			}
		}
	}
	return false;
}

void xoa_doan_duoi() {
	gotoxy(toa_do_x[sl], toa_do_y[sl]);
	// dễ thấy ta đưa con trỏ vê đoạn đuôi của con rắn và cout khoảng space để xóa đi pt cuối
	// Ta khi mà con rắn di chuyển 1 đơn vị thì mảng tọa độ sẽ luôn có phần tử ko đc in
	//Việc của chúng ta là lấy tọa độ của phần tử "vừa bị đẩy ra" và đưa con trỏ về tọa độ đó rồi cout << khoảng trắng
	cout << " ";

}
void di_chuyen_ran(int x, int y) {

	for (int i = sl; i > 0; i--) {
		toa_do_x[i] = toa_do_x[i - 1]; // dịch chuyển các phần tử trong mảng sang trái ( Là xóa phần tử phải nhất)
		toa_do_y[i] = toa_do_y[i - 1]; // nhưng phần từ thứ i = 0 đang được giữ nguyên sẽ được gán bởi 1 tọa độ mới ( đó là toa_do_x[0] = x);
	}

	toa_do_x[0] = x; // phần từ thứ i = 0 đang được giữ nguyên sẽ được gán bởi 1 tọa độ mới
	toa_do_y[0] = y;
}
void khoi_tao_ran() {
	int x_khoitao = 50; // khởi tạo 2 tọa đồ nhằm cho con rắn sẽ mặc định xuất hiện ở giữa màn hình khi bắt đầu game.
	int y_khoitao = 13;
	for (int i = 0; i < sl; ++i) { // thực hiện khởi tạo giá trị tọa độ cho mỗi x0;y0 , x1;y1 , x2;y2, ...
		toa_do_x[i] = x_khoitao--; // x giảm nhưng y không giảm  vì đuôi rắn sẽ là 1 hàng ngang
		toa_do_y[i] = y_khoitao;
	}
}

void ve_ran() {
	for (int i = 0; i < sl; ++i) {
		gotoxy(toa_do_x[i], toa_do_y[i]);
		cout << mssv[i];
		// 2 3 1 2 0 2 4 2 [ 0 -> 7]
		//[sl = 5] giả sử ta muốn in mssv là 2 3 1 2 0; i = (0-4)
		// thì phải in ra các số từ phải sang trái tức là số 2 (nằm phía bên phải nhất) sau đó là số 4 và ....

	}
}

void ShowCur(bool CursorVisibility) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
void gotoxy(int x, int y) { // bởi vì ko có hàm gotoxy trong thư viện của C++ nên ta tự định nghĩa hàm.
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void ve_tuong() {
	for (int x = 10; x <= 110; ++x) {
		gotoxy(x, 1);
		cout << "-";
		gotoxy(x, 25);
		cout << "-";
	}
	for (int y = 1; y <= 25; ++y) {
		gotoxy(10, y);
		cout << "|";
		gotoxy(110, y);
		cout << "|";
	}

}
