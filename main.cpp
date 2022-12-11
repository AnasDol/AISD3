#include "RandBST.cpp"
#include <ctime>
#include <iostream>
using namespace std;

#define KeyType int
#define DataType int

int main()
{
	setlocale(LC_ALL, "rus");

	RandBST<KeyType, DataType> tree;

	BST<KeyType, DataType>::Iterator iter;
	BST<KeyType, DataType>::ReverseIterator riter;

	bool isExit = false;

	cout << "-1. Выход" << endl;
	cout << "0. Просмотр дерева" << endl;
	cout << "1. Опрос размера дерева" << endl;
	cout << "2. Очистка дерева" << endl;
	cout << "3. Проверка дерева на пустоту" << endl;
	cout << "4. Доступ по чтению к данным по ключу" << endl;
	cout << "5. Доступ по записи к данным по ключу" << endl;
	cout << "6. Включение данных с заданным ключом" << endl;
	cout << "7. Удаление данных с заданным ключом" << endl;
	cout << "8. Опрос числа узлов дерева, просмотренных предыдущей операцией" << endl;
	cout << "9. Тестирование" << endl;
	cout << "Прямой итератор:" << endl;
	cout << "\t10. Запрос прямого итератора begin()" << endl;
	cout << "\t11. Операция доступа по чтению к данным текущего узла" << endl;
	cout << "\t12. Операция доступа по записи к данным текущего узла" << endl;
	cout << "\t13. Операция инкремента для перехода к следующему по ключу узлу в дереве" << endl;
	cout << "\t14. Операция декремента для перехода к предыдущему по ключу узлу в дереве" << endl;
	cout << "\t15. Проверка равенства однотипных итераторов (iter и end)" << endl;
	cout << "\t16. Проверка неравенства однотипных итераторов (iter и begin)" << endl;
	cout << "Обратный итератор:" << endl;
	cout << "\t20. Запрос обратного итератора rbegin()" << endl;
	cout << "\t21. Операция доступа по чтению к данным текущего узла" << endl;
	cout << "\t22. Операция доступа по записи к данным текущего узла" << endl;
	cout << "\t23. Операция инкремента для перехода к предыдущему по ключу узлу в дереве" << endl;
	cout << "\t24. Операция декремента для перехода к следующему по ключу узлу в дереве" << endl;
	cout << "\t25. Проверка равенства однотипных итераторов (riter и rend)" << endl;
	cout << "\t26. Проверка неравенства однотипных итераторов (riter и rbegin)" << endl;

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
				cout << "0 - просмотр ключей(весов)\n1 - ключей\n2 - данных\n3 - весов\n";
				int choice;
				cin >> choice;
				switch (choice) {
				case 0:
					cout << "Ключи(веса):\n";
					tree.show_keyweight();
					break;
				case 1:
					cout << "Ключи:\n";
					tree.show_keys();
					break;
				case 2:
					cout << "Данные:\n";
					tree.show_data();
					break;
				case 3:
					cout << "Веса:\n";
					tree.show_weight();
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
				cout << "Чтение по ключу" << endl;
				cout << "Введите ключ: ";
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
				cout << "Запись по ключу" << endl;
				cout << "Введите ключ: ";
				cin >> key;
				cout << "Введите данные: ";
				cin >> data;
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
				cout << "Введите ключ: ";
				cin >> key;
				cout << "Введите данные: ";
				cin >> data;
				cout << tree.insert(key, data) << endl;
				break;
			}
			case 7:
			{
				KeyType key;
				cout << "Удаление по ключу" << endl;
				cout << "Введите ключ: ";
				cin >> key;
				cout << tree.remove(key) << endl;
				break;
			}
			case 8:
			{
				cout << tree.getStepCount() << endl;
				break;
			}
			case 9:
			{
				cout << "Итерация " << 1 << "" << endl;
				cout << "Тест трудоёмкости операций случайного дерева" << endl;
				test_rand(3000);
				cout << endl << "Тест трудоёмкости операций вырожденного дерева" << endl;
				test_ord(3000);
				cout << endl << "______________________________________" << endl << endl;
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
				cout << "Введите данные: ";
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
			case 20:
			{
				riter = tree.rbegin();
				break;
			}
			case 21:
			{
				try { cout << *riter << endl; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 22:
			{
				DataType data;
				cout << "Введите данные: ";
				cin >> data;
				try { *riter = data; }
				catch (...) { cout << "Exception" << endl; }
				break;
			}
			case 23:
			{
				++riter;
				break;
			}
			case 24:
			{
				--riter;
				break;
			}
			case 25:
			{
				auto it2 = tree.rend();
				cout << (it2 == riter) << endl;
				break;
			}
			case 26:
			{
				auto it2 = tree.rbegin();
				cout << (it2 != riter) << endl;
				break;
			}
			default:
			{
				cout << "Введено неверное значение!" << endl;
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
