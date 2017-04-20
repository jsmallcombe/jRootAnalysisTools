todaydate="\/\/	"$(date "+%d %b %Y")
for f in $@
do
# 	echo $todaydate " "$f
	sed -i "5s/.*/$todaydate/" $f
done