#include"GameStat.h"
#include<stdio.h>
#include<windows.h>
#include <sys/types.h>
#include<winsock.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#pragma comment(lib,"ws2_32.lib")
//规定贪吃蛇开始时向右
int main()
{
    while (1)
    {
        GameStartPage();
    }
    return 0;
}
void InitGameInformation()
{
    LinkToInternet(0);
    score = 0;
    length = 2;
    memcpy(GameBackGround, GameBackGround2, sizeof(GameBackGround2));
    //strcpy(GameBackGround,GameBackGround2);
}//
void SrandFood()
{
    srand((unsigned)time(NULL));
        xFood = rand() % 20 + 2;
        yFood = rand() % 50 + 2;
    GameBackGround[xFood][yFood] = -1;
}
void SrandPlayer()
{
    srand((unsigned)time(NULL));
    xPlayerHead = rand() % 20 + 2;
    yPlayerHead = rand() % 50 + 4;
    while (/*xPlayerHead == xFood && yPlayerHead == yFood&&*/ (fabs(xPlayerHead - xFood) < 3) || (fabs(yPlayerHead - yFood) < 3))
    {
        xPlayerHead = rand() % 20 + 2;
        yPlayerHead = rand() % 50 + 4;
    }
    GameBackGround[xPlayerHead][yPlayerHead] = -2;
    PlayerXIndex[0] = PlayerXIndex[1] = xPlayerHead;
    GameBackGround[xPlayerHead][yPlayerHead - 1] = -2;
    PlayerYIndex[0] = yPlayerHead;
    PlayerYIndex[1] = yPlayerHead - 1;
}
void GamePlayIntroduction()
{
    system("cls");
    SetPos(20, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    SetPos(20, 4);
    printf("┃                                                        ┃");
    SetPos(20, 5);
    printf("┃       W:    指引玩家向上前进                           ┃");
    SetPos(20, 6);
    printf("┃       A:    指引玩家向左前进                           ┃");
    SetPos(20, 7);
    printf("┃       S:    指引玩家向下前进                           ┃");
    SetPos(20, 8);
    printf("┃       D:    指引玩家向右前进                           ┃");
    SetPos(20, 9);
    printf("┃       #:   玩家要得到的树莓                            ┃");
    SetPos(20, 10);
    printf("┃       *:   玩家操纵蛇的身体                            ┃");
    SetPos(20, 11);
    printf("┃                                                        ┃");
    SetPos(20, 12);
    printf("┃          按任意键开始游戏！！！                        ┃");
    SetPos(20, 13);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    getchar();
}
void InitGame()
{
    //开始游戏
    system("cls");
    /*    for (int i = 0; i < MAX_BACKGROUND_LINE;i++)
        {
            SetPos(20,3+ i);
            printf("%s\n", GameBackGround[i]);
        }*/
    for (int i = 0; i < MAX_BACKGROUND_LINE;i++)
    {
        SetPos(20, 3 + i);
        for (int j = 0; j < 58;j++)
        {
            if (GameBackGround[i][j] == -1)
            {
                printf("#");
            }
            else if (GameBackGround[i][j] == -2)
            {
                printf("*");
            }
            else if (GameBackGround[i][j] == 0)
            {
                printf(" ");
            }
            else if (GameBackGround[i][j] == 1)
            {
                printf("━");
            }
            else if (GameBackGround[i][j] == 2)
            {
                printf("┃");
            }
            else if (GameBackGround[i][j] == 3)
            {
                printf("┏");
            }
            else if (GameBackGround[i][j] == 4)
            {
                printf("┓");
            }
            else if (GameBackGround[i][j] == 5)
            {
                printf("┗");
            }
            else if (GameBackGround[i][j] == 6)
            {
                printf("┛");
            }
        }
        printf("\n");
    }


}
//int IsAlive()
//{
//    if(xPlayerHead <)
//
//
//}
//int getDirection()
//{
//    int temp = 0;
//    if (!_kbhit)
//    {
//        temp = _getch();
//    }
//
//}
void GetDirection()
{
    int temp = 0;
    if (_kbhit())
    {

        temp = _getch();
        if (temp == 87 || temp == 119 || temp == 65 || temp == 97 || temp == 68 || temp == 100 || temp == 83 || temp == 115)
        {
            if (!((direction == 87 || direction == 119) && (temp == 83 || temp == 115) || (temp == 87 || temp == 119) && (direction == 83 || direction == 115) || (direction == 65 || direction == 97) && (temp == 100 || temp == 68) || (direction == 100 || direction == 68) && (temp == 97 || temp == 65)))
                direction = temp;
        }
    }
}
void PlayerMove()
{

    //向右
    GameBackGround[PlayerXIndex[length - 1]][PlayerYIndex[length - 1]] = 0;
    SetPos(20 + PlayerYIndex[length - 1], 3 + PlayerXIndex[length - 1]);
    printf(" ");
    for (int i = length - 1; i >= 1; i--)
    {
        PlayerXIndex[i] = PlayerXIndex[i - 1];
        PlayerYIndex[i] = PlayerYIndex[i - 1];
    }
    switch (direction)
    {
    case 87:
    case 119:
        PlayerXIndex[0]--;
        //向上
        break;
    case 65:
    case 97:
        PlayerYIndex[0]--;
        //向左
        break;
    case 68:
    case 100:
        PlayerYIndex[0]++;
        //向右
        break;
    case 83:
    case 115:
        PlayerXIndex[0]++;
        //向下 
        break;
    default:
        break;
    }
    GameBackGround[PlayerXIndex[0]][PlayerYIndex[0]] = -2;
    SetPos(20 + PlayerYIndex[0], 3 + PlayerXIndex[0]);
    printf("*");
    /*   GameBackGround[xPlayerHead][++yPlayerHead ] = -2;
        GameBackGround[xPlayerHead][yPlayerHead - 2] = 0;*/

}
void ShowDeadPage()
{
    system("cls");
    SetPos(20, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    SetPos(20, 4);
    printf("┃                                                        ┃");
    SetPos(20, 5);
    printf("┃          很抱歉，你和贝尔的旅途......                  ┃");
    SetPos(20, 6);
    printf("┃                到此结束!!!                             ┃");
    SetPos(20, 7);
    printf("┃                                                        ┃");
    SetPos(20, 8);
    printf("┃                                                        ┃");
    SetPos(30, 8);
    printf("得分：%d", score);
    SetPos(20, 9);
    printf("┃                                                        ┃");
    SetPos(30, 9);
    printf("按任意键继续.....");
    SetPos(20, 10);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    SetPos(30,9);
    SetPos(30,7);
    printf("请输入你的名字:");
    scanf_s("%s",name,50);
    getchar();
}
int IsAlive()
{
    if (PlayerXIndex[0] > 22 || PlayerXIndex[0] < 1 || PlayerYIndex[0] < 1 || PlayerYIndex[0]>56)
        return 0;
    for (int i = 1;i < length;i++)
    {
        if (PlayerXIndex[0] == PlayerXIndex[i] && PlayerYIndex[0] == PlayerYIndex[i])
            return 0;
    }
    return 1;
}
void GameBody()
{

    GamePlayIntroduction();
    SrandFood();
    SrandPlayer();
    //fflush(stdin);
    InitGame();
    while (1)
    {
        ///* SetPos(25, 6);
        // printf("测试123456789");
        // SetPos(25, 6);*/
        // printf("         ");

        GetDirection();
        PlayerMove();
        if (!IsAlive())
        {

            ShowDeadPage();
            system("cls");
            InitGameInformation();
            return;

            //gameover
        }
        if (EatFood())
        {
            SrandFood();
            SetPos(20 + yFood, 3 + xFood);
            printf("#");
        }
        SetPos(20, 3 + MAX_BACKGROUND_LINE);
        printf("得分:%d\n", score);
        Sleep(250);
    }


    //setpos(20, 27);
    //printf("得分：");

}
int EatFood()
{
    if (PlayerXIndex[0] == xFood && PlayerYIndex[0] == yFood)
    {

        score += FoodScore;
        if (direction == 87 || direction == 119)
        {
            PlayerXIndex[length] = PlayerXIndex[length - 1] + 1;
            PlayerYIndex[length] = PlayerYIndex[length - 1];
        }
        else if (direction == 65 || direction == 97)
        {
            PlayerXIndex[length] = PlayerXIndex[length - 1];
            PlayerYIndex[length] = PlayerYIndex[length - 1] - 1;
        }
        else if (direction == 68 || direction == 100)
        {
            PlayerXIndex[length] = PlayerXIndex[length - 1];
            PlayerYIndex[length] = PlayerYIndex[length - 1] + 1;
        }
        else if (direction == 83 || direction == 115)
        {
            PlayerXIndex[length] = PlayerXIndex[length - 1] - 1;
            PlayerYIndex[length] = PlayerYIndex[length - 1];
        }
        length++;
        PlayerMove();
        return 1;
    }
    else
        return 0;
}
void GameStartPage()
{
    char s[100];
    setColor(10, 0);
    SetPos(10, 5);
    printf("┏━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    SetPos(10, 6);
    printf("┃        ┃                                                ┃\n");
    SetPos(10, 7);
    printf("┃ 贪吃蛇 ┃      从前有一条蛇叫做比奇大卢斯拉笨贝尔，她特别┃");
    SetPos(10, 8);
    printf("┃ 的世界 ┃ 喜欢吃树莓，于是她不断前进，不断前进，她打败了 ┃\n");
    SetPos(10, 9);
    printf("┃        ┃ jio级生物，学会了咋瓦鲁多，还驾驶着初号机打败了┃\n");
    SetPos(10, 10);
    printf("┃        ┃ 想要抢夺树莓的使徒们，创造了没有eva的世界，终于┃\n");
    SetPos(10, 11);
    printf("┃ 1.开始 ┃ 在世界的尽头找到了传说中的食品 ----树莓派！！！┃\n");
    SetPos(10, 12);
    printf("┃ 2.排名 ┃ 但是守护树莓派的巨人们寸步不离树莓派，而笨贝尔 ┃\n");
    SetPos(10, 13);
    printf("┃ 3.退出 ┃ 以自己目前的力量还无法消灭他们，为了获得更强的 ┃\n");
    SetPos(10, 14);
    printf("┃        ┃ 力量，实现自己的愿望，她决定要吃更多的树莓来变 ┃\n");
    SetPos(10, 15);
    printf("┃        ┃ 强，而你是和他同行的最好的旅行者，你能帮她实现 ┃\n");
    SetPos(10, 16);
    printf("┃        ┃ 这个永恒的愿望吗？？？？？                     ┃\n");
    SetPos(10, 17);
    printf("┗━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    SetPos(10, 19);
    printf("输入你的选择:");
    //scanf_s("%s",s,10);
    fgets(s, 100, stdin);
    //getline(s);
    switch (s[0])
    {
    case '1':
        GameBody();
        break;
    case '2':
        RankPage();
        //查看排名
        break;
    case '3':
        //退出
        SetPos(10, 20);
        printf("------------------");
        SetPos(10, 21);
        printf("和贝尔的时光总是这么短暂!再见了，旅行者.\n");
        exit(0);
        break;
    default:
        SetPos(10, 20);
        printf("--------------------\n");
        SetPos(10, 21);
        printf("输入错误，程序自动关闭\n");
        exit(0);
        break;
    }
}
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄

    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色

}
void SetPos(int x, int y)
{
    COORD pos;
    HANDLE handle;
    pos.X = x;
    pos.Y = y;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}
void RankPage()
{
    system("cls");
    SetPos(20, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    SetPos(20, 4);
    printf("┃                                                        ┃");
    SetPos(20, 5);
    printf("┃                                                        ┃");
    SetPos(20, 6);
    printf("┃                                                        ┃");
    SetPos(20, 7);
    printf("┃                                                        ┃");
    SetPos(20, 8);
    printf("┃                                                        ┃");
    SetPos(20, 9);
    printf("┃                                                        ┃");
    SetPos(20, 10);
    printf("┃                                                        ┃");
    SetPos(20, 11);
    printf("┃                                                        ┃");
    SetPos(20, 12);
    printf("┃                                                        ┃");
    SetPos(20, 13);
    printf("┃                                                        ┃");
    SetPos(20, 14);
    printf("┃                                                        ┃");
    SetPos(20, 15);
    printf("┃                                                        ┃");
    SetPos(20, 16);
    printf("┃                                                        ┃");
    SetPos(20, 17);
    printf("┃                                                        ┃");
    SetPos(20, 18);
    printf("┃                                                        ┃");
    SetPos(20, 19);
    printf("┃                                                        ┃");
    SetPos(20, 20);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    //SetPos(30, 4);
    //printf("1.巴尔                520");
    LinkToInternet(1);
    //此处打印从服务器收取排名
    SetPos(35, 18);
    printf("按任意键回到菜单和贝尔作战......");
    SetPos(20, 21);
    //system("pause");
     getchar();
    system("cls");

}
void LinkToInternet(int choice)
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return;
    }
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);   //创建和服务器连接套接字
    if (client_socket == -1)
    {
        SetPos(30,4);
        perror("socket");
        return;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;  /* Internet地址族 */
    addr.sin_port = htons(MYPORT);  /* 端口号 */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */
    //inet_aton("127.0.0.1", &(addr.sin_addr));
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.137.146");
    int addrlen = sizeof(addr);
    int listen_socket = connect(client_socket, (struct sockaddr*)&addr, addrlen);  //连接服务器
    if (listen_socket == -1)
    {
        SetPos(30, 4);
        perror("connect");
        return;
    }
    char StopSend[10];
    SetPos(30, 4);
    printf("成功连接到一个服务器\n");
    send(client_socket,&choice,sizeof(choice),0);
    if (choice == 0)//上传
    {
        
          send(client_socket,name,sizeof(name),0);
          recv(client_socket,StopSend,sizeof(StopSend),0);
        send(client_socket,&score,sizeof(score),0);
        memset(name,0,sizeof(name));
    }
    else if (choice == 1)//下载
    {
        
        recv(client_socket,&PlayerNum,sizeof(PlayerNum),0);
        for (int i = 0; i < PlayerNum;i++)
        {
       int l1 = recv(client_socket,name,sizeof(name),0);
         send(client_socket,"ack",sizeof("ack"),0);
        int l2  = recv(client_socket,&score,sizeof(score),0);
            SetPos(30, 5 + i);
            //name[l] = '\0';
            if (l1 > 0 && l2 > 0)
            {
            printf("%d. %s            %d",i+1,name,score);
            memset(name,0,sizeof(name));
            score = 0;
            }
            
        }
    }
    //char buf[MYSIZE] = { 0 };
    //
    //while (1)        //向服务器发送数据，并接收服务器转换后的大写字母
    //{
    //    SetPos(30, 5);
    //    输入



    //    printf("请输入你相输入的：");
    //    memset(buf, 0, MYSIZE);
    //    //scanf("%s", buf);
    //    //write(client_socket, buf, strlen(buf));
    //    send(client_socket, buf, strlen(buf), 0);
    //    int ret = recv(client_socket, buf, strlen(buf), 0);

    //    printf("buf = %s", buf);
    //    printf("\n");
    //    if (strncmp(buf, "END", 3) == 0)     //当输入END时客户端退出
    //    {
    //        break;
    //    }
    //}
   //close(client_socket);
    //close(listen_socket);
    
    return;
}
