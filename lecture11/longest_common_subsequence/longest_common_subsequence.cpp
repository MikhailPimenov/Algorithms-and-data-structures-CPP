#include "longest_common_subsequence.h"

void allocate_and_init(int length1, int length2, int*& fOut, int**& ffOut)
{
	fOut = new int[static_cast <unsigned> ((length1 + 1) * (length2 + 1))];
	for (int index = 0; index < (length1 + 1) * (length2 + 1); ++index)
		fOut[index] = 0;

	ffOut = new int* [static_cast <unsigned> (length1 + 1)];
	for (int index1 = 0; index1 < length1 + 1; ++index1)
		ffOut[index1] = fOut + (length2 + 1) * index1;

}
void delete_all(int*& f, int**& ff)
{
	delete[] ff;
	delete[] f;
}
int calculate_length(const int* sequence1, int length1,
	const int* sequence2, int length2, int** ff)
{
	for (int index1 = 1; index1 < length1 + 1; ++index1)
	{
		for (int index2 = 1; index2 < length2 + 1; ++index2)
		{
			if (sequence1[index1 - 1] == sequence2[index2 - 1])
				ff[index1][index2] = ff[index1 - 1][index2 - 1] + 1;
			else
				ff[index1][index2] = Common::max(ff[index1][index2 - 1], ff[index1 - 1][index2]);

			//            std::cout << ff[index1][index2] << ' ';
		}
		//        std::cout << '\n';
	}
	return ff[length1][length2];
}
void subsequence(const int* sequence1, int length1,
	int length2,
	const int** ff,
	int* subsequenceOut, int length)
{
	assert(subsequenceOut);

	int index1 = length1;
	int index2 = length2;
	int index = length - 1;

	while (index1 > 0 && index2 > 0)
	{
		assert(index1 - 1 >= 0);
		assert(index2 - 1 >= 0);
		if (ff[index1 - 1][index2] == ff[index1][index2 - 1])
		{
			if (ff[index1 - 1][index2 - 1] < ff[index1][index2])
			{
				assert(index >= 0);
				subsequenceOut[index] = sequence1[index1 - 1];
				//                std::cout << subsequenceOut[index];
				--index;
			}
			--index1;
			--index2;
		}
		else if (ff[index1 - 1][index2] > ff[index1][index2 - 1])
		{
			--index1;
		}
		else // ff[index1 - 1][index2] < ff[index1][index2 - 1]
		{
			assert(ff[index1 - 1][index2] < ff[index1][index2 - 1]);
			--index2;
		}
	}
}
int longest_common_subsequence(const int* sequence1, int length1,
	const int* sequence2, int length2,
	int*& subsequenceOut)
{
	int* f = nullptr;
	int** ff = nullptr;

	allocate_and_init(length1, length2, f, ff);
	int result = calculate_length(sequence1, length1, sequence2, length2, ff);
	subsequenceOut = new int[result];
	subsequence(sequence1, length1, length2, const_cast <const int**> (ff), subsequenceOut, result);
	delete_all(f, ff);

	return result;
}
