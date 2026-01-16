#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Dinh nghia so luong
#define MAX_ROOMS 100
#define MAX_BOOKINGS 500

// --- 1. CAU TRUC DU LIEU ---

struct Room {
    char roomId[10];   
    int type;          
    double price;      
    int status;        // 0: Trong, 1: Dang o, 2: Bao tri
};

struct Booking {
    char bookId[20];       
    char roomId[10];       
    char customerName[50]; 
    int days;              
    double totalCost;      // Tong tien
    char checkInDate[20];  
};

// --- 2. BIEN TOAN CUC ---
struct Room rooms[MAX_ROOMS];
int roomCount = 0; 

struct Booking bookings[MAX_BOOKINGS];
int bookingCount = 0; 

// --- 3. HAM HO TRO ---

// Xoa man hinh
void clearScreen() {
    system("cls");
}

// Xoa bo dem (khi nhap so xong ma nhap chu thi can cai nay)
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Xoa dau xuong dong khi dung fgets
void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

// Ham in canh giua cho dep
void printCenter(const char *text, int width) {
    int len = strlen(text);
    int left, right, i;
    
    if (len >= width) {
        printf("%s", text);
        return;
    }
    
    left = (width - len) / 2;
    right = width - len - left;
    
    for (i = 0; i < left; i++) printf(" ");
    printf("%s", text);
    for (i = 0; i < right; i++) printf(" ");
}

void printRoomTitle() {
    printf("--------------------------------------------------------------\n");
    printCenter("SO PHONG", 12);   printf("|");
    printCenter("LOAI", 8);        printf("|");
    printCenter("GIA PHONG", 15);  printf("|");
    printCenter("TRANG THAI", 15); printf("\n");
    printf("--------------------------------------------------------------\n");
}

void printBookingTitle() {
    printf("-------------------------------------------------------------------------------------\n");
    printCenter("MA DAT", 10);       printf("|");
    printCenter("TEN KHACH", 25);    printf("|");
    printCenter("SO NGAY", 10);      printf("|");
    printCenter("TONG TIEN", 15);    printf("|");
    printCenter("NGAY", 15);         printf("\n");
    printf("-------------------------------------------------------------------------------------\n");
}

// --- DU LIEU MAU ---
void initSampleData() {
    // Phong 1
    strcpy(rooms[0].roomId, "101"); rooms[0].type = 1; rooms[0].price = 500000; rooms[0].status = 0;
    // Phong 2
    strcpy(rooms[1].roomId, "102"); rooms[1].type = 2; rooms[1].price = 800000; rooms[1].status = 1;
    // Phong 3
    strcpy(rooms[2].roomId, "201"); rooms[2].type = 1; rooms[2].price = 600000; rooms[2].status = 2;
    // Phong 4
    strcpy(rooms[3].roomId, "202"); rooms[3].type = 2; rooms[3].price = 900000; rooms[3].status = 0;
    // Phong 5
    strcpy(rooms[4].roomId, "301"); rooms[4].type = 1; rooms[4].price = 550000; rooms[4].status = 0;
    
    roomCount = 5;

    // Booking mau
    strcpy(bookings[0].bookId, "BK001");
    strcpy(bookings[0].roomId, "102");
    strcpy(bookings[0].customerName, "Nguyen Van A");
    bookings[0].days = 3;
    bookings[0].totalCost = 2400000; 
    strcpy(bookings[0].checkInDate, "01/01/2024");
    bookingCount = 1;
}

void displayMenu() {
    clearScreen(); 
    printf("\n========================= MENU QUAN LY PHONG ==========================\n");
    printf("||                F01  THEM PHONG MOI                                ||\n");
    printf("||                F02  CAP NHAT PHONG                                ||\n");
    printf("||                F03  BAO TRI PHONG (KHOA)                          ||\n");
    printf("||                F04  HIEN THI DANH SACH                            ||\n");
    printf("||                F05  TIM KIEM PHONG TRONG THEO LOAI                ||\n");
    printf("||                F06  SAP XEP DANH SACH PHONG (GIA GIAM DAN)        ||\n");
    printf("||                F07  CHECK-IN (GIAO DICH NHAN PHONG)               ||\n");
    printf("||                F08  LICH SU THUE                                  ||\n");
    printf("||                F09  THOAT                                         ||\n");
    printf("=======================================================================\n");
    printf("NHAP LUA CHON (1-9): ");
}

