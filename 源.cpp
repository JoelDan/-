#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

#define HEIGHT 65
#define WIDTH 20
#define MAX 200

struct contacts {
	string name;	//����
	int gender;		//�Ա�:1�� 2Ů
	int age;		//����
	string phone;	//�绰
	string addr;	//��ַ
};

struct Addressbooks {
	struct contacts personArray[MAX];		//ͨѶ¼�б������ϵ������
	int size;								//ͨѶ¼����������
};

void initialize(void) {
	char i[128];

	sprintf_s(i, "mode con:cols=%d lines=%d", HEIGHT, WIDTH);
	system(i);
}

void Print_menu(void) {
	printf("      ͨѶ¼����ϵͳ     \n");
	printf("*************************\n");
	printf("****  1.�����ϵ��   ****\n");
	printf("****  2.��ʾ��ϵ��   ****\n");
	printf("****  3.ɾ����ϵ��   ****\n");
	printf("****  4.������ϵ��   ****\n");
	printf("****  5.�޸���ϵ��   ****\n");
	printf("****  6.���ͨѶ¼   ****\n");
	printf("****  0.�˳�ͨѶ¼   ****\n");
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
		printf("��ѡ��");
		cin >> select;

		if (cin.fail()) {
			cin.clear();
			empty_buffer();
			printf("��������ȷ��ѡ�\n");
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
		printf("ͨѶ¼������ �޷���ӣ�\n");
		return;
	} else {
		string name;
		printf("����������:");
		cin >> name;
		i->personArray[i->size].name = name;

		int sex = 0;
		printf("�������Ա�(1 --- �У�2 --- Ů����");
		while (1) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				i->personArray[i->size].gender = sex;
				break;
			} else {
				printf("�����������������룡\n");
				printf("�������Ա�(1 --- �У�2 --- Ů����");
			}
		}

		int age;
		printf("���������䣺");
		while (1) {
			cin >> age;
			if (age > 0 && age < 100) {
				i->personArray[i->size].age = age;
				break;
			} else {
				cin.clear();
				empty_buffer();
				printf("��������ȷ�����䣡\n");
				printf("���������䣺");
			}
		}

		string phone;
		printf("������绰���룺");
		while (1) {
			cin >> phone;
			if (phone.length() == 7 || phone.length() == 11) {
				i->personArray[i->size].phone = phone;
				break;
			} else {
				cin.clear();
				empty_buffer();
				printf("��������Ч�ĵ绰���룡\n");
				printf("������绰���룺");
			}
		}

		string addr;
		printf("�������ַ��");
		cin >> addr;
		i->personArray[i->size].addr = addr;
	}

	printf("��ӳɹ���\n");
	i->size++;
	system("pause");
}

void showPerson(Addressbooks *i) {
	if (i->size == 0) {
		printf("ͨѶ¼��û����ϵ�ˣ�\n");
		system("pause");
	} else {
		for (int f = 0; f < i->size; f++) {
			cout << i->size << "." << "������" << i->personArray[f].name << "\t";
			cout << "�Ա�" << i->personArray[f].gender << "    ";
			cout << "���䣺" << i->personArray[f].age << "\t";
			cout << "�绰���룺" << i->personArray[f].phone << "\t";
			cout << "��ַ��" << i->personArray[f].addr << endl;
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

	printf("��������Ҫɾ������ϵ�ˣ�");
	cin >> name;

	int ret = isExist(i, name);
	
	if (ret != -1) {
		for (int f = ret; f < i->size; f++) {
			i->personArray[f] = i->personArray[f + 1];
		}
		i->size--;
		printf("ɾ���ɹ���\n");
	} else {
		printf("û���ҵ���Ҫɾ������ϵ�ˣ�\n");
	}

	system("pause");
}

void findperson(Addressbooks *i) {
	string name;

	printf("��������Ҫ���ҵ���ϵ��������");
	cin >> name;
	int ret = isExist(i, name);

	if (ret != -1) {
		cout << i->size << "." << "������" << i->personArray[ret].name << "\t";
		cout << "�Ա�" << i->personArray[ret].gender << "    ";
		cout << "���䣺" << i->personArray[ret].age << "\t";
		cout << "�绰���룺" << i->personArray[ret].phone << "\t";
		cout << "��ַ��" << i->personArray[ret].addr << endl;
	} else {
		printf("û���ҵ�����ϵ�ˣ�\n");
	}

	system("pause");
}

void modifyPerson(Addressbooks *i) {
	string name;

	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�";
	cin >> name;
	int ret = isExist(i, name);
	
	if (ret != -1) {
		printf("������Ҫ�޸ĸ���ϵ�˵�ʲô��");
		cin >> name;
		if (name == "����") {
			string name;
			printf("����������:");
			cin >> name;
			i->personArray[ret].name = name;
		} else if(name == "�Ա�") {
			int sex = 0;
			printf("�������Ա�(1 --- �У�2 --- Ů����");
			while (1) {
				cin >> sex;
				if (sex == 1 || sex == 2) {
					i->personArray[ret].gender = sex;
					break;
				} else {
					printf("�����������������룡\n");
					printf("�������Ա�(1 --- �У�2 --- Ů����");
				}
			}
		} else if(name == "����") {
			int age;
			printf("���������䣺");
			while (1) {
				cin >> age;
				if (age > 0 && age < 100) {
					i->personArray[ret].age = age;
					break;
				} else {
					cin.clear();
					empty_buffer();
					printf("��������ȷ�����䣡\n");
					printf("���������䣺");
				}
			}
		} else if(name == "�绰����") {
			string phone;
			printf("������绰���룺");
			while (1) {
				cin >> phone;
				if (phone.length() == 7 || phone.length() == 11) {
					i->personArray[ret].phone = phone;
					break;
				} else {
					cin.clear();
					empty_buffer();
					printf("��������Ч�ĵ绰���룡\n");
					printf("������绰���룺");
				}
			}
		} else if(name == "��ַ") {
			string addr;
			printf("�������ַ��");
			cin >> addr;
			i->personArray[i->size].addr = addr;
		}

		printf("�޸ĳɹ���\n");
	} else {
		printf("û���ҵ�����ϵ�ˣ�\n");
	}
	
	system("pause");
}

void cleanPerson(Addressbooks *i) {
	string whether;

	printf("��ȷ��ɾ��������ϵ����(����ȷ����ɾ��������ϵ��,���������������)��");
	cin >> whether;
	if (whether == "ȷ��") {
		i->size = 0;
	} else {
		return;
	}

	printf("ɾ���ɹ�!\n");
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
			printf("��л����ʹ�ã��ټ���\n");
			system("pause");
			exit(1);
			break;
		default:
			printf("���������е�ѡ�\n");
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