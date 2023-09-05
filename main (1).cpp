#include <iostream>
#include <fstream>
#include <cstring>
#include "TGA.h"
using namespace std;

void Test(){
    TGA file = TGA("EXAMPLE_part2.tga");
    file.output("output.tga", file.pixels);
}

void Task1(){
    TGA file = TGA("layer1.tga");
    file.multiplyFiles(TGA("pattern1.tga"));
    file.output("output/part1.tga", file.pixels);
}

void Task2(){
    TGA file = TGA("car.tga");
    file.subtractFiles(TGA("layer2.tga"));
    file.output("output/part2.tga", file.pixels);
}

void Task3(){
    TGA file = TGA("layer1.tga");
    file.multiplyFiles(TGA("pattern2.tga"));
    file.screenFiles(TGA("text.tga"));
    file.output("output/part3.tga", file.pixels);
}

void Task4(){
    TGA file = TGA("layer2.tga");
    file.multiplyFiles(TGA("circles.tga"));
    TGA file2 = TGA("pattern2.tga");
    file.subtractFiles(file2);
    file.output("output/part4.tga", file.pixels);
}

void Task5(){
    TGA file = TGA("layer1.tga");
    file.overlayFiles(TGA("pattern1.tga"));
    file.output("output/part5.tga", file.pixels);
}

void Task6(){
    TGA file = TGA("car.tga");
    file.add(0, 200, 0);
    file.output("output/part6.tga", file.pixels);
}

void Task7(){
    TGA file = TGA("car.tga");
    file.scale(0, 1, 4);
    file.output("output/part7.tga", file.pixels);
}

void Task8(){
    TGA file = TGA("car.tga");
    file.redChannel();
    file.output("output/part8_r.tga", file.pixels);

    TGA file2 = TGA("car.tga");
    file2.greenChannel();
    file2.output("output/part8_g.tga", file2.pixels);

    TGA file3 = TGA("car.tga");
    file3.blueChannel();
    file3.output("output/part8_b.tga", file3.pixels);
}

void Task9(){
    TGA blueFile = TGA("layer_blue.tga");
    blueFile.combine(TGA("layer_green.tga"), TGA("layer_red.tga"));
    blueFile.output("output/part9.tga", blueFile.pixels);
}

void Task10(){
    TGA file = TGA("text2.tga");
    file.flip();
    file.output("output/part10.tga", file.pixels);
}



