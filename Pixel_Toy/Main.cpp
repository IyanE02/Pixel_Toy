#include "Useful.h"

int g_click_x, g_click_y;                     // Ŭ�� ���� ��ġ
int g_click_x_temp = -1, g_click_y_temp = -1; // Ŭ�� ���� ��ġ temp��
bool g_sound_option = false;                  // ���� �ɼ�
bool g_kill_thread = false;                   // ������ ����

void logo();                           // ���۽� �ΰ� ���
void beforePixelToy();                 // ������ �Է�
void pixelToy(int size_x, int size_y); // ���� ����

int main()
{
    SetCursorType(NOCURSOR);            // Ŀ�� ����
    SetWindow(100, 50);                 // âũ�� ����
    RemoveScrollbar();                  // ��ũ�ѹ� ����
    SetConsoleTitle(TEXT("Pixel Toy")); // �ܼ��� ������ ����
    srand((unsigned int)time(NULL));    // rand()�Լ��� �õ� ����
    if (g_sound_option == true)
    {
        //PlaySound(TEXT("��θ�"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
    }
    logo();
}

void clickTemp()
{
    g_click_x_temp = g_click_x;
    g_click_y_temp = g_click_y;
}

unsigned _stdcall clickToStart(void* arg)
{
    int temp = 0;
    while (true)
    {
        if (g_kill_thread == true)
        {
            _endthread();
            break;
        }

        Gotoxy_(30, 21);
        if (temp == 0)
        {
            TextColor(kLPurple);
            printf("Click to Start");
            temp++;
        }
        else
        {
            TextColor(kLWhite);
            printf("Click to Start");
            temp--;
        }
        Sleep(500);

        if (g_kill_thread == true)
        {
            _endthread();
            break;
        }
    }
    return 0;
}

void logo()
{
    g_click_x_temp = -1;
    g_click_y_temp = -1;

    int pixel[7][50] = {
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0} };
    for (int iCount = 0; iCount < 7; iCount++)
    {
        for (int jCount = 0; jCount < 50; jCount++)
        {
            Gotoxy_(iCount + 18, jCount + 4);
            if (pixel[iCount][jCount] == 1)
            {
                TextColor(kLPurple);
            }
            else
            {
                TextColor(kBlack);
            }
            printf("��");
        }
    }

    _beginthreadex(NULL, 0, clickToStart, 0, 0, NULL);

    Click(&g_click_x, &g_click_y);
    g_kill_thread = true;
    clickTemp();
    TextColor(kLWhite);
    system("cls");
    pixelToy(50, 50);
}

