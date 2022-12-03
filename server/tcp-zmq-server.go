package main

import (
	"encoding/json"
	"fmt"
	zmq "github.com/pebbe/zmq4"
)

// tcp zmq server

/*
func decodeJSON[T any](str string) (T, error) {
  d := json.NewDecoder(str)
  var data T
  return data, d.Decode(&data)
}*/
type basic struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
}

func main() {
	// creatre a NewContext
	// using that context create a NewSocket
	// Bind that

	ctx, err := zmq.NewContext()
	if err != nil {
		fmt.Println(err)
		return
	}
	sock, err := ctx.NewSocket(zmq.REP)
	if err != nil {
		fmt.Println(err)
		return
	}

	//defer ctx.Close()
	defer sock.Close()

	sock.Bind("tcp://*:4000")
	fmt.Println("running on tcp host localhost port 4000")

	for {
		fmt.Println("Listening")

		req, _ := sock.RecvBytes(0) // get a request
		//fmt.Printf("request: %s\n", req)

		var data basic
		err := json.Unmarshal(req, &data)
		fmt.Println("name: ", data.Name)

		if err != nil {
			fmt.Println(err)
		}
		res, err := json.Marshal(data)
		if err != nil {
			fmt.Println(err)
		}

		sock.SendBytes(res, 0) // stringify it
	}
}
