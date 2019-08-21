#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

#define HEIGHT 65
#define WIDTH 20
#define MAX 200

struct contacts {
	string name;	//姓名
	int gender;		//性别:1男 2女
	int age;		//年龄
	string phone;	//电话
	string addr;	//地址
};

struct Addressbooks {
	struct contacts personArray[MAX];		//通讯录中保存的联系人数组
	int size;								//通讯录中人数个数
};

void initialize(void) {
	char i[128];

	sprintf_s(i, "mode con:cols=%d lines=%d", HEIGHT, WIDTH);
	system(i);
}

void Print_menu(void) {
	printf("      通讯录管理系统     \n");
	printf("*************************\n");
	printf("****  1.添加联系人   ****\n");
	printf("****  2.显示联系人   ****\n");
	printf("****  3.删除联系人   ****\n");
	printf("****  4.查找联系人   ****\n");
	printf("****  5.修改联系人   ****\n");
	printf("****  6.清空通讯录   ****\n");
	printf("****  0.退出通讯录   ****\n");
	printf("*************************\n");
}

void empty_buffer(void) {
	char a;

	while ((a = getchar()) != '\n');
}

int select_menuitem(void) {
	int select;

	while (1) {
		Print_menu();
		printf("请选择：");
		cin >> select;

		if (cin.fail()) {
			cin.clear();
			empty_buffer();
			printf("请输入正确的选项！\n");
			system("pause");
			system("cls");
		} else {
			break;
		}
	}
	system("cls");
	return select;
}

void AddPPerson(Addressbooks * i) {
	if (i->size == MAX) {
		printf("通讯录已满， 无法添加！\n");
		return;
	} else {
		string name;
		printf("请输入姓名:");
		cin >> name;
		i->personArray[i->size].name = name;

		int sex = 0;
		printf("请输入性别(1 --- 男，2 --- 女）：");
		while (1) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				i->personArray[i->size].gender = sex;
				break;
			} else {
				printf("输入有误，请重新输入！\n");
				printf("请输入性别(1 --- 男，2 --- 女）：");
			}
		}

		int age;
		printf("请输入年龄：");
		while (1) {
			cin >> age;
			if (age > 0 && age < 100) {
				i->personArray[i->size].age = age;
				break;
			} else {
				cin.clear();
				empty_buffer();
				printf("请输入正确的年龄！\n");
				printf("请输入年龄：");
			}
		}

		string phone;
		printf("请输入电话号码：");
		while (1) {
			cin >> phone;
			if (phone.length() == 7 || phone.length() == 11) {
				i->personArray[i->size].phone = phone;
				break;
			} else {
				cin.clear();
				empty_buffer();
				printf("请输入有效的电话号码！\n");
				printf("请输入电话号码：");
			}
		}

		string addr;
		printf("请输入地址：");
		cin >> addr;
		i->personArray[i->size].addr = addr;
	}

	printf("添加成功！\n");
	i->size++;
	system("pause");
}

void showPerson(Addressbooks *i) {
	if (i->size == 0) {
		printf("通讯录里没有联系人！\n");
		system("pause");
	} else {
		for (int f = 0; f < i->size; f++) {
			cout << i->size << "." << "姓名：" << i->personArray[f].name << "\t";
			cout << "性别：" << i->personArray[f].gender << "    ";
			cout << "年龄：" << i->personArray[f].age << "\t";
			cout << "电话号码：" << i->personArray[f].phone << "\t";
			cout << "地址：" << i->personArray[f].addr << endl;
		}
		system("pause");
	}
}

int isExist(Addressbooks *i, string name) {
	for (int f = 0; f < i->size; f++) {
		if (i->personArray[f].name == name) {
			return f;
		} 
	}
	return -1;
}

