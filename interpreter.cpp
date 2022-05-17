// Encrypter v2.0.5 : interpreter 1.0.2 : Andrew Woo (c) 2017 - present
// Email: seungminleader@gmail.com
// Website: wooandrew.dev
// Project Page: wooandrew.dev/projects/encrypter/encrypter.htm

/**
 * This software is an extension of Encrypter by Andrew Woo
 * The function of this software is to act as the intermediary
    between the GUI and encryption algorithms/styles. Thus, this
    software will recieve commands from GUI inputs and then
    activate an algorithm to encrypt or decrypt.

 * This software is licensed under the MIT License.
**/

/**
Copyright (c) 2018 Andrew Woo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

/**
*** Warning to Potential Users/Buyers ***
The original copy of this software is available @ flamingthanatos.github.io/projects/encrypter/encrypter.htm,
free of charge.
This version of the software may have been modified, and therefore may not be the exact, unmodified
copy distributed by the original creater.
**/

#include <iostream>         // For testing, getline
#include <string>           // For string
#include <cstring>          // For strlen
#include <sstream>          // For stringstream
#include <vector>           // For vector & related functions
#include <bitset>           // For bitset
#include <fstream>          // For ifstream, ofstream
#include <limits>           // For numeric_limits
#include <utility>          // For pair(), get()

#include <stdio.h>          // For printf
#include <windows.h>        // For HRESULT
#include <shlobj.h>         // For shell

#include "miscfunctions.h"  // Various miscellaneous functions
#include "xor.h"            // XOR Algorithm
#include "rbea.h"           // Really Bad Encryption Algorithm

#include "trim.h"           // Not my code.

using namespace std;

void xorit(bool decrypt, bool ufile, bool uline, bool bcotof, string LineString, string FilePath, string Password, string outpath);     // XOR Encryption handler reference
void rbeait(bool ucmd, bool ufile, bool bcotof, string LineString, string FilePath, string Password, string outpath);                   // Really Bad Encryption Algorithm handler reference
void startup();

