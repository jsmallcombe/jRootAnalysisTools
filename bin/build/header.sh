echo "// jROOT Tools library master " $(date "+%d %b %Y") > include/jlibmaster.h


for f in include/j_*.h
do
h=${f:8:${#f}} 
echo "#include <"$h">" >> include/jlibmaster.h
done
