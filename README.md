# Simba Software
A C++ project implementing a class to store and manage IPv4 prefixes. It allows addition, removal, checking, and normalization of IP addresses.

## Main Features
- Insert, delete, check and normalize operations
- No use of STL containers
- Unit tests with Google Test
- Built using CMake

## Project Structure
 ```
simba-software/              # Root project folder
├── .gitignore               # Git ignored files
├── CMakeLists.txt           # Build configuration for CMake
├── IPv4PrefixSet.cpp        # Class source file
├── IPv4PrefixSet.h          # Class header file
├── main.cpp                 # Google tests
└── README.md                # Project documentation
```
## How it works?

### This project implements the IPv4PrefixSet class which is a data structure to store and manage IPv4 address prefixes.

#### Data Structure:
Prefixes are stored in a prefixNode struct:
- `uint32_t ip`: IP address prefix.
- `uint8_t maskLength`: length of the mask.
- `prefixNode* next`: pointer to the next node in the list.
- All prefixes are stored in a linked list starting at the `head`.

#### Key methods:
- `IPv4PrefixSet()`: initializes linked list.
- `~IPv4PrefixSet()`: frees all memory.
- `normalizePrefix(uint32_t ip, uint8_t maskLength)`: normalizes an IP prefix based on the mask length, returns normalized IP address. Example: 192.168.1.100/24 → 192.168.1.0/24.
- `add(uint32_t base, uint8_t maskLength)`: adds a normalized IP prefix if it doesn't already exist. Returns `true` if added, `false` if it was already present.
- `del(uint32_t ip, uint8_t maskLength)`: deletes a normalized IP if it already exists. Returns `true` if deletion was successful and `false` if not.
- `check(uint32_t ip)`: iterates through current prefix set and checks if this IP address mathes any of existing prefixes, return maximum mask value if correct prefix was found and -1 if not.
  
#### Unit tests:
Unit tests are implemented using `gtest` library and divided into 10 test groups:
- `AddValidPrefixes` – verifies successful addition of valid prefixes.

- `AddExistingPrefix` – ensures duplicate prefixes are not added.

- `DeleteExistingAndNonExistingPrefixes` – tests correct deletion behavior on existing and non existing prefixes.

- `CheckMostSpecificMatch` – confirms the most specific (longest mask) prefix is matched.

- `CheckNonExistingAddress` – ensures no match is found for addresses not existing in the set.

- `EdgeCases_Mask0AndMask32` – handles edge cases like `maskLength = 0` (all IPs) and `maskLength = 32` (single IP).

- `InvalidMaskLengths` – rejects invalid subnet masks (`maskLength > 32`).

- `DeleteWithWrongMask` – prevents deletion when the mask doesn't match.

- `DeleteNormalizedPrefix` – allows deletion of normalized equivalent of the stored prefix. 

- `PrefixNormalization` – verifies that IPs are correctly normalized before insertion and comparison.

## How to run this project?
### Make sure you have the following installed:
- CMake
- C++ compiler with C++11 support
- Git
- Google Test
#### Building steps:
1. Clone the repository:
    ```
    git clone https://github.com/mikitahap/simba-software.git
    cd simba-software
    ```
2. Create a build directory and generate the build files:
   ```
   mkdir build
   cd build
   cmake ..
   ```
3. Compile the project:
   ```
   make
   ```
4. Running the Tests:
   ```
   ./tests
   ```
