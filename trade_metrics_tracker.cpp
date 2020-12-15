/* trade_metrics_tracker.cpp
 *
 * finds data such as trade volume and prices fluctuations
 * 
 * Brandon Yazdi
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <exception>
#include <cmath>
#include "csvstream.h"
using namespace std;

class Trader {
private:
	string file; //csv file to be analyzed

	map<string, pair<int, int>> volumes; // { resource, { buy_volume, sell_volume} }
	//public market volumes only! volume is total rss bought/sold during time

	map<string, pair<int, int>> monetary_volumes; // { resource, { buy_volume, sell_volume} }
	//public market volumes only! monetary_volume is total money used to buy/sell rss during time

	// make a date tracker variable

public:
	Trader(string csvin)
		: file(csvin) { }

	//getter functions



	//functions setting variables from init

	void modify_volumes(map<string, string> m) {
		if (stoi((*m.find("offer_type")).second) != 0) {
			return;
		}
		string rss = (*m.find("resource")).second;
		int qty = stoi((*m.find("quantity")).second);
		int price = stoi((*m.find("price")).second);
		string buysell = (*m.find("buy_or_sell")).second;

		if (volumes.find(rss) == volumes.end()) {
			volumes.insert({ rss,{0,0} });
			monetary_volumes.insert({ rss,{0,0} });
		}
		else {
			if (buysell == "buy") {
				(volumes[rss]).first += qty;
				(monetary_volumes[rss]).first += (qty * price);
			}
			if (buysell == "sell") {
				(volumes[rss]).second += qty;
				(monetary_volumes[rss]).second += (qty * price);
			}
		}
	}

	//init_trader is the function that is called to find all the metrics
	void init_trader() {
		csvstream in(file);
		map<string, string> row;
		while (in >> row) {
			//date check when implemented
			modify_volumes(row);
		}
	}
};

Trader init_metrics(string s) {
	Trader t = Trader(s);
	t.init_trader();
	return t;
}

int main(int argc, char** argv) {
	string filename = "trades-2020-12-14.csv";
	Trader t = init_metrics(filename);
}
