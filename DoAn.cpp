#include"models.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

const int SEARCH_AS = 1;
const int SEARCH_DES = 2;


int searchType = 0;
NhanVien* ListData = NULL;
int ListSize = 0;


void readFile();
void writeFile();
void addNhanVien(NhanVien& nv);
NhanVien& newNhanVien();
void showNhanVien(NhanVien nv);
void showListNhanVien();
void remove(int position);
void menu();
void formatData(char *s);
void sortAscending();
void sortDescending();
int searchMSNV(int msnv);
int searchName(char* s);
bool isCompareName(char* s1, char* s2);


void InDanhSach();
void BoSungNhanVien();
void TimKiemNhanVien();
void SapXepNhanVien();
void ChenNhanVien();
void XoaNhanVien();
void XoaNhanVienLonTuoi();
void TinhLuongNhanVien();
void InBangThongKe();


int main() {

	readFile();
	menu();
}


void writeFile() {
	ofstream fileOutput("output.txt");

	if (fileOutput.fail())
	{
		cout << "File not found" << endl;
		return;
	}

	for (int i = 0; i < ListSize; i++) {	
		fileOutput << ListData[i].maNhanVien << " ";
		fileOutput << ListData[i].gioiTinh << " ";
		fileOutput << ListData[i].heSoLuong << " ";
		fileOutput << ListData[i].ngaySinh.ngay << " ";
		fileOutput << ListData[i].ngaySinh.thang << " ";
		fileOutput << ListData[i].ngaySinh.nam << " ";
		fileOutput << ListData[i].ho << "$";
		fileOutput << ListData[i].ten << "$";
		fileOutput << ListData[i].donVi << "$";
		fileOutput << ListData[i].chucVu;
		if (i != ListSize - 1) {
			fileOutput << endl;
		}	
	}

	fileOutput.close();
}

void sortAscending()
{
	searchType = SEARCH_AS;

	for (int i = 0; i < ListSize; i++) {
		for (int j = i+1; j < ListSize; j++) {
			if (ListData[i].maNhanVien > ListData[j].maNhanVien) {
				NhanVien temp = ListData[i];
				ListData[i] = ListData[j];
				ListData[j] = temp;
			}
		}
	}
}

void sortDescending()
{
	searchType = SEARCH_DES;

	for (int i = 0; i < ListSize; i++) {
		for (int j = i + 1; j < ListSize; j++) {
			if (ListData[i].maNhanVien < ListData[j].maNhanVien) {
				NhanVien temp = ListData[i];
				ListData[i] = ListData[j];
				ListData[j] = temp;
			}
		}
	}
}

int searchMSNV(int msnv)
{
	for (int i = 0; i < ListSize; i++) {
		if (ListData[i].maNhanVien == msnv) {
			return i;
		}
	}
	return -1;
}

int searchName(char* s)
{
	for (int i = 0; i < ListSize; i++) {
		if (isCompareName(s, ListData[i].ten)) {
			return i;
		}
	}
	return -1;
}

bool isCompareName(char* s1, char* s2)
{
	int l1 = 0;
	while (s1[l1++] != NULL);

	int l2 = 0;
	while (s2[l2++] != NULL);

	if (l1 != l2)
		return false;
	for (int i = 0; i < l1;i++) {
		if (s1[i] != s2[i]) {
			return false;
		}
	}

	return true;
}


void menu() {
	int select;
	while (true)
	{
		system("cls");
		cout << "1. In danh sach thong tin cac nhan vien" << endl;
		cout << "2. Bo sung mot nhan vien vao danh sach" << endl;
		cout << "3. Tim kiem nhan vien" << endl;
		cout << "4. Sap xep nhan vien" << endl;
		cout << "5. Chen nhan vien" << endl;
		cout << "6. Xoa nhan vien" << endl;
		cout << "7. Xoa nhan vien co do tuoi lon hon 50" << endl;
		cout << "8. Tinh luong cho cac nhan vien" << endl;
		cout << "9. In bang thong ke theo don vi" << endl;
		cout << "10. Thoat chuong trinh" << endl;
		cout << "Moi nhap lua chon: ";
		cin >> select;
		cin.ignore();
		switch (select)
		{
		case 1:
			InDanhSach();
			break;
		case 2:
			BoSungNhanVien();
			break;
		case 3:
			TimKiemNhanVien();
			break;
		case 4:
			SapXepNhanVien();
			break;
		case 5:
			ChenNhanVien();
			break;
		case 6:
			XoaNhanVien();
			break;
		case 7:
			XoaNhanVienLonTuoi();
			break;
		case 8:
			TinhLuongNhanVien();
			break;
		case 9:
			InBangThongKe();
			break;
		case 10:
			writeFile();
			exit(0);
		default:
			break;
		}
	}
}

void formatData(char* s)
{
	int i = 0;
	while (s[i] != '\n') 
	{
		i++;
	}
	s[i] = NULL;
}

