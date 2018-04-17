package main

import "fmt"

func main() {
	var s string
	fmt.Scan(&s)
	ans := 0
	var fix = map[byte]int{}
	for i := range s {
        fix[s[i]] = fix[s[i]] + 1
        if (fix[s[i]] > ans) {
            ans = fix[s[i]]
        }
	}
	fmt.Println(ans)
}
