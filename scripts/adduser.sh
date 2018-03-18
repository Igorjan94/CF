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

function usage {
   cat << END
usage: adduser.sh
    -u | --user     <username>
    -p | --password <password>
    -s | --server   <server_name>
    -k | --sshkey   <sshkey>
    -n | --node
    -d | --docker
    -h | --help
    -f | --force
END
   exit 0
}

OPTS=`getopt -o hfndmu:p:s:k: -l help,force,node,docker,minimal,username:,password:,server:,sshkey:,packages -- "$@"`
if [ $? != 0 ]; then exit 1; fi
eval set -- "$OPTS"

#parsing arguments
while true ; do
    case "$1" in
        -h | --help     ) usage            ;shift;;
        -f | --force    ) force=true       ;shift;;
        -n | --node     ) needsNode=true   ;shift;;
        -d | --docker   ) needsDocker=true ;shift;;
        -m | --minimal  ) minimal=true     ;shift;;

        -u | --username ) user=$2                           ;shift 2;;
        -p | --password ) password=$2                       ;shift 2;;
        -s | --server   ) server=$2                         ;shift 2;;
        -k | --sshkey   ) sshkey=$2                         ;shift 2;;
        --packages      ) packages=$2                       ;shift 2;;

        --              ) shift; break;;
    esac
done

echo "Installer: $installer"

if [ "$server" ]; then
    server="$server: "
else
    server="$HOSTNAME: "
fi

ensureCommandExists "curl"

if [ "$packages" ]; then
    for package in "$packages"; do
        $installer $package
    done
fi

if [ "$minimal" ]; then
    ensureCommandExists "zsh"
    ensureCommandExists "sudo"
    ensureCommandExists "vim"
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
        ensureCommandExists "zsh"
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
    if [ ! -f $zshrc ] || [ "$force" ]; then
        echo "Downloading .zshrc (Prompt: '$server')..."
        curl https://raw.githubusercontent.com/Igorjan94/x/master/.zshrcMinimal 2>/dev/null | sed "s/Server 79: /$server/g" | sed "s:/usr/bin/vim:`which vim`:g" > $zshrc
        echo "alias sudo='sudo -S'" >> $zshrc
        echo "alias magic='curl igorjan94.ru 2&>/dev/null | bash -s -- '" >> $zshrc
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
            pacman -Sy --noconfirm docker docker-compose
        else
            apt-get update
            apt-get install docker-ce
            curl -L https://github.com/docker/compose/releases/download/1.17.1/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
            sudo chmod +x /usr/local/bin/docker-compose
        fi
        if [ "$user" ]; then
            echo "Adding user '$user' in docker group..."
            usermod -aG docker "$user"
        fi 

        echo "Starting and enabling daemon..."
        systemctl start docker
        systemctl enable docker
    else
        echo "Found docker"
    fi
fi
