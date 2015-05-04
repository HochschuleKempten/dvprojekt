# dvprojekt
Source Code from DV-Projekt.

## Installation
1. Install the DirectX SDK
  1. Download: http://www.microsoft.com/en-us/download/details.aspx?id=6812
  2. Before you install go to the windows control panel -> program and features and check if you have the Microsoft Visual C++ 2010 redistributable x86 and x64 entries. If so deinstall them first (otherwise you will get an S1023 Error)
  2. Now install the DirectX SDK
  3. If everything goes well, install the redistributables again: http://www.microsoft.com/de-de/download/details.aspx?id=8328 and http://www.microsoft.com/de-de/download/details.aspx?id=13523
2. Install the boost library into the default directory as described here: http://bpaetzold.blogspot.com/2015/04/kurzanleitung-boost-installieren.html
  1. Currently Boost 1.57 and 1.58 are supported.
  2. Make sure you have the library folder (e. g. C:\local\boost_1_58_0\lib64-msvc-12.0).
3. In your repository folder go to Lib/Release64 and unzip Vektoria_Release64.zip so that the Vektoria_Release64.lib will be located in that folder.
4. Our main project is Hochspannung. You should be able to open and run the corresponding Hochspannung.sln file. x64 build is recommended.
