#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

void drawCat() {
    printf("       ／＞　 フ\n");
    printf("       | 　_　_| \n");
    printf("     ／` ミ＿xノ \n");
    printf("    /　　　　 |  \n");
    printf("   /　 ?　　 ?  \n");
    printf("   │　　|　|　|   \n");
    printf("／￣|　　 |　|　| \n");
    printf("| (￣?＿_?_)__) \n");
    printf("＼二つ\n");
}

void drawRoom(int catPos) {
    printf("##########\n");
    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i == 0) printf("#");
        else if (i == HOME_POS) printf("H");
        else if (i == BOWL_POS) printf("B");
        else printf(" ");
    }
    printf("#\n");
    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i == 0) printf("#");
        else if (i == catPos) printf("C");
        else printf(" ");
    }
    printf("#\n##########\n");
}

void printStatus(int soupCount, int intimacy) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("집사와의 관계(0~4): %d\n", intimacy);
    switch (intimacy) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사 껌딱지입니다.\n"); break;
    default: printf("알 수 없는 상태입니다.\n");
    }
    printf("==================================================\n\n");
}

int getPlayerChoice() {
    int choice = -1;
    printf("어떤 상호작용을 하시겠습니까?\n");
    printf("0. 아무것도 하지 않음 \n");
    printf("1. 긁어 주기 \n>> ");
    while (1) {
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > 1) {
            printf("다시 입력하세요 (0 또는 1): ");
            while (getchar() != '\n');
        }
        else break;
    }
    return choice;
}

int updateIntimacy(int choice, int intimacy) {
    int dice = rand() % 6 + 1;
    if (choice == 0) {
        printf("아무것도 하지 않습니다.\n");
        printf("4/6의 확률로 친밀도가 떨어집니다.\n");
        printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);
        if (dice <= 4 && intimacy > 0) {
            intimacy--;
            printf("친밀도가 떨어집니다. 현재 친밀도: %d\n", intimacy);
        }
        else {
            printf("다행히 친밀도는 그대로입니다. 현재 친밀도: %d\n", intimacy);
        }
    }
    else {
        printf("야옹이의 턱을 긁어주었습니다.\n");
        printf("2/6의 확률로 친밀도가 올라갑니다.\n");
        printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);
        if (dice >= 5 && intimacy < 4) {
            intimacy++;
            printf("친밀도가 올라갑니다. 현재 친밀도: %d\n", intimacy);
        }
        else {
            printf("친밀도는 그대로입니다. 현재 친밀도: %d\n", intimacy);
        }
    }
    return intimacy;
}

void handleMovementAndSoup(int* catPos, int intimacy, int* soupCount) {
    int dice = rand() % 6 + 1;
    int moveToBowl = (dice >= (6 - intimacy)) ? 1 : 0;

    printf("쫀떡이 이동 중...\n");
    printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);

    if (moveToBowl && *catPos < BOWL_POS) {
        (*catPos)++;
        printf("냄비 쪽으로 이동합니다.\n");
    }
    else if (!moveToBowl && *catPos > HOME_POS) {
        (*catPos)--;
        printf("집 쪽으로 이동합니다.\n");
    }
    else {
        printf("더 이상 이동할 수 없습니다.\n");
    }

    if (*catPos == BOWL_POS) {
        int soupType = rand() % 3;
        printf("쫀떡이(가) ");
        switch (soupType) {
        case 0: printf("감자 수프를 만들었습니다!\n"); break;
        case 1: printf("양송이 수프를 만들었습니다!\n"); break;
        case 2: printf("브로콜리 수프를 만들었습니다!\n"); break;
        }
        (*soupCount)++;
    }
    else if (*catPos == HOME_POS) {
        printf("쫀떡이는 집에서 쉬고 있습니다.\n");
    }
}

int main() {
    const char* name = "쫀떡이";
    int intimacy = 2;
    int soupCount = 0;
    int catPos = HOME_POS;
    srand((unsigned int)time(NULL));

    printf("**** 야옹이와 수프 ****\n\n");
    drawCat();
    printf("쫀떡이는 식빵을 굽고 있습니다.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        printStatus(soupCount, intimacy);
        drawRoom(catPos);

        int choice = getPlayerChoice();
        intimacy = updateIntimacy(choice, intimacy);

        handleMovementAndSoup(&catPos, intimacy, &soupCount);

        Sleep(2500);
        system("cls");
    }
    return 0;
}