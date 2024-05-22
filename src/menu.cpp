#ifndef MENU_CPP
#define MENU_CPP

#include "Utils.hpp"
#include "ErrorHandler.cpp"
#include "LogMacros.h"
#include "FileLister.cpp"
#include "Utils.hpp"
#include "../Database/DatabaseConnection.cpp"
#include "../Database/UserManagement.cpp"
#include "../Database/SessionManagement.cpp"
#include <mysql/mysql.h>
// #include <dotenv.h>


string _DEFAULT_PATH = "../assets/";
MYSQL *connection = nullptr;
DatabaseConnection *dbConnection=nullptr;

DatabaseConnection* InitializeDB() {
    // try {
        const char* server = getenv("DB_SERVER");
        const char* user = getenv("DB_USER");
        const char* password = getenv("DB_PASSWORD");
        const char* database = getenv("DB_DATABASE");

        auto con = DatabaseConnection::getInstance(server, user, password, database);
        if (!con) {
            throw CustomException("Failed to connect to the database");
        } 
    // } catch(const CustomException &ex) {
    //     Utils::print("Failed to connect to Database.","Red");
    //     Utils::print("Session ending...","Yellow");
    //     Utils::DelaySeconds(3);
    //     // return;
    // }
    return con;
}
void AssignUserKey(CryptoPP::SecByteBlock& key, string keyInput, size_t keyLength = 16) {
    if (keyInput.length() != keyLength) {
        throw CustomException("Invalid key length. Expected " + to_string(keyLength) + " characters.");
    }
    key.CleanNew(keyLength);
    memcpy(key.data(), keyInput.data(), keyLength);
}

void displayKeyOptions(CryptoPP::SecByteBlock &key) {
    KeyOptions:
        Utils::Clear();
        Utils::print("Please choose which any of the following key lengths:", "Yellow");
        Utils::print("1. 128-bit","Magnetta");
        Utils::print("2. 192-bit","Magnetta");
        Utils::print("3. 256-bit (Recommended)","Magnetta");
        short choice; cin >> choice;
        Utils::Clear();
        string keyInput;
        try {
            Utils::print("Kindly. enter the key.","Magnetta");
            if(choice == 1) {
                cin >> keyInput;
                const size_t chosenSize = 16;
                if(keyInput.size() != chosenSize) {
                    throw CustomException("You should pass " + to_string(chosenSize) + " characters.");
                }
                AssignUserKey(key,keyInput, chosenSize);
            } else if(choice == 2) {
                cin >> keyInput;
                const size_t chosenSize = 24;
                if(keyInput.size() != chosenSize) {
                    throw CustomException("You should pass " + to_string(chosenSize) + " characters.");
                }
                AssignUserKey(key,keyInput, chosenSize);
            } else if(choice == 3) {
                cin >> keyInput;
                const size_t chosenSize = 32;
                if(keyInput.size() != chosenSize) {
                    throw CustomException("You should pass " + to_string(chosenSize) + " characters.");
                }
                AssignUserKey(key,keyInput, chosenSize);
            } else {
                LOG_ERROR("User entered an invalid number.");
                throw CustomException("Invalid choice."); 
            }
            //used for printing the key. delete.
            for (size_t i = 0; i < key.size(); ++i) {
                cout << key[i];
            }
            cout << endl;
        }
        catch(const CustomException &ex ) {
            Utils::print(string(ex.what()),"Red");
            Utils::DelaySeconds(3);
            Utils::Clear();
            goto KeyOptions;
        }
}
void AuthMenu() {
    dbConnection = InitializeDB();
    connection = dbConnection->getConnection();
    Utils::print("Connected to DB!","Green");
    Utils::DelaySeconds(3);
    SessionManagement ManageSession(*dbConnection);
    UserManagement ManageUser(*dbConnection);
    Utils::Clear();
    while (true) {
    Utils::print("1. Register", "White");
    Utils::print("2. Login", "White");
    short choice;
    cin >> choice;
    string username, password, firstName, secondName;
    switch (choice) {
        case 1:
            Utils::Clear();
            Utils::print("Enter username: ", "Magnetta");
            cin >> username;
            Utils::Clear();
            Utils::print("Enter password: ", "Magnetta");
            cin >> password;
            Utils::Clear();
            Utils::print("Enter first name: ", "Magnetta");
            cin >> firstName;
            Utils::Clear();
            Utils::print("Enter second name: ", "Magnetta");
            cin >> secondName;
            Utils::Clear();
            if (ManageUser.Register(username, password, firstName, secondName)) {
                 Utils::print("Registration successful.", "Yellow");
            } else {
                Utils::print("Registration failed.", "Yellow");
            }
            Utils::DelaySeconds(3);
            Utils::Clear();
            break;
        case 2:
            Utils::Clear();
            Utils::print("Enter username: ", "Magnetta");
            cin >> username;
            Utils::Clear();
            Utils::print("Enter password: ", "Magnetta");
            cin >> password;
            Utils::Clear();
            if (ManageUser.Login(username, password)) {
                auto user_id = ManageUser.GetUserID(username);
                if (user_id && ManageSession.CreateSession(*user_id)) {
                    Utils::print("Login successful. Session started. ENJOY!","Yellow");
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                    return;
                    // if (ManageSession.IsValidSession(*user_id)) {
                    //     cout << "Session is valid.\n";
                    // } else {
                    //     cout << "Session is invalid.\n";
                    // }
                } else {
                    LOG_ERROR("Failed to create the session");
                    Utils::print("Failed to create session.","Red");
                    Utils::DelaySeconds(3);
                    Utils::Clear();

                }
            } else {
                LOG_ERROR("Login failed.");
                Utils::print("Login failed.","Red");
            }
            break;
        default:
            Utils::Clear();
            Utils::print("Invalid option. Please try again.","Yellow");
    }
            Utils::DelaySeconds(3);
            Utils::Clear();
    }
}

