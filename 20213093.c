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
    printf("    /　　　　 |  \n");+
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

void printStatus(int soupCount, int intimacy, int mood, int cp) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("CP: %d 포인트\n", cp);
    printf("쫀떡이 기분(0~3): %d\n", mood);
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
    case 2: printf("식빵을 굽습니다.\n"); break;
    case 3: printf("골골송을 부릅니다.\n"); break;
    default: printf("알 수 없는 기분입니다.\n"); break;
    }

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

void handleMovementAndSoup(int* catPos, int* mood, int intimacy, int* soupCount, int* hasScratcher, int* hasTower) {
    printf("쫀떡이 이동 중...\n");

    int destination = *catPos; 

    if (*mood == 0) {
        printf("기분이 매우 나쁜 쫀떡이는 집으로 향합니다.\n");
        destination = HOME_POS;
    }
    else if (*mood == 1) {
        if (*hasScratcher || *hasTower) {
            printf("쫀떡이는 심심해서 놀이기구 쪽으로 이동합니다.\n");
            
            int distToS = (*hasScratcher) ? abs(*catPos - 3) : 1000;
            int distToT = (*hasTower) ? abs(*catPos - 2) : 1000;
            destination = (distToS <= distToT) ? 3 : 2;
        }
        else {
            printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n");
            if (*mood > 0) (*mood)--;
            return;
        }
    }
    else if (*mood == 2) {
        printf("쫀떡이는 기분 좋게 식빵을 굽고 있습니다.\n");
        return;
    }
    else if (*mood == 3) {
        printf("쫀떡이는 골골송을 부르며 수프를 만들러 갑니다.\n");
        destination = BOWL_POS;
    }


    if (*catPos < destination) (*catPos)++;
    else if (*catPos > destination) (*catPos)--;

    if (*catPos == BOWL_POS) {
        int soupType = rand() % 3;
        printf("쫀떡이가 ");
        switch (soupType) {
        case 0: printf("감자 수프를 "); break;
        case 1: printf("양송이 수프를 "); break;
        case 2: printf("브로콜리 수프를 "); break;
        }
        printf("만들었습니다!\n");
        (*soupCount)++;
    }
    else if (*catPos == HOME_POS) {
        static int lastHomePos = -1;
        if (lastHomePos == *catPos && *mood < 3) {
            (*mood)++;
            printf("쫀떡이는 집에서 쉬면서 기분이 조금 나아졌습니다: %d -> %d\n", *mood - 1, *mood);
        }
        else {
            printf("쫀떡이는 집에서 쉬고 있습니다.\n");
        }
        lastHomePos = *catPos;
    }
    else if (*catPos == 2 && *hasTower) {
        int before = *mood;
        *mood = (*mood + 2 > 3) ? 3 : *mood + 2;
        printf("쫀떡이는 캣타워를 뛰어다닙니다. 기분이 제법 좋아졌습니다: %d -> %d\n", before, *mood);
    }
    else if (*catPos == 3 && *hasScratcher) {
        int before = *mood;
        *mood = (*mood + 1 > 3) ? 3 : *mood + 1;
        printf("쫀떡이는 스크래처를 긁고 놀았습니다. 기분이 조금 좋아졌습니다: %d -> %d\n", before, *mood);
    }
}

void updateMoodRandomly(int intimacy, int* mood) 
{
    int dice = rand() % 6 + 1;
    printf("6-%d: 주사위 눈이 %d이하이면 그냥 기분이 나빠집니다.\n", intimacy, 6 - intimacy);
    printf("주사위를 굴립니다... %d이(가) 나왔습니다.\n", dice);

    if (dice <= (6 - intimacy)) {
        if (*mood > 0) 
        {
            (*mood)--;
            printf("쫀떡이의 기분이 나빠집니다: %d -> %d\n", *mood + 1, *mood);
        }
        else 
        {
            printf("이미 기분이 최악입니다.\n");
        }
    }
    else 
    {
        printf("다행히 기분은 그대로입니다.\n");
    }
}

int main() {
    const char* name = "쫀떡이";
    int intimacy = 2;
    int soupCount = 0;
    int catPos = HOME_POS;

    int mood = 3;  
    int cp = 0;  


    int hasScratcher = 0;
    int hasTower = 0;

    srand((unsigned int)time(NULL));

    printf("**** 야옹이와 수프 ****\n\n");
    drawCat();
    printf("쫀떡이는 식빵을 굽고 있습니다.\n");
    Sleep(2000);
    system("cls");

    while (1) {
        printStatus(soupCount, intimacy, mood, cp);
        updateMoodRandomly(intimacy, &mood);
        drawRoom(catPos);

        int choice = getPlayerChoice();
        intimacy = updateIntimacy(choice, intimacy);

        handleMovementAndSoup(&catPos, &mood, intimacy, &soupCount, &hasScratcher, &hasTower);


        Sleep(2500);
        system("cls");
    }
    return 0;
}