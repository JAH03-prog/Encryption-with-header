#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib> 

#ifdef _WIN32
#include <windows.h>
#include <Shlobj.h>
#include <shobjidl.h> 
#pragma comment(lib, "Shell32.lib")
#endif

using namespace std;

// Function to get the Downloads folder path
string getDownloadsPath();

// Function to create a file if it does not exist
void createFileIfNotExists(const string& filePath);

// XOR Encryption/Decryption function
void encryptDecryptFile(const string& filePath, const string& password, bool encrypt = true);

// Function to check password strength
string checkPasswordStrength(const string& password);

#endif // ENCRYPTION_H

