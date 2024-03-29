#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream out("D:\out.txt");
ofstream out1("D:\out1.txt");
ofstream outTarget("D:\outTarget.txt");
typedef struct point { int x, y; char type; };

int Map1[5001][5001], Map2[5001][5001], Target[10002][10002];
int Lines[7][6001][6001];
int BMsize = 0, width, height, width1, height1, width2, height2, heightTarget, widthTarget;
char file[10];
#pragma region interface
void read_matrix1()
{
	char a[1000] = "D:\imaj";
	strcat(a, file);
	strcat(a, ".txt");
	ifstream f(a);
	f >> height1;
	f >> width1;
	for (int i = 0;i < height1;i++)
		for (int j = 0;j < width1;j++)
			f >> Map1[i][j];
}
void read_matrix2()
{
	char a[1000] = "D:\imaj";
	strcat(a, file);
	strcat(a, ".txt");
	ifstream f(a);
	f >> height2;
	f >> width2;
	for (int i = 0;i < height2;i++)
		for (int j = 0;j < width2;j++)
			f >> Map2[i][j];
}
void print_cute()
{
	ifstream in("aia_mare.txt");
	in >> height1;
	in >> width1;
	for (int i = 0;i < height1;i++)
		for (int j = 0;j < width1;j++)
			in >> Map1[i][j];
}
void printMap1()
{
	out << width1 << ' ' << height1 << '\n';
	for (int i = 0;i < height1;i++)
	{
		for (int j = 0;j < width1;j++)
		{
			/*if (!Map1[i][j])
				out << "  ";
			else*/
			out << Map1[i][j] << ' ';
			if (Map1[i][j] < 10) out << "  ";
			else if (Map1[i][j] < 100) out << " ";
		}
		out << '\n' << '\n' << '\n';
	}
}
void printMap2()
{
	for (int i = 0;i < height2;i++)
	{
		for (int j = 0;j < width2;j++)
		{
			if (!Map2[i][j])
				out1 << "  ";
			else
				out1 << Map2[i][j] << ' ';
			if (Map2[i][j] < 10) out1 << "  ";
			else if (Map2[i][j] < 100) out1 << " ";
		}
		out1 << '\n' << '\n' << '\n';
	}
}
void printTarget()
{
	outTarget << heightTarget << ' ' << widthTarget << '\n';
	for (int i = 0;i < heightTarget;i++)
	{
		for (int j = 0;j < widthTarget;j++)
		{
			if (Target[i][j] == 2)
				outTarget << "  ";
			else
				outTarget << Target[i][j] << ' ';
			if (Target[i][j] < 10) outTarget << "  ";
			else if (Target[i][j] < 100) outTarget << " ";
		}
		outTarget << '\n';
	}
}
void printLine(int act_line)
{
	out << Lines[0][act_line][2] << ' ' << Lines[0][act_line][1] << '\n';
	for (int i = 0;i < Lines[0][act_line][1];i++)
	{
		for (int j = 0;j < Lines[0][act_line][2];j++)
		{
			out << Lines[act_line][i][j] << ' ';
			if (Lines[act_line][i][j] < 10) out << "  ";
			else if (Lines[act_line][i][j] < 100) out << " ";
		}
		out << '\n' << '\n' << '\n';
	}
}
/*void readBMP_RGB()
{
	ifstream f("input.txt");
	int a;
	f >> width;
	f >> height;
	while (BMsize <= 3 * width*height)
	{

		f >> a;
		BMap[++BMsize] = a;
	}
}
void print_RGB()
{
	ofstream r("red.txt");
	ofstream g("green.txt");
	ofstream b("blue.txt");
	out << width << ' ' << height << '\n';
	for (int i = 0;i < BMsize;i++)
	{

		out << BMap[i] << ' ';
		b << BMap[i] << ' ';
		if (BMap[i] < 10) b << "  ";
		else if (BMap[i] < 100) b << " ";
		g << BMap[++i] << ' ';
		if (BMap[i] < 10) g << "  ";
		else if (BMap[i] < 100) g << " ";
		r << BMap[++i] << ' ';
		if (BMap[i] < 10) r << "  ";
		else if (BMap[i] < 100) r << " ";


		if (i % width == 2)
		{
			r << '\n';
			g << '\n';
			b << '\n';
		}
	}
}*/
#pragma endregion

