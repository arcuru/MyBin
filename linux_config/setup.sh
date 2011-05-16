#!/bin/bash

# Sets up the appropriate symlinks for the config files located here

#ln -s source_file link_name

files=('bashrc' 'bash_profile' 'vimrc' 'vimrc-p' 'Xdefaults' 'xinitrc' 'conkyrc')
forced=false

# itarate over all arguments
for i in "$@"
do
	if [ $i = "f" ]; then
		forced=true
	fi
done

for i in "${files[@]}"
do
	if  $forced ; then
		rm ~/.$i
	fi
	ln -s ~/bin/linux_config/$i ~/.$i
done

