# qwnPlayer


This is early version of ownCloud music player wrote with Qt.<br><br>

Tested on:<br>
    1) Win32 - everything is working<br>
    2) WinRT - playback isn't working - Qt bug (reported)<br>
    3) Android (4.*)- everything is working<br>
    4) iOS (9.2)- everything is working<br>
    5) OS X (10.11.3)- everything is working<br>
    6) SailfishOS (ARM, 2.0.0.10) - everything is working after installation of unofficial qt5-qtquickcontrols package<br>
        possible porting to qt5-qtquickcontrols-nemo by Mer/Nemo project<br>
    7) Linux (Arch) - everything is working<br><br>

Notes:<br>
    1) [Linux Users] Make sure, that you have qt5-graphicaleffects, qt5-qtquickcontrols<br><br>

Known issues:<br>
    1) Ugly UI<br>
    2) QMultimedia use native playback backend - some formats on some platforms are unsupported<br>
    3) Metadata is not showing correctly<br>