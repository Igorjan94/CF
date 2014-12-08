package main
import (
 "os"
 "bufio"
"regexp"
)
 
func main() {
        in := bufio.NewReader(os.Stdin)
        line, _ := in.ReadString('\n')
        if (line[len(line)-1] == '\n') {
            line = line[0 : len(line)-2]
        }
        match, _ := regexp.MatchString(".{5,}", line)
        match1, _ := regexp.MatchString("[0-9]", line)
        match2, _ := regexp.MatchString("[a-z]", line)
        match3, _ := regexp.MatchString("[A-Z]", line)
        match4 := match && match2 && match3 && match1
        if (match4) {
    	     os.Stdout.WriteString("Correct")
        } else {
             os.Stdout.WriteString("Too weak") 
        }
}
