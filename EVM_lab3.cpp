#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define size 4
using namespace std;

int main()
{
	signed short int mtx[size][size];
	signed short int temp[size][size];
	signed short int sum[size];

	cout << "Enter matrix 4x4\n";
	for (int i = 0; i < size; i++) //заполняем матрицу
	{
		cout << "Enter " << i << " row: ";
		for (int j = 0; j < size; j++)
			cin >> mtx[i][j];
	}
	for (int i = 0; i < size; i++) //транспанируем матрицу в отдельный массив для вычисления сумм строк
		for (int j = 0; j < size; j++)
			temp[i][j] = mtx[j][i];
	_asm
	{
		mov ecx, size //счётчик 
		mov ebx, 0	//начальное смещение
		cycl:
		movq mm1, temp[ebx] //перемещаем "строку" в регистр mmx
		paddw mm0, mm1 //складываем регистры
		add ebx, 2 * size //увеличиваем смещение на размер массива * размер типа данных
		loop cycl
		movq[sum], mm0 //перемещаем результат в sum
	}

	cout << "Original sum\n";
	for (int i = 0; i < size; i++)
		printf("%d ", sum[i]);
	cout << '\n';

	_asm
	{
			/*Используем сортировку пузырьком*/

		mov ecx, size - 1	//счётчик внешнего цикла сортировки...
		ext:
		push ecx	//...заносим в стек
		mov ebx, 0	//начальное смещение
		mov ecx, size - 1	//счётчик внутреннего цикла сортировки
			inter:
			mov ax, sum[ebx]	//перемещаем элемент(изначальный) sum с смещением ebx в ax 
			add ebx, 2	//увеличиваем смещение на размер типа данных (2)
			cmp sum[ebx], ax	//сравниваем изначальный элемент со следующим элементом sum
			jg next1	//если меньше 'перепрыгиваем вызов подпрограммы'
			call swaping	//иначе вызываем свап
			next1:
	        loop inter	//зациливание внутреннего цикла
		pop ecx		//извлечение счётцика внешнего цикла из стека
		loop ext	//зациливание внешнего цикла
		jmp ending	//'прыжок' в конец
		    swaping:	//подпрограмма обмена
			mov dx, sum[ebx]	//перемещаем в dx элемент sum 
			mov sum [(ebx - 2)], dx	//перемещаем из dx на место изначального элемента со смещением минус размер типа данных
		    mov sum[ebx], ax	//перемещаем на текущий элемент sum предыдущий из ax
			sar ebx, 1	//смещаем в право(делим на 2)
			movq mm0, mtx [ebx * 8]	//заносим cтроку соотвествующую текущей сумме(sum) в mm0
			dec ebx	//уменьшаем смещение на один
			movq mm1, mtx [ebx * 8]	//заносим cтроку соотвествующую изначальной сумме(sum) в mm1
			movq mtx[ebx * 8], mm0	//замещаем изначальную строку текущей
			inc ebx	//обратно, увеличиваем смещение на один
			movq mtx [ebx * 8], mm1 //замещаем текущую строку изначальной
			sal ebx, 1 //обратно, смещаем влево (умножаем на 2)
			ret	//выход из подпрограммы
		ending:
	}
	
	cout << "\nSorted matrix and sum\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << mtx[i][j] << ' ';
		cout << '\n';
	}
	cout << '\n';
	for (int i = 0; i < size; i++)
		printf("%d ", sum[i]);
	return 0;
}