#pragma region normalize
void normalizeIsolatedPoints(int map)
{
	if (map == 1)
	{
		for (int i = 0;i < height1;i++)
			for (int j = 0;j < width1;j++)
				if (Map1[i][j] != Map1[i - 1][j] &&
					Map1[i][j] != Map1[i + 1][j] &&
					Map1[i][j] != Map1[i][j - 1] &&
					Map1[i][j] != Map1[i][j + 1])
					Map1[i][j] = 0;
		if (map == 2)
		{
			for (int i = 0;i < height2;i++)
				for (int j = 0;j < width2;j++)
					if (Map2[i][j] != Map2[i - 1][j] &&
						Map2[i][j] != Map2[i + 1][j] &&
						Map2[i][j] != Map2[i][j - 1] &&
						Map2[i][j] != Map2[i][j + 1])
						Map2[i][j] = 0;
		}
	}
}

void normalizeDeadEnds(int map)
{
	int ok = 0;
	if (map == 1)
	{
		while (!ok)
		{
			ok = 1;
			for (int i = 0;i < height1;i++)
				for (int j = 0;j < width1;j++)
				{
					int c = 0;
					if (Map1[i - 1][j] == Map1[i][j]) c++;
					if (Map1[i + 1][j] == Map1[i][j]) c++;
					if (Map1[i][j - 1] == Map1[i][j]) c++;
					if (Map1[i][j + 1] == Map1[i][j]) c++;
					if (c < 2 && Map1[i][j])
					{
						Map1[i][j] = 0;
						ok = 0;
					}
				}
		}
	}
	if (map == 2)
	{
		while (!ok)
		{
			ok = 1;
			for (int i = 0;i < height2;i++)
				for (int j = 0;j < width2;j++)
				{
					int c = 0;
					if (Map2[i - 1][j] == Map2[i][j]) c++;
					if (Map2[i + 1][j] == Map2[i][j]) c++;
					if (Map2[i][j - 1] == Map2[i][j]) c++;
					if (Map2[i][j + 1] == Map2[i][j]) c++;
					if (c < 2 && Map2[i][j])
					{
						Map2[i][j] = 0;
						ok = 0;
					}
				}
		}
	}
}

void normalizeRectangles(int map)
{
	int ok = 0;
	if (map == 1)
		while (!ok)
		{
			ok = 1;
			for (int i = 1;i < height1;i++)
				for (int j = 1;j < width1;j++)
				{
					if (Map1[i][j] == 0 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] >= 510)
					{
						Map1[i][j] = 255;
						ok = 0;
					}

					if (Map1[i][j] == 255 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] < 510)
					{
						Map1[i][j] = 0;
						ok = 0;
					}

					int c50 = 0;
					if (Map1[i - 1][j] == 50) c50++;
					if (Map1[i + 1][j] == 50) c50++;
					if (Map1[i][j - 1] == 50) c50++;
					if (Map1[i][j + 1] == 50) c50++;
					if (Map1[i][j] != 50 && c50 >= 2)
					{
						Map1[i][j] = 50;
						ok = 0;
					}

					int c100 = 0;
					if (Map1[i - 1][j] == 100) c100++;
					if (Map1[i + 1][j] == 100) c100++;
					if (Map1[i][j - 1] == 100) c100++;
					if (Map1[i][j + 1] == 100) c100++;
					if (Map1[i][j] != 100 && c100 >= 2)
					{
						Map1[i][j] = 100;
						ok = 0;
					}

				}
		}
	if (map == 2)
		while (!ok)
		{
			ok = 1;
			for (int i = 0;i < height2;i++)
				for (int j = 0;j < width2;j++)
				{
					if (Map2[i][j] == 0 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] >= 510)
					{
						Map2[i][j] = 255;
						ok = 0;
					}

					if (Map2[i][j] == 255 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] < 510)
					{
						Map2[i][j] = 0;
						ok = 0;
					}

					int c50 = 0;
					if (Map2[i - 1][j] == 50) c50++;
					if (Map2[i + 1][j] == 50) c50++;
					if (Map2[i][j - 1] == 50) c50++;
					if (Map2[i][j + 1] == 50) c50++;
					if (Map2[i][j] != 50 && c50 >= 2)
					{
						Map2[i][j] = 50;
						ok = 0;
					}

					int c100 = 0;
					if (Map2[i - 1][j] == 100) c100++;
					if (Map2[i + 1][j] == 100) c100++;
					if (Map2[i][j - 1] == 100) c100++;
					if (Map2[i][j + 1] == 100) c100++;
					if (Map2[i][j] != 100 && c100 >= 2)
					{
						Map2[i][j] = 100;
						ok = 0;
					}

				}
		}
}

