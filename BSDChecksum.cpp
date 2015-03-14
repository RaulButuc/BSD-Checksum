/**
 *  BSDChecksum.cpp
 *  Purpose: Compute the checksum of a given stream of bytes using the BSD algorithm.
 *
 *  @author Raul Butuc.
 *  @version 1.0.0 14/03/2015
 */

#include <iostream>
#include <fstream>
#include <vector>

using std::ios;
using std::cout;
using std::vector;
using std::fstream;
using std::exception;

typedef char byte;

static vector<byte> readAllBytes(char const*);

int main(int argc, char* argv[]) {
  try {
    // If there is more than one argument (we ignore the default argv[0]), then throw an exception.
    if (argc != 2) {
      throw argc;
    }

    // Initialise the checksum with all bits set to zero; read the stream of bytes; set the begin iterator.
    int checksum = 0x0;
    vector<byte> bytes = readAllBytes(argv[1]);
    vector<byte>::iterator itBegin = bytes.begin();

    // Iterate through the stream of bytes and compute the checksum using the BSD algorithm.
    for (vector<byte>::iterator it = itBegin; it != bytes.end(); ++it) {
      checksum = (((checksum >> 1) + ((checksum & 1) << 15)) + (*it)) & 0xFFFF;
    }

    cout << "BSD Checksum for file " << argv[1] << " is: " << checksum << "\n";
  }
  catch (int numArgs) {
    cout << "You have entered " << (numArgs - 1) << " arguments instead of one (the file name)" << "\n";
  }
  catch (const exception& e) {
    cout << "Standard exception caught: " << e.what() << "\n";
  }

  system("pause");

  return 0;
}

/**
 *  Get the stream of bytes from a given file.
 *
 *  @param filename The name of the file in the current directory that is to be used.
 *  @return The stream of bytes to compute the checksum on.
 */
static vector<byte> readAllBytes(char const* filename) {
  fstream file(filename, ios::in | ios::binary | ios::ate);
  fstream::pos_type pos = file.tellg();

  vector<byte> bytes(pos);

  file.seekg(0, ios::beg);
  file.read(&bytes[0], pos);

  return bytes;
}