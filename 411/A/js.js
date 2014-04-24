var line = readline()
if (line.match(/.{5,}/) && line.match(/[a-z]/) && line.match(/[0-9]/) && line.match(/[A-Z]/))
    print("Correct")
else
    print("Too weak")
