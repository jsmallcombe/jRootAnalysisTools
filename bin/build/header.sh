echo "// James library master " $(date "+%d %b %Y") > include/jlibmaster.h


for f in include/james*.h
do
h=${f:8:${#f}} 
echo "#include <"$h">" >> include/jlibmaster.h
done

echo "#include <LeeNucleus.h>" >> include/jlibmaster.h