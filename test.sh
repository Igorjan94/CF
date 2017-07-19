#!/usr/bin/env bash
# projects contains this array:
# [{
#   type: one of ['front', 'node', 'tarantool', 'mysql'(not supported)],
#   name: 'deskplanNode',
#   container: 'nodeContainer',
#   port: port
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
    port=$4
    if [ ! "$container" ]; then container="$type"; fi
    if [ ! "$port" ]; then port="7000"; fi
}

addProject () {
    toNamedParams $@
    projects=`echo $projects | jq ". + [{\"type\": \"$type\", \"name\": \"$name\", \"container\": \"$container\", \"port\": \"$port\", \"server\": \"$server\"}]"`
}

getProjectByName () {
    foundName=$1
    found=`echo $projects | jq "map(select(.name == \"$1\"))[]"`
    foundType=`echo $found | jq '.type'`
    foundContainer=`echo $found | jq '.container'`
    foundPort=`echo $found | jq '.port'`
    foundServer=`echo $found | jq '.server'`
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







OPTS=`getopt -o h -l name:,port:,rep:,repository:,type:,container:,server:,help -- "$@"`
if [ $? != 0 ]; then exit 1; fi
eval set -- "$OPTS"

#parsing arguments
while true ; do
    case "$1" in
        -h | --help          ) usage        ;shift;;

        --name               ) name=$2      ;shift 2;;
        --port               ) port=$2      ;shift 2;;
        --rep | --repository ) rep=$2       ;shift 2;;
        --type               ) type=$2      ;shift 2;;
        --container          ) container=$2 ;shift 2;;
        --server             ) server=$2    ;shift 2;;

        --              ) shift; break;;
    esac
done

if [ "$1" == "create" ]; then
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

    addProject "$type" "$name" "$container" "$port" "$server"
    if [ "$type" == "front" ]; then
#        docker exec -ti "$container" bash -c "cd /home/nesuko && git clone $rep $name && cd $name && npm i && bower i --allow-root"
        echo -e "#!/usr/bin/env bash\ndocker exec -ti $container bash -c 'cd /home/nesuko/$name && git pull && SRV=$server npm run build && cp -r /home/nesuko/$name/dist /var/www/$name'" > "/bin/$type-$name.sh"
        echo -e "#!/usr/bin/env bash\ndocker exec -ti $container bash -c 'cd /home/nesuko/$name && git pull && rm -rf bower_components && bower i --allow-root && SRV=$server npm run build && cp -r /home/nesuko/$name/dist /var/www/$name'" > "/bin/$type-$name-bower.sh"
	chmod +x "/bin/$type-$name.sh"
	chmod +x "/bin/$type-$name-bower.sh"
	docker exec -ti "$container" bash -c "mkdir -p /var/www/$name"
    fi
fi

echo "$projects"
echo "$projects" > $settings
