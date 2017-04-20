echo "#ifdef __CINT__" > bin/build/Linkdef.h
echo "" >> bin/build/Linkdef.h
echo "#pragma link off all globals;" >> bin/build/Linkdef.h
echo "#pragma link off all classes;" >> bin/build/Linkdef.h
echo "#pragma link off all functions;" >> bin/build/Linkdef.h
echo "#pragma link C++ nestedclasses;" >> bin/build/Linkdef.h
echo "" >> bin/build/Linkdef.h


for f in include/james*.h
do
# for f in $@
# do

echo -n "#pragma link C++ defined_in \"" >> bin/build/Linkdef.h
echo -n $f >> bin/build/Linkdef.h
echo  "\";" >> bin/build/Linkdef.h

done

echo "" >> bin/build/Linkdef.h
echo "#endif" >> bin/build/Linkdef.h
