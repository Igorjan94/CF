line=gets()
if (line =~ /.{5,}/ && line =~ /[0-9]/ && line =~ /[A-Z]/ && line =~ /[a-z]/)
puts "Correct"
else
puts "Too weak"
end
