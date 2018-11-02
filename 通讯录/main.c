#include<stdio.h>
#include <string.h>
#include "phone.h"


int fno;

int main(void){
    phone_init();
    printf("通讯录初始化完成！\n\n");
    //显示软件的界面
    printf("**************************\n");
    printf("****** 欢迎使用通讯录 ******\n");
    printf("****** 1.添加联系人 *******\n");
    printf("****** 2.删除联系人 *******\n");
    printf("****** 3.修改联系人 *******\n");
    printf("****** 4.查看所有联系人 ****\n");
    printf("****** 5.搜索联系人 *******\n");
    printf("****** 6.退出系统   *******\n");
    printf("**************************\n\n");

    while (1) {
        printf("请选择功能:输入编号1~6\n");
        while (1) {
            scanf("%d",&fno);
            if (validateInput(fno, 1, 6)) {
                break;
            }
            else{
                printf("非法输入！请重新输入！\n");
            }
        }
        
        switch (fno) {
            case 1:
                addContact();
                break;
            case 2:
                delContact();
                break;
            case 3:
                modContact();
                break;
            case 4:
                getContactList();
                break;
            case 5:
                searchContact();
                break;
            case 6:
                printf("系统正在退出...\n");
                printf("系统已经退出！\n");
                return 0;
                break;   
            default:
                break;
        }
        
    }
    return 0;
}


void phone_init(){
    FILE * fp = fopen(phonePath, "r");//打开通讯录文件
    if (fp != NULL) {
         //第一步，读取联系人个数
        fread(&current_total, sizeof(current_total), 1, fp);
        //第二步，读取每一个联系人
        int i;
        for (i = 0; i < current_total; i++) {
            //读取联系人数据到联系人数组中
            fread(&personList[i], sizeof(Person), 1, fp);
        }
    }else{
        printf("******欢迎使用简易通讯录工具******\n");
        printf("******作者：邹慧刚 (学习C语言项目)*****\n");
        printf("******正在为您初始化存储空间******\n");
        fp = fopen(phonePath, "wb");//第一步，创建文件
        fwrite(&current_total, sizeof(current_total), 1, fp); //第二步，写入联系人个数
    }
    fclose(fp);

}

void writeFile(){
    FILE *fp = fopen(phonePath, "wb");
    if (fp != NULL) {
        //先写入联系人个数
        fwrite(&current_total, sizeof(current_total), 1, fp);
        //写每个联系人数据
        int i;
        for (i =0; i < current_total; i++) {
            fwrite(&personList[i], sizeof(Person), 1, fp);
        }
        printf("数据更新成功！\n");
    }
    fclose(fp);
}


/**
 *  添加联系人
 */
void addContact()
{
    printf("您选择的是添加联系人，请按提示操作:\n");
    printf("请输入联系人姓名:(*联系人姓名中间不能有空格)\n");
    scanf("%s",personList[current_total].realname);
    printf("请输入联系人电话:(*联系人电话中间不能有空格)\n");
    scanf("%s",personList[current_total].phone);
    int flag;
    printf("确定要添加该联系人吗？1.确认 0.取消\n");
    scanf("%d",&flag);
    if (flag == 1) {
        current_total++;//联系人个数加1
        writeFile();//使用函数
    }
}

/*
修改联系人
*/
void modContact(){
    printf("您选择的是修改联系人，请按提示操作:\n");
    //提示用户输入要修改的用户编号
    printf("请输入要修改的联系人的编号:\n");
    int no1;
    //判断编号是否合法，编号不能大于联系人个数
    while (1) {
        scanf("%d",&no1);
        if (validateInput(no1, 1, current_total)) {
            char realname1[REALNAME_LEN];
            printf("请输入新的联系人姓名:(*联系人姓名中间不能有空格)\n");
            scanf("%s",realname1);
            char phone1[PHONE_LEN];
            printf("请输入新的联系人电话:(*联系人电话中间不能有空格)\n");
            scanf("%s",phone1);
            //让用户再次确认修改
            int flag;
            printf("修改联系人后,数据发生改变，您确定要修改吗？1.确定 0.取消\n");
            scanf("%d",&flag);
            if (flag == 1) {
                strcpy(personList[no1-1].realname, realname1);
                strcpy(personList[no1-1].phone, phone1);
                writeFile();//更新文件
                break;
            }
            else{
                printf("请再次输入要修改的联系人编号:\n");
            }
        }
        else{
            printf("不存在该编号，请重新输入！\n");
        }
    }
}



/**
 *  删除联系人
 */
void delContact()
{
    printf("您选择的是删除联系人，请按提示操作:\n");
    printf("请输入要删除的联系人的编号:\n");//提示用户输入要删除的联系人编号
    int no1;
    //判断编号是否合法，编号不能大于联系人个数
    while (1) {
        scanf("%d",&no1);
        if (validateInput(no1, 1, current_total)) {
            int flag;
            printf("删除联系人后,数据将无法恢复，您确定要删除吗？1.确定 0.取消\n");
            scanf("%d",&flag);
            if (flag == 1) {
                //判断编号是不是最后一个元素
                if (no1 != current_total) {
                    int i;
                    for (i = no1; i < current_total; i++) {
                        //元素的移动和覆盖
                        personList[i-1] = personList[i];
                    }
                }
                current_total--;
                writeFile();
                break;
            }
            else{
                printf("请再次输入要删除的联系人编号:\n");
            }
        }
        else{
            printf("不存在该编号，请重新输入！\n");
        }
    }
}


/*
查看所有联系人
*/
void getContactList(){
    system("clear");/*清屏*/
    printf("联系人信息如下:\n");
    if (current_total ==0) {
        printf("您的通讯录还没有小伙伴，请添加联系人！\n");
    }
    else{
        printf("编号\t 姓名\t 电话\t \n");
        int i;
        for (i = 0; i < current_total; i++) {
            printf("%d\t %s\t %s\t \n",i+1,personList[i].realname,personList[i].phone);
        }
    }
}

/*
搜索联系人
*/
void searchContact(){
    system("clear");
    printf("请输入姓名或手机号:\n");
    char skey[20];
    scanf("%s",skey);
    int a;
    int is_success=0;
    for (a = 0; a < current_total; a++) {
        if (strcmp(skey, personList[a].realname) == 0 || strcmp(skey, personList[a].phone) == 0) {
            system("clear");
            printf("您所查找的联系人信息如下:\n");
            printf("姓名%s\t 手机号%s\t \n",personList[a].realname,personList[a].phone);
            is_success=1;
        }

    }
    if (is_success==0) {
        system("clear");
        printf("对不起，查无此人！\n");
    }
}


/**
 *  验证输入是否合法
 *
 *  @param num 待验证的数
 *  @param min 最小值
 *  @param max 最大值
 *
 *  @return 1非法，0合法
 */
int validateInput(int num,int min,int max)
{
    if (num < min ||num > max) {
//        printf("非法输入！请重新输入！\n");
//        printf("系统正在退出...\n");
//        printf("系统已经退出！\n");
        return 0;
    }
    return 1;
}