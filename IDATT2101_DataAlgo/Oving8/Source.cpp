#include "LZ.h"
#include <vector>
#include <string>
#include <iostream>

int main() {

	std::string path = "diverse.lyx";

	LZ lz(path);

	lz.compress();

	return 0;
}

