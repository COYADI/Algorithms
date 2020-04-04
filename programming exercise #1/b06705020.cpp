#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAXBUILDINGCNT = 1000;
struct Building
{
	int left;
	int height;
	int right;
};
class ThePoint
{
		int left = 0;
		int height = 0;

	public:
		ThePoint();
		ThePoint(int left, int height);
		~ThePoint();

	friend class Skyline;
};
ThePoint::ThePoint():left(0), height(0)
{
};
ThePoint::ThePoint(int left, int height)
{
	this->left = left;
	this->height = height;
}
ThePoint::~ThePoint()
{
	this->left = 0;
	this->height = 0;
};
class Skyline
{
	private:
		ThePoint* skyline = NULL;
		int capacity = 0;
		int currentCnt = 0;
	
	public:
		Skyline();
		Skyline(int capacity);
		~Skyline();
		void addToSkyline(ThePoint* currentPoint);
		void print();
		Skyline* merge(Skyline* operand);
	
	friend Skyline* divideAndConquer(Building buildings[], int LEFT, int RIGHT);
};
Skyline::Skyline():capacity(0),currentCnt(0)
{
};
Skyline::Skyline(int capacity)
{
	this->capacity = capacity;
	skyline = new ThePoint[capacity];
}
Skyline::~Skyline()
{
	delete[] skyline;
}
void Skyline::addToSkyline(ThePoint* currentPoint)
{
	if(this->currentCnt > 0 && skyline[currentCnt - 1].height == currentPoint->height)
		return;
	if(this->currentCnt > 0 && skyline[currentCnt - 1].left == currentPoint->left)
		if(currentPoint->height > skyline[currentCnt - 1].height)
		{
			skyline[currentCnt - 1].height = currentPoint->height;
			return;
		}
	skyline[currentCnt] = *currentPoint;
	currentCnt++;
}
Skyline* Skyline::merge(Skyline* operand)
{
	Skyline* result = new Skyline(this->capacity + operand->capacity);
	int thisHeight = 0, operandHeight = 0, thisNum = 0, operandNum = 0;
	while(thisNum < this->capacity && operandNum < operand->capacity)
	{
		if(this->skyline[thisNum].left < operand->skyline[operandNum].left)
		{
			thisHeight = this->skyline[thisNum].height;
			int maxHeight = thisHeight;
			if(operandHeight > thisHeight)
				maxHeight = operandHeight;
			result->addToSkyline(new ThePoint(this->skyline[thisNum].left, maxHeight));
			thisNum ++;
		}
		else
		{
			operandHeight = operand->skyline[operandNum].height;
			int maxHeight = operandHeight;
			if(thisHeight > operandHeight)
				maxHeight = thisHeight;
			result->addToSkyline(new ThePoint(operand->skyline[operandNum].left, maxHeight));
			operandNum ++;
		}
	}
	while(this->capacity > thisNum)
	{
		result->addToSkyline(&this->skyline[thisNum]);
		thisNum ++;
	}
	while(operand->capacity > operandNum)
	{
		result->addToSkyline(&operand->skyline[operandNum]);
		operandNum ++;
	}

	return result;
}
////
void Skyline::print()
{
	bool printed = false;
	for(int i = 0; i < this->capacity; i++)
	{
		if(!printed)
		{
			cout << this->skyline[i].left << " " << this->skyline[i].height;
			printed = true;
		}
		else if(this->skyline[i].left != 0)
		{
			if(this->skyline[i].height != 0 || this->skyline[i + 1].height != 0 || this->skyline[i + 2].height != 0)
				cout << " " << this->skyline[i].left << " " << this->skyline[i].height;
			else
				cout << " " << this->skyline[i].left;
		}	
			
	}
}

Skyline* divideAndConquer(Building buildings[] , int LEFT, int RIGHT)
{
	if(LEFT == RIGHT)
		{
			Skyline* result = new Skyline(2);
			result->addToSkyline(new ThePoint(buildings[LEFT].left, buildings[LEFT].height));
			result->addToSkyline(new ThePoint(buildings[LEFT].right, 0));
//			result->print();
			return result;
		}
	else
	{
		int MIDDLE = (LEFT + RIGHT) / 2;
//		cout << MIDDLE << LEFT << RIGHT;
		Skyline* leftSkyline = divideAndConquer(buildings, LEFT, MIDDLE);
//		leftSkyline->print();
		Skyline* rightSkyline = divideAndConquer(buildings, MIDDLE + 1, RIGHT);
//		rightSkyline->print();
		Skyline* result = leftSkyline->merge(rightSkyline);
//		result->print();
/*		delete[] leftSkyline;
		delete[] rightSkyline;
*/		return result;
	}
}

int main(int argc, char** argv){
	ifstream in(argv[1]);
  	streambuf *cinbuf = cin.rdbuf();
  	cin.rdbuf(in.rdbuf());

	int buildings = 0;
	cin >> buildings;
	Building* array = new Building[buildings];
	
	for(int i = 0; i < buildings; i++)
	{
		int left = 0, height = 0, right = 0;
		cin >> left >> height >> right;
		array[i] = {left, height, right};
	}
	
	int LEFT = 0, RIGHT = buildings  - 1;
	Skyline* result = divideAndConquer(array, LEFT, RIGHT);
	result->print();

	cin.rdbuf(cinbuf);
	return 0;
}
