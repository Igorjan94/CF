$_ = <>;
s/([^a-zA-Z0-9 )(])\)/<S>\1\)<\/S>/g;
s/\(([A-Za-z]+)\)/<S>\(\1\)<\/S>/g;
print;
