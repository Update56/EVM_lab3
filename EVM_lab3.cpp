#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define size 4
using namespace std;

int main()
{
	int sz = size, nol = 0;
	int schet = 0;
	unsigned int ncx;
    signed short int mtx[size][size];
	printf("Enter matrix 4x4\n");
	for (int i = 0; i < size; i++)
	{
		printf("Enter %i row: ", i);
		for (int j = 0; j < size; j++)
		{
			int k;
			scanf("%d", &k);
			mtx[i][j] = k;
		}
	}
	signed short int temp[size][size];
	signed short int sum[size];
	for (int i = 0; i < size; i++) //транспанируем матрицу
		for (int j = 0; j < size; j++)
			temp[i][j] = mtx[j][i];
	_asm
	{
		mov ecx, [sz]
		mov eax, 0
		mov ebx, 0
		cycl:
		movq mm1, temp [ebx]
		paddw mm0, mm1
		add ebx, type sum * size
		loop cycl
		movq [sum], mm0
	//	lea edx, sum //заносим адрес массива
	//	mov ecx, 3
	//	ext:
	//	mov ebx, nol //начальное смещение
	//		inter:
	//		mov eax, [edx + ebx * type sum]
	//		inc ebx
	//		cmp eax, [edx + ebx * type sum]
	//		jle next1
	//		call swaping
	//		next1:
	//		cmp sz - 1, ebx 
	//      jge inter
	//	loop ext
	//	jmp ending
	//	swaping: 
	//		xchg eax, [edx + ebx * type sum]
	//		mov [edx + (ebx - 1) * type sum], eax
	//		movq mm0, mtx [type sum * size * (ebx - 1)]
	//		movq mm1, mtx [type sum * size * ebx]
	//		movq mtx [type sum * size * ebx], mm0
	//		movq mtx [type sum * size * (ebx - 1)], mm1
	//		mov ncx, type mtx / size
	//		ret
	//	ending:
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (sum[j] > sum[j+1])
			{
				swap(sum[j], sum[j + 1]);
				_asm 
				{
					movq mm0, [mtx + type sum * size * j]
					movq mm1, [mtx + type sum * size * j + 1]
					movq [mtx + type sum * size * j], mm0
					movq [mtx + type sum * size * (j + 1)], mm1
				}
			}
		}
	}



	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", mtx[i][j]);
		printf("\n");
	}
	printf("%d %d %d %d ", sum[0], sum[1], sum[2], sum[3]);
	cout << schet;
	return 0;
}