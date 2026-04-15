#include <stdio.h>
#include <string.h>

#define SEATS 48
#define NAME_LEN 20

struct seat {
    int id;
    int assigned;
    char first[NAME_LEN];
    char last[NAME_LEN];
};

// function list
void showMainMenu();
void showFlightMenu();
void initSeats(struct seat s[]);
void showEmptyCount(struct seat s[]);
void showEmptyList(struct seat s[]);
void showAlphabetical(struct seat s[]);
void assignSeat(struct seat s[]);
void deleteSeat(struct seat s[]);

// NEW (file functions)
void saveToFile(struct seat s[], char filename[]);
void loadFromFile(struct seat s[], char filename[]);

int main() {
    struct seat outbound[SEATS];
    struct seat inbound[SEATS];

    char choice1, choice2;

    // LOAD DATA (instead of init)
    loadFromFile(outbound, "outbound.dat");
    loadFromFile(inbound, "inbound.dat");

    while (1) {
        showMainMenu();
        printf("Choose: ");
        scanf(" %c", &choice1);

        if (choice1 == 'c') {
            // SAVE BEFORE EXIT
            saveToFile(outbound, "outbound.dat");
            saveToFile(inbound, "inbound.dat");
            printf("Goodbye!\n");
            break;
        }

        struct seat *flight;

        if (choice1 == 'a')
            flight = outbound;
        else if (choice1 == 'b')
            flight = inbound;
        else {
            printf("Invalid option\n");
            continue;
        }

        while (1) {
            showFlightMenu();
            printf("Choose: ");
            scanf(" %c", &choice2);

            if (choice2 == 'f')
                break;

            switch (choice2) {
                case 'a': showEmptyCount(flight); break;
                case 'b': showEmptyList(flight); break;
                case 'c': showAlphabetical(flight); break;
                case 'd': assignSeat(flight); break;
                case 'e': deleteSeat(flight); break;
                default: printf("Invalid option\n");
            }
        }
    }

    return 0;
}

// ---------------- FUNCTIONS ----------------

void showMainMenu() {
    printf("\n====== Colossus Airlines ======\n");
    printf("a) Outbound Flight\n");
    printf("b) Inbound Flight\n");
    printf("c) Quit\n");
}

void showFlightMenu() {
    printf("\n------ Flight Menu ------\n");
    printf("a) Show number of empty seats\n");
    printf("b) Show list of empty seats\n");
    printf("c) Show alphabetical list of seats\n");
    printf("d) Assign a seat\n");
    printf("e) Delete a seat\n");
    printf("f) Return to main menu\n");
}

void initSeats(struct seat s[]) {
    for (int i = 0; i < SEATS; i++) {
        s[i].id = i + 1;
        s[i].assigned = 0;
    }
}

void showEmptyCount(struct seat s[]) {
    int count = 0;
    for (int i = 0; i < SEATS; i++)
        if (s[i].assigned == 0)
            count++;

    printf("Empty seats: %d\n", count);
}

void showEmptyList(struct seat s[]) {
    printf("Empty seats: ");
    for (int i = 0; i < SEATS; i++)
        if (s[i].assigned == 0)
            printf("%d ", s[i].id);

    printf("\n");
}

void showAlphabetical(struct seat s[]) {
    struct seat temp[SEATS];
    int count = 0;

    for (int i = 0; i < SEATS; i++) {
        if (s[i].assigned == 1) {
            temp[count++] = s[i];
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(temp[j].last, temp[j+1].last) > 0) {
                struct seat t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }
        }
    }

    printf("Seats (alphabetical):\n");
    for (int i = 0; i < count; i++) {
        printf("Seat %d: %s %s\n",
            temp[i].id,
            temp[i].first,
            temp[i].last);
    }
}

void assignSeat(struct seat s[]) {
    int num;

    printf("Enter seat number (1-48) or 0 to cancel: ");
    scanf("%d", &num);

    if (num == 0) return;

    if (num < 1 || num > SEATS || s[num-1].assigned == 1) {
        printf("Invalid or seat taken.\n");
        return;
    }

    printf("First name: ");
    scanf("%s", s[num-1].first);

    printf("Last name: ");
    scanf("%s", s[num-1].last);

    s[num-1].assigned = 1;

    printf("Seat assigned!\n");
}

void deleteSeat(struct seat s[]) {
    int num;

    printf("Enter seat number (1-48) or 0 to cancel: ");
    scanf("%d", &num);

    if (num == 0) return;

    if (num < 1 || num > SEATS || s[num-1].assigned == 0) {
        printf("Seat already empty.\n");
        return;
    }

    s[num-1].assigned = 0;
    printf("Seat cleared.\n");
}

// -------- FILE FUNCTIONS --------

void saveToFile(struct seat s[], char filename[]) {
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    fwrite(s, sizeof(struct seat), SEATS, fp);
    fclose(fp);
}

void loadFromFile(struct seat s[], char filename[]) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        initSeats(s);
        return;
    }

    fread(s, sizeof(struct seat), SEATS, fp);
    fclose(fp);
}
