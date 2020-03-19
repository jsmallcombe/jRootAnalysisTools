echo "$(whoami) $HOSTNAME" > bin/BuildInfo
echo $(date "+%d %b %Y") >> bin/BuildInfo
git rev-parse HEAD >> bin/BuildInfo


