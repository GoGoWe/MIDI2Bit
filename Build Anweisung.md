Zum compilen wird minGW benötigt: https://nuwen.net/mingw.html

zuerst einen build Ordner erstellen und in diesen wechseln, in diesem unter Windows folgenden Befehl ausführen: `cmake .. -G "MinGW Makefiles"`

Nachdem kann mit dem Befehl: `cmake --build . --target MIDI2Bit` das Program erstellt werden. 
Die resultierende Anwendung wird in dem build Ordner befinden. 