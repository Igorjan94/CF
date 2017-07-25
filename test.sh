#!/usr/bin/env bash
# projects contains this array:
# [{
#   type: one of ['front', 'node', 'tarantool', 'mysql'(not suphosted)],
#   name: 'deskplanNode',
#   container: 'nodeContainer',
#   host: host
# }]

settings="settings.json"
if [ ! -f $settings ]; then
    echo '[]' > "$settings"
fi

projects=`jq '.' $settings`

fail () {
    echo "$1"
    exit 1
}

usage () {
   echo "H" 
   exit 0
}

toNamedParams () {
    type=$1
    name=$2
    container=$3
    host=$4
    if [ ! "$container" ]; then container="$type"; fi
    if [ ! "$host" ]; then host="7000"; fi
}

addProject () {
    toNamedParams $@
    projects=`echo $projects | jq ". + [{\"type\": \"$type\", \"name\": \"$name\", \"container\": \"$container\", \"host\": \"$host\", \"server\": \"$server\"}]"`
}

getProjectByName () {
    foundName=$1
    found=`echo $projects | jq "map(select(.name == \"$1\"))[]"`
    foundType=`echo $found | jq -r '.type'`
    foundContainer=`echo $found | jq -r '.container'`
    foundHost=`echo $found | jq -r '.host'`
    foundServer=`echo $found | jq -r '.server'`
    unset found
    if [ "$foundType" != "" ]; then found=true; fi
}

deleteProjectByName () {
    projects=`echo $projects | jq "map(select(.name != \"$1\"))"`
}

checkType () {
    if [ "$1" == "node" ] || [ "$1" == "front" ] || [ "$1" == "tarantool" ]; then return; fi
    fail "Incorrect type!"
}







OPTS=`getopt -o h -l name:,host:,rep:,repository:,type:,container:,server:,help -- "$@"`
if [ $? != 0 ]; then exit 1; fi
eval set -- "$OPTS"

#parsing arguments
while true ; do
    case "$1" in
        -h | --help          ) usage        ;shift;;

        --name               ) name=$2      ;shift 2;;
        --host               ) host=$2      ;shift 2;;
        --rep | --repository ) rep=$2       ;shift 2;;
        --type               ) type=$2      ;shift 2;;
        --container          ) container=$2 ;shift 2;;
        --server             ) server=$2    ;shift 2;;

        --              ) shift; break;;
    esac
done

#Parsing # {{{
if [ "$1" == "create" ]; then # {{{
    if [ ! "$name" ] || [ ! "$type" ] || [ ! "$rep" ]; then fail "Type and name and rep are required!"; fi
    case "$name" in
        *\ *) fail 'Name cannot contain spaces!';;
    esac

    getProjectByName "$name"
    if [ "$found" ]; then fail "Project already exists!"; fi
    checkType $type

    addProject "$type" "$name" "$container" "$host" "$server"
    if [ "$type" == "front" ]; then
#TODO: pull на горячую
        docker exec -ti "$container" bash -c "mkdir -p /home/nesuko && cd /home/nesuko && rm -rf $name && git clone $rep $name && cd $name && npm i && bower i -F --allow-root"
        docker exec -ti "$container" bash -c "rm -rf /var/www/$name && mkdir -p /var/www/$name"
        docker exec -ti "$container" bash -c "echo -e \"server {
    listen   80;

    server_name $host;
    root /var/www/$name/dist;
    index index.html index.htm;

    location / {
        allow all;
        try_files \"'$'\"uri \"'$'\"uri/ /index.html =404;
    }
}\" > /etc/nginx/sites-available/$host"
        docker exec -ti "$container" bash -c "ln -fs /etc/nginx/sites-available/$host /etc/nginx/sites-enabled/$host"
        docker restart $container
    elif [ "$type" == "mysql" ]; then
        docker run -p 3306:3306 --name mysql -e MYSQL_ROOT_PASSWORD=y3l0l3k0r -e MYSQL_USER=external -e MYSQL_PASSWORD=y3l0l3k0r -e MYSQL_DATABASE=damos --restart=always -d mysql/mysql-server  --character-set-server=utf8 --collation-server=utf8_general_ci
#CREATE USER foo@'%' IDENTIFIED BY 'password';
#GRANT ALL PRIVILEGES ON *.* TO 'foo'@'%' WITH GRANT OPTION;
#FLUSH PRIVILEGES;
    elif [ "$type" == "node" ]; then
        path="/var/node/$name"
        logs="/var/logs/$name"
        #TODO: подумать на счёт порта!1!!1
        docker exec -ti "$container" bash -c "mkdir -p $logs && mkdir -p /var/node && cd /var/node && rm -rf $name && git clone $rep $name && cd $name && npm i"
        docker exec -ti "$container" bash -c "NODE_ENV=production HOST=$host PORT=$port forever start -a -c 'node --harmony' --pidFile '$path/pid' --sourceDir '$path' --workingDir '$path' -l '$logs/.log' -e '$logs/.err' -o '$logs/.out' bin/www"
    fi
# }}}

elif [ "$1" == "pull" ]; then # {{{
    if [ ! "$name" ]; then fail "Name is required!"; fi
    getProjectByName "$name"
    if [ ! "$found" ]; then fail "Project with name '$name' is not found!"; fi

    if [ $foundType == "front" ]; then
        docker exec -ti $foundContainer bash -c "cd /home/nesuko/$foundName && git pull | grep bower && rm -rf bower_components && bower i -F --allow-root; SRV=$foundServer npm run build && cp -r /home/nesuko/$foundName/dist /var/www/$foundName"
    elif [ "$type" == "node" ]; then
        if [ "$nodeModules" ]; then
            docker exec -ti "$container" bash -c "cd /var/node/$name && git pull && rm -rf node_modules && npm i"
        else
            docker exec -ti "$container" bash -c "cd /var/node/$name && git pull"
        fi
    fi
fi #}}}
# }}}

echo "$projects"
echo "$projects" > $settings


