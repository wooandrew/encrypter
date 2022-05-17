// Encrypter : xor.h v1.0 : Andrew Woo (c) 2017 - present
// Email: seungminleader@gmail.com
// Website: wooandrew.dev

/** A subsidary .h file of Project Encrypter by Andrew Woo

  * XOR cipher
  * More info on the eXclusive OR cipher can be found at:

        https://en.wikipedia.org/wiki/XOR_cipher

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

#include <iostream>     // For cout, endl                                       [Debugging purposes]
#include <vector>       // For vector & related functions
#include <bitset>       // For bitset
#include <string>       // For string


std::vector<std::bitset<8>> XOR(std::vector<std::string>input, std::vector<std::bitset<8>>cipher){

    std::vector<std::bitset<8>>output;  // Output bitset vector
    unsigned char reconvert;            // Converter bitset -> char (Ascii)
    unsigned int cipher_iter = 0;       // Cipher iterator

    for(unsigned int x = 0; x < input.size(); x++){                                     // Outer loop: loops through elements in input vector
        for(unsigned int y = 0; y < input[x].size(); y++){                              // Inner loop: loops through characters in element
            reconvert = static_cast<unsigned char>(cipher[cipher_iter].to_ulong());     // Converts bitset from cipher vector to char
            output.push_back(std::bitset<8>(input[x][y] ^ reconvert));                  // Pushes XOR'ed bitset into output vector

            //std::cout << input[x][y] << "  "
            //          << (int)input[x][y] << ":\t\t"
            //          << std::bitset<8>(input[x][y]) << "\t^\t"
            //          << cipher[cipher_iter] << "\t=\t"
            //          << std::bitset<8>(input[x][y] ^ reconvert) << "\t: "
            //          << (input[x][y] ^ reconvert) << "\t: "
            //          << (char)(input[x][y] ^ reconvert) << std::endl;

            cipher_iter++;  // Add 1 to cipher_iter
            if(cipher_iter > cipher.size()-1){cipher_iter = 0;}   // Set cipher_iter to 0 if > than size of cipher
        }
    }

    return output;  // Return output vector
}
