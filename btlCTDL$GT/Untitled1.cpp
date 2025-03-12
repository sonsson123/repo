#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Dinh nghia cau truc Sinh vien
struct SinhVien {
    string maSV;      // Ma sinh vien
    string hoTen;     // Ho va ten
    int namSinh;      // Nam sinh
    double diemTB;    // Diem trung binh
};

// Dinh nghia Node cua cay nhi phan tim kiem
struct Node {
    SinhVien sv;      // Du lieu cua sinh vien
    Node* trai;       // Con trai
    Node* phai;       // Con phai
};

// Ham tao mot node moi
Node* taoNode(SinhVien sv) {
    Node* nodeMoi = new Node;  // Cap phat bo nho cho node moi
    nodeMoi->sv = sv;          // Gan du lieu sinh vien vao node
    nodeMoi->trai = nullptr;   // Ban dau node chua co con trai
    nodeMoi->phai = nullptr;   // Ban dau node chua co con phai
    return nodeMoi;
}

// Ham chen sinh vien vao cay BST
Node* chenNode(Node* goc, SinhVien sv) {
    if (goc == nullptr) {
        return taoNode(sv);  // Neu cay rong, tao node moi lam goc
    }

    if (sv.maSV < goc->sv.maSV) {
        goc->trai = chenNode(goc->trai, sv);  // Chen vao cay con trai neu ma sinh vien nho hon
    } else if (sv.maSV > goc->sv.maSV) {
        goc->phai = chenNode(goc->phai, sv); // Chen vao cay con phai neu ma sinh vien lon hon
    }

    return goc;
}

// Ham duyet cay theo thu tu LRN
void duyetLRN(Node* goc) {
    if (goc != nullptr) {
        duyetLRN(goc->trai);    // Duyet cay con trai
        duyetLRN(goc->phai);   // Duyet cay con phai
        cout << "Ma SV: " << goc->sv.maSV << ", Ho ten: " << goc->sv.hoTen
             << ", Nam sinh: " << goc->sv.namSinh << ", Diem TB: " << goc->sv.diemTB << endl;
    }
}

// Ham dem so node co dung hai cay con
int demNodeHaiCon(Node* goc) {
    if (goc == nullptr) return 0;

    int dem = demNodeHaiCon(goc->trai) + demNodeHaiCon(goc->phai);

    if (goc->trai != nullptr && goc->phai != nullptr) {
        dem++;  // Neu node co ca hai con, tang bien dem
    }

    return dem;
}

// Ham doc du lieu tu file
Node* docFileVaTaoCay(string tenFile) {
    ifstream file(tenFile);
    if (!file) {
        cout << "Khong the mo file!" << endl;
        return nullptr;
    }

    Node* goc = nullptr;
    SinhVien sv;
    
    while (file >> sv.maSV) { 
        file.ignore();  
        getline(file, sv.hoTen);
        file >> sv.namSinh >> sv.diemTB;

        goc = chenNode(goc, sv);  // Chen sinh vien vao cay
    }

    file.close();
    return goc;
}

// Ham tim sinh vien theo ma
Node* timSinhVien(Node* goc, string maSV) {
    if (goc == nullptr || goc->sv.maSV == maSV) {
        return goc;  // Tra ve node neu tim thay hoac neu cay rong
    }

    if (maSV < goc->sv.maSV) {
        return timSinhVien(goc->trai, maSV);  // Tim ben trai neu ma nho hon
    } else {
        return timSinhVien(goc->phai, maSV); // Tim ben phai neu ma lon hon
    }
}

int main() {
    string tenFile = "sinhvien.txt";
    Node* goc = docFileVaTaoCay(tenFile);

    if (goc == nullptr) {
        cout << "Khong the khoi tao cay!" << endl;
        return 1;
    }

    cout << "Danh sach sinh vien (duyet theo LRN):\n";
    duyetLRN(goc);

    cout << "\nSo node co dung hai con: " << demNodeHaiCon(goc) << endl;

    // Tim sinh vien theo ma
    string maTim;
    cout << "\nNhap ma sinh vien can tim: ";
    cin >> maTim;

    Node* ketQua = timSinhVien(goc, maTim);
    if (ketQua) {
        cout << "Tim thay: " << ketQua->sv.hoTen << " - Diem TB: " << ketQua->sv.diemTB << endl;
    } else {
        cout << "Khong tim thay sinh vien!\n";
    }

    return 0;
}

