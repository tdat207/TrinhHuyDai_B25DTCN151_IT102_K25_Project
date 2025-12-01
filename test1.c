// TRINH HUY DAI - B25DTCN151
// PROJECT QUAN LY KHACH SAN

#include <stdio.h>      // printf, scanf, fgets
#include <string.h>     // strlen, strcmp, strcpy, sprintf
#include <stdlib.h>     // system

// ----------------- HANG SO -----------------
#define MAX_ROOMS 100       // so phong toi da
#define MAX_BOOKINGS 500    // so giao dich toi da

// ----------------- CAU TRUC DU LIEU -----------------

// Cau truc luu thong tin phong
struct Room {
    char roomId[5];     // ma phong (toi da 4 ky tu + 1 ky tu ket thuc)
    int type;           // loai phong: 1 = don, 2 = doi
    double price;       // gia phong 1 dem
    int status;         // trang thai: 0 trong, 1 dang o, 2 bao tri
};

// Cau truc luu thong tin 1 lan dat phong
struct Booking {
    char bookId[20];        // ma dat phong (VD: B001, B002)
    char roomId[5];         // phong nao duoc thue
    char customerName[50];  // ten khach hang
    int days;               // so ngay o
    double totalCost;       // tong tien = price * days
};

// ----------------- MANG TOAN CUC -----------------

struct Room rooms[MAX_ROOMS];          // mang luu danh sach phong
int roomCount = 0;                     // so phong hien co

struct Booking bookings[MAX_BOOKINGS]; // mang luu lich su dat phong
int bookingCount = 0;                  // so giao dich hien co

// ----------------- HAM TIEN ICH NHO -----------------

// ham xoa man hinh
void clearScreen() {
    system("cls");
}

// ham xoa ky tu '\n' con lai trong buffer sau khi dung scanf
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // chi doc va bo qua
    }
}

// ham can giua chuoi trong 1 cot co do rong 'width'
void printCenter(const char *text, int width) {
    int len = strlen(text);        // do dai chuoi
    if (len >= width) {            // neu dai hon cot thi in thang
        printf("%s", text);
        return;
    }

    int left = (width - len) / 2;  // so space ben trai
    int right = width - len - left;// so space ben phai

    for (int i = 0; i < left; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < right; i++) printf(" ");
}

// in tieu de bang phong
void printRoomTitle() {
    printCenter("SO PHONG", 12);   printf("|");
    printCenter("LOAI", 8);        printf("|");
    printCenter("GIA PHONG", 15);  printf("|");
    printCenter("TRANG THAI", 15); printf("\n");
    printf("--------------------------------------------------------------\n");
}

// ----------------- HAM HIEN MENU -----------------

void displayMenu() {
    printf("\n========================= MENU QUAN LY PHONG ==========================\n");
    printf("||               F01  THEM PHONG MOI                                 ||\n");
    printf("||               F02  CAP NHAT PHONG                                 ||\n");
    printf("||               F03  BAO TRI PHONG (KHOA)                           ||\n");
    printf("||               F04  HIEN THI DANH SACH                             ||\n");
    printf("||               F05  TIM KIEM PHONG TRONG THEO LOAI                 ||\n");
    printf("||               F06  SAP XEP DANH SACH PHONG (THEO GIA GIAM DAN)    ||\n");
    printf("||               F07  CHECK-IN (GIAO DICH NHAN PHONG)                ||\n");
    printf("||               F08  LICH SU THUE                                   ||\n");
    printf("||               F09  THOAT                                          ||\n");
    printf("=======================================================================\n\n");
    printf("NHAP LUA CHON (1-9): ");
}

// ----------------- F01 - THEM PHONG MOI -----------------

