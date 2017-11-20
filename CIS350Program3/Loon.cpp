/*
Author: Peter O'Donohue
Creation Date: 11/16/17
Modification Date: 11/19/17
Description: FILL IN
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
	id = stationNum;
	xCoordinate = xCoord;
	yCoordinate = yCoord;
	adjStation1 = nullptr;
	adjStation2 = nullptr;
}
void Station::setAdjStation1(Station* adjStation)
{
	adjStation1 = adjStation;
}
void Station::setAdjStation2(Station* adjStation)
{
	adjStation2 = adjStation;
}
int Station::getId()
{
	return id;
}
int Station::getXCoordinate()
{
	return xCoordinate;
}
int Station::getYCoordinate()
{
	return yCoordinate;
}
Station* Station::getAdjStation1()
{
	return adjStation1;
}
Station* Station::getAdjStation2()
{
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
	std::vector<Station> network;
};
void AerialNetwork::addStation(int id, int xCoord, int yCoord)
{
	Station newStation(id, xCoord, yCoord);
	network.push_back(newStation);
}
void AerialNetwork::connectStations()
{
	float tempDistance = 0;
	float minDistance = 57; //max distance possible
	int tempAdjStation = 0;
	int adjStation = 0;

	for (int i = 0; i < network.size(); ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < network.size(); ++k)
			{
				if (i != k && (k + 1) != adjStation)
				{
					tempDistance += pow(abs(network[i].getXCoordinate() - network[k].getXCoordinate()), 2);
					tempDistance += pow(abs(network[i].getYCoordinate() - network[k].getYCoordinate()), 2);
					sqrt(tempDistance);
					if (tempDistance < minDistance)
					{
						minDistance = tempDistance;
						tempAdjStation = (k + 1);
					}
					else if (tempDistance == minDistance)
					{
						if (network[k].getXCoordinate() < network[tempAdjStation - 1].getXCoordinate())
						{
							tempAdjStation = (k + 1);
						}
						else if (network[k].getXCoordinate() == network[tempAdjStation - 1].getXCoordinate() && network[k].getYCoordinate() < network[tempAdjStation - 1].getYCoordinate())
						{
							tempAdjStation = (k + 1);
						}
					}
					tempDistance = 0;
				}
			}
			adjStation = tempAdjStation;
			minDistance = 57;
			if (j == 0)
				network[i].setAdjStation1(&network[adjStation - 1]);
			else
				network[i].setAdjStation2(&network[adjStation - 1]);
		}
	}
}
void AerialNetwork::checkNetworkTraversal()
{
	std::vector<int> stationList;
	std::vector<int> reachableStations;
	for (int i = 0; i < network.size(); ++i)
		stationList.push_back(network[i].getId());
	if (stationList.size() == 1)
	{
		std::cout << "yes" << std::endl;
		return;
	}
	checkStationTraversal(network[0], reachableStations);
	if (reachableStations.size() != stationList.size())
	{
		std::cout << "no" << std::endl;
		return;
	}
	std::cout << "yes" << std::endl;
}
void AerialNetwork::checkStationTraversal(Station balloon, std::vector<int>& reachableStationList)
{
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
	for (auto balloon : reachableStationList)
	{
		if (id == balloon)
			return true;
	}
	return false;
}
void AerialNetwork::eraseNetwork()
{
	network.erase(network.begin(), network.end());
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
