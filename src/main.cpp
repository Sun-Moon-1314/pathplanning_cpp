#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "boost/algorithm/dijkstra/dijsktra_core.h"
#include "boost/algorithm/floyd/floyd_core.h"
#include "boost/utils/Log.h"


#ifndef RUN_TEST

int main(int argc, char* argv[]) {
	int choice;
	std::cout << "Choose a algorithm:\n";
	std::cout << "1: Dijkstra" << "\n";
	std::cout << "2: Floyd" << "\n";
	std::cout << "Please input: ";
	std::cin >> choice;
	switch (choice)
	{
	case 1: run_dijkstra();
	case 2: 
	default:
		std::cin.get();
	}
	
	//PROFILE_FUNCTION();
	std::cin.get();
	return 0;
}
#endif