// --- 4. CAC CHUC NANG CHINH ---

// F01 - Them phong
void addRoom() {
    struct Room newRoom;
    char temp[100];
    int duplicate = 0;
    int i;
    
    clearScreen();
    printf("=========== THEM PHONG MOI ===========\n");

    if (roomCount >= MAX_ROOMS) {
        printf("Loi: Danh sach day roi!\n");
        printf("Nhan Enter de quay lai..."); getchar(); return; 
    }

    // Nhap Ma Phong
    while (1) {
        printf("Nhap so phong (3-4 ky tu) hoac 'q' de thoat: "); 
        fgets(temp, sizeof(temp), stdin); 
        trimNewline(temp);

        if (strcmp(temp, "q") == 0) return; // Thoat neu nhap q

        int len = strlen(temp);
        if (len < 3 || len > 4) {
            printf("Loi: So phong phai tu 3 den 4 ky tu!\n"); continue;
        }

        // Kiem tra trung ma
        duplicate = 0;
        for (i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, temp) == 0) {
                duplicate = 1; break;
            }
        }
        if (duplicate == 1) {
            printf("Loi: So phong nay da co roi!\n");
        } else {
            strcpy(newRoom.roomId, temp);
            break; // Nhap dung thi thoat vong lap
        }
    }

    // Nhap Loai
    while (1) {
        printf("Nhap loai phong (1 Don, 2 Doi): ");
        fgets(temp, sizeof(temp), stdin);
        // Thu lay so tu chuoi nhap vao
        if (sscanf(temp, "%d", &newRoom.type) == 1) {
            if (newRoom.type == 1 || newRoom.type == 2) break;
        }
        printf("Loi: Chi duoc nhap 1 hoac 2!\n");
    }

    // Nhap Gia
    while (1) {
        printf("Nhap gia phong (>0): ");
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%lf", &newRoom.price) == 1) {
            if (newRoom.price > 0) break;
        }
        printf("Loi: Gia phong phai lon hon 0!\n");
    }

    newRoom.status = 0; // Mac dinh la TRONG
    rooms[roomCount] = newRoom; 
    roomCount++; 

    printf("--> Them phong thanh cong!\n");
    printf("Nhan Enter de quay lai..."); getchar();
}

// F02 - Cap nhat
void updateRoom() {
    char id[10], temp[100];
    int index = -1;
    int i;
    int newType;
    double newPrice;

    clearScreen();
    printf("=========== CAP NHAT PHONG ===========\n");

    // Tim phong
    while (1) {
        printf("Nhap so phong can cap nhat (hoac 'q' de thoat): ");
        fgets(id, sizeof(id), stdin); 
        trimNewline(id);

        if (strcmp(id, "q") == 0) return;

        for (i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, id) == 0) {
                index = i; break;
            }
        }

        if (index == -1) {
            printf("Loi: Khong tim thay phong!\n");
        } else {
            break; 
        }
    }

    printf("-- DA TIM THAY PHONG %s --\n", id);
    
    // Nhap lai Loai
    while (1) {
        printf("Nhap loai phong moi (1 Don, 2 Doi): ");
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%d", &newType) == 1) {
            if (newType == 1 || newType == 2) break;
        }
        printf("Loi: Nhap sai!\n");
    }
    rooms[index].type = newType;

    // Nhap lai Gia
    while (1) {
        printf("Nhap gia phong moi (>0): ");
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%lf", &newPrice) == 1) {
            if (newPrice > 0) break;
        }
        printf("Loi: Nhap sai!\n");
    }
    rooms[index].price = newPrice;
    
    printf("--> Cap nhat thanh cong!\n");
    printf("Nhan Enter de quay lai..."); getchar();
}

// F03 - Bao tri
int maintenanceRoom() {
    char id[10];
    int index, i;
    
    clearScreen();
    printf("=========== BAO TRI PHONG ===========\n");
    
    while (1) {
        printf("Nhap so phong bao tri (hoac 'q' de thoat): ");
        fgets(id, sizeof(id), stdin); 
        trimNewline(id);

        if (strcmp(id, "q") == 0) return 0;

        index = -1;
        for (i = 0; i < roomCount; i++) {
            if (strcmp(rooms[i].roomId, id) == 0) {
                index = i; break;
            }
        }

        if (index == -1) {
            printf("Loi: Khong tim thay phong!\n");
        } else {
            // Phong dang co khach thi khong duoc bao tri
            if (rooms[index].status == 1) {
                printf("Loi: Phong dang co khach, khong the bao tri!\n");
            } else {
                rooms[index].status = 2; // Chuyen sang bao tri
                printf("--> Phong %s da chuyen sang BAO TRI!\n", id);
                printf("Nhan Enter de quay lai..."); getchar();
                return 1;
            }
        }
    }
    return 0;
}

