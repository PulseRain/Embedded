echo "==========================================="
echo "prepare ..."
echo "==========================================="

rm -f *.o
rm -f demo
rm -f demo.*
 
aclocal
cp -a /usr/share/automake-1.11/install-sh .
cp -a /usr/share/automake-1.11/mkinstalldirs .
cp -a /usr/share/automake-1.11/missing .
touch NEWS AUTHORS ChangeLog
cp -a /usr/share/automake-1.11/INSTALL .
cp -a /usr/share/automake-1.11/COPYING .

automake --add-missing

echo " automake ..."
echo "==========================================="
automake

echo " autoconf ..."
echo "==========================================="
autoconf

echo " done"
echo "==========================================="
