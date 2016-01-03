# qwnPlayer


This is early version of ownCloud music player wrote with Qt.

Tested on:
    1) Win32 - everything is working
    2) WinRT - playback isn't working - Qt bug (reported)
    3) Android (4.*)- everything is working
    4) iOS (9.2)- everything is working
    5) OS X (10.11.3)- everything is working
    6) SailfishOS (ARM, 2.0.0.10) - everything is working after installation of unofficial qt5-qtquickcontrols package
        possible porting to qt5-qtquickcontrols-nemo by Mer/Nemo project
    7) Linux (Arch) - everything is working

Known issues:
    1) Ugly UI
    2) QMultimedia use native playback backend - some formats on some platforms are unsupported
    3) Metadata is not showing correctly