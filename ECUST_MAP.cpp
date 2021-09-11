#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#define INF 999999
#define M 20
int dist[M][M];///距离
int path[M][M];///路径
int Stack[M];///路径栈
int top;///栈顶
int counts;///记录路径数
int visited[M];///标记数组
using namespace std;
struct vertex///景点信息结构体
{
    int num;///景点编号
    char name[20];///景点名称
    char info[300];///景点介绍
};
struct maps
{
    int n;///点数
    int m;///边数
    vertex v[M];
    int edgs[M][M];///邻接矩阵
} g; ///景点图的结构体
void Creat_vertex()
{
    g.v[0].num=1;
    strcpy(g.v[0].name,"北大门");
    strcpy(g.v[0].info,"整体建筑复刻徐汇校区大门（疫情期间仅此门开放）");
    g.v[1].num=2;
    strcpy(g.v[1].name,"花田");
    strcpy(g.v[1].info,"谁不想和向日葵合影呢？");
    g.v[2].num=3;
    strcpy(g.v[2].name,"卫生所");
    strcpy(g.v[2].info,"常备救护车。");
    g.v[3].num=4;
    strcpy(g.v[3].name,"C60雕塑");
    strcpy(g.v[3].info,"足球烯");
    g.v[4].num=5;
    strcpy(g.v[4].name,"实验楼");
    strcpy(g.v[4].info,"来做实验吗？");
    g.v[5].num=6;
    strcpy(g.v[5].name,"亲水广场");
    strcpy(g.v[5].info,"红旗升起的地方");
    g.v[6].num=7;
    strcpy(g.v[6].name,"南大门");
    strcpy(g.v[6].info,"海思路999号");
    g.v[7].num=8;
    strcpy(g.v[7].name,"体育馆");
    strcpy(g.v[7].info,"学校体育馆内有主馆、副馆、游泳馆组成");
    g.v[8].num=9;
    strcpy(g.v[8].name,"南侧门");
    strcpy(g.v[8].info,"旁边也有小花花");
    g.v[9].num=10;
    strcpy(g.v[9].name,"教学楼ABCD");
    strcpy(g.v[9].info,"上课、自习好去处。");
    g.v[10].num=11;
    strcpy(g.v[10].name,"体育场");
    strcpy(g.v[10].info,"体育课、运动会都少不了它。");
    g.v[11].num=12;
    strcpy(g.v[11].name,"一食堂");
    strcpy(g.v[11].info,"一食堂有三层，食物种类繁多。");
    g.v[12].num=13;
    strcpy(g.v[12].name,"大学生活动中心");
    strcpy(g.v[12].info,"各种社团、艺术团、公益组织聚集地。");
    g.v[13].num = 14;
    strcpy(g.v[13].name, "菜鸟驿站");
    strcpy(g.v[13].info, "取快递吗？");
    g.v[14].num = 15;
    strcpy(g.v[14].name, "外语楼");
    strcpy(g.v[14].info, "外国语学院、晨读、财务处。");
    g.v[15].num = 16;
    strcpy(g.v[15].name, "图书馆");
    strcpy(g.v[15].info, "知识的殿堂，内有大型炼丹图。图书馆外有平静的通海湖，时不时有鸭子和孔雀在水中嬉戏。");
    g.v[16].num = 17;
    strcpy(g.v[16].name, "信息楼");
    strcpy(g.v[16].info, "机房、电子信息实验中心、阳光平台");
    g.v[17].num = 18;
    strcpy(g.v[17].name, "教师公寓");
    strcpy(g.v[17].info, "可搭乘梦境班车前往上海南站、徐汇校区");
    g.v[18].num = 19;
    strcpy(g.v[18].name, "二食堂");
    strcpy(g.v[18].info, "共两层可供选择。");
}
void Creat_maps()
{
    int i,j;
    g.n=19;///19个景点
    g.m=35;///35条双向路径
    for(i=0; i<g.n; i++) ///初始化邻接矩阵
    {
        for(j=0; j<g.n; j++)
        {
            g.edgs[i][j]=INF;
        }
    }
    g.edgs[0][1]=g.edgs[1][0]=175;  ///写入边的信息
    g.edgs[0][16]=g.edgs[16][0]=300;
    g.edgs[0][18]=g.edgs[18][0]=260;
    g.edgs[0][17]=g.edgs[17][0]=340;
    g.edgs[1][2]=g.edgs[2][1]=130;
    g.edgs[2][3]=g.edgs[3][2] =445;
    g.edgs[2][4]=g.edgs[4][2]=790;
    g.edgs[3][4] = g.edgs[4][3]=340;
    g.edgs[3][18]=g.edgs[18][3]=265;
    g.edgs[3][16]=g.edgs[16][3]=250;
    g.edgs[16][18]=g.edgs[18][16]=140;
    g.edgs[4][5]=g.edgs[5][4]=270;
    g.edgs[4][6]=g.edgs[6][4]=460;
    g.edgs[5][6]=g.edgs[6][5]=170;
    g.edgs[6][7]=g.edgs[7][6]=380;
    g.edgs[7][8]=g.edgs[8][7]=200;
    g.edgs[7][9]=g.edgs[9][7]=280;
    g.edgs[5][9]=g.edgs[9][5]=390;
    g.edgs[5][15]=g.edgs[15][5]=390;
    g.edgs[15][16]=g.edgs[16][15]=270;
    g.edgs[14][16] = g.edgs[16][14] = 250;
    g.edgs[15][14] = g.edgs[14][15] = 110;
    g.edgs[15][9] = g.edgs[9][15] = 215;
    g.edgs[9][14] = g.edgs[14][9] = 225;
    g.edgs[9][10] = g.edgs[10][9] = 180;
    g.edgs[7][10] = g.edgs[10][7] = 230;
    g.edgs[13][14] = g.edgs[14][13] = 290;
    g.edgs[9][13] = g.edgs[13][9] = 460;
    g.edgs[9][11] = g.edgs[11][9] = 310;
    g.edgs[10][11] = g.edgs[11][10] = 340;
    g.edgs[11][13] = g.edgs[13][11] = 240;
    g.edgs[13][17] = g.edgs[17][13] = 170;
    g.edgs[13][12] = g.edgs[12][13] = 300;
    g.edgs[11][12] = g.edgs[12][11] = 300;
    g.edgs[12][17] = g.edgs[17][12] = 320;
}
void Search_info()
{
    int i,n;
    printf("华东理工大学奉贤校区的景点有：\n");
    for(i=0; i<19; i++)
    {
        printf("%d:%s\n",g.v[i].num,g.v[i].name);
    }
    while(1)
    {
        printf("请输入你想要查询的景点编号：\n");
        printf("按0退出\n\n");
        scanf("%d",&n);
        getchar();
        if(n==0)
        {
            break;
        }
        else if(n<0||n>19)
        {
            printf("输入有误，请重新输入！！！\n\n");
            continue;
        }
        else
        {
            printf("%d:%s\n",g.v[n-1].num,g.v[n-1].name);
            printf("%s\n\n",g.v[n-1].info);
        }
    }
    return ;
}
void Floyd() ///弗洛伊德
{
    int i,j,k;
    for(i=0; i<g.n; i++) ///初始化距离与路径矩阵
    {
        for(j=0; j<g.n; j++)
        {
            dist[i][j]=g.edgs[i][j];
            if(i!=j&&dist[i][j]<INF)
            {
                path[i][j]=i;
            }
            else
            {
                path[i][j]=-1;///-1代表不可达
            }
        }
    }
    //printf("%d\n",g.n);
    for(k=0; k<g.n; k++)
    {
        for(i=0; i<g.n; i++)
        {
            for(j=0; j<g.n; j++)
            {
                if(dist[i][j]>(dist[i][k]+dist[k][j]))
                {
                    dist[i][j]=dist[i][k]+dist[k][j];///更新
                    path[i][j]=k;         ///path用于记录最短路径上的结点*/
                }
            }
        }
    }
    return ;
}
void Floyd_print(int s, int e)
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)///递归终止条件
    {
        return;
    }
    else
    {
        Floyd_print(s,path[s][e]);///将中间点作为终点继续打印路径
        printf("%s->",g.v[path[s][e]].name);///打印中间景点名字
        Floyd_print(path[s][e],e);///将中间点作为起点继续打印路径
    }
}

