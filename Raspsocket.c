
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include<stdlib.h>

#define PORT 9990   //端口号
#define SIZE 1024   //定义的数组大小

typedef struct RankInfo* pRankInfo;
typedef struct RankInfo Rank;
struct RankInfo {
	char* name;
	int score;
	pRankInfo link;

};

pRankInfo ptrl = NULL;
pRankInfo CreateList(char* name, int score);
int Length(pRankInfo ptrl);
pRankInfo ReturnLastNode(pRankInfo ptrl);
pRankInfo CreateOtherNode(pRankInfo ptrl, char* name, int score);
pRankInfo CreateList(char* name, int score)
{
	pRankInfo ptrl = (pRankInfo)malloc(sizeof(Rank));
	ptrl->name = (char*)malloc(sizeof(50));
	strcpy(ptrl->name, name);
	ptrl->score = score;
	ptrl->link = NULL;
	return ptrl;

}

int Length(pRankInfo ptrl)
{
	int len = 0;
	pRankInfo p = ptrl;
	while (p)
	{
		p = p->link;
		len++;
	}
	return len;
}
pRankInfo ReturnLastNode(pRankInfo ptrl)
{
	pRankInfo p = ptrl;
	while (p->link != NULL)
	{
		p = p->link;
	}
	return p;
}
pRankInfo CreateOtherNode(pRankInfo ptrl, char* name, int score)
{
	if (Length(ptrl) < 10)
	{
		if (score > ptrl->score)
		{
			pRankInfo p = (pRankInfo)malloc(sizeof(Rank));
			p->name = (char*)malloc(sizeof(50));
			strcpy(p->name, name);
			p->score = score;
			p->link = ptrl;
			return p;
		}
		else
		{
			pRankInfo temp = ptrl;
			pRankInfo pp = ptrl;
			while (pp != NULL && score < (pp->score))
			{
				temp = pp;
				pp = pp->link;
			}
			pRankInfo p = (pRankInfo)malloc(sizeof(Rank));
			p->name = (char*)malloc(sizeof(50));
			strcpy(p->name, name);
			p->score = score;
			p->link = NULL;
			if (pp == NULL)
			{
				temp->link = p;
			}
			else
			{
				temp->link = p;
				p->link = pp;
			}
		}
	}
	else
	{
		if (score > ptrl->score)
		{
			pRankInfo p = (pRankInfo)malloc(sizeof(Rank));
			p->name = (char*)malloc(sizeof(50));
			strcpy(p->name, name);
			p->score = score;
			p->link = ptrl;
			return p;
		}
		else
		{
			pRankInfo p = (pRankInfo)malloc(sizeof(Rank));
			p->name = (char*)malloc(sizeof(50));
			strcpy(p->name, name);
			p->score = score;
			p->link = NULL;
			pRankInfo temp = ptrl;
			pRankInfo pp = ptrl;
			while (score < pp->score && pp != NULL)
			{
				temp = pp;
				pp = pp->link;
			}
			if (pp != NULL)
			{
				temp->link = p;
				p->link = pp;
			}
		}
	}
	return ptrl;
}
int Creat_socket()    //创建套接字和初始化以及监听函数
{
	int ret, on;
	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);   //创建一个负责监听的套接字
	if (listen_socket == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	on = 1;
	ret = setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	addr.sin_family = AF_INET;  /* Internet地址族 */
	addr.sin_port = htons(PORT);  /* 端口号 */
	addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */

	ret = bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr));  //连接
	if (ret == -1)
	{
		perror("bind");
		return -1;
	}

	ret = listen(listen_socket, 5);        //监听
	if (ret == -1)
	{
		perror("listen");
		return -1;
	}
	return listen_socket;
}

int wait_client(int listen_socket)
{
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	printf("等待客户端连接。。。。\n");
	int client_socket = accept(listen_socket, (struct sockaddr*)&cliaddr, &addrlen);   //创建一个和客户端交流的套接字
	if (client_socket == -1)
	{
		perror("accept");
		return -1;
	}

	printf("成功接收到一个客户端：%s\n", inet_ntoa(cliaddr.sin_addr));

	return client_socket;
}
void CopyInfoToFile(pRankInfo PTRL, FILE* fp, char* name, int score)
{
	char temp[100];
	fclose(fp);
	fp = fopen("/home/pi/text.txt", "w+");
	printf("%d\n", Length(PTRL));
	if (Length(PTRL) == 0)
	{
		PTRL = CreateList(name, score);
	}
	else
	{
		PTRL = CreateOtherNode(PTRL, name, score);
	}
	pRankInfo pp = PTRL;
	while (pp != NULL)
	{
		sprintf(temp, "%s %d", pp->name, pp->score);
		fputs(temp, fp);
		fwrite("\n", sizeof(char), 1, fp);
		memset(temp, 0, sizeof(temp));
		pp = pp->link;
	}



}
void DeleteList(pRankInfo ptrl)
{
	pRankInfo p = ptrl;
	pRankInfo pp = p;
	while (p)
	{

		pp = p;
		p = p->link;
		free(pp);

	}

}
pRankInfo CopyInfoFromFile(FILE* fp)
{
	pRankInfo p = NULL;
	char name[50];
	int score;


	rewind(fp);
	while (!feof(fp))
	{
		if (fscanf(fp, "%s %d", name, &score) == 2)
		{
			if (p == NULL)
			{
				p = CreateList(name, score);
			}
			else
			{
				p = CreateOtherNode(p, name, score);
			}
			memset(name, 0, sizeof(name));
		}
	}
	return p;


}
void hanld_client(int listen_socket, int client_socket)
{
	char name[50];
	int score = 0;
	int choice = 0;
	FILE* fp = NULL;
	fp = fopen("/home/pi/text.txt", "r+");
	recv(client_socket, &choice, sizeof(choice), 0);

	printf("%d\n", choice);
	if (choice == 0)//上传数据
	{


		int l1 = recv(client_socket, name, sizeof(name), 0);
		send(client_socket, "ACK", sizeof("ACK"), 0);
		int l2 = recv(client_socket, &score, sizeof(score), 0);
		if (l1 > 0 && l2 > 0)
		{
			printf("%s %d\n", name, score);
			pRankInfo ppp = CopyInfoFromFile(fp);
			CopyInfoToFile(ppp, fp, name, score);
			DeleteList(ppp);
		}

	}
	else if (choice == 1)
	{//下载

		char StopSend[10];
		pRankInfo ppp = CopyInfoFromFile(fp);
		pRankInfo pppp = ppp;
		int temp = Length(ppp);
		if (temp <= 0)
			return;
		send(client_socket, &temp, sizeof(temp), 0);
		int i = 0;
		while (pppp != NULL && i < 10)
		{
			i++;
			printf("%s %d\n", pppp->name, pppp->score);
			send(client_socket, pppp->name, strlen(pppp->name) + 1, 0);

			recv(client_socket, StopSend, sizeof(StopSend), 0);
			send(client_socket, &(pppp->score), sizeof(pppp->score), 0);
			pppp = pppp->link;
			memset(StopSend, 0, sizeof(StopSend));
		}
		DeleteList(pppp);

	}


	close(client_socket);
	fclose(fp);
}

int main()
{
	while (1)
	{
		int listen_socket = Creat_socket();


		int client_socket = wait_client(listen_socket);


		hanld_client(listen_socket, client_socket);

		//close(client_socket);

		close(listen_socket);
		sleep(1);
	}

	return 0;
}