// F04 - Hien thi
void displayRooms() {
    int perPage = 5; 
    int page = 0;
    int totalPage;
    int start, end, i;
    char typeStr[10], statusStr[20];
    char buf[10];

    if (roomCount == 0) {
        clearScreen();
        printf("Danh sach dang rong!\n"); 
        printf("Nhan Enter de quay lai..."); getchar();
        return;
    }

    // Tinh tong so trang
    totalPage = (roomCount + perPage - 1) / perPage;

    while (1) {
        clearScreen();
        printf("=========== DANH SACH PHONG (Trang %d/%d) ===========\n", page + 1, totalPage);
        printRoomTitle();

        start = page * perPage;
        end = start + perPage;
        if (end > roomCount) end = roomCount;

        for (i = start; i < end; i++) {
            strcpy(typeStr, (rooms[i].type == 1) ? "DON" : "DOI");
            
            if (rooms[i].status == 0) strcpy(statusStr, "TRONG");
            else if (rooms[i].status == 1) strcpy(statusStr, "DANG O");
            else strcpy(statusStr, "BAO TRI");

            printCenter(rooms[i].roomId, 12); printf("|");
            printCenter(typeStr, 8);          printf("|");
            printf("%14.0lf |", rooms[i].price); 
            printCenter(statusStr, 15);       printf("\n");
        }
        printf("--------------------------------------------------------------\n");

        printf("\n[n] Trang tiep | [p] Trang truoc | [q] Thoat: ");
        fgets(buf, sizeof(buf), stdin);
        trimNewline(buf); 
        
        if (buf[0] == 'n' && page < totalPage - 1) page++;
        else if (buf[0] == 'p' && page > 0) page--;
        else if (buf[0] == 'q') {
            break; 
        }
    }
}

// F05 - Tim kiem
void searchEmptyRoomsByType() {
    int type;
    char temp[100];
    int found, i;
    char typeStr[10];

    clearScreen();
    printf("=========== TIM PHONG TRONG THEO LOAI ===========\n");
    
    while (1) {
        printf("Nhap loai (1 Don, 2 Doi): ");
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%d", &type) == 1) {
            if (type == 1 || type == 2) break;
        }
        printf("Loi: Nhap sai!\n");
    }

    printf("\nKET QUA TIM KIEM:\n");
    printRoomTitle();
    found = 0;
    for (i = 0; i < roomCount; i++) {
        // Chi tim phong TRONG va dung loai
        if (rooms[i].type == type && rooms[i].status == 0) {
            strcpy(typeStr, (rooms[i].type == 1) ? "DON" : "DOI");
            
            printCenter(rooms[i].roomId, 12); printf("|");
            printCenter(typeStr, 8);          printf("|");
            printf("%14.0lf |", rooms[i].price);
            printCenter("TRONG", 15);         printf("\n");
            found = 1;
        }
    }
    if (found == 0) printf("--> Khong co phong trong nao phu hop!\n");
    
    printf("\nNhan Enter de quay lai..."); getchar();
}

