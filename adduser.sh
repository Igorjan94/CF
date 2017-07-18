#!/usr/bin/env bash

ensureCommandExists () {
    echo "Installing $1..."
    if ! [ -x "$(command -v $1)" ]; then
        $installer $1
    else
        echo "Found $1"
    fi
}

if [ $EUID -ne 0 ]; then
    echo "Only root can run this script"
    exit 1
fi

if [ -x "$(command -v pacman)" ]; then
    installer="pacman -Sy --noconfirm"
    isArch="isArch"
else
    installer="apt-get install -y"
fi

echo "Installer: $installer"

function usage {
   echo "usage: adduser.sh -u username -p password -s server_name -k sshkey -n <install node> -d <install docker> -i 'image1 image2 ...' -g <install git> -v <install vim> -h <help> -r <rewrite zshrc>" 
   exit 0
}

#parsing arguments
while getopts "u:p:s:k:ndi:vghr" opt; do
  case $opt in
    \?) usage;;
    h) usage;;
    u) user=$OPTARG;;
    p) password=$OPTARG;;
    s) server=$OPTARG;;
    k) sshkey=$OPTARG;;
    v) needsVim=true;;
    g) needsGit=true;;
    n) needsNode=true;;
    d) needsDocker=true;;
    i) needsDocker=true; dockerImages=$OPTARG;;
    r) rewriteZshrc=true;;
  esac
done

shift $(($OPTIND - 1))

if [ "$server" ]; then
    server="$server: "
else
    server="$HOSTNAME: "
fi

ensureCommandExists "zsh"
ensureCommandExists "curl"
ensureCommandExists "sudo"
if [ "$needsVim" ]; then
    ensureCommandExists "vim"
fi
if [ "$needsGit" ]; then
    ensureCommandExists "git"
fi

if [ ! `getent group sudo 2>/dev/null` ]; then
    echo "Creating group sudo..."
    groupadd sudo
    sed -i.bak "s/\# %sudo/%sudo/g" /etc/sudoers
fi

if [ "$user" ]; then
    home="/home/$user"
    if [ "$user" == "root" ]; then
        home="/root"
    fi

    if [ ! `getent passwd $user 2>/dev/null` ]; then
        if [ "$password" ]; then
            echo "Creating user '$user' with password '$password'..."
            useradd -m -g sudo -p $(openssl passwd -1 $password) -s `which zsh` $user
        else
            echo "Creating user '$user'..."
            useradd -m -g sudo -s `which zsh` $user
        fi
    else
        chsh -s `which zsh` $user
        usermod -aG sudo $user
    fi

    zshrc="$home/.zshrc"
    if [ ! -f $zshrc ] || [ "$rewriteZshrc" ]; then
        echo "Downloading .zshrc (Prompt: '$server')..."
        curl https://raw.githubusercontent.com/Igorjan94/x/master/.zshrcMinimal 2>/dev/null | sed "s/Server 79: /$server/g" | sed "s:/usr/bin/vim:`which vim`:g" > $zshrc
        echo "alias sudo='sudo -S'" >> $zshrc
        echo "alias magic='curl igorjan94.ru | bash -s -- '" >> $zshrc
    fi

    if [ "$sshkey" ]; then
        echo "Appending ssh key to authorized_keys..."
        mkdir -p "$home/.ssh"
        keys_file="$home/.ssh/authorized_keys"
        if [ ! -f $keys_file ]; then
            touch "$keys_file"
        fi
        echo "$sshkey" >> "$keys_file"
    fi
fi

#node
if [ "$needsNode" ]; then
    echo "Installing nodejs..."
    if ! [ -x "$(command -v node)" ]; then
        if [ "$isArch" ]; then
            pacman -Sy --noconfirm nodejs npm
        else
            curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
            apt-get install -y nodejs
        fi
    else
        echo "Found node"
    fi
fi

#docker
if [ "$needsDocker" ]; then
    echo "Installing docker..."
    if ! [ -x "$(command -v docker)" ]; then
        if [ "$isArch" ]; then
            pacman -Sy --noconfirm docker
        else
            apt-get update
            apt-get install docker-ce
        fi
    else
        echo "Found docker"
    fi

    if [ "$user" ]; then
        echo "Adding user '$user' in docker group..."
        usermod -aG docker "$user"
    fi 

    echo "Starting and enabling daemon..."
    systemctl start docker
    systemctl enable docker

    if [ "$dockerImages" ]; then
        echo "Loading docker images..."
        for container in "$dockerImages"
        do
            echo "Loading '$container'..."
            curl "igorjan94.ru/data/$container.tar.gz" | gunzip | docker load
        done
    fi
fi