void deletePerson(Addressbooks *i) {
	string name;

	printf("请输入您要删除的联系人：");
	cin >> name;

	int ret = isExist(i, name);
	
	if (ret != -1) {
		for (int f = ret; f < i->size; f++) {
			i->personArray[f] = i->personArray[f + 1];
		}
		i->size--;
		printf("删除成功！\n");
	} else {
		printf("没有找到您要删除的联系人！\n");
	}

	system("pause");
}

void findperson(Addressbooks *i) {
	string name;

	printf("请输入您要查找的联系人姓名：");
	cin >> name;
	int ret = isExist(i, name);

	if (ret != -1) {
		cout << i->size << "." << "姓名：" << i->personArray[ret].name << "\t";
		cout << "性别：" << i->personArray[ret].gender << "    ";
		cout << "年龄：" << i->personArray[ret].age << "\t";
		cout << "电话号码：" << i->personArray[ret].phone << "\t";
		cout << "地址：" << i->personArray[ret].addr << endl;
	} else {
		printf("没有找到该联系人！\n");
	}

	system("pause");
}

void modifyPerson(Addressbooks *i) {
	string name;

	cout << "请输入您要修改的联系人：";
	cin >> name;
	int ret = isExist(i, name);
	
	if (ret != -1) {
		printf("请问您要修改该联系人的什么：");
		cin >> name;
		if (name == "姓名") {
			string name;
			printf("请输入姓名:");
			cin >> name;
			i->personArray[ret].name = name;
		} else if(name == "性别") {
			int sex = 0;
			printf("请输入性别(1 --- 男，2 --- 女）：");
			while (1) {
				cin >> sex;
				if (sex == 1 || sex == 2) {
					i->personArray[ret].gender = sex;
					break;
				} else {
					printf("输入有误，请重新输入！\n");
					printf("请输入性别(1 --- 男，2 --- 女）：");
				}
			}
		} else if(name == "年龄") {
			int age;
			printf("请输入年龄：");
			while (1) {
				cin >> age;
				if (age > 0 && age < 100) {
					i->personArray[ret].age = age;
					break;
				} else {
					cin.clear();
					empty_buffer();
					printf("请输入正确的年龄！\n");
					printf("请输入年龄：");
				}
			}
		} else if(name == "电话号码") {
			string phone;
			printf("请输入电话号码：");
			while (1) {
				cin >> phone;
				if (phone.length() == 7 || phone.length() == 11) {
					i->personArray[ret].phone = phone;
					break;
				} else {
					cin.clear();
					empty_buffer();
					printf("请输入有效的电话号码！\n");
					printf("请输入电话号码：");
				}
			}
		} else if(name == "地址") {
			string addr;
			printf("请输入地址：");
			cin >> addr;
			i->personArray[i->size].addr = addr;
		}

		printf("修改成功！\n");
	} else {
		printf("没有找到该联系人！\n");
	}
	
	system("pause");
}

void cleanPerson(Addressbooks *i) {
	string whether;

	printf("您确定删除所有联系人吗(输入确定将删除所有联系人,输入任意键将返回)？");
	cin >> whether;
	if (whether == "确定") {
		i->size = 0;
	} else {
		return;
	}

	printf("删除成功!\n");
	system("pause");
}

void choice_menus(void) {
	int select;
	struct Addressbooks abs;
	abs.size = 0;

	while (1) {
		select = select_menuitem();

		switch (select) {
		case 1:
			AddPPerson(&abs);
			system("cls");
			break;
		case 2:
			showPerson(&abs);
			system("cls");
			break;
		case 3:
			deletePerson(&abs);
			system("cls");
			break;
		case 4:
			findperson(&abs);
			system("cls");
			break;
		case 5:
			modifyPerson(&abs);
			system("cls");
			break;
		case 6:
			cleanPerson(&abs);
			system("cls");
			break;
		case 0:
			printf("感谢您的使用，再见！\n");
			system("pause");
			exit(1);
			break;
		default:
			printf("请输入已有的选项！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}


int main(void) {
	initialize();

	choice_menus();

	system("pause");
	return 0;
}