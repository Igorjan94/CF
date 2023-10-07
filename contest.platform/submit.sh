source ./.env

file="$1.out"
if [[ $2 != '' ]]; then
    file="$2"
fi

echo "Submitting $file to $1"

curl -X POST -H "Authorization: Bearer $TOKEN" -F "file=@$file" "https://aicontest.dev/contest-platform/api/submit/$1"
