/*%!@\$!@\$%&&\$#@%@^#%&\$**(\$%&%#\$%@#%^#@^&#@\$%#!@^@#^&@#^
░██████╗░█████╗░███╗░░░███╗██╗░░░██╗██████╗░░█████╗░██╗
██╔════╝██╔══██╗████╗░████║██║░░░██║██╔══██╗██╔══██╗██║
╚█████╗░███████║██╔████╔██║██║░░░██║██████╔╝███████║██║
░╚═══██╗██╔══██║██║╚██╔╝██║██║░░░██║██╔══██╗██╔══██║██║
██████╔╝██║░░██║██║░╚═╝░██║╚██████╔╝██║░░██║██║░░██║██║
╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝
^@#^@&@#%@*^%*&\$%^#\$^\$***%^#\$@%\$@#\$!@\$!@#\$%@#^@&@#%@#*/


#include "ImageReader.h"
#include "ImageWriter.h"
#include <iostream>
#include "IEncrypt.hpp"
#include <cryptopp/osrng.h>
#include <vector>
#include <utility>
#include <fstream>
#include <filesystem>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <algorithm>
#include <numeric>
#include <cryptopp/hex.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/ccm.h>
#include <cryptopp/base64.h>
#include <opencv2/opencv.hpp>
#include "AES256Encryption.h"
#include "NPCRTest.hpp"
#include "TestRunner.hpp"
#include "UACI.hpp"
#include "HammingDistanceTest.hpp"
#include "ChisquareTest.hpp"
#include "CorrelationTest.hpp"
#include "InformationEntropyTest.hpp"
#include "EncryptionQualityTest.hpp"
#include "TimePerformanceTest.hpp"
#include "LSB.hpp"
#include "IHide.hpp"
#include "Macros.h"
#include <string>
#include "UnitTest.hpp"
#include "PrepareTesting.cpp"
#include "menu.cpp"


#include "menu.cpp"

using namespace std;

signed main() {
    // send help pls;
    Utils::Clear();
    MainMenu();
}