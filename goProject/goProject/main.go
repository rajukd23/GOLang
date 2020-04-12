package main

import (
    "fmt"
    "log"
    "net/http"
    "encoding/json"
)

type Article struct {
    Id string `json:"Id"`
    Title string `json:"Title"`
    Desc string `json:"desc"`
    Content string `json:"content"`
}

// let's declare a global Articles array
// that we can then populate in our main function
// to simulate a database

var Articles []Article

func homePage(w http.ResponseWriter, r *http.Request){
    fmt.Fprintf(w, "Welcome to the HomePage!")
    fmt.Println("Endpoint Hit: homePage")
}

func handleRequests() {
    http.HandleFunc("/", homePage)
    http.HandleFunc("/articles", returnAllArticles)
    //http.HandleFunc("/articles?id={id}", returnArticlesId)
    log.Fatal(http.ListenAndServe(":10000", nil))
}

func returnArticlesId(w http.ResponseWriter, r *http.Request, val []string) { //m map[string] string) {
	fmt.Printf("Endpoint Hit: returnArticlesId %T, %d\n",val, len(val))

	for _,k := range val {
		fmt.Println("outer for", k)
		for _,article := range Articles {
			fmt.Println("inner for",article.Id)
			if article.Id == k {
				fmt.Println("In if")
				json.NewEncoder(w).Encode(article)
				fmt.Println(article)
			}
		}
	}
}

func returnAllArticles(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Endpoint Hit: returnAllArticles")
	json.NewEncoder(w).Encode(Articles)
//	returnArticlesId(w, r)
	
	for k, v := range r.URL.Query(){
	fmt.Printf("  type of v in query %T\n",v)
		fmt.Println("Keys", k,v)
		switch k {
			case "id" : 
				fmt.Println("key provided :", k)
				returnArticlesId(w, r, v)
			default :
				fmt.Println("Wrong key :", k)
		}
	}
}

func main() {
	Articles = []Article{
		Article{Id:"1", Title: "Hello", Desc: "Article Description", Content: "Article Content"},
		Article{Id:"2", Title: "Hello 2", Desc: "Article Description2", Content: "Article Content2"},
    }
    handleRequests()

}
