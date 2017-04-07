# 3280
![Logo](logo.png "Logo")
The proper way to write a GUI is to use only 1 or 2 images.
## Trello page
[https://trello.com/b/Mb0lOT44/csci3280](https://trello.com/b/Mb0lOT44/csci3280)
## For developers
The GUI will be implemented using Qt.

1. [Download Visual Studio 2015 Community (in case you don't have it)](https://www.visualstudio.com/downloads/)
2. [Download Qt 5.8.0 for Windows 64-bit (VS 2015, 1.0 GB)](http://download.qt.io/official_releases/qt/5.8/5.8.0/qt-opensource-windows-x86-msvc2015_64-5.8.0.exe.mirrorlist)
3. [Download Git for Windows (NOT GitHub for Windows!)](https://git-scm.com/download/win)
  * Leave the defaults in the installation wizard.
4. Type <kbd>⊞ Win</kbd>+<kbd>R</kbd>, then type ```cmd```, and <kbd>Enter</kbd> to open the Command Prompt.
5. Go to [this page](https://github.com/settings/tokens) to generate a GitHub access token.
5. Run: ```git config --global github.user ***YOUR_USERNAME*** && git config --global github.token ***THE_TOKEN_YOU_HAVE_GENERATED***```
6. ```cd``` to a folder you want to hold the project files.
7. Run ```git clone https://github.com/SoftFeta/3280.git```
8. Type <kbd>⊞ Win</kbd>+<kbd>R</kbd>, then type ```C:\Qt\Qt5.8.0\Tools\QtCreator\bin\qtcreator.exe```, and <kbd>Enter</kbd> to open Qt Creator.
9. Pin Qt Creator to your taskbar.
10. Open ```sans_titre.pro``` in Qt Creator.
