#include <iostream>
#include <math.h>
#include <utility>
#include <cfloat>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX_ISLAND_CNT = 100;
const double TEST_NUMBER = 1e-8;
int main(int argc, char** argv)
{
	ifstream in(argv[1]);
  	streambuf *cinbuf = cin.rdbuf();
  	cin.rdbuf(in.rdbuf());

	double adjMatrix[MAX_ISLAND_CNT][MAX_ISLAND_CNT];
	pair<int, int> sPathMatrix[MAX_ISLAND_CNT][MAX_ISLAND_CNT];
	int islandCnt = 0, special1 = 0, special2 = 0;
	double xAxis[MAX_ISLAND_CNT], yAxis[MAX_ISLAND_CNT];

	cin >> islandCnt >> special1 >> special2;
	for(int i = 0; i < islandCnt ; i++)
		cin >> xAxis[i] >> yAxis[i];
	
	double distance = DBL_MAX;
	for(int i = 0; i < islandCnt; i++)
		for(int j = 0; j < islandCnt; j++)
			adjMatrix[i][j] = distance;
	adjMatrix[0][0] = 0;

	for(int i = 0; i < islandCnt; i++)
	{
		for(int j = 0; j < islandCnt; j++)
		{
			int middleLand = max(i ,j) + 1;
			if(middleLand != special2) 
			{
                if(adjMatrix[i][middleLand] > adjMatrix[i][j] + hypot(xAxis[middleLand] - xAxis[j], yAxis[middleLand] - yAxis[j])) 
                {
                    adjMatrix[i][middleLand] = adjMatrix[i][j] + hypot(xAxis[middleLand] - xAxis[j], yAxis[middleLand] - yAxis[j]);
                    sPathMatrix[i][middleLand] = make_pair(i, j);
                }
            }
            if(middleLand != special1) 
            {
                if(adjMatrix[middleLand][j] > adjMatrix[i][j] + hypot(xAxis[middleLand]-xAxis[i], yAxis[middleLand]-yAxis[i])) 
                {
                    adjMatrix[middleLand][j] = adjMatrix[i][j] + hypot(xAxis[middleLand]-xAxis[i], yAxis[middleLand]-yAxis[i]);
                    sPathMatrix[middleLand][j] = make_pair(i, j);
                }
            }
		}
	}
	for(int i = 0; i < islandCnt; i++) 
	{
        distance = min(distance, adjMatrix[i][islandCnt - 1] + hypot(xAxis[islandCnt-1]-xAxis[i], yAxis[islandCnt-1]-yAxis[i]));
        distance = min(distance, adjMatrix[islandCnt - 1][i] + hypot(xAxis[islandCnt-1]-xAxis[i], yAxis[islandCnt-1]-yAxis[i]));
    }

    pair<int, int> tempt;
    for(int i = 0; i < islandCnt; i++)
    {
    	if(fabs(adjMatrix[i][islandCnt - 1] + hypot(xAxis[islandCnt - 1] - xAxis[i], yAxis[islandCnt - 1] - yAxis[i]) - distance) < TEST_NUMBER)
    	{
    		tempt = make_pair(i, islandCnt - 1);
    		break;
    	}
    	if(fabs(adjMatrix[islandCnt - 1][i] + hypot(xAxis[islandCnt - 1] - xAxis[i], yAxis[islandCnt - 1] - yAxis[i]) - distance) < TEST_NUMBER)
    	{
    		tempt = make_pair(islandCnt - 1, i);
    		break;
    	}
    }

    int path1[MAX_ISLAND_CNT], path2[MAX_ISLAND_CNT], pivot1 = 0, pivot2 = 0;
    while(true) 
    {
        int island1 = tempt.first, island2 = tempt.second;
        tempt = sPathMatrix[island1][island2];
        if(island1 != tempt.first)
        {
            path1[pivot1] = island1;
            pivot1++;
        }
        else
        {
            path2[pivot2] = island2;
            pivot2++;
        }
        if(tempt.first == 0 && tempt.second == 0) {
            break;
        }
    }

    distance = distance * 100;
    distance = round(distance);
    distance = distance / 100;
    cout << fixed << setprecision(2) << distance;
    cout << ", 0";

    if(path2[pivot2 - 1] == 1)
    {
    	for(int i = pivot2 - 1; i >= 0; i--)
    		cout << " " << path2[i];
    	for(int i = 0; i < pivot1; i++)
    		cout << " " << path1[i];
    }
    else
    {
    	for(int i = pivot1 - 1; i >= 0; i--)
    		cout << " " << path1[i];
    	for(int i = 0; i < pivot2; i++)
    		cout << " " << path2[i];
    }
    cout << " 0";

    cin.rdbuf(cinbuf);
	return 0;
}