void InDanhSach()
{
	system("cls");
	showListNhanVien();
	system("pause");
}

void BoSungNhanVien()
{
	system("cls");
	NhanVien nv = newNhanVien();

	for (int i = 0; i < ListSize; i++) {
		if (ListData[i].maNhanVien == nv.maNhanVien) {
			cout << "Ma nhan vien bi trung!" << endl;
			return;
		}
	}
	addNhanVien(nv);
	cout << "Da them thanh cong!"<<endl;
	system("pause");
}

void TimKiemNhanVien()
{
	system("cls");
	int select;
	do
	{
		cout << "1. Tim kiem theo ma nhan vien" << endl;
		cout << "2. Tim kiem theo ten nhan vien" << endl;
		cout << "Moi nhap lua chon: ";
		cin >> select;
	} while (select < 1 || select > 2);
	
	if (select == 1)
	{
		int msnv = 0;
		cout << "Nhap ma nhan vien: ";
		cin >> msnv;
		int position = searchMSNV(msnv);
		if (position == -1) {
			cout << "Khong tim thay!" << endl;
		}
		else {
			showNhanVien(ListData[position]);
		}
	}
	else
	{
		cin.ignore();
		char s[30];
		cout << "Nhap ten nhan vien: ";
		fgets(s, 30, stdin);
		formatData(s);
		int position = searchName(s);
		if (position == -1) {
			cout << "Khong tim thay!" << endl;
		}
		else {
			showNhanVien(ListData[position]);
		}
	}
	system("pause");
}

void SapXepNhanVien()
{
	system("cls");
	int select;
	do
	{
		cout << "1. Sap xep tang dan" << endl;
		cout << "2. Sap xep giam dan" << endl;
		cout << "Moi nhap lua chon: ";
		cin >> select;
	} while (select < 1 || select > 2);

	if (select == 1)
	{
		sortAscending();
	}
	else
	{
		sortDescending();
	}
	cout << "Da sap xep xong!" << endl;
	system("pause");
}

void ChenNhanVien()
{
	system("cls");
	NhanVien nv = newNhanVien();

	NhanVien *temp = new NhanVien[ListSize];
	for (int i = 0; i < ListSize; i++) {
		temp[i] = ListData[i];
	}

	if (searchType == SEARCH_AS) {
		int index = 0;
		for (int i = 0; i < ListSize; i++) {
			if (nv.maNhanVien < ListData[i].maNhanVien) {
				index = i;
				break;
			}

		}
		delete[] ListData;
		ListData = new NhanVien[ListSize + 1];

		for (int i = 0; i < index; i++) {
			ListData[i] = temp[i];
		}
		ListData[index] = nv;
		for (int i = index; i < ListSize; i++) {
			ListData[i + 1] = temp[i];
		}
		ListSize++;
	}
	else if (searchType == SEARCH_DES) {
		int index = 0;
		for (int i = 0; i < ListSize; i++) {
			if (nv.maNhanVien > ListData[i].maNhanVien) {
				index = i;
				break;
			}

		}
		delete[] ListData;
		ListData = new NhanVien[ListSize + 1];

		for (int i = 0; i < index; i++) {
			ListData[i] = temp[i];
		}
		ListData[index] = nv;
		for (int i = index; i < ListSize; i++) {
			ListData[i + 1] = temp[i];
		}
		ListSize++;
	}
	else {
		cout << "Ban phai sap xep truoc khi chen!";
		delete[] temp;
		system("pause");
		return;
	}
	delete[] temp;
	cout << "Da chen thanh cong!" << endl;
	system("pause");
}

void XoaNhanVien()
{
	system("cls");
	if (ListSize == 0) {
		cout << "Khong co du lieu de xoa!" << endl;
		system("pause");
		return;
	}

	cout << "MSNV " << "Ten nhan vien" << endl;
	for (int i = 0; i < ListSize; i++) {
		cout << setw(4);
		cout << ListData[i].maNhanVien;
		cout << ListData[i].ho << " " << ListData[i].ten << endl;
	}
	cout << "Nhap ma nhan vien muon xoa: ";
	int msnv;
	cin >> msnv;
	for (int i = 0; i < ListSize; i++) {
		if (msnv == ListData[i].maNhanVien) {
			remove(i);
			cout << "Da xoa thanh cong!" << endl;
			system("pause");
			return;
		}
	}
	cout << "MSNV khong ton tai!" << endl;
	system("pause");
}

void XoaNhanVienLonTuoi()
{
}

void TinhLuongNhanVien()
{
}

void InBangThongKe()
{
}

void remove(int position) {
	const int max = ListSize - 1;

	NhanVien* temp = new NhanVien[max];

	for (int i = 0; i < position; i++) {
		temp[i] = ListData[i];
	}
	for (int i = position + 1; i < ListSize; i++) {
		temp[i - 1] = ListData[i];
	}

	delete[] ListData;
	ListData = new NhanVien[max];
	for (int i = 0; i < max; i++) {
		ListData[i] = temp[i];
	}

	ListSize--;
	delete[] temp;
}

