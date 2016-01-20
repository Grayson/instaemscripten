# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  # https://atlas.hashicorp.com/search.
  config.vm.box = "ubuntu/trusty64"
  config.vm.network "forwarded_port", guest: 80, host: 8888

  config.vm.provider "virtualbox" do |vb|
	# Display the VirtualBox GUI when booting the machine
	vb.gui = false

	# Customize the amount of memory on the VM:
	vb.memory = "2048"
  end
  
  config.vm.provision "shell", inline: <<-SHELL
	sudo apt-get update
	sudo apt-get install -y python2.7
	sudo apt-get install -y nodejs
	sudo apt-get install -y build-essential
	sudo apt-get install -y cmake
	sudo apt-get install -y git-core
	sudo apt-get install -y default-jre
	
	# Build fastcomp
	mkdir dev
	cd dev
	git clone https://github.com/kripken/emscripten-fastcomp fastcomp
	cd fastcomp
	git clone https://github.com/kripken/emscripten-fastcomp-clang tools/clang
	mkdir build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD="X86;JSBackend" -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_INCLUDE_TESTS=OFF -DCLANG_INCLUDE_EXAMPLES=OFF -DCLANG_INCLUDE_TESTS=OFF
	make -j$(cat /proc/cpuinfo | grep "^cpu cores" | uniq | awk -F: '{print $2}' | sed 's/[ \t]//g')
	
	# Update profile
	echo "export PATH=\"\\\$HOME/dev/fastcomp/build/bin:\$PATH\"" >> /home/vagrant/.profile
	echo "export LLVM=\"\\\$HOME/dev/fastcomp/build/bin\"" >> /home/vagrant/.profile
	source /home/vagrant/.profile
	
	# Clone and setup emscripten
	cd /home/vagrant/dev/
	git clone https://github.com/kripken/emscripten.git
	chown -R vagrant:vagrant /home/vagrant/dev
	cd emscripten
	./emcc --help > /dev/null
	for cli in "emcc" "emmake" "emcmake" "emrun"; do
	  ln -s $cli /usr/local/bin/
	done
  SHELL


  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"
end