void addRoom() {
    struct Room newRoom;       // bien phong moi

    clearScreen();
    printf("=========== THEM PHONG MOI ===========\n");

    // ------- NHAP SO PHONG -------
    while (1) {
        printf("Nhap so phong (3-4 ky tu): ");
        fgets(newRoom.roomId, sizeof(newRoom.roomId), stdin);           // nhap chuoi
        newRoom.roomId[strcspn(newRoom.roomId, "\n")] = '\0';           // xoa '\n'

        int len = strlen(newRoom.roomId);                               // do dai ma phong

        if (len < 3 || len > 4) {                                       // kiem tra do dai
            clearScreen();
            printf("So phong phai tu 3 den 4 ky tu!\n");
            continue;                                                   // nhap lai
        }

        int duplicate = 0;                                              // kiem tra trung phong
        for (int i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, newRoom.roomId) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            clearScreen();
            printf("So phong da ton tai, vui long nhap so khac!\n");
        } else {
            break;                                                      // hop le
        }
    }

    // ------- NHAP LOAI PHONG -------
    while (1) {
        printf("Nhap loai phong (1 Don, 2 Doi): ");
        if (scanf("%d", &newRoom.type) != 1) {                          // neu nhap sai kieu
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();                                                  // xoa '\n'

        if (newRoom.type != 1 && newRoom.type != 2) {
            printf("Loai phong chi duoc nhap 1 hoac 2!\n");
        } else {
            break;
        }
    }

    // ------- NHAP GIA PHONG -------
    while (1) {
        printf("Nhap gia phong (>0): ");
        if (scanf("%lf", &newRoom.price) != 1) {                        // kieu double
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (newRoom.price <= 0) {
            printf("Gia phong phai lon hon 0!\n");
        } else {
            break;
        }
    }

    newRoom.status = 0;                                                 // mac dinh phong trong

    rooms[roomCount++] = newRoom;                                       // luu vao mang

    clearScreen();
    printf("Them phong thanh cong!\n");
}

// ----------------- F02 - CAP NHAT PHONG -----------------

void updateRoom() {
    char id[5];                 // ma phong can cap nhat
    int index;                  // vi tri phong trong mang

    while (1) {                 // vong lap de nhap lai id neu sai
        clearScreen();
        printf("=========== CAP NHAT PHONG ===========\n");

        printf("Nhap so phong can cap nhat: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';   // xoa ky tu Enter

        // tim phong trong mang rooms[]
        index = -1;
        for (int i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, id) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {  // khong tim thay phong
            clearScreen();
            printf("Khong tim thay so phong %s!\n", id);
            printf("Nhan Enter de nhap lai so phong!!!\n");
            getchar();      // dung man hinh cho nguoi dung doc
           
        } else {
            break;          // tim thay phong -> thoat vong while
        }
    }

    int newType;
    double newPrice;

    // ------- CAP NHAT LOAI PHONG -------
    while (1) {
        clearScreen();
        printf("=========== CAP NHAT PHONG ===========\n");
        printf("-- DA TIM THAY PHONG %s O VI TRI %d --\n", id, index);

        printf("Nhap loai phong moi (1 Don, 2 Doi): ");
        if (scanf("%d", &newType) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (newType != 1 && newType != 2) {
            printf("Loai phong chi duoc nhap 1 hoac 2!\n");
        } else {
            break;
        }
    }

    // ------- CAP NHAT GIA PHONG -------
    while (1) {
        printf("Nhap gia phong moi (>0): ");
        if (scanf("%lf", &newPrice) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (newPrice <= 0) {
            printf("Gia phong phai lon hon 0!\n");
        } else {
            break;
        }
    }

    rooms[index].type  = newType;   // cap nhat loai phong
    rooms[index].price = newPrice;  // cap nhat gia phong

    clearScreen();
    printf("Cap nhat phong %s thanh cong!\n", id);
}

// ----------------- F03 - BAO TRI PHONG (KHOA) -----------------

int maintenanceRoom() {
    char id[5];

    clearScreen();
    printf("=========== BAO TRI PHONG (KHOA) ===========\n");

    printf("Nhap so phong can bao tri: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = -1;                     // vi tri phong
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].roomId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        clearScreen();
        printf("Khong tim thay so phong %s!\n", id);
        return 0;
    }

    if (rooms[index].status == 1) {     // phong dang co khach
        clearScreen();
        printf("Phong %s dang co khach, khong the dua vao bao tri!\n", id);
        return 0;
    }

    rooms[index].status = 2;           // dat sang trang thai bao tri

    clearScreen();
    printf("Phong %s da duoc dua vao trang thai BAO TRI!\n", id);
    return 1;
}

// ----------------- F04 - HIEN THI DANH SACH (PHAN TRANG) -----------------

void displayRooms() {
    int perPage = 5;                                    // so phong tren 1 trang
    int page = 0;                                       // trang hien tai (0-based)
    int totalPage;

    if (roomCount == 0) {
        clearScreen();
        printf("Danh sach phong dang rong!\n");
        return;
    }

    totalPage = (roomCount + perPage - 1) / perPage;    // tinh so trang

    while (1) {
        clearScreen();
        printf("=========== DANH SACH PHONG (Trang %d/%d) ===========\n",
               page + 1, totalPage);
        printRoomTitle();

        int start = page * perPage;                     // chi so bat dau
        int end = start + perPage;                      // chi so ket thuc
        if (end > roomCount) end = roomCount;

        for (int i = start; i < end; i++) {
            char typeStr[10], priceStr[20], statusStr[20];

            strcpy(typeStr, (rooms[i].type == 1) ? "DON" : "DOI");
            sprintf(priceStr, "%.2lf", rooms[i].price);

            if (rooms[i].status == 0) strcpy(statusStr, "TRONG");
            else if (rooms[i].status == 1) strcpy(statusStr, "DANG O");
            else strcpy(statusStr, "BAO TRI");

            printCenter(rooms[i].roomId, 12); printf("|");
            printCenter(typeStr, 8);          printf("|");
            printCenter(priceStr, 15);        printf("|");
            printCenter(statusStr, 15);       printf("\n");
        }

        printf("\nNhap 'n' + Enter: trang tiep | 'p' + Enter: trang truoc | 'q' + Enter: thoat");
        printf("\nMoi ban lua chon:"); 

        char c = getchar();                   // doc 1 ky tu lenh
        clearBuffer();                        // xoa phan con lai (neu co)

        if (c == 'n' || c == 'N') {           // sang trang sau
            if (page < totalPage - 1) page++;
        } else if (c == 'p' || c == 'P') {    // ve trang truoc
            if (page > 0) page--;
        } else if (c == 'q' || c == 'Q') {    // thoat
            break;
        }
    }
}

// ----------------- F05 - TIM PHONG TRONG THEO LOAI -----------------

void searchEmptyRoomsByType() {
    int type;

    clearScreen();
    printf("=========== TIM PHONG TRONG THEO LOAI ===========\n");

    // nhap loai phong
    while (1) {
        printf("Nhap loai phong can tim (1 Don, 2 Doi): ");
        if (scanf("%d", &type) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (type != 1 && type != 2) {
            printf("Loai phong chi duoc nhap 1 hoac 2!\n");
        } else {
            break;
        }
    }

    int found = 0;                 // co tim duoc phong nao khong

    clearScreen();
    printf("======== DANH SACH PHONG TRONG LOAI %s ========\n",
           (type == 1) ? "DON" : "DOI");
    printRoomTitle();

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].type == type && rooms[i].status == 0) {   // dung loai va dang trong
            char typeStr[10], priceStr[20], statusStr[20];

            strcpy(typeStr, (rooms[i].type == 1) ? "DON" : "DOI");
            sprintf(priceStr, "%.2lf", rooms[i].price);
            strcpy(statusStr, "TRONG");

            printCenter(rooms[i].roomId, 12); printf("|");
            printCenter(typeStr, 8);          printf("|");
            printCenter(priceStr, 15);        printf("|");
            printCenter(statusStr, 15);       printf("\n");

            found = 1;
        }
    }

    if (!found) {
        printf("Hien tai khong co phong trong loai %s!\n",
               (type == 1) ? "DON" : "DOI");
    }

    printf("\nNhan Enter de quay lai menu...");
    getchar();
}

// ----------------- F06 - SAP XEP PHONG THEO GIA GIAM DAN -----------------

void sortRoomsByPriceDesc() {
    if (roomCount <= 1) {
        clearScreen();
        printf("So luong phong qua it, khong can sap xep!\n");
        return;
    }

    // bubble sort don gian
    for (int i = 0; i < roomCount - 1; i++) {
        for (int j = i + 1; j < roomCount; j++) {
            if (rooms[i].price < rooms[j].price) {   // neu phong i co gia nho hon phong j thi doi cho
                struct Room temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }

    clearScreen();
    printf("Da sap xep danh sach phong theo gia GIAM DAN!\n");
    printf("Nhan Enter de xem danh sach sau khi sap xep...\n");
    getchar();

    displayRooms();    // goi lai ham hien thi de kiem tra ket qua
}

// ----------------- F07 - CHECK-IN (GIAO DICH NHAN PHONG) -----------------

void checkIn() {
    char id[5];
    char name[50];
    int days;

    clearScreen();
    printf("=========== CHECK-IN (NHAN PHONG) ===========\n");

    // nhap so phong can check in
    printf("Nhap so phong muon nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = -1;
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].roomId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        clearScreen();
        printf("Khong tim thay so phong %s!\n", id);
        return;
    }

    // kiem tra trang thai phong
    if (rooms[index].status == 1) {
        clearScreen();
        printf("Phong %s dang co khach, khong the nhan them!\n", id);
        return;
    }
    if (rooms[index].status == 2) {
        clearScreen();
        printf("Phong %s dang BAO TRI, khong the nhan khach!\n", id);
        return;
    }

    // nhap ten khach
    printf("Nhap ten khach hang: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    // nhap so ngay o
    while (1) {
        printf("Nhap so ngay o: ");
        if (scanf("%d", &days) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (days <= 0) {
            printf("So ngay phai > 0!\n");
        } else {
            break;
        }
    }

    if (bookingCount >= MAX_BOOKINGS) {
        clearScreen();
        printf("He thong da day giao dich, khong the check-in them!\n");
        return;
    }

    // tao booking moi
    struct Booking bk;

    sprintf(bk.bookId, "B%03d", bookingCount + 1);  // tao ma dat phong B001, B002...
    strcpy(bk.roomId, id);                          // phong nao
    strcpy(bk.customerName, name);                  // ten khach
    bk.days = days;                                 // so ngay
    bk.totalCost = rooms[index].price * days;       // tinh tien

    bookings[bookingCount++] = bk;                  // luu vao mang booking

    // cap nhat trang thai phong sang "dang o"
    rooms[index].status = 1;

    clearScreen();
    printf("CHECK-IN thanh cong!\n");
    printf("Ma dat phong: %s\n", bk.bookId);
    printf("Phong: %s\n", bk.roomId);
    printf("Khach: %s\n", bk.customerName);
    printf("So ngay: %d\n", bk.days);
    printf("Tong tien: %.2lf\n", bk.totalCost);
    printf("\nNhan Enter de quay lai menu...");
    getchar();
}

// ----------------- F08 - LICH SU THUE THEO PHONG -----------------

void viewBookingHistory() {
    char id[5];
    int found = 0;

    clearScreen();
    printf("=========== LICH SU THUE PHONG ===========\n");

    printf("Nhap so phong can xem lich su: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    clearScreen();
    printf("=== LICH SU THUE CUA PHONG %s ===\n", id);

    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].roomId, id) == 0) {       // cung phong
            printf("Ma dat: %s\n", bookings[i].bookId);
            printf("Khach: %s\n", bookings[i].customerName);
            printf("So ngay: %d\n", bookings[i].days);
            printf("Tong tien: %.2lf\n", bookings[i].totalCost);
            printf("------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Phong %s chua co lich su thue!\n", id);
    }

    printf("\nNhan Enter de quay lai menu...");
    getchar();
}

// ----------------- HAM MAIN -----------------

int main() {
    int choice;

    do {
        displayMenu();                             // in menu
        if (scanf("%d", &choice) != 1) {           // nhap lua chon
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();                             // xoa '\n'

        switch (choice) {
            case 1:
                addRoom();
                break;
            case 2:
                updateRoom();
                break;
            case 3:
                maintenanceRoom();
                break;
            case 4:
                displayRooms();
                break;
            case 5:
                searchEmptyRoomsByType();
                break;
            case 6:
                sortRoomsByPriceDesc();
                break;
            case 7:
                checkIn();
                break;
            case 8:
                viewBookingHistory();
                break;
            case 9:
                clearScreen();
                printf("Thoat chuong trinh thanh cong!\n");
                break;
            default:
                clearScreen();
                printf("Lua chon khong hop le, vui long nhap 1-9!\n");
                break;
        }
    } while (choice != 9);

    return 0;
}