void MainMenu() {
    AuthMenu();
    short choice;
    ImageReader reader;
    ImageWriter writer;
    string key;
    auto lsb = make_shared<LSB>();

    auto iHideEncryptionStrategy = make_unique<AES256Encryption>();
    auto iHideEncryptor = make_shared<IEncrypt>(move(iHideEncryptionStrategy));

    IHide service(lsb, iHideEncryptor);

    IEncrypt iEncrypt(make_unique<AES256Encryption>());




    // auto aesenc = make_unique<AES256Encryption>();
    // auto iEncryptptr = make_shared<AES256Encryption>();
    // IHide service(lsb,iEncryptptr);
    // IEncrypt iHideEncryption(iEncryptptr);
    // IEncrypt iEncrypt(make_unique<AES256Encryption>()); // as we're just interested in the AES encryption.
    // cout << IEncrypt::checkIsInstantiated() << endl;
    Utils::Clear();
    while (true) {
        Utils::print("1. Encrypt image");
        Utils::print("2. Decrypt image");
        Utils::print("3. Test my image \xF0\x9F\x94\xA5");
        Utils::print("4. Embed Text into the image");
        Utils::print("5. Retrieve info from the image");
        Utils::print("6. Exit");
        
        // cin >> choice;
        try {
            choice = Utils::getValidChoice(6);
        } catch(const CustomException &ex) {
            Utils::Clear();
            Utils::print(string(ex.what()),"Red");
            LOG_ERROR(string(ex.what()));
            Utils::DelaySeconds(2);
            Utils::Clear();
            continue;
        }
        Utils::Clear();
        // IHide service(make_shared<LSB>());
        switch(choice) {
            case 1: {
                caseOne1:
                    Utils::print("1. Link to an existing image", "c");
                    Utils::print("2. Generate a random image.","Magnetta");
                    Utils::print("3. Choose from the existing images in your directory.","Magnetta");
                    cin >> choice;
                    cv::Mat img;
                    Utils::Clear();
                    string outputFile;
                    if(choice == 1) {
                        caseOne2:
                            Utils::print("1. Grey scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            caseOnePath:
                                Utils::print("Kindly, enter the path of target image.","Magnetta");
                                string path; cin >> path;
                                Utils::Clear();
                                if(choice == 1) {
                                    try {
                                        img = reader.ReadImage(path, false);
                                        outputFile = Utils::SplitAndReturnLastPart(path);
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseOnePath;
                                    }
                                } else if(choice == 2) {
                                    try {
                                        img = reader.ReadImage(path);
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseOnePath;
                                    }
                                } else {
                                    try {
                                        throw CustomException("Invalid option.");
                                    } catch (const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseOne2;
                                    }
                                }
                    } else if(choice == 2) {
                        colorEnc:
                            Utils::Clear();
                            Utils::print("1. Gray scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            int imgChannels = 1;
                            if(choice == 1) {
                                imgChannels = 1;
                            } else if(choice == 2) {
                                imgChannels = 3;
                            } else {
                                try {
                                    throw CustomException("Invalid option.");
                                } catch(const CustomException &ex) {
                                    Utils::print(string(ex.what()),"Red");
                                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto colorEnc;
                                }
                            }
                            mathEnc:
                                Utils::Clear();
                                Utils::print("Enter the width and height respectively.","Magnetta");
                                ll width, height; cin >> width >> height;
                                if(width <= 0 || height <=0) {
                                    try {
                                        throw CustomException("Width and height must be greater than 0");
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto mathEnc;
                                    }
                                }
                            Utils::Clear();
                            Utils::print("Please choose a pattern.", "Yellow");
                            Utils::print("1. Gradient", "Magnetta");
                            Utils::print("2. Shapes", "Magnetta");
                            Utils::print("3. Noise With Patterns", "Magnetta");
                            Utils::print("4. Pure Noise", "Magnetta");
                            Utils::print("5. Perlin Noise", "Magnetta");
                            Utils::print("6. Fractal", "Magnetta");
                            Utils::print("7. Marble", "Magnetta");
                            Utils::print("8. Combination", "Magnetta");
                            cin >> choice;
                            patternEnc:
                                Utils::Clear();
                                string pattern,IMGTYPE = (imgChannels == 1? "Grey scale" : "Colored");
                                try {
                                    if(choice == 1) {
                                        pattern = "Gradient";
                                        img = Utils::GenerateGradientImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 2) {
                                        pattern = "Shapes";
                                        img = Utils::GenerateShapeImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 3) {
                                        pattern = "Noise With Patterns";
                                        img = Utils::GenerateNoisePatternImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 4) {
                                        pattern = "Pure Noise";
                                        img = Utils::GenerateRandomImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 5) {
                                        pattern = "Perlin Noise";
                                        img = Utils::GeneratePerlinNoiseImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 6) {
                                        pattern = "Fractal";
                                        img = Utils::GenerateMandelbrotImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 7) {
                                        pattern = "Marble";
                                        img = Utils::GenerateMarbleTextureImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 8) {
                                        pattern = "Combination";
                                        img = Utils::GenerateCombinedPatternImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    }
                                    else {
                                        throw CustomException("Invalid Option");
                                    }
                                } catch(const CustomException &ex) {
                                    Utils::print(string(ex.what()),"Red");
                                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto patternEnc;
                                }
                                Utils::Clear();
                                writer.WriteImage(_DEFAULT_PATH, img);
                                Utils::print("Image has been printed.","Yellow");
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                    }
                    else if(choice == 3) {
                        Utils::Clear();
                        caseOne3:
                            auto filteredFiles = FileLister::listFilesInDirectory(_DEFAULT_PATH);
                            ll o(0);
                            for(const auto &el : filteredFiles) {
                                cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                            }
                            Utils::print("Enter which file you want.","Magnetta");

                            try {
                                choice = Utils::getValidChoice(filteredFiles.size());
                            } catch(const CustomException &ex) {
                                Utils::Clear();
                                Utils::print(string(ex.what()),"Red");
                                LOG_ERROR(string(ex.what()));
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseOne3;
                            }

                            auto it = filteredFiles.begin() + (choice-1);
                            outputFile =*it;

                            try {
                                img = reader.ReadImage(_DEFAULT_PATH+*it,cv::IMREAD_UNCHANGED);
                            } catch(const CustomException &ex) {
                                Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                                LOG_ERROR("USER ERROR:" + string(ex.what()));
                                LOG_INFO((img.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it);
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseOne3;                           
                            }

                    } else {
                        try {
                            throw CustomException("Invalid option.");
                        } catch(const CustomException &ex) {
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseOne1;
                        }
                    }
                Utils::Clear();
                Utils::print("1. Enter an existing key.","Magnetta");
                Utils::print("2. Generate a new key.","Magnetta");
                cin >> choice;
                Utils::Clear();
                CryptoPP::SecByteBlock key;
                if(choice == 1) {
                makeKey2:
                    Utils::print("Kindly, input your key.","Magnetta");
                    // LOG_WARNING("Kindly, input your key.");
                    // cin >> key;
                    try {
                        displayKeyOptions(key);
                    } catch(const CustomException &ex){
                        Utils::Clear();
                        LOG_ERROR(string(ex.what()));
                        Utils::print(string(ex.what()),"Red");
                        Utils::DelaySeconds(3);
                        Utils::Clear();
                        goto makeKey2;
                    }
                    iEncrypt.changeKey(key);
                    Utils::print("Key has been set.", "Yellow");
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                }
                else if(choice == 2) {
                    KeyOptions:
                        Utils::Clear();
                        Utils::print("Please choose which any of the following key lengths:", "Yellow");
                        Utils::print("1. 128-bit","Magnetta");
                        Utils::print("2. 192-bit","Magnetta");
                        Utils::print("3. 256-bit (Recommended)","Magnetta");
                        short choice; cin >> choice;
                        Utils::Clear();
                        try {
                            if(choice == 1) {
                                const size_t chosenSize = 16;
                                iEncrypt.AssignRandomKey(key);
                            } else if(choice == 2) {
                                const size_t chosenSize = 24;
                                iEncrypt.AssignRandomKey(key,2);
                            } else if(choice == 3) {
                                const size_t chosenSize = 32;
                                iEncrypt.AssignRandomKey(key,3);
                            } else {
                                LOG_ERROR("User entered an invalid number.");
                                throw CustomException("Invalid choice."); 
                            }
                        }
                    // LOG_INFO("Key has been generated");
                    // LOG_INFO(Utils::SecByteBlockToBase64String(iEncrypt.getKey()));
                    // LOG_INFO(Utils::testBlock(iEncrypt.getKey()));
                    // cout << "Key has been generated\n You can see the key in the logs.\n";
        catch(const CustomException &ex ) {
            Utils::print(string(ex.what()),"Red");
            Utils::DelaySeconds(3);
            Utils::Clear();
            goto KeyOptions;
        }
                    Utils::Clear();
                    Utils::print("Key has been generated\n You can see the key in the logs.","Yellow");
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                }
                else {
                    // LOG_ERROR("Invalid option. A key has been generated.");
                    LOG_ERROR("USER ERROR: invalid input, a key has been generated.");
                    Utils::Clear();
                    Utils::print("Invalid option. A key has been generated.","Yellow");
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                }
                // Utils::Clear();
                dist3:
                    Utils::print("Wish to modify the image? (change one bit)","Magnetta");
                    Utils::print("1. Yes.\n2. No","Magnetta");
                    // cin >> choice;
                    string newChoice; cin >> newChoice;
                    Utils::Clear();
                    if(newChoice == "1" || newChoice == "Yes") {
                        Utils::ModifyImage(img); //og img
                        Utils::print("Image has been modified.","Yellow");
                        Utils::DelaySeconds(3);
                        Utils::Clear();
                    } else if(newChoice == "2" || newChoice == "No") {
                        Utils::print("Image will remain the same.","Yellow");
                        Utils::DelaySeconds(3);
                        Utils::Clear();
                    }  else {
                        Utils::print("Invalid option.","Red");
                        Utils::DelaySeconds(5);
                        goto dist3;
                    }
                    dist4:
                        Utils::print("Wish to modify the key? (One arbitrary bit only).","Magnetta");
                        Utils::print("1. Yes.\n2. No","Magnetta");
                        cin >> newChoice;
                        Utils::Clear();
                        if(newChoice == "1" || newChoice == "Yes") {
                            CryptoPP::SecByteBlock modifiedKey = Utils::ModifyKey(iEncrypt.getKey());
                            iEncrypt.changeKey(modifiedKey);
                            Utils::print("Key has been modified.","Yellow");
                            Utils::DelaySeconds(3);
                            Utils::Clear();
                        } else if(newChoice == "2" || newChoice == "No") {
                            Utils::print("Key will remain the same.","Yellow");
                            Utils::DelaySeconds(3);
                            Utils::Clear();
                        }  else {
                            Utils::print("Invalid option.","Red");
                            Utils::DelaySeconds(3);
                            Utils::Clear();
                            //delay here.
                            goto dist4;
                        }
                    
                    cv::Mat encryptedImage = iEncrypt.Encrypt(img);
                    const auto currentFileName = Utils::SplitStringIntoPair(outputFile,'.');
                    writer.WriteImage(_DEFAULT_PATH + currentFileName.first + "." + currentFileName.second,encryptedImage);
                    break;
            }
            case 2: {
                caseTwo1:
                    Utils::print("1. Link to an existing image","Magnetta");
                    Utils::print("2. Generate a random image.","Magnetta");
                    Utils::print("3. Choose from the existing images in your directory.","Magnetta");
                    cin >> choice;
                    cv::Mat img;
                    string outputName;
                    if(choice == 1) {
                        caseTwo2:
                            Utils::print("1. Grey scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            caseTwoPath:
                                Utils::print("Kindly, enter the path of target image.","Magnetta");
                                string path; cin >> path;
                                Utils::Clear();
                                if(choice == 1) {
                                    try {
                                        img = reader.ReadImage(path, false);
                                        outputName = Utils::SplitAndReturnLastPart(path);
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseTwoPath;
                                    }
                                } else if(choice == 2) {
                                    try {
                                        img = reader.ReadImage(path);
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseTwoPath;
                                    }
                                } else {
                                    try {
                                        throw CustomException("Invalid option.");
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto caseTwo2;
                                    }
                                }
                    } else if(choice == 2) {
                        colorDec:
                            Utils::Clear();
                            Utils::print("1. Gray scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            int imgChannels = 1;
                            if(choice == 1) {
                                imgChannels = 1;
                            } else if(choice == 2) {
                                imgChannels = 3;
                            } else {
                                try {
                                    throw CustomException("Invalid option.");
                                } catch(const CustomException &ex) {
                                    Utils::print(string(ex.what()),"Red");
                                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto colorDec;
                                }
                            }

                            mathDec:
                                Utils::Clear();
                                Utils::print("Enter the width and height respectively.","Magnetta");
                                ll width, height; cin >> width >> height;
                                if(width <= 0 || height <=0) {
                                    try {
                                        throw CustomException("Width and height must be greater than 0");
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto mathDec;
                                    }
                                }
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            Utils::print("Please choose a pattern.", "Yellow");
                            Utils::print("1. Gradient", "Magnetta");
                            Utils::print("2. Shapes", "Magnetta");
                            Utils::print("3. Noise With Patterns", "Magnetta");
                            Utils::print("4. Pure Noise", "Magnetta");
                            cin >> choice;
                            patternDec:
                                Utils::Clear();
                                string pattern,IMGTYPE = (imgChannels == 1? "Grey scale" : "Colored");
                                try {
                                    if(choice == 1) {
                                        pattern = "Gradient";
                                        img = Utils::GenerateGradientImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 2) {
                                        pattern = "Shapes";
                                        img = Utils::GenerateShapeImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 3) {
                                        pattern = "Noise With Patterns";
                                        img = Utils::GenerateNoisePatternImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 4) {
                                        pattern = "Pure Noise";
                                        img = Utils::GenerateRandomImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 5) {
                                        pattern = "Perlin Noise";
                                        img = GraphicsUtils::GeneratePerlinNoiseImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 6) {
                                        pattern = "Fractal";
                                        img = Utils::GenerateMandelbrotImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 7) {
                                        pattern = "Marble";
                                        img = Utils::GenerateMarbleTextureImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    } else if(choice == 8) {
                                        pattern = "Combination";
                                        img = Utils::GenerateCombinedPatternImage(width,height,imgChannels);
                                        Utils::print("Your Grey " + IMGTYPE + " has been generated. \n Pattern: " + pattern,"Yellow");
                                    }
                                    else {
                                        throw CustomException("Invalid Option");
                                    }
                                } catch(const CustomException &ex) {
                                    Utils::print(string(ex.what()),"Red");
                                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto patternDec;
                                }
                                Utils::Clear();
                                writer.WriteImage(_DEFAULT_PATH, img);
                                Utils::print("Image has been printed.","Yellow");
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                    } else if(choice == 3) {
                        Utils::Clear();
                        caseTwo5:
                            auto filteredFiles = FileLister::listFilesInDirectory(_DEFAULT_PATH);
                            ll o(0);
                            for(const auto &el : filteredFiles) {
                                cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                            }
                            // cout << "Enter which file you want.\n"; // name of the file only. other could be handled but meeeh
                            Utils::print("Enter which file you want.","Magnetta");
                            // string imagePath; cin >> imagePath;
                            try {
                                choice = Utils::getValidChoice(filteredFiles.size());
                            } catch(const CustomException &ex) {
                                Utils::Clear();
                                Utils::print(string(ex.what()),"Red");
                                LOG_ERROR(string(ex.what()));
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseTwo5;
                            }
                            
                            auto it = filteredFiles.begin() + (choice-1);
                            outputName =*it;

                            try {
                                img = reader.ReadImage(_DEFAULT_PATH+*it,cv::IMREAD_UNCHANGED);
                            } catch(const CustomException &ex) {
                                Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                                LOG_ERROR("USER ERROR:" + string(ex.what()));
                                LOG_INFO((img.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it);
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseTwo5;                           
                            }
                    } else {
                        try {
                            throw CustomException("Invalid option.");
                        } catch(const CustomException &ex) {
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseTwo1;
                        }
                    }
                Utils::Clear();
                dist5:
                    Utils::print("1. Enter an existing key.","Magnetta");
                    Utils::print("2. Decrypt using cached keys.","Magnetta");
                    Utils::print("\t |==+=+==> Works only upon saved sessions, else you need to save the key used.","Blue");
                    cin >> choice;
                    Utils::Clear();
                    CryptoPP::SecByteBlock key;
                    if(choice == 1) {
                        dist:
                            makeKey:
                                Utils::print("Kindly, input your key.","Magnetta");
                            // LOG_WARNING("Kindly, input your key.");
                                // cin >> key;
                                try {
                                    displayKeyOptions(key);
                                } catch(const CustomException &ex){
                                    Utils::Clear();
                                    LOG_ERROR(string(ex.what()));
                                    Utils::print(string(ex.what()),"Red");
                                    Utils::DelaySeconds(3);
                                    Utils::Clear();
                                    goto makeKey;
                                }
                            iEncrypt.changeKey(key);
                    }
                    else if(choice == 2) {
                        // generateKey(key);
                        // LOG_INFO("Key has been generated");
                        if(IEncrypt::checkIsInstantiated()) {
                            if(iEncrypt.isNotCached()) {
                                Utils::print("No work has been cached. Please enter a key.","Red");
                                Utils::DelaySeconds(3);
                                Utils::Clear();
                                goto dist;
                            }
                        }
                        // Utils::print("Key has been generated.","Yellow");
                    }
                    else {
                        // generateKey(key);
                        // LOG_ERROR("Invalid option. A key has been generated.");
                        // cout <<"Invalid option. A key has been generated." << endl;
                        try {
                            throw CustomException("Invalid Option.");
                        } catch(const CustomException &ex) {
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto dist5;
                        }
                    }
                const auto currentFileName = Utils::SplitStringIntoPair(outputName,'.');
                cv::Mat decryptedImg = iEncrypt.Decrypt(img);
                writer.WriteImage(_DEFAULT_PATH + currentFileName.first + "." + currentFileName.second,decryptedImg,false);
                break;
            }
            case 3: {
                cv::Mat image1,image2;
                dist2:
                    Utils::print("1. Plain Sensitivity.","Magnetta");
                    Utils::print("2. Key Sensitivity.","Magnetta");
                    cin >> choice;
                    if(choice > 2 || choice <=0) {
                        try {
                            throw CustomException("Invalid Option.");
                        } catch(const CustomException &ex) {
                            Utils::Clear();
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                            Utils::DelaySeconds(3);
                            Utils::Clear();
                            goto dist2;
                        }
                    }
                    Utils::Clear();
                    // Utils::print("Kindly, provide us with the paths of these respectively:\n - Non-Encrypted Image \n - Encrypted Version of the same Image.","Magnetta");
                    // string path1,path2; cin >> path1 >> path2;
                    // cv::Mat image1 = reader.ReadImage("../assets/BaboonRGB.bmp"); 
                    // cv::Mat image2 = reader.ReadImage("../assets/EncryptedImage.bmp"); // change into path
                    caseThree1:
                        Utils::print("Please choose 2 files maximum to perform the tests on.", "Magnetta");
                        auto filteredFiles = FileLister::listFilesInDirectory(_DEFAULT_PATH);
                        ll o(0);
                        for(const auto &el : filteredFiles) {
                            cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                        }
                            // cout << "Enter which file you want.\n"; // name of the file only. other could be handled but meeeh
                            Utils::print("Enter which file you want.","Magnetta");
                            // string imagePath; cin >> imagePath;
                            ll choice1,choice2;
                                try {
                                Utils::print("Number of the first file:","Yellow");
                                choice1 = Utils::getValidChoice(filteredFiles.size());
                                Utils::print("Number of the second file:","Yellow");
                                choice2 = Utils::getValidChoice(filteredFiles.size());
                            } catch(const CustomException &ex) {
                                Utils::Clear();
                                Utils::print(string(ex.what()),"Red");
                                LOG_ERROR(string(ex.what()));
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseThree1;
                            }

                            // Utils::print("Number of the first file:","Yellow");
                            // cin >> choice1;
                            // Utils::print("Number of the second file:","Yellow");
                            // cin >> choice2;
                            // try {
                            //     if((choice1 > filteredFiles.size() && choice1 > 0) || (choice2 > filteredFiles.size() && choice2 > 0)) {
                            //         throw CustomException("Please use a valid number.");
                            //     }
                            // } catch(const CustomException &ex) {
                            //     Utils::print(string(ex.what()),"Red");
                            //     LOG_ERROR("User has given an out of bound number.");
                            //     Utils::DelaySeconds(2);
                            //     Utils::Clear();
                            //     goto caseThree1;
                            // }
                            auto it1 = filteredFiles.begin() + (choice1-1);
                            auto it2 = filteredFiles.begin() + (choice2-1);
                        try {
                            image1 = reader.ReadImage(_DEFAULT_PATH+*it1,cv::IMREAD_UNCHANGED);
                            image2 = reader.ReadImage(_DEFAULT_PATH+*it2,cv::IMREAD_UNCHANGED);
                        } catch(const CustomException &ex) {
                            Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                            LOG_INFO((image1.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it1);
                            LOG_INFO((image2.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it2);
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseThree1;                           
                        }
                    Utils::Clear();
                    Utils::print("Kindly, enter how many required tests you need.","Magnetta");
                    ll tc; cin >> tc;
                    Utils::Clear();
                    Utils::print("Kindly, select the required tests.","Magnetta");
                    Utils::print("Available tests:\n 1. NPCR \n 2. UACI \n 3. Hamming Distance \n 4. Chisquare \n 5. Information Entropy \n 6. Encryption Quality \n 7. Time Performanec \n 8. All tests","Magnetta");
                    vector<bool> selected(7,false);
                    Utils::print("Enter the number associated with each test","Magnetta");
                    ll savetc = tc;
                    while(tc--) {
                        Utils::Clear();
                        Utils::print("Available tests:\n 1. NPCR \n 2. UACI \n 3. Hamming Distance \n 4. Chisquare \n 5. Information Entropy \n 6. Encryption Quality \n 7. Time Performanec \n 8. All tests\n","Magnetta");
                        Utils::print("Selected Tests" + to_string(savetc - (tc + 1)) + '/' + to_string(savetc),"Yellow");
                        ll num; cin >> num;
                        if(num == 8) {
                            for(int o  =0; o < selected.size();o++)
                                selected[o] = true;
                            break;
                        }
                        if(num >= selected.size() || num <= 0) {
                            Utils::Clear();
                            Utils::print("Please input a valid number.","Red");
                            Utils::DelaySeconds(3);
                            tc++;
                        } else {
                            if(selected[num]) {
                                Utils::Clear();
                                Utils::print("You already have chosen this test. Please consider checking on an another test.","Red");
                                Utils::DelaySeconds(3);
                                tc++;
                                continue;
                            }
                            selected[num] = true;
                        }
                    }
                    Utils::Clear();
                    if(choice == 1) {
                        PrepareTesting us(image1,image2,iEncrypt);
                        us.InitalizeTests(selected);
                        us.RunSelectedTests();
                    } else if(choice == 2) {
                        PrepareTesting us(image1,image2,iEncrypt);
                        us.InitalizeTests(selected);
                        us.RunSelectedTests();

                    } else {
                        Utils::print("Bad input.","Red");
                        goto dist2;
                    }
                    break;
            }
            case 4: {
                cv::Mat img;
                caseFour1:
                    auto filteredFiles = FileLister::listFilesInDirectory(_DEFAULT_PATH);
                    ll o(0);
                    for(const auto &el : filteredFiles) {
                        cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                    }
                        Utils::print("Enter which file you want.","Magnetta");
                        try {
                            choice = Utils::getValidChoice(filteredFiles.size());
                        } catch(const CustomException &ex) {
                            Utils::Clear();
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR(string(ex.what()));
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseFour1;
                        }
                        auto it = filteredFiles.begin() + (choice-1);

                    try {
                        img = reader.ReadImage(_DEFAULT_PATH+*it,cv::IMREAD_UNCHANGED);
                    } catch(const CustomException &ex) {
                        Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                        LOG_INFO((img.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it);
                        Utils::DelaySeconds(2);
                        Utils::Clear();
                        goto caseFour1;
                    }
                    Utils::Clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    string msg;
                    cout << "Kindly, enter the msg to be embedded into the image:";
                    getline(cin, msg);
                    cout << '\n';
                // auto lsb = make_shared<LSB>();
                // auto aesenc = make_shared<AES256Encryption>();
                // const string msg = "God Bless Gaza";
                EncryptionOptions:
                    Utils::Clear();
                    Utils::print("Please choose your text's condition.");
                    Utils::print("1. Encrypted Text.","Magnetta");
                    Utils::print("2. Normal Text.","Magnetta");
                    cin >> choice;
                    Utils::Clear();
                    bool encrypt;
                    try {
                        if(choice == 1) {
                            encrypt = true;
                        } else if(choice == 2) {
                            encrypt = false;
                        } else {
                            throw CustomException("Invalid option.");
                        }
                        if(encrypt) {
                            StegKey:
                                Utils::Clear();
                                Utils::print("1. Enter a key.","Magnetta");
                                Utils::print("2. Generate a random key.","Magnetta");
                                cin >> choice;
                                CryptoPP::SecByteBlock key;
                                try {
                                    if(choice == 1) {
                                        displayKeyOptions(key);
                                        iHideEncryptor->changeKey(key);
                                    } else if(choice == 2) {
                                        StegKeyOptions:
                                            Utils::Clear();
                                            Utils::print("Please choose which any of the following key lengths:", "Yellow");
                                            Utils::print("1. 128-bit","Magnetta");
                                            Utils::print("2. 192-bit","Magnetta");
                                            Utils::print("3. 256-bit (Recommended)","Magnetta");
                                            short choice; cin >> choice;
                                            Utils::Clear();
                                            StegGeneratedKey:
                                                try {
                                                    if(choice == 1) {
                                                        const size_t chosenSize = 16;
                                                        iHideEncryptor->AssignRandomKey(key);
                                                    } else if(choice == 2) {
                                                        const size_t chosenSize = 24;
                                                        iHideEncryptor->AssignRandomKey(key,2);
                                                    } else if(choice == 3) {
                                                        const size_t chosenSize = 32;
                                                        iHideEncryptor->AssignRandomKey(key,3);
                                                    } else {
                                                        LOG_ERROR("User entered an invalid number.");
                                                        throw CustomException("Invalid choice."); 
                                                    }
                                                } catch(const CustomException &ex) {
                                                    Utils::print(string(ex.what()),"Red");
                                                    LOG_ERROR("USER ERROR" + string(ex.what()));
                                                    Utils::DelaySeconds(3);
                                                    Utils::Clear();
                                                    goto StegGeneratedKey;
                                                }
                                } else {
                                    throw CustomException("Invalid option.");
                                }
                            } catch(const CustomException &ex) {
                                Utils::print(string(ex.what()),"Red");
                                LOG_ERROR("USER ERROR" + string(ex.what()));
                                Utils::DelaySeconds(3);
                                Utils::Clear();
                                goto StegKey;
                            }
                        }
                    } catch(const CustomException &ex) {
                        Utils::print(string(ex.what()),"Red");
                        LOG_ERROR("USER ERROR" + string(ex.what()));
                        Utils::DelaySeconds(3);
                        Utils::Clear();
                        goto EncryptionOptions;
                    }
                try {
                    service.embedMessage(img,msg,encrypt);
                    writer.WriteImage(_DEFAULT_PATH+*it,img);
                    Utils::Clear();
                    Utils::DelaySeconds(3);
                    Utils::print("Text has successfully been inserted into the image.","Yellow");
                } catch(const CustomException &ex) {
                    Utils::print(string(ex.what()),"Red");
                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                }

                // cout << service.retrieveMessage(img,msg.length()) << endl;
                break;
            }
            case 5: {
                cv::Mat img;
                caseFive1:
                    auto filteredFiles = FileLister::listFilesInDirectory(_DEFAULT_PATH);
                    ll o(0);
                    for(const auto &el : filteredFiles) {
                        cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                    }
                        Utils::print("Enter which file you want.","Magnetta");
                        try {
                            choice = Utils::getValidChoice(filteredFiles.size());
                        } catch(const CustomException &ex) {
                            Utils::Clear();
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR(string(ex.what()));
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseFive1;
                        }
                        auto it = filteredFiles.begin() + (choice-1);

                    try {
                        img = reader.ReadImage(_DEFAULT_PATH+*it,cv::IMREAD_UNCHANGED);
                    } catch(const CustomException &ex) {
                        Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                        LOG_INFO((img.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it);
                        Utils::DelaySeconds(2);
                        Utils::Clear();
                        goto caseFive1;
                    }
                    Utils::Clear();
                    cout << "Kindly, enter the msg size to be retrieved from the image:";
                    ll msgLength; cin >> msgLength;
                    cout << '\n';
                    Utils::Clear();
                    DecryptionOptions:
                        Utils::print("Please choose your hidden text's condition.");
                        Utils::print("1. Encrypted Text.","Magnetta");
                        Utils::print("2. Normal Text.","Magnetta");
                        cin >> choice;
                        bool decrypt;
                        try {
                            if(choice == 1) {
                                decrypt = true;
                            } else if(choice == 2) {
                                decrypt = false;
                            } else {
                                throw CustomException("Invalid option.");
                            }
                        } catch(const CustomException &ex) {
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("USER ERROR" + string(ex.what()));
                            Utils::DelaySeconds(3);
                            Utils::Clear();
                            goto DecryptionOptions;
                        }
                        if(decrypt) {
                            DecryptionKeyOptions:
                                Utils::Clear();
                                Utils::print("1. Enter an existing key.","Magnetta");
                                Utils::print("2. Decrypt using cached keys.","Magnetta");
                                Utils::print("\t |==+=+==> Works only upon saved sessions, else you need to save the key used.","Blue");
                                cin >> choice;
                                Utils::Clear();
                                CryptoPP::SecByteBlock key;
                                if(choice == 1) {
                                    StegoDist:
                                        inputKey:
                                            Utils::print("Kindly, input your key.","Magnetta");
                                        // LOG_WARNING("Kindly, input your key.");
                                            // cin >> key;
                                            try {
                                                displayKeyOptions(key);
                                            } catch(const CustomException &ex){
                                                Utils::Clear();
                                                LOG_ERROR(string(ex.what()));
                                                Utils::print(string(ex.what()),"Red");
                                                Utils::DelaySeconds(3);
                                                Utils::Clear();
                                                goto inputKey;
                                            }
                                        iHideEncryptor->changeKey(key);
                                }
                                else if(choice == 2) {
                                    if(IEncrypt::checkIsInstantiated()) {
                                        // if(IEncrypt::getIntancesCount() < 1) {
                                        //     // throw CustomException("Something went wrong.");
                                        //     Utils::print("Something went wrong.", "Red");
                                        //     Utils::DelaySeconds(3);
                                        //     Utils::Clear();
                                        //     goto StegoDist;
                                        // }
                                            if(iHideEncryptor->isNotCached()) {
                                                Utils::print("No work has been cached. Please enter a key.","Red");
                                                Utils::DelaySeconds(3);
                                                Utils::Clear();
                                                goto StegoDist;
                                            }
                                    }
                                }
                                else {
                                    try {
                                        throw CustomException("Invalid Option.");
                                    } catch(const CustomException &ex) {
                                        Utils::print(string(ex.what()),"Red");
                                        LOG_ERROR("USER ERROR:" + string(ex.what()));
                                        Utils::DelaySeconds(2);
                                        Utils::Clear();
                                        goto DecryptionKeyOptions;
                                    }
                                }
                        }
                try {
                    Utils::Clear();
                    Utils::print("Text has been successfully extraxted!\n Embeded Text:" + service.retrieveMessage(img,msgLength,decrypt),"Yellow");
                } catch(const CustomException &ex) {
                    Utils::Clear();
                    Utils::print(string(ex.what()),"Red");
                    LOG_ERROR("USER ERROR:" + string(ex.what()));
                    Utils::DelaySeconds(3);
                    Utils::Clear();
                }
                break;
            }
            case 6: {
                SessionManagement ManageSession(*dbConnection);
                if(ManageSession.ClearAllSessions()) {
                    LOG_WARNING("Exiting Program.");
                    Utils::print("Exiting Program","Red");
                    Utils::print("Cya v1rushb! come back real soon pls\no_O","White",true);
                } else {
                    Utils::print("Something wrong happened.","Red");
                }
                mysql_close(connection);
                return;
            }
            default: {
                LOG_ERROR("Invalid Option.");
                Utils::print("Invalid Option","Red");
                break;
            }
        }
        Utils::DelaySeconds(4);
        Utils::Clear();
    }
}

#endif