#include "Encryption.h"

string getDownloadsPath() {
#ifdef _WIN32
    PWSTR path = NULL;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &path);
    if (SUCCEEDED(hr)) {
        wstring wPath(path);
        CoTaskMemFree(path);
        return string(wPath.begin(), wPath.end());
    }
    else {
        cerr << "Failed to retrieve Downloads folder on Windows!" << endl;
        return "";
    }
#else
    const char* home = getenv("HOME");
    if (home) {
        return string(home) + "/Downloads";
    }
    else {
        cerr << "Failed to retrieve Downloads folder on Linux/macOS!" << endl;
        return "";
    }
#endif
}

void createFileIfNotExists(const string& filePath) {
    ifstream infile(filePath);
    if (!infile) {
        ofstream outfile(filePath);
        if (!outfile) {
            cerr << "Error: Unable to create file!\n";
            exit(1);
        }
        outfile << "This is a secret file. Encrypt it before viewing!\n";
        outfile.close();
    }
}

void encryptDecryptFile(const string& filePath, const string& password, bool encrypt) {
    ifstream infile(filePath, ios::binary);
    if (!infile) {
        cerr << "Error: Unable to open file!\n";
        return;
    }

    string outputFile = filePath + (encrypt ? ".enc" : ".dec");
    ofstream outfile(outputFile, ios::binary);
    if (!outfile) {
        cerr << "Error: Could not create output file!\n";
        return;
    }

    size_t passLen = password.length();
    char ch;
    size_t i = 0;

    while (infile.get(ch)) {
        ch ^= password[i % passLen];
        outfile.put(ch);
        i++;
    }

    infile.close();
    outfile.close();

    if (encrypt) {
        remove(filePath.c_str());
    }
    else {
        remove(filePath.c_str());
        rename(outputFile.c_str(), filePath.c_str());
    }
}

string checkPasswordStrength(const string& password) {
    int lengthScore = password.length() >= 12 ? 1 : 0;
    int upperScore = 0, lowerScore = 0, digitScore = 0, specialScore = 0;

    for (char ch : password) {
        if (isupper(ch)) upperScore = 1;
        else if (islower(ch)) lowerScore = 1;
        else if (isdigit(ch)) digitScore = 1;
        else specialScore = 1;
    }

    int totalScore = lengthScore + upperScore + lowerScore + digitScore + specialScore;

    if (totalScore <= 2) return "Weak";
    else if (totalScore == 3) return "Medium";
    else return "Strong";
}
