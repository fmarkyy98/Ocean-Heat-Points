#include <iostream>

using namespace std;

struct field
{
	int temperature = -999;
	bool hotSpot = false;
};

struct rectSize
{
	int height = 0;
	int width = 0;
};

const int MAX_N = 1000;

field ocean[MAX_N][MAX_N];

rectSize rectangles[32];
int rectanglesCount = 0;

bool isHotSpot(int m, int n, int heigth, int width)
{
	bool result;
	if (m == 0 && n == 0) // topLeft Field
	{
		result = ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;            // right neighbour
	}
	else if (m == 0 && n == width - 1) // topRight Field
	{
		result = ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature;           // left neighbour
	}
	else if (m == heigth - 1 && n == 0) // botomLeft Field
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;       // right neighbour
	}
	else if (m == heigth - 1 && n == width - 1) // botomRight Field
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature;      // left neighbour
	}
	else if (m == 0)  // topRow except first and last.
	{
		result = ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature&&      // left neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;       // right neighbour
	}
	else if (n == 0) // leftColumn except top and botom.
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;       // right neighbour
	}
	else if (m == heigth - 1) // botomRow except first and last.
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature&&      // left neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;       // right neighbour
	}
	else if (n == width) // rightColumn except top and botom.
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature;      // left neighbour
	}
	else // not in any border.
	{
		result = ocean[m][n].temperature > ocean[m - 1][n].temperature&& // top neighbour
			ocean[m][n].temperature > ocean[m + 1][n].temperature&&      // botom neighbour
			ocean[m][n].temperature > ocean[m][n - 1].temperature&&      // left neighbour
			ocean[m][n].temperature > ocean[m][n + 1].temperature;       // right neighbour
	}
	return result;
}

void collectDivisors(int n)
{
	for (int i = 1; i <= sqrt(n); ++i)
	{
		if (n % i == 0)
		{
			rectangles[rectanglesCount].width = i;
			rectangles[rectanglesCount].height = n / i;
			++rectanglesCount;
		}
	}
	int actualRectanglesCount = rectangles[rectanglesCount - 1].width == rectangles[rectanglesCount - 1].height ? rectanglesCount - 1 : rectanglesCount;
	for (int i = actualRectanglesCount - 1; i >= 0; --i)
	{
		rectangles[rectanglesCount].width = rectangles[i].height;
		rectangles[rectanglesCount].height = rectangles[i].width;
		++rectanglesCount;
	}
}

bool isValidRectangleSize(int heigth, int width, int maxHeight, int maxWidth)
{
	bool result;
	result = heigth < maxHeight && width < maxWidth;
	return result;
}

int hotSpotCount(int x, int y, int n, int m)
{
	int result = 0;
	for (int i = x; i < n; ++i)
	{
		for (int j = y; j < m; ++j)
		{
			if (ocean[i][j].hotSpot)
			{
				++result;
			}
		}
	}
	return result;
}

int main()
{
	int heigth, width, rectArea;

	cin >> heigth >> width >> rectArea;
	collectDivisors(rectArea);

	for (int i = 0; i < heigth; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cin >> ocean[i][j].temperature;
		}
	}

	for (int i = 0; i <= heigth; ++i)
	{
		for (int j = 0; j <= width; ++j)
		{
			ocean[i][j].hotSpot = isHotSpot(i, j, heigth, width);
		}
	}

	int max = -1;
	int maxIndexRow = -1;
	int maxIndexColumn = -1;
	rectSize maxRectangleSize;
	for (int i = 0; i < rectanglesCount; ++i)
	{
		for (int j = 0; j <= heigth - rectangles[i].height; ++j)
		{
			for (int k = 0; k <= width - rectangles[i].width; ++k)
			{
				int currentHotSpotCount = hotSpotCount(j, k, j + rectangles[i].height, k + rectangles[i].width);
				if (max < currentHotSpotCount)
				{
					max = currentHotSpotCount;
					maxIndexRow = j;
					maxIndexColumn = k;
					maxRectangleSize.height = rectangles[i].height;
					maxRectangleSize.width = rectangles[i].width;
				}
			}
		}
	}

	std::cout << maxIndexRow +1 << " " << maxIndexColumn+1 << " " << maxIndexRow + maxRectangleSize.height << " " << maxIndexColumn + maxRectangleSize.width;

	return 0;
}