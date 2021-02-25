echo "$(whoami) $HOSTNAME" > bin/BuildInfo
echo $(date "+%d %b %Y") >> bin/BuildInfo
if [ -d .git ]; then
	git rev-parse HEAD >> bin/BuildInfo;
fi


