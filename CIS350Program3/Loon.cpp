/*
Author: Peter O'Donohue
Creation Date: 11/16/17
Modification Date: 11/21/17
Description: This program determines if a message can be broadcasted across a network of
high altitude balloons, each tasked with the goal of providing internet access to rural
and remote areas. A message must be able to reach every station within the network in
order for it to successfully broadcast, and to conserve battery each station can only 
communicate with the two stations closest to itself. If there is a tie in distance, the 
program will first select the western most station, and in the case that's a tie the
program will then select the southern most station. To utilize the program input
the number of stations on the first line(1 to 1000), and then input the X and Y 
coordinates(-20 to 20) of each station on the following line, separating each coordinate 
with a space. The program will then connect each station, forming the aerial network, and 
will then compute whether or not a message can be broadcasted across the entire network.
The program will then output a 'yes' or 'no' answer, indicating whether or not a message can
be broadcasted. It will finish by giving you the option to input another set of stations or 
exiting the program by inputting 0.
*/

#include <iostream>
#include <vector>
#include <cmath>

class Station
{
public:
	Station(int, int, int);
	void setAdjStation1(Station*);
	void setAdjStation2(Station*);
	int getId();
	int getXCoordinate();
	int getYCoordinate();
	Station* getAdjStation1();
	Station* getAdjStation2();
private:
	int id;
	int xCoordinate;
	int yCoordinate;
	Station* adjStation1;
	Station* adjStation2;
};
Station::Station(int stationNum, int xCoord, int yCoord)
{
	/*
	PRE: Takes 3 int arguments ranging from values (1 - 1000, -20 - 20, -20 - 20).
	POST: all private variables have been initialized to either default values or 
	values passed through the parameters.
	*/

	id = stationNum;
	xCoordinate = xCoord;
	yCoordinate = yCoord;
	adjStation1 = nullptr;
	adjStation2 = nullptr;
}
void Station::setAdjStation1(Station* adjStation)
{
	/*
	PRE: Takes a single argument of type Station*.
	POST: adjstation1 is set to nullptr or a memory address.
	*/

	adjStation1 = adjStation;
}
void Station::setAdjStation2(Station* adjStation)
{
	/*
	PRE: Takes a single argument of type Station*.
	POST: adjstation2 is set to nullptr or a memory address.
	*/

	adjStation2 = adjStation;
}
int Station::getId()
{
	/*
	PRE: Object's constructor successfully completed.
	POST: The value of id is returned to the function caller.
	*/

	return id;
}
int Station::getXCoordinate()
{
	/*
	PRE: Object's constructor successfully completed.
	POST: The value of xCoordinate is returned to the function caller.
	*/

	return xCoordinate;
}
int Station::getYCoordinate()
{
	/*
	PRE: Object's constructor successfully completed.
	POST: The value of yCoordinate is returned to the function caller.
	*/

	return yCoordinate;
}
Station* Station::getAdjStation1()
{
	/*
	PRE: Object's constructor successfully completed.
	POST: The value of adjStation1 is returned to the function caller.
	*/

	return adjStation1;
}
Station* Station::getAdjStation2()
{
	/*
	PRE: Object's constructor successfully completed.
	POST: The value of adjStation2 is returned to the function caller.
	*/

	return adjStation2;
}

