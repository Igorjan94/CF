let s=read_line() in
if (Str.string_match (Str.regexp ".*[0-9].*") s 0) && (Str.string_match (Str.regexp ".*[a-z].*") s 0) && (Str.string_match (Str.regexp ".*[A-Z].*") s 0) && (String.length(s) >= 5)
then print_string "Correct"
else
print_string "Too weak";;

