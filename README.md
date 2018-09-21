# Parking Lot
  
 A simple program that identifies the busiest time on the parking lot.    
Both basic and advanced requirements are implemented.    
Supported features:    
1. Input files in a basic text format    
2. Input files in JSON format    
3. Visualization of a graph of busyness on the parking lot    
    
## Building    
  
The code is completely platform-independent,    
so it should compile on every C++17 - compliant compiler.

You should replace make command with the command from the compiler`s toolchain.
  
### Requirements  
1. C++17 compliant compiler  
2. CMake >= 3.9  
3. Git  
4. Qt5 >= 5.9 + QtCharts (it is installed separately) - this is only needed if you are going to build the GUI part
  
### Steps  
1. Clone the project:
    ```console
    git clone https://github.com/olokshyn/ParkingLot.git
    cd ParkingLot
    ```
3. Init submodules:  
    ```console  
    git submodule update --init
    ```  
4. Load CMake project:  
    ```console  
    mkdir build  
    cd build  
    cmake ../ -DCMAKE_PREFIX_PATH=[path to your Qt 5 installation]  
    ```  
    Note that -DCMAKE_PREFIX_PATH option can be skipped if you have no Qt installed, but it will prevent you from building the GUI part.  
5. Build the CLI part  
    ```console  
    make -j2 cli_ParkingLot  
    ```  
6. Build the GUI part (only if you have Qt5 installed):  
    ```console  
    make -j2 gui_ParkingLot  
    ```  
7. Build tests only:  
    ```console  
    make -j2 lib_tests  
    ```  
  
 ## Running  
  
For the sake of demonstration there are sample input files stored in test_data folder.  
  
 ### CLI  
  
 ```console  
 ./cli/cli_ParkingLot ./test_data/input.json  
 ```  
 CLI accepts the path to the input file as the only argument.  
  
 ### GUI  
  
 ```console  
 ./gui/gui_ParkingLot  
 ```  
  
### Tests  
  
```console  
./lib/tests/lib_tests  
```
