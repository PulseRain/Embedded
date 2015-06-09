echo "==========================================="
echo "prepare ..."
echo "==========================================="

rm -f *.o
rm -f demo
rm -f demo.*

aclocal
cp -a /usr/share/automake-1.8/install-sh .
cp -a /usr/share/automake-1.8/mkinstalldirs .
cp -a /usr/share/automake-1.8/missing .
touch NEWS AUTHORS ChangeLog
cp -a /usr/share/automake-1.8/INSTALL .
cp -a /usr/share/automake-1.8/COPYING .

automake --add-missing

echo " automake ..."
echo "==========================================="
automake

echo " autoconf ..."
echo "==========================================="
autoconf

echo " releasing ..."
echo "==========================================="
rm -rf ./release
mkdir -p release
cp -f ./configure ./release
cp -f ./Makefile.am ./release
cp -f ./Makefile.in ./release
cp -f ./configure.ac ./release
cp -av src ./release
cd release

echo " done"
echo "==========================================="
