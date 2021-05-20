#include "matrix.h"
matrix<int> matrix_void();

int main()
{
	setlocale(LC_ALL, "rus");

	matrix<int> initializer_check({ {5, 6}, {3, 4}, {4, 5} }); //Проверка конструктора инициализации
	cout << "Конструктор инициализации:" << initializer_check << endl;
	int rows, cols;
	cin >> rows >> cols;
	matrix<int> mtr1(rows, cols); //Проверка конструктора с rows и cols
	cin >> mtr1;
	cout << "\nПроверка матрицы на треугольную:" << mtr1.is_angle() << endl;
	cout << "\nМаксимальный элемент: " << mtr1.find_max() << endl;
	cout << "\nМинимальный элемент: " << mtr1.find_min() << endl;
	cout << "\nКонструктор rows, cols и <<:\n" << mtr1 << endl; //Проверка оператора <<
	matrix<int> mtr2(mtr1); //Проверка конструктора копирования
	cout << "\nКонструктор копирования:\n" << mtr2 << endl;
	matrix<int> mtr3 = matrix_void(); //Проверка конструктора перемещения
	cin >> mtr2; //Проверка оператора дополнительного >>
	cout << "\n>>:\n" << mtr2 << endl;
	mtr3 = mtr2; //Проверка оператора присваивания
	cout << "\n=:\n" << mtr3 << endl;
	mtr3 += mtr2; //Проверка оператора +=
	cout << "\n+=:\n" << mtr3 << endl;
	mtr2 -= mtr3; //Проверка оператора -=
	cout << "\n-=:\n" << mtr2 << endl;
	mtr1.set_elem(1, 2, 4); //Проверка присваивания значения элементу
	cout << "\n" << mtr3.get_elem(1, 2) << endl; //Проверка метода get_elem()
	cout << "\n" << mtr1(1, 2) << endl; //Проверка оператора ()
	cout << "\n1 - квадратная, 0 - не квадратная: "<< mtr2.is_square() << endl; //Проверка матрицы на квадратную
	cout << "\nСумма 2х матриц:\n" << mtr3 + mtr2 << endl; //Проверка оператора+ mtr2 отрицательная
	cout << "\nРазность 2х матриц:\n" << mtr3 - mtr2 << endl; //Проверка оператора- mtr2 отрицательная
	cout << "\nПроизведение 2х матриц:\n" << mtr2 * mtr3 << endl; //Проверка оператора*
	matrix<double> matr(3, 3);
	cout << "Введите матрицу 3х3:" << endl;
	cin >> matr;
	cout << "\nСумма матрицы и числа:\n" << matr + 2 << endl; //Проверка оператора+ с числом
	cout << "\nРазность матрицы и числа:\n" << matr - 2 << endl; //Проверка оператора- с числом
	cout << "\nУмножение матрицы на число:\n" << matr * 2 << endl; //Проверка оператора* с числом
	cout << "\nДеление матрицы на число\n" << matr / 2 << endl; //Проверка оператора/ с числом
	cout << "Число строк в матрице #2: " << mtr2.get_rows() << endl; //Проверка метода get_rows - получение кол-ва строк
	cout << "Число столбцов в матрице #2: " << mtr2.get_columns() << endl; //Проверка метода get_columns - получение кол-ва столбцов
	
	//Проверка работы итератора
	matrix<int> mtr({ {1, 2}, {3, 4}, {5, 6} });
	cout << mtr << endl;
	matrix<int>::Iterator a(mtr); 

	cout << *a << endl; //Проверка оператора*
	++a; //Проверка префиксного инкремента
	cout << *a << endl;
	a.next(); //Проверка метода next()
	cout << a.value() << endl; //Проверка метода value()
	while (!a.is_end()) //Проверка метода is_end()
	{
		cout << *a << " ";
		a.next();
	}
	cout << "\n\n";
	for (matrix<int>::Iterator a = mtr.iterator_begin(); a != mtr.iterator_end(); ++a) //Проверка iterator _begin() и _end()
		cout << " " << *a;
	return 0;
}

matrix<int> matrix_void()
{
	matrix<int> v(3 , 3);
	return move(v);

}