void pixelToy(int size_x, int size_y)
{
    size_x = 50, size_y = 50;

    g_click_x_temp = -1;
    g_click_y_temp = -1;
    int iCount, jCount;
    system("cls");
    SetWindow(5, 5); // ���� �ذ� ���ؼ� â ũ�� ����
    SetWindow(size_x * 2 + 4, size_y + 5);
    RemoveScrollbar();

    TextColor(kLWhite);

    //Click(&g_click_x, &g_click_y);

    iCount = 0, jCount = 0;
    int iCount_max = size_x + 1;
    int jCount_max = size_y + 1;
    int map[52][52] = { 0 };
    int block = 1, rand_;
    bool pause = false;

    const int kErase = 0;
    const int kWater = 1;
    const int kBlock = 2;
    const int kLava = 3;
    const int kMaxBlock = 4;

    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            if ((i == 0 || i == 51) && (j == 0 || j == 51))
            {
                map[i][j] = kBlock;
            }
        }
    }
    Gotoxy_(iCount_max, 0);
    for (int i = 0; i < 104; i++)
    {
        printf("��");
    }

    Gotoxy_(iCount_max + 1, 1);
    TextColor(kLWhite);
    printf("Water");
    Gotoxy_(iCount_max + 2, 0);
    TextColor(0x0f); //���� kBlack ���� kLWhite
    printf("��");
    TextColor(0x89); //���� kGray ���� kLBlue
    printf("��");
    TextColor(0x0f); //���� kBlack ���� kLWhite
    printf("��");
    TextColor(0x0c); //���� kBlack ���� kLRed
    printf("��");
    Gotoxy_(iCount_max + 2, jCount_max - 4);
    TextColor(0x0f); //���� kBlack ���� kLWhite
    printf("II");
    Gotoxy_(iCount_max + 2, jCount_max - 2);
    TextColor(0x0f); //���� kBlack ���� kLWhite
    printf("����");

    Click__(&g_click_x, &g_click_y);

    while (true)
    {
        for (iCount = iCount_max - 1; iCount >= 0; iCount--)
        {
            rand_ = rand() % 2;
            if (rand_) // �ʱ��
            {
                jCount = jCount_max - 1;
            }
            else
            {
                jCount = 0;
            }

            while (true)
            {
                if ((rand_ && !(jCount >= 0)) || (!rand_ && !(jCount <= jCount_max - 1))) // ���ǽ�
                {
                    break;
                }
                if (BeInput())
                {
                    Click__(&g_click_x, &g_click_y);

                    if (g_click_x != g_click_x_temp || g_click_y != g_click_y_temp) // ���� ������ �ƴϸ�
                    {
                        if (g_click_x < iCount_max && g_click_x > 0 && g_click_y < jCount_max && g_click_y > 0) // �ڽ� ���� Ŭ��
                        {
                            clickTemp();
                            map[g_click_x][g_click_y] = block;
                            Gotoxy_(g_click_x, g_click_y);
                            switch (block)
                            {
                            case kErase: // Erase
                                TextColor(kLWhite);
                                printf("  ");
                                break;
                            case kWater: // Water
                                TextColor(kLBlue);
                                printf("��");
                                break;
                            case kBlock: // Block
                                TextColor(kLWhite);
                                printf("��");
                                break;
                            case kLava: // Lava
                                TextColor(kLRed);
                                printf("��");
                                break;
                            }
                        }
                        else if (g_click_x == iCount_max + 2)
                        {
                            if (g_click_y < kMaxBlock) // �� ����
                            {
                                clickTemp();

                                Gotoxy_(iCount_max + 2, block); // ���� ����
                                switch (block)
                                {
                                case kErase:
                                    TextColor(0x0f);
                                    printf("��");
                                    break;
                                case kWater:
                                    TextColor(0x09);
                                    printf("��");
                                    break;
                                case kBlock:
                                    TextColor(0x0f);
                                    printf("��");
                                    break;
                                case kLava:
                                    TextColor(0x0c);
                                    printf("��");
                                    break;
                                }

                                block = g_click_y;

                                Gotoxy_(iCount_max + 2, block); // ���� ����
                                switch (block)
                                {
                                case kErase:
                                    TextColor(0x8f);
                                    printf("��");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Erase     ");
                                    break;
                                case kWater:
                                    TextColor(0x89);
                                    printf("��");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Water     ");
                                    break;
                                case kBlock:
                                    TextColor(0x8f);
                                    printf("��");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Block     ");
                                    break;
                                case kLava:
                                    TextColor(0x8c);
                                    printf("��");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Lava     ");
                                    break;
                                }
                            }
                            else if (g_click_y >= jCount_max - 2) // ���� ����
                            {
                                clickTemp();
                                return;
                            }
                            else if (g_click_y == jCount_max - 4) // �Ͻ����� ����
                            {
                                clickTemp();

                                if (pause) // ����� ���� ���
                                {
                                    pause = false;
                                    Gotoxy_(iCount_max + 2, jCount_max - 4);
                                    TextColor(kLWhite);
                                    printf("II");
                                }
                                else // ������ ���� ���
                                {
                                    pause = true;
                                    Gotoxy_(iCount_max + 2, jCount_max - 4);
                                    TextColor(kLWhite);
                                    printf("��");
                                }
                            }
                        }
                    }
                }

                if ((map[iCount][jCount] != kErase && map[iCount][jCount] != kBlock) && pause == false) // �� ������ ����
                {
                    if (map[iCount + 1][jCount] == kErase) // ������
                    {
                        switch (map[iCount][jCount])
                        {
                        case kWater: // ���� ���
                            if (iCount < iCount_max - 1) {
                                map[iCount + 1][jCount] = kWater;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kLBlue);
                                printf("��");
                            }
                            map[iCount][jCount] = kErase;
                            Gotoxy_(iCount, jCount);
                            TextColor(kBlack);
                            printf("  ");
                            break;
                        case kLava: // ����� ���
                            if (iCount < iCount_max - 1) {
                                map[iCount + 1][jCount] = kLava;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kLRed);
                                printf("��");
                            }
                            map[iCount][jCount] = kErase;
                            Gotoxy_(iCount, jCount);
                            TextColor(kBlack);
                            printf("  ");
                            break;
                        }
                    }
                    else if ((map[iCount + 1][jCount] == kBlock || map[iCount + 1][jCount] == map[iCount][jCount] || iCount == iCount_max - 1) && (map[iCount][jCount - 1] == kErase || map[iCount][jCount + 1] == kErase)) // ������ �带 ��
                    {
                        /*
                            �ڱ� �� ������ ���̰ų�, �ڱ� �ڽ� (����� ���, ���� ��)�̰ų�, ���� ��� &&
                            �� ���� �ϳ��� �� ���� �� �� ������ �帥��.
                        */
                        const int all = 0, left = 1, right = 2;

                        int blankwhere = all; // all: �Ѵ� ��, left: ���� ��, right: ������ ��
                        if (map[iCount][jCount - 1] == kErase && map[iCount][jCount + 1] == kErase)
                        {
                            blankwhere = all;
                        }
                        else if (map[iCount][jCount - 1] == kErase)
                        {
                            blankwhere = left;
                        }
                        else if (map[iCount][jCount + 1] == kErase)
                        {
                            blankwhere = right;
                        }
                        else
                        {
                            continue;
                        }


                        if ((rand() % 2 && blankwhere != left) || blankwhere == right) // ���������� �̵�
                        {
                            switch (map[iCount][jCount])
                            {
                            case kWater: // ���� ���
                                map[iCount][jCount + 1] = kWater;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kLBlue);
                                printf("��");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            case kLava: // ����� ���
                                map[iCount][jCount + 1] = kLava;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kLRed);
                                printf("��");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            }
                        }
                        else if ((rand() % 2 && blankwhere != right) || blankwhere == left) // �������� �̵�
                        {
                            switch (map[iCount][jCount])
                            {
                            case kWater: // ���� ���
                                map[iCount][jCount - 1] = kWater;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kLBlue);
                                printf("��");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            case kLava: // ����� ���
                                map[iCount][jCount - 1] = kLava;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kLRed);
                                printf("��");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            }
                        }
                    }
                    if (map[iCount][jCount] == kLava || map[iCount == kWater])
                    {
                        int plus = 0;

                        if (map[iCount][jCount] == kLava)
                        {
                            if (map[iCount - 1][jCount] == kWater)
                            {
                                plus++;
                                map[iCount - 1][jCount] = kBlock;
                                Gotoxy_(iCount - 1, jCount);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount + 1][jCount] == kWater)
                            {
                                plus++;
                                map[iCount + 1][jCount] = kBlock;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount][jCount - 1] == kWater)
                            {
                                plus++;
                                map[iCount][jCount - 1] = kBlock;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount][jCount + 1] == kWater)
                            {
                                plus++;
                                map[iCount][jCount + 1] = kBlock;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kGray);
                                printf("��");
                            }
                        }

                        else if(map[iCount][jCount] == kWater)
                        {
                            if (map[iCount - 1][jCount] == kLava)
                            {
                                plus++;
                                map[iCount - 1][jCount] = kBlock;
                                Gotoxy_(iCount - 1, jCount);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount + 1][jCount] == kLava)
                            {
                                plus++;
                                map[iCount + 1][jCount] = kBlock;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount][jCount - 1] == kLava)
                            {
                                plus++;
                                map[iCount][jCount - 1] = kBlock;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kGray);
                                printf("��");
                            }
                            if (map[iCount][jCount + 1] == kLava)
                            {
                                plus++;
                                map[iCount][jCount + 1] = kBlock;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kGray);
                                printf("��");
                            }

                        }

                        if (plus > 0)
                        {
                            map[iCount][jCount] = kBlock;
                            Gotoxy_(iCount, jCount);
                            TextColor(kGray);
                            printf("��");
                        }
                    }
                }
                if (rand_)
                {
                    jCount--;
                }
                else
                {
                    jCount++;
                }
            }
        }
        iCount = iCount_max - 1;
    }
}