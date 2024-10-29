#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include <string>
#include "sandpile.h"

using namespace std;

class BMPWriter {
public:
    static void save(const SandpileModel &model, const string &outputDir, int iteration);
};

#endif
