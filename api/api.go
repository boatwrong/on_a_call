package main

import "fmt"
import "net/http"

var on_a_call bool = false

func enableCors(w http.ResponseWriter) {
    w.Header().Set("Access-Control-Allow-Origin", "*")
    w.Header().Set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
    w.Header().Set("Access-Control-Allow-Headers", "Content-Type, Authorization")
}

func main() {
    http.HandleFunc("/get", func (w http.ResponseWriter, r *http.Request) {
        enableCors(w)

        fmt.Println("test")

        var state int
        if (on_a_call) {
            state = 1
        } else {
            state = 0
        }
        fmt.Fprintf(w, "%d", state)
    })

    http.HandleFunc("/set", func (w http.ResponseWriter, r *http.Request) {
        on_a_call = !on_a_call
    })

    fs := http.FileServer(http.Dir("static/"))
    http.Handle("/static/", http.StripPrefix("/static/", fs))

    http.ListenAndServe(":8080", nil)
}

