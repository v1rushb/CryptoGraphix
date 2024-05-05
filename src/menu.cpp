#ifndef MENU_CPP
#define MENU_CPP

#include "Utils.hpp"
#include "ErrorHandler.cpp"
#include "LogMacros.h"
#include "FileLister.cpp"
#include "Utils.hpp"

string _DEFAULT_PATH = "../assets/";

void MainMenu() {
    short choice;

    ImageReader reader;
    ImageWriter writer;
    string key;
    auto lsb = make_shared<LSB>();
    auto aesenc = make_shared<AES256Encryption>();
    IHide service(lsb);
    IEncrypt iEncrypt(make_unique<AES256Encryption>()); // as we're just interested in the AES encryption.
    // cout << IEncrypt::checkIsInstantiated() << endl;
    Utils::Clear();
    while (true) {
        Utils::print("1. Encrypt image");
        Utils::print("2. Decrypt image");
        Utils::print("3. Test my image :fire:");
        Utils::print("4. Embed Text into the image");
        Utils::print("5. Retrieve info from the image");
        Utils::print("6. Exit");
        cin >> choice;
        Utils::Clear();
        IHide service(make_shared<LSB>());
        switch(choice) {
            case 1: {
                caseOne1:
                    Utils::print("1. Link to an existing image", "c");
                    Utils::print("2. Generate a random image.","Magnetta");
                    Utils::print("3. Choose from the existing images in your directory.","Magnetta");
                    cin >> choice;
                    cv::Mat img;
                    Utils::Clear();
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
                            Utils::print("1. Grey scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            Utils::print("Enter the width and height respectively.","Magnetta");
                            mathEnc:
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
                            if(choice == 1) {
                                img = Utils::GenerateRandomImage(width,height);
                                Utils::print("Your Grey scale image has been generated.","Yellow");
                            } else if(choice == 2) {
                                img = Utils::GenerateRandomImage(width,height,3);
                                Utils::print("Your colored image has been generated.","Yellow");
                            } else {
                                try {
                                    throw CustomException("Invalid option.");
                                } catch(const CustomException &ex) {
                                    cerr << ex.what() << endl;
                                    Utils::print(string(ex.what()),"Red");
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto colorEnc;
                                }
                            }
                    }
                    else if(choice == 3) {
                        caseOne3:
                            auto filteredFiles = FileLister::listFilesInDirectory("../assets/");
                            ll o(0);
                            for(const auto &el : filteredFiles) {
                                cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                            }
                            caseOne4:
                                // cout << "Enter which file you want.\n"; // name of the file only. other could be handled but meeeh
                                Utils::print("Enter which file you want.","Magnetta");
                                // string imagePath; cin >> imagePath;
                                cin >> choice;
                                try {
                                    if(choice > filteredFiles.size() && choice > 0) {
                                        throw CustomException("Please use a valid number.");
                                    }
                                } catch(const CustomException &ex) {
                                    Utils::Clear();
                                    Utils::print(string(ex.what()),"Red");
                                    LOG_ERROR("User has given an out of bound number.");
                                    Utils::DelaySeconds(2);
                                    Utils::Clear();
                                    goto caseOne4;
                                }
                                auto it = filteredFiles.begin() + choice;

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
                if(choice == 1) {
                    Utils::print("Kindly, input your key.","Magnetta");
                    // LOG_WARNING("Kindly, input your key.");
                    cin >> key;
                    iEncrypt.changeKey(key);
                    Utils::print("Key has been changed.", "Yellow");
                }
                else if(choice == 2) {
                    // LOG_INFO("Key has been generated");
                    // LOG_INFO(Utils::SecByteBlockToBase64String(iEncrypt.getKey()));
                    // LOG_INFO(Utils::testBlock(iEncrypt.getKey()));
                    // cout << "Key has been generated\n You can see the key in the logs.\n";
                    Utils::print("Key has been generated\n You can see the key in the logs.","Yellow");
                }
                else {
                    // LOG_ERROR("Invalid option. A key has been generated.");
                    LOG_ERROR("USER ERROR: invalid input, a key has been generated.");
                    Utils::print("Invalid option. A key has been generated.","Yellow");
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
                    } else if(newChoice == "2" || newChoice == "No") {
                        Utils::print("Image will remain the same.","Yellow");
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
                        } else if(newChoice == "2" || newChoice == "No") {
                            Utils::print("Key will remain the same.","Yellow");
                        }  else {
                            Utils::print("Invalid option.","Red");
                            //delay here.
                            goto dist4;
                        }
                    
                    cv::Mat encryptedImage = iEncrypt.EncryptImage(img);
                    const string path = "../assets/EncryptedImage.bmp";
                    writer.WriteImage(path,encryptedImage);
                    Utils::print("Image has been successfully encrypted and written on: " + path,"Yellow");
                    break;
            }
            case 2: {
                caseTwo1:
                    Utils::print("1. Link to an existing image","Magnetta");
                    Utils::print("2. Generate a random image.","Magnetta");
                    Utils::print("3. Choose from the existing images in your directory.","Magnetta");
                    cin >> choice;
                    cv::Mat img;
                    Utils::Clear();
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
                                }
                                else if(choice == 3) {
                                    caseTwo3:
                                        auto filteredFiles = FileLister::listFilesInDirectory("../assets/");
                                        ll o(0);
                                        for(const auto &el : filteredFiles) {
                                            cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                                        }
                                        caseTwo4:
                                            // cout << "Enter which file you want.\n"; // name of the file only. other could be handled but meeeh
                                            Utils::print("Enter which file you want.","Magnetta");
                                            // string imagePath; cin >> imagePath;
                                            cin >> choice;
                                            try {
                                                if(choice > filteredFiles.size() && choice > 0) {
                                                    throw CustomException("Please use a valid number.");
                                                }
                                            } catch(const CustomException &ex) {
                                                Utils::Clear();
                                                Utils::print(string(ex.what()),"Red");
                                                LOG_ERROR("User has given an out of bound number.");
                                                Utils::DelaySeconds(2);
                                                Utils::Clear();
                                                goto caseTwo4;
                                            }
                                            auto it = filteredFiles.begin() + choice;

                                        try {
                                            img = reader.ReadImage(_DEFAULT_PATH+*it,cv::IMREAD_UNCHANGED);
                                        } catch(const CustomException &ex) {
                                            Utils::print("Invalid name, file could've been deleted or misspelled.\n Please try again.","Red");
                                            LOG_ERROR("USER ERROR:" + string(ex.what()));
                                            LOG_INFO((img.channels() == 1? "User has read chosen a gray scale image, name: " : "User has read chosen a colored image, name: ") + *it);
                                            Utils::DelaySeconds(2);
                                            Utils::Clear();
                                            goto caseTwo3;                           
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
                            Utils::print("1. Gray scale image","Magnetta");
                            Utils::print("2. Colored image","Magnetta");
                            cin >> choice;
                            Utils::Clear();
                            Utils::print("Enter the width and height respectively.","Magnetta");
                            mathDec:
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
                            if(choice == 1) {
                                img = Utils::GenerateRandomImage(width,height);
                                Utils::print("Your Grey scale image has been generated.","Yellow");
                            } else if(choice == 2) {
                                img = Utils::GenerateRandomImage(width,height,3);
                                Utils::print("Your colored image has been generated.","Magnetta");
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
                    if(choice == 1) {
                        dist:
                            Utils::print("Kindly, input your key.","Magnetta");
                            // LOG_WARNING("Kindly, input your key.");
                            cin >> key;
                            iEncrypt.changeKey(key);
                    }
                    else if(choice == 2) {
                        // generateKey(key);
                        // LOG_INFO("Key has been generated");
                        if(IEncrypt::checkIsInstantiated()) {
                            if(iEncrypt.isNotCached()) {
                                Utils::print("No work has been cached. Please enter a key.","Red");
                                goto dist;
                            }
                        }
                        Utils::print("Key has been generated.","Yellow");
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
                // cv::Mat img = reader.ReadImage("../assets/EncryptedImage.bmp"); 
                cv::Mat decryptedImg = iEncrypt.DecryptImage(img);
                writer.WriteImage("../assets/DecryptedImage.jpg",decryptedImg);
                break;
            }
            case 3: {
                cv::Mat image1,image2;
                dist2:
                    Utils::print("1. Plain Sensitivity.","Magnetta");
                    Utils::print("2. Key Sensitivity.","Magnetta");
                    cin >> choice;
                    // system("\\"clear\\" && echo \\"noice\\" | lolcat");
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

                            Utils::print("Number of the first file:","Yellow");
                            cin >> choice1;
                            Utils::print("Number of the second file:","Yellow");
                            cin >> choice2;
                            try {
                                if((choice1 > filteredFiles.size() && choice1 > 0) || (choice2 > filteredFiles.size() && choice2 > 0)) {
                                    throw CustomException("Please use a valid number.");
                                }
                            } catch(const CustomException &ex) {
                                Utils::print(string(ex.what()),"Red");
                                LOG_ERROR("User has given an out of bound number.");
                                Utils::DelaySeconds(2);
                                Utils::Clear();
                                goto caseThree1;
                            }
                            auto it1 = filteredFiles.begin() + choice1;
                            auto it2 = filteredFiles.begin() + choice2;
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
                    auto filteredFiles = FileLister::listFilesInDirectory("../assets/");
                    ll o(0);
                    for(const auto &el : filteredFiles) {
                        cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                    }
                        Utils::print("Enter which file you want.","Magnetta");
                        cin >> choice;
                        try {
                            if(choice > filteredFiles.size() && choice > 0) {
                                throw CustomException("Please use a valid number.");
                            }
                        } catch(const CustomException &ex) {
                            Utils::Clear();
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("User has given an out of bound number.");
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseFour1;
                        }
                        auto it = filteredFiles.begin() + choice;

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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    string msg;
                    cout << "Kindly, enter the msg to be embedded into the image:";
                    getline(cin, msg);
                    cout << '\n';
                // auto lsb = make_shared<LSB>();
                // auto aesenc = make_shared<AES256Encryption>();
                // const string msg = "God Bless Gaza";
                try {
                    service.embedMessage(img,msg);
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
                    auto filteredFiles = FileLister::listFilesInDirectory("../assets/");
                    ll o(0);
                    for(const auto &el : filteredFiles) {
                        cout << "\033[33m" << ++o << ". " << "\033[31m" <<el << endl << "\033[35m"; 
                    }
                        Utils::print("Enter which file you want.","Magnetta");
                        cin >> choice;
                        try {
                            if(choice > filteredFiles.size() && choice > 0) {
                                throw CustomException("Please use a valid number.");
                            }
                        } catch(const CustomException &ex) {
                            Utils::Clear();
                            Utils::print(string(ex.what()),"Red");
                            LOG_ERROR("User has given an out of bound number.");
                            Utils::DelaySeconds(2);
                            Utils::Clear();
                            goto caseFive1;
                        }
                        auto it = filteredFiles.begin() + choice;

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
                    cout << "Kindly, enter the msg size to be retrieved from the image:";
                    ll msgLength; cin >> msgLength;
                    cout << '\n';
                try {
                    Utils::Clear();
                    Utils::print("Text has been successfully extraxted!\n Embeded Text:" + service.retrieveMessage(img,msgLength),"Yellow");
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
                LOG_WARNING("Exiting Program.");
                Utils::print("Exiting Program","Red");
                Utils::print("Cya v1rushb! come back real soon pls\no_O","White",true);
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