int main(int argc, char* argv[]) {
    // no arguments
    if (argc == 1) {
        cout
                << "Project 2: Image Processing, Spring 2023\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]"
                << endl;
        // only argument is --help
    } else if (strcmp(argv[1], "--help") == 0) {
        cout
                << "Project 2: Image Processing, Spring 2023\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]"
                << endl;
    } else {
        // output name
        string str(argv[1]);
        int strLength = str.size();
        if (strLength < 4) {
            cout << "Invalid file name." << endl;
        } else {
            string strEnd = str.substr(strLength - 4);
            if (strEnd != ".tga") {
                cout << "Invalid file name." << endl;
            } else {
                // input name
                if (argc >= 3) {
                    string str2(argv[2]);
                    int strLength2 = str2.size();
                    if (strLength2 < 4) {
                        cout << "Invalid file name." << endl;
                    } else {
                        string strEnd2 = str2.substr(strLength2 - 4);
                        if (strEnd2 != ".tga") {
                            cout << "Invalid file name." << endl;
                        } else {
                            // load tracking file
                            ifstream trackingFile(str2, ios_base::in);
                            if (trackingFile.is_open()) {
                                trackingFile.close();
                                // manipulation method
                                int counter = 4;
                                while(argc >= counter){
                                    if (argc >= counter) {
                                        string methodStr(argv[counter-1]);
                                        // multiply
                                        if (methodStr == "multiply") {
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                // file to multiply
                                                string secondFile(argv[counter]);
                                                int secondFileLength = secondFile.size();
                                                if (secondFileLength < 4) {
                                                    cout << "Invalid argument, invalid file name." << endl;
                                                } else {
                                                    string secondFileEnd = secondFile.substr(secondFileLength - 4);
                                                    if (secondFileEnd != ".tga") {
                                                        cout << "Invalid argument, invalid file name." << endl;
                                                    } else {
                                                        // multiplying files if they exist
                                                        ifstream loadFile2(secondFile, ios_base::in);
                                                        if (loadFile2.is_open()) {
                                                            loadFile2.close();
                                                            TGA multFile1 = TGA(str2);
                                                            multFile1.multiplyFiles(TGA(secondFile));
                                                            multFile1.output(str, multFile1.pixels);
                                                            cout << "Multiplying " << str2 << " and " << secondFile << " ..." << endl;
                                                            cout << "... and saving output to " << str << "!" << endl;
                                                        } else {
                                                            cout << "Invalid argument, file does not exist." << endl;
                                                        }
                                                    }

                                                }
                                                counter += 2;
                                            }
                                        } else if (methodStr == "subtract"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                // file to subtract
                                                string secondFile(argv[counter]);
                                                int secondFileLength = secondFile.size();
                                                if (secondFileLength < 4) {
                                                    cout << "Invalid argument, invalid file name." << endl;
                                                } else {
                                                    string secondFileEnd = secondFile.substr(secondFileLength - 4);
                                                    if (secondFileEnd != ".tga") {
                                                        cout << "Invalid argument, invalid file name." << endl;
                                                    } else {
                                                        // subtracting files if they exist
                                                        ifstream loadFile2(secondFile, ios_base::in);
                                                        if (loadFile2.is_open()) {
                                                            loadFile2.close();
                                                            TGA subtractFile1 = TGA(str2);
                                                            subtractFile1.subtractFiles(TGA(secondFile));
                                                            subtractFile1.output(str, subtractFile1.pixels);
                                                            cout << "Subtracting " << secondFile << " from " << str2 << " ..." << endl;
                                                            cout << "... and saving output to " << str << "!" << endl;
                                                        } else {
                                                            cout << "Invalid argument, file does not exist." << endl;
                                                        }
                                                    }

                                                }
                                                counter += 2;
                                            }
                                        } else if (methodStr == "overlay"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                // file to overlay
                                                string secondFile(argv[counter]);
                                                int secondFileLength = secondFile.size();
                                                if (secondFileLength < 4) {
                                                    cout << "Invalid argument, invalid file name." << endl;
                                                } else {
                                                    string secondFileEnd = secondFile.substr(secondFileLength - 4);
                                                    if (secondFileEnd != ".tga") {
                                                        cout << "Invalid argument, invalid file name." << endl;
                                                    } else {
                                                        // overlaying files if they exist
                                                        ifstream loadFile2(secondFile, ios_base::in);
                                                        if (loadFile2.is_open()) {
                                                            loadFile2.close();
                                                            TGA overlayFile1 = TGA(str2);
                                                            overlayFile1.overlayFiles(TGA(secondFile));
                                                            overlayFile1.output(str, overlayFile1.pixels);
                                                            cout << "Overlaying " << secondFile << " and " << str2 << " ..." << endl;
                                                            cout << "... and saving output to " << str << "!" << endl;
                                                        } else {
                                                            cout << "Invalid argument, file does not exist." << endl;
                                                        }
                                                    }

                                                }
                                                counter += 2;
                                            }
                                        } else if (methodStr == "screen"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                // file to screen
                                                string secondFile(argv[counter]);
                                                int secondFileLength = secondFile.size();
                                                if (secondFileLength < 4) {
                                                    cout << "Invalid argument, invalid file name." << endl;
                                                } else {
                                                    string secondFileEnd = secondFile.substr(secondFileLength - 4);
                                                    if (secondFileEnd != ".tga") {
                                                        cout << "Invalid argument, invalid file name." << endl;
                                                    } else {
                                                        // screening files if they exist
                                                        ifstream loadFile2(secondFile, ios_base::in);
                                                        if (loadFile2.is_open()) {
                                                            loadFile2.close();
                                                            TGA screenFile1 = TGA(str2);
                                                            screenFile1.screenFiles(TGA(secondFile));
                                                            screenFile1.output(str, screenFile1.pixels);
                                                            cout << "Screening " << secondFile << " and " << str2 << " ..." << endl;
                                                            cout << "... and saving output to " << str << "!" << endl;
                                                        } else {
                                                            cout << "Invalid argument, file does not exist." << endl;
                                                        }
                                                    }

                                                }
                                                counter += 2;
                                            }
                                        } else if (methodStr == "combine"){
                                            if (argc < counter + 2) {
                                                cout << "Missing argument." << endl;
                                                counter += 2;
                                            } else {
                                                // green file
                                                string secondFile(argv[counter]);
                                                int secondFileLength = secondFile.size();
                                                if (secondFileLength < 4) {
                                                    cout << "Invalid argument, invalid file name." << endl;
                                                } else {
                                                    string secondFileEnd = secondFile.substr(secondFileLength - 4);
                                                    if (secondFileEnd != ".tga") {
                                                        cout << "Invalid argument, invalid file name." << endl;
                                                    } else {
                                                        // blue file
                                                        string blueFile(argv[counter + 1]);
                                                        int blueFileLength = blueFile.size();
                                                        if (blueFileLength < 4) {
                                                            cout << "Invalid argument, invalid file name." << endl;
                                                        } else {
                                                            string blueFileEnd = blueFile.substr(blueFileLength - 4);
                                                            if (blueFileEnd != ".tga") {
                                                                cout << "Invalid argument, invalid file name." << endl;
                                                            } else {
                                                                // combining files if they exist
                                                                ifstream loadFile2(secondFile, ios_base::in);
                                                                if (loadFile2.is_open()) {
                                                                    loadFile2.close();
                                                                    ifstream loadBlueFile(blueFile, ios_base::in);
                                                                    if (loadBlueFile.is_open()){
                                                                        TGA CombineFile = TGA(blueFile);
                                                                        CombineFile.combine(TGA(secondFile), TGA(str2));
                                                                        CombineFile.output(str, CombineFile.pixels);
                                                                        cout << "Combining " << str2 << ", " << secondFile << ", and " << blueFile << " ..." << endl;
                                                                        cout << "... and saving output to " << str << "!" << endl;
                                                                    } else {
                                                                        cout << "Invalid argument, file does not exist." << endl;
                                                                    }
                                                                } else {
                                                                    cout << "Invalid argument, file does not exist." << endl;
                                                                }
                                                            }
                                                        }
                                                    }

                                                }
                                                counter += 3;
                                            }
                                        } else if (methodStr == "flip"){
                                            TGA flipFile = TGA(str2);
                                            flipFile.flip();
                                            flipFile.output(str, flipFile.pixels);
                                            cout << "Flipping " << str2 << " ..." << endl;
                                            cout << "... and saving output to out.tga!" << endl;
                                            counter += 1;
                                        } else if (methodStr == "onlyred"){
                                            TGA redFile = TGA(str2);
                                            redFile.redChannel();
                                            redFile.output(str, redFile.pixels);
                                            cout << "Only red channel of " << str2 << " ..." << endl;
                                            cout << "... and saving output to out.tga!" << endl;
                                            counter += 1;
                                        } else if (methodStr == "onlygreen"){
                                            TGA greenFile = TGA(str2);
                                            greenFile.greenChannel();
                                            greenFile.output(str, greenFile.pixels);
                                            cout << "Only green channel of " << str2 << " ..." << endl;
                                            cout << "... and saving output to out.tga!" << endl;
                                            counter += 1;
                                        } else if (methodStr == "onlyblue"){
                                            TGA blueFile = TGA(str2);
                                            blueFile.blueChannel();
                                            blueFile.output(str, blueFile.pixels);
                                            cout << "Only blue channel of " << str2 << " ..." << endl;
                                            cout << "... and saving output to out.tga!" << endl;
                                            counter += 1;
                                        } else if (methodStr == "addred"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA addFile = TGA(str2);
                                                    addFile.add(0, 0, finalNum);
                                                    addFile.output(str, addFile.pixels);
                                                    cout << "Adding " << finalNum << " to red " << str2 << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else if (methodStr == "addgreen") {
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA addFile = TGA(str2);
                                                    addFile.add(0, finalNum, 0);
                                                    addFile.output(str, addFile.pixels);
                                                    cout << "Adding " << finalNum << " to green " << str2 << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else if (methodStr == "addblue"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA addFile = TGA(str2);
                                                    addFile.add(finalNum, 0, 0);
                                                    addFile.output(str, addFile.pixels);
                                                    cout << "Adding " << finalNum << " to blue " << str2 << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else if (methodStr == "scalered"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA scaleFile = TGA(str2);
                                                    scaleFile.scale(1, 1, finalNum);
                                                    scaleFile.output(str, scaleFile.pixels);
                                                    cout << "Scaling " << str2 << "'s red by " << finalNum << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else if (methodStr == "scalegreen"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA scaleFile = TGA(str2);
                                                    scaleFile.scale(1, finalNum, 1);
                                                    scaleFile.output(str, scaleFile.pixels);
                                                    cout << "Scaling " << str2 << "'s green by " << finalNum << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else if (methodStr == "scaleblue"){
                                            if (argc < counter + 1) {
                                                cout << "Missing argument." << endl;
                                                counter += 1;
                                            } else {
                                                string num1(argv[counter]);
                                                int finalNum;
                                                try {
                                                    finalNum = stoi(num1);
                                                    TGA scaleFile = TGA(str2);
                                                    scaleFile.scale(finalNum, 1, 1);
                                                    scaleFile.output(str, scaleFile.pixels);
                                                    cout << "Scaling " << str2 << "'s blue by " << finalNum << " ..." << endl;
                                                    cout << "... and saving output to out.tga!" << endl;
                                                }
                                                catch (invalid_argument){
                                                    cout << "Invalid argument, expected number." << endl;
                                                }
                                            }
                                            counter += 2;
                                        } else {
                                            cout << "Invalid method name." << endl;
                                            counter += 10000;
                                        }
                                    }
                                    str2 = str;
                                }
                            } else {
                                cout << "File does not exist." << endl;
                            }
                        }
                    }
                }


            }
        }
    }
}