void Dfs_allpath(int s,int e)
{
    int dis=0;
    int i,j;
    Stack[top]=s;
    top++;  ///起点入栈
    visited[s]=1;///标记入栈
    for(i=0; i<g.n; i++)
    {
        if(g.edgs[s][i]>0&&g.edgs[s][i]!=INF&&!visited[i])
        {
            ///表明两点可达且未被访问
            if(i==e)///DFS到了终点，打印路径
            {
                printf("第%d条路:",counts++);
                for(j=0; j<top; j++)
                {
                    printf("%s->",g.v[Stack[j]].name);
                    if(j<top-1)///统计路径长度
                    {
                        dis=dis+g.edgs[Stack[j]][Stack[j+1]];
                    }
                }
                dis=dis+g.edgs[Stack[top-1]][e];
                printf("%s\n",g.v[e].name);///打印终点
                printf("总长度是：%dm\n\n",dis);
            }
            else///不是终点接着DFS
            {
                Dfs_allpath(i,e);
                top--;///支路全被访问一遍,顶点出栈
                visited[i]=0;///出栈点标记为已出栈，允许下次访问
            }
        }
    }
}
void Bestpath_Multispot()
{
    int vNum[M]= {0};
    int i,j,dis;
    j=1;
    dis=0;///统计全程总长
    printf("请输入你要游览的第%d个景点的编号（输入-1结束输入）：",j);
    scanf("%d",&vNum[j-1]);
    while(vNum[j-1]!=-1&&j<13)
    {
        printf("请输入你要游览的第%d个景点编号：",++j);
        scanf("%d", &vNum[j-1]);
        if(vNum[j-1]==-1)
        {
            break;
        }
    }
    printf("\n这是最佳访问路径：");
    for(i=0; vNum[i]>0&&vNum[i+1]>0; i++)
    {
        printf("%s->",g.v[vNum[i]-1].name);///输出路径上的起点
        Floyd_print(vNum[i]-1,vNum[i+1]-1);///利用佛洛依德算法
        dis+=dist[vNum[i]-1][vNum[i+1]-1];
    }
    printf("%s\n\n",g.v[vNum[j-2]-1].name);///*输出路径上的终点*/
    printf("全程总长为：%dm\n\n",dis);
}

