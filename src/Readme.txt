          11                                           
         11 0             1                             
        01   0      1111111111111                       
       01     01  101     11    101        111          
      10       1001    111111111  10     11  0          
      01         101      111  10  10 101    11         
      01111111      1111111 101 001101       10         
      1111001101         11111111            10         
          1011 11111                         11         
       01110000001111                        0          
       10   10111101                     1  01          
        10    01   1011              10001 01           
         10     1111  111111111111100011 101            
           01      11111111111111111   101              
             111                     111                
               11111            11111                   
                   11111111111111                       
     _____ _____ ____  __  __    _  _____ _   _ 
    |  ___| ____|  _ \|  \/  |  / \|_   _| | | |
    | |_  |  _| | |_) | |\/| | / _ \ | | | |_| |
    |  _| | |___|  _ <| |  | |/ ___ \| | |  _  |
    |_|   |_____|_| \_\_|  |_/_/   \_\_| |_| |_|


 (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  

Fermath Project: main
V 1.0

To compile the graphic version, you will need the following libraries installed:
build essential
libgtk2.0-0
libgtk2.0-dev

g++ -o fermath main.cpp `pkg-config --libs --cflags gtk+-2.0`

Fermath has two main programs:
main.cpp (fermath) graphical interface for using fermath
fermath_database.cpp modify fermath database 