class AerialNetwork
{
public:
	void addStation(int, int, int);
	void connectStations();
	void checkStationTraversal(Station, std::vector<int>&);
	void checkNetworkTraversal();
	void eraseNetwork();
	bool stationVisited(int id, std::vector<int> reachableStationList);
private:
	std::vector<Station> stationList;
};
void AerialNetwork::addStation(int id, int xCoord, int yCoord)
{
	/*
	PRE: Takes three int variables in the ranges (1 - 1000, -20 - 20, -20 - 20).
	POST: Object's private variable 'stationList' contains one more element.
	*/

	Station newStation(id, xCoord, yCoord);
	stationList.push_back(newStation);
}
void AerialNetwork::connectStations()
{
	/*
	PRE: Object's variable stationList size > 0
	POST: every element of StationList has their adjStation1 and adjStation2 != nullptr.
	*/

	float tempDistance = 0;
	float minDistance = 57; //max distance possible
	int tempAdjStation = 0;
	int adjStation = 0;

	for (int i = 0; i < stationList.size(); ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < stationList.size(); ++k)
			{
				if (i != k && (k + 1) != adjStation)
				{
					tempDistance += pow(abs(stationList[i].getXCoordinate() - stationList[k].getXCoordinate()), 2);
					tempDistance += pow(abs(stationList[i].getYCoordinate() - stationList[k].getYCoordinate()), 2);
					sqrt(tempDistance);
					if (tempDistance < minDistance)
					{
						minDistance = tempDistance;
						tempAdjStation = (k + 1);
					}
					else if (tempDistance == minDistance)
					{
						if (stationList[k].getXCoordinate() < stationList[tempAdjStation - 1].getXCoordinate())
						{
							tempAdjStation = (k + 1);
						}
						else if (stationList[k].getXCoordinate() == stationList[tempAdjStation - 1].getXCoordinate()
							    && stationList[k].getYCoordinate() < stationList[tempAdjStation - 1].getYCoordinate())
						{
							tempAdjStation = (k + 1);
						}
					}
					tempDistance = 0;
				}
			}
			adjStation = tempAdjStation;
			minDistance = 57;
			if (stationList.size() != 1)
			{
				if (j == 0)
					stationList[i].setAdjStation1(&stationList[adjStation - 1]);
				else
					stationList[i].setAdjStation2(&stationList[adjStation - 1]);
			}
		}
	}
}
void AerialNetwork::checkNetworkTraversal()
{
	/*
	PRE: connectStations successfully completed.
	POST: CheckStationTraversal executed on the first element in StationList if stationList.size() > 1. 
	'yes' or 'no' printed to screen. 
	*/

	std::vector<int> tempStationList;
	std::vector<int> reachableStations;
	for (int i = 0; i < stationList.size(); ++i)
		tempStationList.push_back(stationList[i].getId());
	if (tempStationList.size() == 1)
	{
		std::cout << "yes" << std::endl;
		return;
	}
	checkStationTraversal(stationList[0], reachableStations);
	if (reachableStations.size() != stationList.size())
	{
		std::cout << "no" << std::endl;
		return;
	}
	std::cout << "yes" << std::endl;
}
void AerialNetwork::checkStationTraversal(Station balloon, std::vector<int>& reachableStationList)
{
	/*
	PRE: Takes Station and vector<int> type variables. 
	POST: baloon's id value was pushed onto reachableStationList if stationVisited returns false.
	Recursive call on balloon's adjStation1 and adjStation2 variables if stationVisited returns
	false on either variable.
	*/

	if (!stationVisited(balloon.getId(), reachableStationList))
	{
		reachableStationList.push_back(balloon.getId());
	}
	if (!stationVisited(balloon.getAdjStation1()->getId(), reachableStationList))
		checkStationTraversal(*balloon.getAdjStation1(), reachableStationList);
	if (!stationVisited(balloon.getAdjStation2()->getId(), reachableStationList))
		checkStationTraversal(*balloon.getAdjStation2(), reachableStationList);
}
bool AerialNetwork::stationVisited(int id, std::vector<int> reachableStationList)
{
	/*
	PRE: Takes int and vector<int> variables.
	POST: Returns true if id is contained within reachableStationList, false otherwise.
	*/

	for (auto balloon : reachableStationList)
	{
		if (id == balloon)
			return true;
	}
	return false;
}
void AerialNetwork::eraseNetwork()
{
	/*
	PRE: object's constructor has successfully completed
	POST: stationList has been erased.
	*/

	stationList.erase(stationList.begin(), stationList.end());
}

int main()
{
	int numStations = 0;
	int xCoordinate = 0;
	int yCoordinate = 0;
	std::vector<int> stationCoordinates;
	AerialNetwork loonNetwork;

	std::cin >> numStations;
	do
	{
		for (int i = 0; i < numStations; ++i)
		{
			std::cin >> xCoordinate >> yCoordinate;
			loonNetwork.addStation(i + 1, xCoordinate, yCoordinate);
		}
		loonNetwork.connectStations();
		loonNetwork.checkNetworkTraversal();
		loonNetwork.eraseNetwork();
		std::cin >> numStations;
	} while (numStations != 0);

	return 0;
}
