#include "RandBST.cpp"
#include <ctime>
#include <iostream>
using namespace std;

#define KeyType int
#define DataType int

int main()
{
	
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	

	RandBST<KeyType, DataType> tree;

	BST<KeyType, DataType>::Iterator iter;
	BST<KeyType, DataType>::ReverseIterator riter;

	bool isExit = false;

	cout << "-1. �����" << endl;
	cout << "0. �������� ������" << endl;
	cout << "1. ����� ������� ������" << endl;
	cout << "2. ������� ������" << endl;
	cout << "3. �������� ������ �� �������" << endl;
	cout << "4. ������ �� ������ � ������ �� �����" << endl;
	cout << "5. ������ �� ������ � ������ �� �����" << endl;
	cout << "6. ��������� ������ � �������� ������" << endl;
	cout << "7. �������� ������ � �������� ������" << endl;
	cout << "8. ������������ ������ ������ � ������" << endl;
	cout << "9. (���) ����������� ����������� ������ ��� �������� � �������� ������" << endl;
	cout << "������ ��������:" << endl;
	cout << "\t10. ������ ������� ��������� begin()" << endl;
	cout << "\t11. �������� ������� �� ������ � ������ �������� ����" << endl;
	cout << "\t12. �������� ������� �� ������ � ������ �������� ����" << endl;
	cout << "\t13. �������� ���������� ��� �������� � ���������� �� ����� ���� � ������" << endl;
	cout << "\t14. �������� ���������� ��� �������� � ����������� �� ����� ���� � ������" << endl;
	cout << "\t15. �������� ��������� ���������� ���������� (iter � end)" << endl;
	cout << "\t16. �������� ����������� ���������� ���������� (iter � begin)" << endl;
	cout << "�������� ��������:" << endl;
	cout << "\t17. ������ ��������� ��������� rbegin()" << endl;
	cout << "\t18. �������� ������� �� ������ � ������ �������� ����" << endl;
	cout << "\t19. �������� ������� �� ������ � ������ �������� ����" << endl;
	cout << "\t20. �������� ���������� ��� �������� � ����������� �� ����� ���� � ������" << endl;
	cout << "\t21. �������� ���������� ��� �������� � ���������� �� ����� ���� � ������" << endl;
	cout << "\t22. �������� ��������� ���������� ���������� (riter � rend)" << endl;
	cout << "\t23. �������� ����������� ���������� ���������� (riter � rbegin)" << endl;
	cout << "24. ����� ����� ����� ������, ������������� ���������� ���������\n" << endl;

	while (!isExit)
	{
		int ans;
		cin >> ans;
		try
		{
			switch (ans)
			{
			case -1:
				isExit = true;
				break;
			case 0:
			{
				cout << "0 - �������� ������(�����)\n1 - ������\n2 - ������\n3 - �����\n4 - ���������� �������\n";
				int choice;
				cin >> choice;
				switch (choice) {
				case 0:
					cout << "�����(����):\n";
					tree.show_keyweight();
					break;
				case 1:
					cout << "�����:\n";
					tree.show_keys();
					break;
				case 2:
					cout << "������:\n";
					tree.show_data();
					break;
				case 3:
					cout << "����:\n";
					tree.show_weight();
					break;
				case 4:
					cout << "���������� ������:\n";
					tree.show_numbers();
					break;
				}
				cout << "\n";
				break;
			}
			case 1:
			{
				cout << tree.getSize() << endl;
				break;
			}
			case 2:
			{
				tree.clear();
				break;
			}
			case 3:
			{
				cout << tree.isEmpty() << endl;
				break;
			}
			case 4:
			{
				KeyType key;
				cout << "������ �� �����" << endl;
				cout << "������� ����: ";
				cin >> key;

				try {
					cout << *(tree.readwrite(key)) << endl;
				}
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 5:
			{
				KeyType key;
				DataType data;
				cout << "������ �� �����" << endl;
				cout << "������� ����: ";
				cin >> key;
				cout << "������� ������: ";
				cin >> data;
				//cout << tree.write(key, data) << endl;
				try {
					*(tree.readwrite(key)) = data;
				}
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 6:
			{
				KeyType key;
				DataType data;
				cout << "������� ����: ";
				cin >> key;
				cout << "������� ������: ";
				cin >> data;
				cout << tree.insert(key, data) << endl;
				break;
			}
			case 7:
			{
				KeyType key;
				cout << "�������� �� �����" << endl;
				cout << "������� ����: ";
				cin >> key;
				cout << tree.remove(key) << endl;
				break;
			}
			case 8:
			{
				tree.show_keylist();
				cout << endl;
				break;
			}
			case 9:
			{
				KeyType key;
				cout << "������� ����: ";
				cin >> key;
				cout << tree.getSerialNumber(key) << endl;
				break;
			}
			case 10:
			{
				iter = tree.begin();
				break;
			}
			case 11:
			{
				try { cout << *iter << endl; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 12:
			{
				DataType data;
				cout << "������� ������: ";
				cin >> data;
				try { *iter = data; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 13:
			{
				++iter;
				break;
			}
			case 14:
			{
				--iter;
				break;
			}
			case 15:
			{
				auto it2 = tree.end();
				cout << (it2 == iter) << endl;
				break;
			}
			case 16:
			{
				auto it2 = tree.begin();
				cout << (it2 != iter) << endl;
				break;
			}
			case 17:
			{
				riter = tree.rbegin();
				break;
			}
			case 18:
			{
				try { cout << *riter << endl; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 19:
			{
				DataType data;
				cout << "������� ������: ";
				cin >> data;
				try { *riter = data; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 20:
			{
				++riter;
				break;
			}
			case 21:
			{
				--riter;
				break;
			}
			case 22:
			{
				auto it2 = tree.rend();
				cout << (it2 == riter) << endl;
				break;
			}
			case 23:
			{
				auto it2 = tree.rbegin();
				cout << (it2 != riter) << endl;
				break;
			}
			case 24:
			{
				cout << tree.getStepCount() << endl;
				break;
			}
			default:
			{
				cout << "������� �������� ��������!" << endl;
				break;
			}
			}
		}
		catch (...)
		{
			cout << "Exception" << endl;
		}
	}
	
	return 0;

}



