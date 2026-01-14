#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 100
#define MAX_BOOKINGS 500

struct Room {
    char roomId[5];
    int type;
    double price;
    int status;
};

struct Booking {
    char bookId[20];
    char roomId[5];
    char customerName[50];
    int days;
    double totalCost;
};

struct Room rooms[MAX_ROOMS];
int roomCount = 0;

struct Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

void clearScreen() {
    system("cls");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int isAllSpaces(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

void printCenter(const char *text, int width) {
    int len = strlen(text);
    if (len >= width) {
        printf("%s", text);
        return;
    }

    int left = (width - len) / 2;
    int right = width - len - left;

    for (int i = 0; i < left; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < right; i++) printf(" ");
}

void printRoomTitle() {
    printCenter("SO PHONG", 12);   printf("|");
    printCenter("LOAI", 8);        printf("|");
    printCenter("GIA PHONG", 15);  printf("|");
    printCenter("TRANG THAI", 15); printf("\n");
    printf("--------------------------------------------------------------\n");
}

void printBookingTitle() {
    printCenter("MA DAT", 10);       printf("|");
    printCenter("TEN KHACH", 25);    printf("|");
    printCenter("SO NGAY", 10);      printf("|");
    printCenter("TONG TIEN", 15);    printf("\n");
    printf("---------------------------------------------------------------------\n");
}

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
    printf("=======================================================================\n");
    printf("NHAP LUA CHON (1-9): ");
}
void initSampleData() {
    strcpy(rooms[0].roomId, "101"); rooms[0].type = 1; rooms[0].price = 300000; rooms[0].status = 0;
    strcpy(rooms[1].roomId, "102"); rooms[1].type = 2; rooms[1].price = 500000; rooms[1].status = 1;
    strcpy(rooms[2].roomId, "201"); rooms[2].type = 1; rooms[2].price = 350000; rooms[2].status = 2;
    strcpy(rooms[3].roomId, "202"); rooms[3].type = 2; rooms[3].price = 550000; rooms[3].status = 0;
    strcpy(rooms[4].roomId, "301"); rooms[4].type = 1; rooms[4].price = 300000; rooms[4].status = 0;
    roomCount = 5;
}

// ====================== F01 - THEM PHONG MOI ======================

void addRoom() {
    struct Room newRoom;

    clearScreen();
    printf("=========== THEM PHONG MOI ===========\n");

    while (1) {
        printf("Nhap so phong (3-4 ky tu): ");
        if (fgets(newRoom.roomId, sizeof(newRoom.roomId), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }
        newRoom.roomId[strcspn(newRoom.roomId, "\n")] = '\0';

        int len = strlen(newRoom.roomId);

        if (len == 0 || isAllSpaces(newRoom.roomId)) {
            clearScreen();
            printf("So phong khong duoc de trong hoac chi la khoang trang!\n");
            continue;
        }

        if (len < 3 || len > 4) {
            clearScreen();
            printf("So phong phai tu 3 den 4 ky tu!\n");
            continue;
        }

        int duplicate = 0;
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
            break;
        }
    }

    while (1) {
        printf("Nhap loai phong (1 Don, 2 Doi): ");
        if (scanf("%d", &newRoom.type) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        if (newRoom.type != 1 && newRoom.type != 2) {
            printf("Loai phong chi duoc nhap 1 hoac 2!\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("Nhap gia phong (>0): ");
        if (scanf("%lf", &newRoom.price) != 1) {
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

    newRoom.status = 0;

    rooms[roomCount++] = newRoom;

    clearScreen();
    printf("Them phong thanh cong!\n");
}

// ====================== F02 - CAP NHAT PHONG ======================

void updateRoom() {
    char id[5];
    int index;

    while (1) {
        clearScreen();
        printf("=========== CAP NHAT PHONG ===========\n");

        printf("Nhap so phong can cap nhat: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (id[0] == '\0' || isAllSpaces(id)) {
            clearScreen();
            printf("So phong khong duoc de trong hoac chi la khoang trang!\n");
            printf("Nhan Enter de nhap lai so phong!!!\n");
            getchar();
            clearBuffer();
            continue;
        }

        index = -1;
        for (int i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, id) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            clearScreen();
            printf("Khong tim thay so phong %s!\n", id);
            printf("Nhan Enter de nhap lai so phong!!!\n");
            getchar();
            clearBuffer();
        } else {
            break;
        }
    }

    int newType;
    double newPrice;

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

    rooms[index].type  = newType;
    rooms[index].price = newPrice;

    clearScreen();
    printf("Cap nhat phong %s thanh cong!\n", id);
}

// ====================== F03 - BAO TRI PHONG (KHOA) ======================

int maintenanceRoom() {
    char id[5];

    clearScreen();
    printf("=========== BAO TRI PHONG (KHOA) ===========\n");

    while (1) {
        printf("Nhap so phong can bao tri: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (id[0] == '\0' || isAllSpaces(id)) {
            clearScreen();
            printf("So phong khong duoc de trong hoac chi la khoang trang!\n");
            continue;
        }
        break;
    }

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
        return 0;
    }

    if (rooms[index].status == 1) {
        clearScreen();
        printf("Phong %s dang co khach, khong the dua vao bao tri!\n", id);
        return 0;
    }

    rooms[index].status = 2;

    clearScreen();
    printf("Phong %s da duoc dua vao trang thai BAO TRI!\n", id);
    return 1;
}

// ====================== F04 - HIEN THI DANH SACH PHONG ======================

void displayRooms() {
    int perPage = 5;
    int page = 0;
    int totalPage;

    if (roomCount == 0) {
        clearScreen();
        printf("Danh sach phong dang rong!\n");
        return;
    }

    totalPage = (roomCount + perPage - 1) / perPage;

    while (1) {
        clearScreen();
        printf("=========== DANH SACH PHONG (Trang %d/%d) ===========\n",
               page + 1, totalPage);
        printRoomTitle();

        int start = page * perPage;
        int end = start + perPage;
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
        printf("\nMoi ban lua chon: ");

        char buf[10];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        char c = buf[0];

        if (c == 'n' || c == 'N') {
            if (page < totalPage - 1) page++;
        } else if (c == 'p' || c == 'P') {
            if (page > 0) page--;
        } else if (c == 'q' || c == 'Q') {
            break;
        }
    }
}

// ====================== F05 - TIM PHONG TRONG THEO LOAI ======================

void searchEmptyRoomsByType() {
    int type;

    clearScreen();
    printf("=========== TIM PHONG TRONG THEO LOAI ===========\n");

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

    int found = 0;

    clearScreen();
    printf("======== DANH SACH PHONG TRONG LOAI %s ========\n",
           (type == 1) ? "DON" : "DOI");
    printRoomTitle();

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].type == type && rooms[i].status == 0) {
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

// ====================== F06 - SAP XEP PHONG THEO GIA GIAM DAN ======================

void sortRoomsByPriceDesc() {
    if (roomCount <= 1) {
        clearScreen();
        printf("So luong phong qua it, khong can sap xep!\n");
        return;
    }

    for (int i = 0; i < roomCount - 1; i++) {
        for (int j = i + 1; j < roomCount; j++) {
            if (rooms[i].price < rooms[j].price) {
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

    displayRooms();
}

// ====================== F07 - CHECK-IN (NHAN PHONG) ======================

void checkIn() {
    char id[5];
    char name[50];
    int days;

    clearScreen();
    printf("=========== CHECK-IN (NHAN PHONG) ===========\n");

    int index;
    while (1) {
        printf("Nhap so phong muon nhan: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (id[0] == '\0' || isAllSpaces(id)) {
            printf("So phong khong duoc de trong hoac chi la khoang trang! Moi nhap lai.\n");
            continue;
        }

        index = -1;
        for (int i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, id) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("Khong tim thay so phong %s! Moi nhap lai.\n", id);
            continue;
        }

        break;
    }

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

    while (1) {
        printf("Nhap ten khach hang: ");
        if (fgets(name, sizeof(name), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }

        name[strcspn(name, "\n")] = '\0';

        if (name[0] == '\0') {
            printf("Ten khong duoc de trong! Moi nhap lai.\n");
            continue;
        }

        if (isAllSpaces(name)) {
            printf("Ten khong duoc chi la khoang trang! Moi nhap lai.\n");
            continue;
        }

        break;
    }

    char buf[20];
    while (1) {
        printf("Nhap so ngay o: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }

        if (buf[0] == '\n') {
            printf("Khong duoc de trong! Moi nhap lai.\n");
            continue;
        }

        if (sscanf(buf, "%d", &days) != 1) {
            printf("Nhap sai kieu du lieu! Moi nhap lai.\n");
            continue;
        }

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

    struct Booking bk;

    sprintf(bk.bookId, "B%03d", bookingCount + 1);
    strcpy(bk.roomId, id);
    strcpy(bk.customerName, name);
    bk.days = days;
    bk.totalCost = rooms[index].price * days;

    bookings[bookingCount++] = bk;

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

// ====================== F08 - LICH SU THUE THEO PHONG ======================

void viewBookingHistory() {
    char id[5];
    int found = 0;

    clearScreen();
    printf("=========== LICH SU THUE PHONG ===========\n");

    while (1) {
        printf("Nhap so phong can xem lich su: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap! Moi nhap lai.\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (id[0] == '\0' || isAllSpaces(id)) {
            printf("So phong khong duoc de trong hoac chi la khoang trang! Moi nhap lai.\n");
            continue;
        }
        break;
    }

    clearScreen();
    printf("=== LICH SU THUE CUA PHONG %s ===\n\n", id);

    printBookingTitle();

    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].roomId, id) == 0) {
            char daysStr[10], costStr[20];

            sprintf(daysStr, "%d", bookings[i].days);
            sprintf(costStr, "%.2lf", bookings[i].totalCost);

            printCenter(bookings[i].bookId, 10);       printf("|");
            printCenter(bookings[i].customerName, 25); printf("|");
            printCenter(daysStr, 10);                  printf("|");
            printCenter(costStr, 15);                  printf("\n");

            found = 1;
        }
    }

    if (!found) {
        printf("Phong %s chua co lich su thue!\n", id);
    }

    printf("\nNhan Enter de quay lai menu...");
    getchar();
}

// ====================== F09 - THOAT CHUONG TRINH (MAIN MENU) ======================

int main() {
    int choice;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("Nhap sai kieu du lieu!\n");
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:     // F01 - Them phong moi
                addRoom();
                break;
            case 2:     // F02 - Cap nhat phong
                updateRoom();
                break;
            case 3:     // F03 - Bao tri phong
                maintenanceRoom();
                break;
            case 4:     // F04 - Hien thi danh sach
                displayRooms();
                break;
            case 5:     // F05 - Tim phong trong theo loai
                searchEmptyRoomsByType();
                break;
            case 6:     // F06 - Sap xep phong theo gia giam dan
                sortRoomsByPriceDesc();
                break;
            case 7:     // F07 - Check-in
                checkIn();
                break;
            case 8:     // F08 - Lich su thue
                viewBookingHistory();
                break;
            case 9:     // F09 - Thoat
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