void normalize()
{
	normalizeIsolatedPoints(1);
	normalizeIsolatedPoints(2);
	normalizeRectangles(1);
	normalizeRectangles(2);
	normalizeDeadEnds(1);
	normalizeDeadEnds(2);
	normalizeRectangles(1);
	normalizeRectangles(2);
}
#pragma endregion

#pragma region utility
/*int minim(int a, int b)
{
	if (a < b) return a;
	return b;
}
int maxim(int a, int b)
{
	if (a > b) return a;
	return b;
}*/
point DetectTopLeft(int pic)
{
	int i, j;
	point P;
	int mini = 100000;
	if (!pic)
	{
		for (i = height2;i <= height1 + height2;i++)
			for (j = width2;j <= width1 + width2;j++)
				if (mini > i + j && Target[i][j] != 0 && Target[i][j] != 255)
				{
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					mini = i + j;
				}
	}
	else
	{
		for (i = 0;i < height2;i++)
			for (j = 0;j < width2;j++)
				if (mini > i + j && Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					mini = i + j;
				}
	}
	return P;
}
point DetectTopRight(int pic)
{
	int i, j;
	point P;
	int maxi = 0;
	if (!pic)
	{
		for (i = height2;i <= height1 + height2;i++)
			for (j = width1 + width2;j >= width2;j--)
				if (i-height2<j-width2 && (j - width2) - (i- height2)>maxi && Target[i][j] != 0 && Target[i][j] != 255)
				{
					while (Target[i][j] == Target[i][j - 1])
						j--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					maxi = j - i;
				}
	}
	else
	{
		for (i = 0;i < height2;i++)
			for (j = width2 - 1;j >= 0;j--)
				if (i<j && j - i>maxi && Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					while (Map2[i][j] == Map2[i][j - 1])
						j--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					maxi = j - i;
				}
	}
	return P;
}
point DetectBottomLeft(int pic)
{
	int i, j;
	point P;
	if (!pic)
	{
		for (i = height1 + height2;i >= height2;i--)
			for (j = width2;j <= width1 + width2;j++)
				if (Target[i][j] != 0 && Target[i][j] != 255)
				{
					while (Target[i][j] == Target[i - 1][j])
						i--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
	else
	{
		for (i = height2;i >= 1;i--)
			for (j = 1;j <= width2;j++)
				if (Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					while (Map2[i][j] == Map2[i - 1][j])
						i--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
}
point DetectBottomRight(int pic)
{
	int i, j;
	point P;
	if (!pic)
	{
		for (i = height1 + height2;i >= height2;i--)
			for (j = width1 + width2;j >= width2;j--)
				if (Target[i][j] != 0 && Target[i][j] != 255)
				{
					while (Target[i][j] == Target[i - 1][j])
						i--;
					while (Target[i][j] == Target[i][j - 1])
						j--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
	else
	{
		for (i = height2;i >= 1;i--)
			for (j = width2;j >= 1;j--)
				if (Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					while (Map2[i][j] == Map2[i][j - 1])
						j--;
					while (Map2[i][j] == Map2[i - 1][j])
						i--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
}
void createLine(int line)
{
	int i, j, i1, j1;
	if (line % 2 == 0)
	{
		for (i = height1 - 1;i >= 0;i--)
			for (j = 0;j < width1;j++)
				Lines[line][j][height1-i-1] = Map1[i][j];

		Lines[0][line][1] = width1;
		Lines[0][line][2] = height1;
	}
	else
	{
		for (i = 0;i < width1 ;i++)
			for (j = 0;j < width1;j++)
				Lines[line][i][j] = Map1[j][width1 -i+1];
		Lines[0][line][1] = width1;
		Lines[0][line][2] = height1;
		cout << '\n'<<'\n' << '\n'<<height1<<' '<<width1;
	}

}
#pragma endregion

#pragma region compute
void create_target()
{
	int i, j;
	heightTarget = 2 * height2 + height1;
	widthTarget = 2 * width2 + width1;
	for (i = 0;i <= heightTarget;i++)
		for (j = 0;j <= widthTarget;j++)
			Target[i][j] = 0;
	for (i = height2;i < height1 + height2;i++)
		for (j = width2;j < width1 + width2;j++)
			Target[i][j] = Map1[i - height2][j - width2];

}
void merge()
{
	int i, i1, j1, j;
	int startx, starty, stopx, stopy;
	create_target();
#pragma region point aquisition
	point Pattern_TopLeft, Pattern_TopRight, Pattern_BottomLeft, Pattern_BottomRight;
	point Sticker_TopLeft, Sticker_TopRight, Sticker_BottomLeft, Sticker_BottomRight;
	Pattern_TopLeft = DetectTopLeft(0);
	Sticker_TopLeft = DetectTopLeft(1);
	Pattern_TopRight = DetectTopRight(0);
	Sticker_TopRight = DetectTopRight(1);
	//to fix
	/*Pattern_BottomLeft = DetectBottomLeft(0);
	Sticker_BottomLeft = DetectBottomLeft(1);
	Pattern_BottomRight = DetectBottomRight(0);
	Sticker_BottomRight = DetectBottomRight(1);*/
	//to fix
	cout << Pattern_TopLeft.x << ' ' << Pattern_TopLeft.y << '\n' << Sticker_TopRight.x << ' ' << Sticker_TopRight.y << '\n';
#pragma endregion
#pragma region Horizontal
	/*for (int i = 0;i < heightTarget;i++)
	{
		for (int j = 0;j < widthTarget;j++)
		{
			out << Target[i][j] << ' ';
			if (Target[i][j] < 10) out << "  ";
			else if (Target[i][j] < 100) out << " ";
		}
		out << '\n';
	}*/
	if (Pattern_TopLeft.type == Sticker_TopRight.type)
	{
		for (i = Pattern_TopLeft.x - (height2 - (height2 - Sticker_TopRight.x)), i1 = Sticker_TopRight.x - (height2 - (height2 - Sticker_TopRight.x));
		i <= Pattern_TopLeft.x + (height2 - Sticker_TopRight.x), i1 <= height2;
			i++, i1++)
			for (j = Pattern_TopLeft.y + (width2 - Sticker_TopRight.y), j1 = Sticker_TopRight.y + (width2 - Sticker_TopRight.y);
		j >= Pattern_TopLeft.y - Sticker_TopRight.y, j1 >= 0;
			j--, j1--)
				Target[i][j] = Map2[i1][j1];
	}
	startx = height1;
	stopx = Pattern_TopLeft.x + (height2 - Sticker_TopRight.x);
	starty = Pattern_TopLeft.y - Sticker_TopRight.y;
	stopy = width1 + width2;
	for (i = height1;i <= stopx;i++)
		for (j = starty;j <= stopy;j++)
			Map1[i - startx][j - starty] = Target[i][j];
	height1 = stopx - startx;
	width1 = stopy - starty;
#pragma endregion
#pragma region Vertical
	if (Pattern_TopLeft.type == Sticker_TopRight.type)
	{

	}
#pragma endregion


}

#pragma endregion
int main()
{
	strcpy(file, "3");
	read_matrix1();
	strcpy(file, "2");
	read_matrix2();

	normalize();
	merge();
	strcpy(file, "1");
	read_matrix2();
	normalize();
	merge();
	normalize();
	createLine(1);
	//printMap2();
	//printMap1();
	strcpy(file, "6");
	read_matrix1();
	strcpy(file, "5");
	read_matrix2();
	normalize();
	merge();
	strcpy(file, "4");
	read_matrix2();
	normalize();
	merge();
	normalize();
	//printMap1();
	createLine(2);
	for (int i = 0;i < Lines[0][2][1];i++)
		for (int j = 0;j < Lines[0][2][2];j++)
			Map1[i][j] = Lines[2][i][j];

	for (int i = 0;i < Lines[0][1][1];i++)
		for (int j = 0;j < Lines[0][1][2];j++)
			Map2[i][j] = Lines[1][i][j];
	height1 = Lines[0][2][1];
	width1 = Lines[0][2][2];
	height2 = Lines[0][1][1];
	width2 = Lines[0][1][2];
	cout << height1 << ' ' << width1 << '\n' << height2 << ' ' << width2;
	//printLine(2);
	merge();
	normalize();
	printMap1();

	return 0;
}