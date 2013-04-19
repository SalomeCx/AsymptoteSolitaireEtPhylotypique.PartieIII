rm -f toto*
make
./draw test toto.c
gcc toto.c -lcairo -o toto.exe
./toto.exe
xpdf toto.c.pdf