#!/usr/bin/bash

set -e

if [ "$1" == re ]; then
	echo "Reinstalling Falcon..."
	
	make clean

	make
	
	echo "Removing from Path..."
	sed -i 's|export PATH="$HOME/.local/bin/flcn:$PATH"||g' "$HOME/.bashrc"
	rm -rf ~/.local/bin/flcn

	
	mkdir -p ~/.local/bin/flcn
	cp falcon ~/.local/bin/flcn
	chmod +x ~/.local/bin/flcn/falcon

	if [ -f "$HOME/.bashrc" ]; then

		echo 'export PATH="$HOME/.local/bin/flcn:$PATH"' >> ~/.bashrc
		echo "Setting up Falcon in bashrc..."
		source ~/.bashrc

		elif [ -f "$HOME/.zshrc" ]; then

			echo 'export PATH="$HOME/.local/bin/flcn:$PATH"' >> ~/.zshrc
			echo "Setting up Falcon in zshrc..."
			source ~/.zshrc
		
	else
		echo "Unknown configuration file."
		exit 1
	fi
	
	echo "Done!"
	exit 1;
fi





if [ "$1" == un ] ; then

	read -p "Are you sure you want to unninstall Falcon ? [y/n]: " confirm

	if [[ "$confirm" == "y" || "$confirm" == "Y" ]] ; then
		echo "Removing Falcon completly..."

		sed -i 's|export PATH="$HOME/.local/bin/flcn:$PATH"||g' "$HOME/.bashrc"
		rm -rf ~/.local/bin/flcn

		rm -rf inc lib src .git falcon makefile README.md installer.sh
	
		echo "If you want to reinstall Falcon, you can clone the repo again using the following command:"
		echo "git clone https://github.com/BrunoOfAstora/falcon-V2.git"
		echo "Done."

		exit 1
	else 
		echo "Aborting..."
		exit 1
	fi
fi




mkdir -p ~/.local/bin/flcn
echo "Creating path..."

if grep "falcon" "$HOME/.local/bin/flcn/falcon" > /dev/null 2>&1; then
	echo "Falcon is already installed."
	exit 1
fi

cp falcon ~/.local/bin/flcn
echo "Setting falcon in path..."

chmod +x ~/.local/bin/flcn/falcon
echo "Giving permissions..."

if [ -f "$HOME/.bashrc" ]; then

	if  grep 'export PATH="$HOME/.local/bin/flcn:$PATH"' "$HOME/.bashrc" > /dev/null 2>&1 ; then
		echo "Falcon is already configured in your system."
		exit 1
	fi

	echo 'export PATH="$HOME/.local/bin/flcn:$PATH"' >> ~/.bashrc
	echo "Setting up Falcon in bashrc..."
	source ~/.bashrc

elif [ -f "$HOME/.zshrc" ]; then

	if  grep 'export PATH="$HOME/.local/bin/flcn:$PATH"' "$HOME/.zshrc" > /dev/null 2>&1 ; then
		echo "Falcon is already configured in your system."
		exit 1
	fi

	echo 'export PATH="$HOME/.local/bin/flcn:$PATH"' >> ~/.zshrc
	echo "Setting up Falcon in zshrc..."
	source ~/.zshrc
		
else
	echo "Unknown configuration file."
	exit 1
fi

echo "finishing..."
echo "Done"
echo "If falcon it's not working, try to restart the current terminal."
echo "Falcon Installed Successfully!"
