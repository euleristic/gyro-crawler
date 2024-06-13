#! /usr/bin/bash

# Remember where we came from
# workingDir=`pwd`

cd `dirname $0`

if [ ! -d "resource-embeds" ]; then
	mkdir resource-embeds
	mkdir resource-embeds/resources
else
	rm -rf resource-embeds/*
	mkdir resource-embeds/resources
fi

for resource in `ls resources/`; do
	guard="`echo $resource | tr "[:lower:]" "[:upper:]" | tr '.-' _`_HPP"
	definition="EMBED_`echo $resource | tr "[:lower:]" "[:upper:]" | tr '.-' _`"
	destination="resource-embeds/resources/${resource}.hpp"
	embedder -o $destination -d $definition resources/$resource
done
