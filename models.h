#pragma once

typedef struct mNgaySinh
{
	int ngay;
	int thang;
	int nam;
} NgaySinh;

/*
** true:Nam - flase:Nu
*/
typedef struct mNhanVien
{
	int maNhanVien;
	char ho[30];
	char ten[30];
	NgaySinh ngaySinh;
	bool gioiTinh;
	char donVi[30];
	char chucVu[30];
	float heSoLuong;
	float luong = 0;
	float phuCap = 0;
	float thucLinh = 0;
} NhanVien;
