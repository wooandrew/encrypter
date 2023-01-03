Archived 01/03/2023

# Basic

Encrypter is a Text Encrypt program.  
Current version: 2.0.5  
Available at: https://wooandrew.dev/projects/encrypter/encrypter.htm

# Disclaimer
 This application is created for educational purposes only. I guarantee no security.

 Please note that Encrypter is only a programming challenge and should not be used to encrypt truly important data such as passwords, pin codes, banking data, and other such important information.
 While XOR is a one-time pad algorithm and has been used historically, my implementation is NOT up to standards and should NEVER be used for encrypting data more sensitive than a personal journal. RBEA is only a mathematical function and can be reversed engineered with relative ease. As with the XOR implementation, it should NEVER be used to encrypt anything except to hide private thoughts from nosy siblings. 

# How to Use?

 It will take in text or text files and encrypt its contents. Encrypter uses either the eXclusive OR [XOR] cipher, or my Really Bad Encryption Algorithm [RBEA].
 and while it is not the best, it will prevent most people from decrypting your data.
 
 1. Download the full package from [here](https://wooandrew.dev/projects/encrypter/encrypter.htm). Open the archive and extract it.
 2. Using Encrypter is fairly simple. First, start the provided GUI.
 3. Next, choose an algorithm to use. Currently, there are two options, XOR or RBEA.
 4. Next, enter a password in the password field.
 5. Then, choose an input type. If you are encrypting/decrypting data from a text or other file, use `-file`. If you want to encrypt/decrypt data from a line, use `-line`.
 6. Next, enter your data in the data field. If you chose `-file`, enter the path to the file. If you chose `-line`, enter the string you wish to encrypt.
 7. Next, choose an output type. If you want to output to the preview area, choose `line`. If you want to output to a text file or other file type, choose `file`. 
Alternatively, leave the File Path input blank. The encrypted/decrypted data will be outputted to your personal Documents folder, and named __def_enc_output.txt.
 8. Finally, press the Encrypt/Decrypt button.

 Check out the [project page](https://wooandrew.dev/projects/encrypter/encrypter.htm) for more detailed instructions.

 
# Extra
 Use `default` to output/input data from `_decrypt.txt` or `_encrypt.txt`  
 
 Commands       | Function
 :--------------|:---------------------
 -e; -exit      | Exits Encrypter
 -a; -algorithm | Set Algorithm to Use
 -p; -password  | Set Encryption/Decryption Password
 -e; -encrypt   | Use Encrypt Function [LEGACY]
 -d; -decrypt   | Use Decrypt Function [LEGACY]
 -l; -line      | Source Type Line
 -f; -file      | Source Type File
 -oto=line      | Output Type Line
 -oto=file      | Output Type File

 
# Contact Me

Email: wooandrew@gatech.edu  
Personal: seungminleader@gmail.com