int main(int argv, char *argc[]){

    char default_opath_char[numeric_limits<char>::max()] = {};                              // Char holding path tp CSIDL_PERSONAL, i.e Documents folder on windows
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, default_opath_char);    // Command to get CSIDL_PERSONAL and assign to default_opath_char
    string default_opath = default_opath_char;                                              // Convert char default_opath_char to string (default_opath)

    const string coma = "a"; const string comA = "algorithm";   string AlgType = "default"; // Algorithm Command

    const string come = "e"; const string comE = "encrypt";     bool ucme = false;  // Encrypt Command  [LEGACY]
    const string comd = "d"; const string comD = "decrypt";     bool ucmd = false;  // Decrypt Command  [LEGACY]

    const string comp = "p"; const string comP = "password";    string Password = "7825";   // Password Command
    const string comc = "c"; const string comC = "cipher";      string Cipher = "7825";     // Cipher Command

    const string comf = "f"; const string comF = "file";    bool ufile = false;     string FilePath = "default";    // Option: from File
    const string coml = "l"; const string comL = "line";    bool uline = false;     string LineString = "";         // Option: from Line

    const string cotof = "-oto=file";    bool bcotof = false;     string outpath = default_opath + "\\__def_enc_output.txt";    // Output to file   REQUIRES PATH AFTER [DEFAULT=CSIDL_PERSONAL + \\__def_enc_output.txt"]
    const string cotol = "-oto=line";                                                                                           // Output to line   [DEFAULT]

    const string ext = "-exit"; bool uexit = false;   // Exit Command

    const string at_xor = "xor";        // Algorithm: eXclusive OR
    const string at_rbea = "rbea";      // Algorithm: Really Bad Encryption Algorithm

    string tmp = "";    // Temporary string storage
    string input = "";  // User input

    vector<string>inputted;     // Input vector

    // COMMAND LINE INPUT
    if(argv > 1){   // Check if user entered commands via command line

        for(int x = 1; x < argv; x++){
            if(argc[x][0] != 45){                   // Check if argc[x] is command
                tmp += (string)argc[x] + " ";       // Concatenate non-command argc[x]
            } else {
                if(tmp != ""){inputted.push_back(rtrim(tmp));}      // push_back concatenated non-empty, non-command strings into vector
                inputted.push_back(argc[x]);                        // push_back commands (beginning in -) into vector
                tmp = "";   // Reset temp
            }
        }

        if(tmp != ""){inputted.push_back(tmp);tmp = "";} // Final check & push into vector, then reset tmp

        for(unsigned int x = 0; x < inputted.size(); x++){  // While x < amount of objects in inputted

            if(inputted[x][0] == 45){   // If first character of inputted[x] == Ascii 45 (-)
                for(unsigned int z = 1; z < inputted[x].size(); z++){   // While z < length of inputted[x] without Ascii 45 (-)
                    tmp += inputted[x][z];                              // Store command in temp without Ascii 45 (-)
                }

                if(tmp == coma || tmp == comA){if(inputted[x+1][0] != 45){AlgType = inputted[x+1];}}                                                                                    // If command algorthm is used, set AlgType to inputted[current+1]
                else if(tmp == come || tmp == comE){ucme = true;}                                                                                                                       // If command encrypt is used, set ucme to true
                else if(tmp == comd || tmp == comD){ucmd = true;}                                                                                                                       // If command decrypt is used, set ucmd to true
                else if(tmp == comp || tmp == comP){if(inputted[x+1][0] != 45){Password = inputted[x+1];}}                                                                              // If command password is used, set Password to inputted[current+1]
                else if(tmp == comc || tmp == comC){if(inputted[x+1][0] != 45){Cipher = inputted[x+1];}}                                                                                // If command cipher is used, set Cipher to inputted[current+1] ** LEGACY **
                else if(tmp == comf || tmp == comF){if(inputted[x+1][0] != 45){FilePath = inputted[x+1];ufile = true; uline = false;}}                                                  // If command file is used, set FilePath to inputted[current+1]
                else if(tmp == coml || tmp == comL){if(inputted[x+1][0] != 45){LineString = inputted[x+1];ufile = false; uline = true;}}                                                // If command line is used, set Linestring to inputted[current+1]
                else if("-" + tmp == cotof){if(x+1 < inputted.size()){if(inputted[x+1][0] != 45){outpath = inputted[x+1];bcotof = true;}else{bcotof = true;}}else{bcotof = true;}}      // If command oto=file, set outpath to argc[current+1], and set bcotof to true
                else if("-" + tmp == cotol){bcotof = false;}                                                                                                                            // If command oto=line, set bcotol to true
                tmp = "";   // Reset tmp
            }
        }

        if(AlgType == at_xor){  // If algorithm == xor
                xorit(ucmd, ufile, uline, bcotof, LineString, FilePath, Password, outpath); // Call XOR Encryption handler
            }
        else if(AlgType == at_rbea){    // If algorithm == rbea
            rbeait(ucmd, ufile, bcotof, LineString, FilePath, Password, outpath);           // Call Really Bad Encryption Algorithm handler
        }

        AlgType = "default"; Password = "7825"; Cipher = "7825"; FilePath = "default"; LineString = ""; outpath = default_opath + "\\__def_enc_output.txt"; // Reset strings
        uexit = true;   // Kill interpreter instance
    }

    if(!uexit){
        startup();
    }

    // APPLICATION INPUT
    while(uexit == false){  // MAIN LOOP

        printf("$ > ");             // Prompt
            getline(cin, input);    // Get user input

        string buf;                 // BUF
        stringstream ss(input);     // stringstream input

        while(ss >> buf){               // Break [input] by space and

            if(buf[0] != 45){           // Check if buf is command
                tmp += buf + " ";       // Concatenate non-command buf
            } else {
                if(tmp != ""){inputted.push_back(rtrim(tmp));}      // push_back concatenated non-empty, non-command strings into vector
                inputted.push_back(buf);                            // push_back commands (beginning in -) into vector
                tmp = "";   // Reset temp
            }

            if(buf == ext){             // If exit command is executed
                uexit = true;           // Set exit to true
            }
        }

        if(tmp != ""){inputted.push_back(tmp);tmp = "";} // Final check & push into vector, then reset tmp

        if(uexit == false){ // If exit is not true

            for(unsigned int x = 0; x < inputted.size(); x++){  // While x < amount of objects in inputted

                if(inputted[x][0] == 45){   // If first character of inputted[x] == Ascii 45 (-)
                    for(unsigned int z = 1; z < inputted[x].size(); z++){   // While z < length of inputted[x] without Ascii 45 (-)
                        tmp += inputted[x][z];                              // Store command in temp without Ascii 45 (-)
                    }

                    if(tmp == coma || tmp == comA){if(inputted[x+1][0] != 45){AlgType = inputted[x+1];}}                                                                                    // If command algorthm is used, set AlgType to inputted[current+1]
                    else if(tmp == come || tmp == comE){ucme = true;}                                                                                                                       // If command encrypt is used, set ucme to true
                    else if(tmp == comd || tmp == comD){ucmd = true;}                                                                                                                       // If command decrypt is used, set ucmd to true
                    else if(tmp == comp || tmp == comP){if(inputted[x+1][0] != 45){Password = inputted[x+1];}}                                                                              // If command password is used, set Password to inputted[current+1]
                    else if(tmp == comc || tmp == comC){if(inputted[x+1][0] != 45){Cipher = inputted[x+1];}}                                                                                // If command cipher is used, set Cipher to inputted[current+1] ** LEGACY **
                    else if(tmp == comf || tmp == comF){if(inputted[x+1][0] != 45){FilePath = inputted[x+1];ufile = true; uline = false;}}                                                  // If command file is used, set FilePath to inputted[current+1]
                    else if(tmp == coml || tmp == comL){if(inputted[x+1][0] != 45){LineString = inputted[x+1];ufile = false; uline = true;}}                                                // If command line is used, set Linestring to inputted[current+1]
                    else if("-" + tmp == cotof){if(x+1 < inputted.size()){if(inputted[x+1][0] != 45){outpath = inputted[x+1];bcotof = true;}else{bcotof = true;}}else{bcotof = true;}}      // If command oto=file, set outpath to argc[current+1], and set bcotof to true
                    else if("-" + tmp == cotol){bcotof = false;}                                                                                                                            // If command oto=line, set bcotol to true
                    tmp = "";   // Reset tmp
                }
            }

            if(AlgType == at_xor){  // If algorithm == xor
                xorit(ucmd, ufile, uline, bcotof, LineString, FilePath, Password, outpath); // Call XOR Encryption handler
            }
            else if(AlgType == at_rbea){    // If algorithm == rbea
                rbeait(ucmd, ufile, bcotof, LineString, FilePath, Password, outpath);       // Call Really Bad Encryption Algorithm handler
            }
        }
        ufile = false; uline = false; bcotof = false; ucmd = false; ucme = false;           // Reset booleans
        AlgType = "default"; Password = "7825"; Cipher = "7825"; FilePath = "default"; LineString = ""; outpath = default_opath + "\\__def_enc_output.txt"; // Reset Strings
    }

    return 0;
}

