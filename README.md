# qwnPlayer


This is early version of ownCloud music player wrote with Qt.<br><br>

There is a way to achive Zen:<br>
    - buy music (or rip own official CD via legal way)<br>
    - setup your owncloud server<br>
    - install music app for owncloud (see owncloud/music git repo)<br>
    - add music collection to your own owncloud<br>
    - build and install qwnPlayer to your device<br>
    - login to owncloud from app<br>
    - ???<br>
    - profit<br><br>

Tested on:<br>
    1) Win32 - everything is working<br>
    2) WinRT - playback isn't working - Qt bug (reported)<br>
    3) Android (4.*)- everything is working<br>
    4) iOS (9.2)- everything is working<br>
    5) OS X (10.11.3)- everything is working<br>
    6) SailfishOS (ARM, 2.0.0.10) - everything is working after installation of unofficial qt5-qtquickcontrols package<br>
        possible porting to qt5-qtquickcontrols-nemo by Mer/Nemo project<br>
    7) Linux (Arch) - everything is working<br>
    8) Android (>= 5.*) - bug like on WinRT<br><br>

Notes:<br>
    1) [Linux Users] Make sure, that you have qt5-graphicaleffects, qt5-qtquickcontrols<br><br>

Known issues:<br>
    1) Poor blayback implementation with QMultimedia. There are a lot of bugs and restrictions,<br>
       particularly with playing password-protected url on new Android<br>
    2) QMultimedia use native playback backend - some formats on some platforms are unsupported<br>
    3) Metadata is not showing correctly<br><br>

We have some bad thoughts about resolving some restrictions and bugs in QMultimedia by Qt team.<br>
We wanna move the playback to libvlc from QMultimedia, i.e. using QtVLC.<br>
So, we glad to see everyone of you, and we'll be pleasure, if you help us with qwnPlayer project!
