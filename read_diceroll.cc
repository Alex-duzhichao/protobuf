#include <iostream>
#include <fstream>
#include "diceroll.pb.h"

using namespace std;
void ListDiceRolls(const codelab::DiceSeries& dice_series) {
	cout << "Number of rolls: " << dice_series.rolls_size() << endl;
	for (int i = 0; i < dice_series.rolls_size(); i++) {
		const codelab::DiceSeries_DiceRoll& roll = dice_series.rolls(i);
		cout << "Roll:" << i << " Value:" << roll.value();
		cout << " Nickname:" << (roll.has_nickname() ? roll.nickname() : "null") << endl;
	}
}

int main(int argc, char *argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
		return -1;
	}

	codelab::DiceSeries dice_series;
	{
		fstream input(argv[1], ios::in | ios::binary);
		if (!dice_series.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return -1;
		}
	}

	ListDiceRolls(dice_series);

	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
