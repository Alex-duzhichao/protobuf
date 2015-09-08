#include <iostream>
#include <fstream>
#include <random>

#include "diceroll.pb.h"

using namespace std;

void add_diceroll(codelab::DiceSeries_DiceRoll* roll)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1,6);
	int dice1 = distribution(generator);
	int dice2 = distribution(generator);
	int value = dice1 + dice2;
	roll->set_value(value);
	roll->set_nickname("empty");	
}

int main(int argc, char *argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " DICE_FILE" << endl;
		return -1;
	}

	codelab::DiceSeries dice_series;
	fstream input((const char*) argv[1], ios_base::in | ios_base::binary);	
	if (!input) {
		cout << argv[1] << ": file not found. Creating new one" << endl;
	}
	else if (!dice_series.ParseFromIstream(&input) ){ 
		cerr << "error, todo parse current file" << endl;
		return -1;
	}

	// add diceroll
	add_diceroll(dice_series.add_rolls());

	{
		fstream output(argv[1], ios_base::out | ios_base::trunc | ios_base::binary);
		if (!dice_series.SerializeToOstream(&output)) {
			cerr << "failed to write dice series." << endl;
			return -1;
		}
	}
	
	
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
