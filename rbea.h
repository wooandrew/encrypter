// Encrypter : rbea.h v2.0.1 : Andrew Woo (c) 2017 - present
// Email: seungminleader@gmail.com
// Website: wooandrew.dev

/** A subsidary .h file of Project Encrypter by Andrew Woo
  * RBEA, Really Bad Encryption Algorithm
  * RBEA is a very simple text encryption
  * algorithm, using a very simple equation
  * to encrypt each individual letter in a
  * file:
             2(x^2)z-(5^z)

  * As the name suggests, this algorithm is
  * REALLY BAD, and should only be used for
  * simple encrypting to prevent friends or
  * family from snooping around documents.

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

#include <string>           // For string
#include <vector>           // For vector & related functions
#include <algorithm>        // For reverse
#include <fstream>          // For ifstream, ofstream
#include <cmath>            // For pow(), sqrt()
#include <sstream>          // For stringstream
#include <utility>          // For std::pair, std::make_pair


std::pair<std::vector<long int>, bool> rbea(bool ufile, std::string input, std::string password){

    std::string temp = "";      // Temporary string
    std::string temp1 = "";     // Second temporary string

    int z = 0;          // Encryption/decryption key
    int passw = 0;      // Sum of decimal values in password

    std::vector<long int>convert;    // Vector holding converted values

    bool decrypt = false;   // Set decrypt line to false

    for(unsigned int x = 0; x < password.size(); x++){passw += password[x];}        // Add decimal values of characters in password to passw
    z = (passw % 10) + 2;   // Set z to passw % 10, plus 2

    if(ufile){                              // If input is from file
        std::ifstream ifile(input);         // Create file input stream and open file path
        if(ifile.is_open()){                // Check if the file is open
            while(getline(ifile, temp)){    // Set temp to line x in file
                temp1 += temp + '\n';       // Add line x and new line to temp1
            }
        } ifile.close();    // Close file

        std::string buf;                // Create temporary string buf
        std::stringstream ss(temp1);    // Create stringstream

        while(ss >> buf){   // While streaming ss >> buf
            if(decrypt){convert.push_back(sqrt((stoi(buf)+pow(5, z))/(2*z)));}  // If input is encrypted, decrypt and then push value into convert vector.  [Decrypt is always false for first iteration, which ensures the algorithm does not attempt to decrypt the signal.]
            if(buf == "toDEC__::"){decrypt = true;}                             // If decrypt signal is read, set decrypt to true.                          [Decrypt is always false for first iteration, which ensures the algorithm does not attempt to decrypt the signal.]
            if(!decrypt){                                                       // If decrypt is false                                                      [This part only occurs if the input is not encrypted.]
                for(unsigned int x = 0; x < buf.size(); x++){                   // Iterate through every character in (ASCII)
                    int toInt = buf[x];                                         // Convert element x in buf to decimal value
                    convert.push_back(2*(pow(toInt, 2))*z-pow(5, z));           // Encrypt decimal value of element x, then push into convert vector
                }
                convert.push_back(2*(pow(32, 2))*z-pow(5, z));                  // Convert an additional space, then push into convert vector   [This is because spaces are "removed" during the stringstream process]
            }
        }
    } else {                                                                        // If input is from console line
        std::string buf;                                                            // Create temporary string buf
        std::stringstream ss(input);                                                // Create stringstream

        while(ss >> buf){   // While streaming ss >> buf
            if(decrypt){convert.push_back(sqrt((stoi(buf)+pow(5, z))/(2*z)));}      // If input is encrypted, decrypt and then push value into convert vector.  [Decrypt is always false for first iteration, which ensures the algorithm does not attempt to decrypt the signal.]
            if(buf == "toDEC__::"){decrypt = true;}                                 // If decrypt signal is read, set decrypt to true.                          [Decrypt is always false for first iteration, which ensures the algorithm does not attempt to decrypt the signal.]
        }
        if(!decrypt){                                                               // If decrypt is false                                                      [This part only occurs if the input is not encrypted.]
            for(unsigned int x = 0; x < input.size(); x++){                         // Iterate through everey character in input
                int toInt = input[x];                                               // Convert element x in input to decimal value (ASCII)
                convert.push_back(2*(pow(toInt, 2))*z-pow(5, z));                   // Encrypt decimal value of element x, then push into convert vector
            }
        }
    }

    reverse(convert.begin(), convert.end());        // Reverse convert vector
    return std::make_pair(convert, decrypt);        // Return pair, convert vector and decrypt bool
}