// F06 - Sap xep
void sortRoomsByPriceDesc() {
    int i, j;
    struct Room temp;

    // Thuat toan sap xep noi bot (Bubble Sort)
    for (i = 0; i < roomCount - 1; i++) {
        for (j = i + 1; j < roomCount; j++) {
            if (rooms[i].price < rooms[j].price) { 
                temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }
    printf("--> Da sap xep xong! Vao F04 de xem ket qua.\n");
    printf("Nhan Enter de quay lai..."); getchar();
}

// F07 - Check-in
void checkIn() {
    struct Booking b;
    char id[10], name[50];
    int days, index = -1;
    char temp[100];
    int i;

    clearScreen();
    printf("=========== CHECK-IN ===========\n");

    if (bookingCount >= MAX_BOOKINGS) {
        printf("Loi: Bo nho Booking day!\n");
        printf("Nhan Enter de quay lai..."); getchar(); return;
    }

    printf("Nhap so phong (hoac 'q' de thoat): ");
    fgets(id, sizeof(id), stdin); 
    trimNewline(id);
    
    if (strcmp(id, "q") == 0) return;

    for (i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].roomId, id) == 0) {
            index = i; break;
        }
    }
    
    if (index == -1) { 
        printf("Loi: Khong tim thay phong!\n"); 
        printf("Nhan Enter de quay lai..."); getchar();
        return; 
    }
    if (rooms[index].status != 0) { 
        printf("Loi: Phong khong TRONG!\n"); 
        printf("Nhan Enter de quay lai..."); getchar();
        return; 
    }

    printf("Ten khach hang: ");
    fgets(name, sizeof(name), stdin); 
    trimNewline(name);

    while (1) {
        printf("So ngay o: ");
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%d", &days) == 1) {
            if (days > 0) break;
        }
        printf("Loi: So ngay phai > 0!\n");
    }

    // Nhap ngay checkin don gian 
    printf("Ngay Check-in (DD/MM/YYYY): ");
    fgets(b.checkInDate, sizeof(b.checkInDate), stdin);
    trimNewline(b.checkInDate);

    // Tao ma booking tu dong
    sprintf(b.bookId, "BK%03d", bookingCount + 1); 
    strcpy(b.roomId, id);
    strcpy(b.customerName, name);
    b.days = days;
    b.totalCost = rooms[index].price * days; 

    bookings[bookingCount] = b; 
    bookingCount++;
    rooms[index].status = 1; // Cap nhat trang thai phong      

    printf("\n--> Check-in THANH CONG!\n");
    printf("Ma Book: %s | Tong tien: %.0f\n", b.bookId, b.totalCost);
    printf("Nhan Enter de quay lai..."); getchar();
}

// F08 - Lich su thue
void viewBookingHistory() {
    char id[10];
    int found, i;
    char daysStr[10], costStr[20];

    clearScreen();
    printf("=========== LICH SU THUE PHONG ===========\n");
    
    printf("Nhap so phong: ");
    fgets(id, sizeof(id), stdin); 
    trimNewline(id);

    printf("\nLICH SU DAT PHONG CUA %s:\n", id);
    printBookingTitle();
    
    found = 0;
    for (i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].roomId, id) == 0) {
            sprintf(daysStr, "%d", bookings[i].days);
            sprintf(costStr, "%.0f", bookings[i].totalCost);
            
            printCenter(bookings[i].bookId, 10);    printf("|");
            printCenter(bookings[i].customerName, 25); printf("|");
            printCenter(daysStr, 10);               printf("|");
            printCenter(costStr, 15);               printf("|");
            printCenter(bookings[i].checkInDate, 15); printf("\n");
            found = 1;
        }
    }
    
    if (found == 0) printf("--> Phong nay chua tung co khach thue!\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("Nhan Enter de quay lai..."); getchar();
}

// ====================== MAIN ======================
int main() {
    int choice;
    char temp[100]; 

    initSampleData();

    do {
        displayMenu();
        
        // Nhap lua chon an toan
        fgets(temp, sizeof(temp), stdin);
        if (sscanf(temp, "%d", &choice) != 1) {
            choice = 0; 
        }

        switch (choice) {
            case 1: // F01 - Them phong moi
                addRoom();
                break;
            case 2: // F02 - Cap nhat phong
                updateRoom();
                break;
            case 3: // F03 - Bao tri phong
                maintenanceRoom();
                break;
            case 4: // F04 - Hien thi danh sach
                displayRooms();
                break;
            case 5: // F05 - Tim phong trong theo loai
                searchEmptyRoomsByType();
                break;
            case 6: // F06 - Sap xep phong theo gia giam dan
                sortRoomsByPriceDesc();
                break;
            case 7: // F07 - Check-in
                checkIn();
                break;
            case 8: // F08 - Lich su thue
                viewBookingHistory();
                break;
            case 9: // F09 - Thoat
                clearScreen();
                printf("Thoat chuong trinh! Hen gap lai.\n");
                return 0; // Thoat luon
            default:
                printf("Lua chon khong hop le!\n");
                printf("Nhan Enter de thu lai..."); getchar();
                break;
        }
    } while (choice != 9);

    return 0;
}