void startup(){

    string p_version = "";

    ifstream version("version.txt");
    if(version.is_open()){
        getline(version, p_version);
    }
    version.close();

    cout << "FTP Encrypter [Version " + p_version + "] (c) 2018" << endl;
    cout << "Supported System Types -> MCW x86, x64\n\n";
}

void xorit(bool decrypt, bool ufile, bool uline, bool bcotof, string LineString, string FilePath, string Password, string outpath) {  // XOR Encryption handler

    vector<string>xorin;        // XOR input vector
    vector<bitset<8>>xorout;    // XOR output vector

    // int iter = 0;       // Iterator
    // int inputlen = 0;   // Number of characters in input, including whitespace

    string tmp = "";    // Temporary string storage

    unsigned char u_ch_tmp;     // Temporary unsigned char storage

    bool ucmd = decrypt;

    if(uline){                          // Check if input comes from command line (-l)
        string buf;                     // Temporary string buf
        stringstream ss(LineString);    // Split LineString by space

        while(ss >> buf){                           // While ss >> buf
            if(buf == "toDEC__::"){ucmd = true;}    // If input is encrypted, set mode decrypt -> true
            if(ucmd){                               // If decrypt = true
                if(buf != "toDEC__::"){             // As long as buf != signal to decrypt
                    u_ch_tmp = static_cast<unsigned char>(bitset<8>(buf).to_ulong());   // Convert string bitset to bitset, then to char
                    tmp = u_ch_tmp;                                                     // Convert char to string
                    xorin.push_back(tmp);                                               // push_back string
                }
            } else {
                xorin.push_back(buf);       // push_back buf into xor in vector
                xorin.push_back(" ");       // push_back space into xor in vector
            }
        }
        if(!ucmd){xorin.pop_back();}    // If operation is not decrypt, delete last element (space)
    }
    else if(ufile){ // Check if input comes from file (-f)

        tmp = "";                                   // Reset tmp (defensive programming, incase tmp is filled)

        ifstream xorfile_in(FilePath);              // Open file
        if(xorfile_in.is_open()){                   // If file is open,
            while(getline(xorfile_in, tmp)){        // Get the first line in file

                string buf;             // Temporary string buf
                stringstream ss(tmp);   // Split tmp by space

                while(ss >> buf){
                    if(buf == "toDEC__::"){ucmd = true;}    // If input is encrypted, set mode decrypt -> true
                    if(ucmd){                               // If decrypt = true
                        if(buf != "toDEC__::"){             // As long as buf != signal to decrypt
                            u_ch_tmp = static_cast<unsigned char>(bitset<8>(buf).to_ulong());   // Convert string bitset to bitset, then to char
                            tmp = u_ch_tmp;                                                     // Convert char to string
                            xorin.push_back(tmp);                                               // push_back string

                            tmp = "";
                        }
                    } else {                    // If input is not encrypted
                        xorin.push_back(buf);   // push_back string
                        xorin.push_back(" ");   // push_back additional space
                    }
                }
                if(!ucmd){xorin.pop_back();}    // Delete last element in XOR in vector as long as decrypt = false
                xorin.push_back("\n");          // push_back newline at end of line
            }
            xorin.pop_back();   // Delete last element (\n)
        }
    }

    xorout = XOR(xorin, xor_n.gen_cipher(Password));   // Set xorout vector to vector returned by XOR function

    if(!ucmd){                                      // If decrypt = false
        xor_n.output_e_(xorout, bcotof, outpath);   // Call function encryption output, sending output vector, fileoutput true/false, and output path
    } else {                                        // If decrypt = true
        xor_n.output_d_(xorout, bcotof, outpath);   // Call function decruption output, sending output vector, fileoutput true/false, and output path
    }
    xorin.clear(); xorout.clear();    // Reset vectors
    tmp = "";   // Reset strings
}

void rbeait(bool ucmd, bool ufile, bool bcotof, string LineString, string FilePath, string Password, string outpath){   // Really Bad Encryption Algorithm handler

    string input = "";  // Create blank string input

    if(ufile){input = FilePath;}    // If using file for input, set input to filepath
    else {input = LineString;}      // If using line for input, set input to linestring

    pair<vector<long int>, bool> rbeaout = rbea(ufile, input, Password);     // Create pair holding vector and bool
    rbea_n._output(get<0>(rbeaout), get<1>(rbeaout), bcotof, outpath);  // Output encrypted/decrypted data
}
