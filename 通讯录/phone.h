//定义基础信息
#define REALNAME_LEN 20 //真实姓名
#define PHONE_LEN 11    //手机号长度
#define CAPACITY 100    //通讯录容量

int   current_total =0;               //当前通讯录中联系人总数
char *phonePath   = "phone.dat";//定义数据文件保存的位置

//声明方法
void phone_init();//程序初始化
void addContact(); //增加联系人
void delContact();//删除联系人
void modContact();//修改联系人
void getContactList();//查看所有联系人
void searchContact();//搜索联系人
void writeFile();//将信息写入phone.dat
int validateInput();//验证输入

//定义联系人结构体
typedef struct {
    char realname[REALNAME_LEN];    //联系人
    char phone[PHONE_LEN];          //联系人号码
}Person;

Person personList[CAPACITY];//存储所有联系人的数组
