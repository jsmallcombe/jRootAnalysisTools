
echo "export JATOOLLIB="$(pwd) > bin/thisjlib.sh
echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$JATOOLLIB/bin:\$JATOOLLIB/bin/build:\$JATOOLLIB">> bin/thisjlib.sh
echo "export CPATH=\$CPATH:\$JATOOLLIB/include">> bin/thisjlib.sh
echo "export PATH=\$PATH:\$JATOOLLIB/include:\$JATOOLLIB/src:\$JATOOLLIB/bin:\$JATOOLLIB/bin/build">> bin/thisjlib.sh
echo "export LIBRARY_PATH=\$LIBRARY_PATH:\$JATOOLLIB/bin:\$JATOOLLIB/bin/build:\$JATOOLLIB/src:\$JATOOLLIB/include:\$JATOOLLIB">> bin/thisjlib.sh

echo "{gSystem->Load(\"libJanalysistools.so\");ExtractErrorTest(\"\");}" > bin/root_start.C

# alias root='root -l /home/jsmallcombe/test.C'
