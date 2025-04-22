# 🔐 File Encryptor & Decryptor

A simple C++ tool to **encrypt and decrypt files using XOR encryption** based on a user-provided password. It includes password strength checking and cross-platform support for locating the Downloads folder on **Windows, Linux, and macOS**.

---

## 📦 Features

- 🔁 **XOR-based encryption/decryption**
- 📂 Automatically finds and creates a file in the system's **Downloads** folder
- 🔒 Simple password strength evaluation (Weak / Medium / Strong)
- 🧩 Cross-platform support (Windows and POSIX systems)
- 💡 Beginner-friendly and easy to customize

---

## 🚀 How It Works

1. **Finds Downloads folder**
   - Uses `SHGetKnownFolderPath()` on Windows
   - Uses `HOME` environment variable on Linux/macOS

2. **Creates a file if it doesn’t exist**
   - Initializes it with a sample message:  
     _"This is a secret file. Encrypt it before viewing!"_

3. **Encrypts or decrypts the file**
   - Uses XOR with a cycling password for basic obfuscation
   - Outputs `.enc` or `.dec` version of the file
   - Deletes the original file after encryption/decryption

4. **Evaluates password strength**
   - Based on presence of uppercase, lowercase, digits, symbols, and length

---

## 🧠 How to Use

### 🔧 Compile

> Make sure you have a C++17 compatible compiler

#### On Windows (MSVC)
```bash
cl /EHsc main.cpp Encryption.cpp /link Shell32.lib Ole32.lib
