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

usage () {
   echo "H" 
   exit 0
}

projects=`jq '.' $settings`

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
    echo "Incorrect type!"
    exit 1
}







OPTS=`getopt -o h -l name:,host:,rep:,repository:,type:,container:,server:,help,bower -- "$@"`
if [ $? != 0 ]; then exit 1; fi
eval set -- "$OPTS"

#parsing arguments
while true ; do
    case "$1" in
        -h | --help          ) usage        ;shift;;
        --bower              ) bower="bower";shift;;

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
    if [ ! "$name" ] || [ ! "$type" ] || [ ! "$rep" ]; then
        echo "Type and name and rep are required!"
        exit 1
    fi
    getProjectByName "$name"
    if [ "$found" ]; then
        echo "Project already exists!"
        exit 1
    fi
    checkType $type

    addProject "$type" "$name" "$container" "$host" "$server"
    if [ "$type" == "front" ]; then
        docker exec -ti "$container" bash -c "cd /home/nesuko && rm -rf $name && git clone $rep $name && cd $name && npm i && bower i --allow-root"
        docker exec -ti "$container" bash -c "mkdir -p /var/www/$name"
        docker exec -ti "$container" bash -c "echo -e \"server {
    listen   80;

    server_name $host;
	root /var/www/$name/dist;
    index index.html index.htm;

	location / {
		allow all;
		try_files \$uri \$uri/ /index.html =404;
	}
}\" > /etc/nginx/sites-available/$host"
        docker exec -ti "$container" bash -c "ln -s /etc/nginx/sites-available/$host /etc/nginx/sites-enabled/$host"
        docker restart $container
    fi
# }}}

elif [ "$1" == "pull" ]; then # {{{
    if [ ! "$name" ]; then
        echo "Name is required!"
        exit 1
    fi
    getProjectByName "$name"
    if [ ! "$found" ]; then
        echo "Project with name '$name' is not found!"
        exit 1
    fi
    echo "Found project $foundName of type $foundType!"
    if [ $foundType == "front" ]; then
        if [ "$bower" ]; then
            docker exec -ti $foundContainer bash -c "cd /home/nesuko/$foundName && git pull && rm -rf bower_components && bower i --allow-root && SRV=$foundServer npm run build && cp -r /home/nesuko/$foundName/dist /var/www/$foundName"
        else
            docker exec -ti $foundContainer bash -c "cd /home/nesuko/$foundName && git pull && SRV=$foundServer npm run build && cp -r /home/nesuko/$foundName/dist /var/www/$foundName"
        fi
    fi
fi #}}}
# }}}

echo "$projects"
echo "$projects" > $settings