void showListNhanVien() {
	system("cls");
	cout << "DANH SACH NHAN VIEN" << endl;

	for (int i = 0; i < ListSize; i++) {
		cout << endl;
		cout << "Ho va ten: " << ListData[i].ho << " " << ListData[i].ten << endl;
		cout << "Ma nhan vien: " << ListData[i].maNhanVien << endl;
		cout << "Ngay sinh: " << ListData[i].ngaySinh.ngay << "/" << ListData[i].ngaySinh.thang << "/" << ListData[i].ngaySinh.nam << endl;
		cout << "Gioi tinh: " << (ListData[i].gioiTinh ? "Nam" : "Nu") << endl;
		cout << "Don vi: " << ListData[i].donVi << endl;
		cout << "Chuc vu: " << ListData[i].chucVu << endl;
		cout << "He so luong: " << ListData[i].heSoLuong << endl;
		cout << "Luong: " << ListData[i].luong << endl;
		cout << "Phu cap: " << ListData[i].phuCap << endl;
		cout << "Thuc linh: " << ListData[i].thucLinh << endl;

	}
}

void readFile() {
	ifstream fileInput("data.txt");

	if (fileInput.fail())
	{
		cout << "File not found" << endl;
		return;
	}

	ListData = new NhanVien[1];

	while (!fileInput.eof()) {
		try
		{
			//1 1 1 1 1 1999 Vo$Van Mot$Cong ty phan bon Ninh Binh$GD
			NhanVien nv;

			fileInput >> nv.maNhanVien;
			fileInput >> nv.gioiTinh;
			fileInput >> nv.heSoLuong;
			fileInput >> nv.ngaySinh.ngay;
			fileInput >> nv.ngaySinh.thang;
			fileInput >> nv.ngaySinh.nam;		

			fileInput.getline(nv.ho, 30,'$');
			fileInput.getline(nv.ten, 30, '$');
			fileInput.getline(nv.donVi, 30, '$');
			fileInput.getline(nv.chucVu, 30);
			
			addNhanVien(nv);
		}
		catch (const std::exception & e)
		{
			cout << "Error: Do not read file" << endl;
		}
	}


	fileInput.close();

}

void addNhanVien(NhanVien& nv) {
	if (ListSize == 0) {
		ListData = new NhanVien[1];
		ListData[0] = nv;
		ListSize++;
	}
	else {
		NhanVien* temp = new NhanVien[ListSize];
		for (int i = 0; i < ListSize; i++) {
			temp[i] = ListData[i];
		}
		delete[] ListData;
		ListData = new NhanVien[ListSize + 1];
		for (int i = 0; i < ListSize; i++) {
			ListData[i] = temp[i];
		}
		ListData[ListSize] = nv;
		ListSize++;
		delete[] temp;
	}
}

NhanVien& newNhanVien()
{
	NhanVien nv;
	rewind(stdin);
	cout << "Nhap ma nhan vien: ";
	cin >> nv.maNhanVien;
	cout << "Nhap gioi tinh(1.Nam - 0.Nu): ";
	cin >> nv.gioiTinh;
	cout << "Nhap he so luong: ";
	cin >> nv.heSoLuong;
	cout << "Nhap ngay sinh: ";
	cin >> nv.ngaySinh.ngay;
	cout << "Nhap thang sinh: ";
	cin >> nv.ngaySinh.thang;
	cout << "Nhap nam sinh: ";
	cin >> nv.ngaySinh.nam;
	cin.ignore();
	cout << "Nhap ho nhan vien: ";
	fgets(nv.ho, 30, stdin);
	formatData(nv.ho);
	cout << "Nhap ten nhan vien: ";
	fgets(nv.ten, 30, stdin);
	formatData(nv.ten);
	cout << "Nhap don vi: ";
	fgets(nv.donVi, 30, stdin);
	formatData(nv.donVi);
	cout << "Nhap chuc vu: ";
	fgets(nv.chucVu, 30, stdin);
	formatData(nv.chucVu);
	return nv;
}

void showNhanVien(NhanVien nv)
{
	cout << "Ho va ten: " << nv.ho << " " << nv.ten << endl;
	cout << "Ma nhan vien: " << nv.maNhanVien << endl;
	cout << "Ngay sinh: " << nv.ngaySinh.ngay << "/" << nv.ngaySinh.thang << "/" << nv.ngaySinh.nam << endl;
	cout << "Gioi tinh: " << (nv.gioiTinh ? "Nam" : "Nu") << endl;
	cout << "Don vi: " << nv.donVi << endl;
	cout << "Chuc vu: " << nv.chucVu << endl;
	cout << "He so luong: " << nv.heSoLuong << endl;
	cout << "Luong: " << nv.luong << endl;
	cout << "Phu cap: " << nv.phuCap << endl;
	cout << "Thuc linh: " << nv.thucLinh << endl;
}
