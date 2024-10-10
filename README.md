# CMLandShark

## Build & Compile

### Windows

#### Prerequisites
1. Have CMake installed
2. Have vcpkg installed
3. Have Ninja installed

#### Steps (Use a terminal)
1. Navigate to where the `CMLandShark/vcpkg.json` file is located and run:

   ```bash
   ./vcpkg install
    ```

2. Navigate to where the top-level CMakeLists.txt file is located (CMLandShark/CMakeLists.txt)
  a. Create a build directory
      ```bash
      mkdir build
      cd build
      ```
   b. Use CMake to configure project, replace "path_to_vcpkg" with the actual path to the vcpkg tool chain:
      ```bash
      cmake .. -DCMAKE_TOOLCHAIN_FILE=**path_to_vcpkg**/scripts/buildsystems/vcpkg.cmake -G Ninja
      ```

4. After configuring build project using Ninja:
     ```bash
      ninja
     ```
5. After building, can run CMLandShark from the build directory

### Linux
Install Dependencies: Ensure you have the necessary development tools installed. You may need to install cmake, ninja, and vcpkg. You can do this using your package manager. For example, on Ubuntu, run:

```bash
sudo apt update
sudo apt install cmake ninja-build
```

Install Vcpkg: Clone the vcpkg repository and install it:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

Integrate Vcpkg with CMake: You can integrate vcpkg with your CMake projects by adding the vcpkg toolchain file to your CMake command:

```bash
export VCPKG_ROOT=/path/to/vcpkg  # Replace with the actual path to vcpkg
```

Set Up Your Project: Clone CMLandShark, then navigate to CMLandShark's root directory:

bash
Copy code
git clone [<your-repo-url>](https://github.com/MexicanCacti/CMLandShark.git)
cd <where-you-cloned-it>

Install Project Dependencies with Vcpkg: Navigate to the vcpkg directory and install the required dependencies defined in vcpkg.json:

```bash
./vcpkg install
```

Build Project: Create a build directory, navigate into it, and run CMake with the vcpkg toolchain:

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake ..
cmake --build .
```

Run Your Executable: After the build is complete, your executable will be located in the build directory. You can run it as follows:

```bash
Copy code
./CMLandShark
```

# Usage

![image](https://github.com/user-attachments/assets/7aada872-260a-4a0c-8862-9b0c519fa4ad)

When asked to select a directory of movies the format of the folder holding the movies should look like the above.
Meaning:
- Directory
  - SubFolders
    - Then in each subfolder:
      - movieFile AND movieImage

See filesystem.cpp for valid media files.
The folder names will be the selectable button text.