void Dis_menu()
{
    printf("\n");
    printf("       **欢迎使用华东理工大学（奉贤校区）导游咨询系统*******\n\n");
    printf("       *****   1.景点信息查询             ******************\n");
    printf("       *****   2.景点之间最短路查询       ******************\n");
    printf("       *****   3.景点间所有路径查询       ******************\n");
    printf("       *****   4.多景点间访问路线查询     ******************\n");
    printf("       *****   5.退出系统                 ******************\n");
    printf("       *****************************************************\n");
    return ;
}
void Dis_map()
{
	printf("\t\t****************************************\n");
	printf("\t\t华东理工大学（奉贤校区）地图\n ");
	printf(" ┌───────────────────────────────────┐\n");
	printf(" │  MAP OF ECUST(FENGXIAN CAMPUS)    │\n");
	printf(" │  3  █2  1 18╔═════╤═╤══╕13     ↑N │\n");
	printf(" │╔╧═════╧═╬═══╬═════╪═╪══╧═╦════╗   │\n");
	printf(" │║   █    ║   ║     │█│    ║    ║   │\n");
	printf(" │║   █    ║   ╠═══╤═╪═╪════╣12   ║  │\n");
	printf(" │║   █ 19 ║   ║  14 │█│    ╠══════╣ │ \n");
	printf(" │╬══════╦═╩═══╬═════╪═╪════╬══╗   ║ │\n");
	printf(" │║ 4 █  ║17   ║15   │█│  10║  ║11  ║│\n");
	printf(" │╠═╦════╩══╤══╩═════╪═╪════╬══╣    ║│\n");
	printf(" │║ ║    ███│    16  │█│    ║  ╠════╣│\n");
	printf(" │║ ║  █████└────────┘█╞════╩══╣    ║│\n");
	printf(" │╠═╣   ███████████████ │      ║    ║│\n");
	printf(" │║ ║     ██████████████ │     ║    ║│\n");
	printf(" │║ ║5      ████████████  │    ║    ║│\n");
	printf(" │║ ╟────────── 6   ────┘      ║8   ║│\n");
	printf(" │╚═╩══════════╬╬══════════════╩═══╦╝│\n");
	printf(" │             7                   9 │\n");
	printf(" └───────────────────────────────────┘\n");
}
int main()
{
    int i,n;
    int start,ends;
    Creat_vertex();
    Creat_maps();
    Dis_map();
    while(1)
    {
        Dis_menu();
        printf("请输入需要操作的命令：\n");
        scanf("%d",&n);
        getchar();
        if(n<1||n>5)
        {
            printf("输入有误，请重新输入！！！\n");
            continue;
        }
        else
        {
            if(n==1)
            {
                Search_info();
            }
            else if(n==2)
            {
                Dis_map();
                printf("请输入起点的景点：\n");
                scanf("%d",&start);
                printf("请输入终点的景点：\n");
                scanf("%d",&ends);
                Floyd();///弗洛伊德
                printf("从%s到%s最短距离是：%d\n",g.v[start-1].name,g.v[ends-1].name,dist[start-1][ends-1]);
                printf("%s->",g.v[start-1].name);
                Floyd_print(start-1, ends-1);
                printf("%s\n",g.v[ends-1].name);
            }
            else if(n==3)
            {
                Dis_map();
                counts=1;///起始路径数为1
                printf("请输入起点的景点：\n");
                scanf("%d",&start);
                printf("请输入终点的景点：\n");
                scanf("%d",&ends);
                Dfs_allpath(start-1,ends-1);
            }
            else if(n==4)
            {
                Dis_map();
                Floyd();///弗洛伊德
                Bestpath_Multispot();
            }
            else if(n==5)
            {
                return 0;
            }
        }

    }
    return 0;
}
