package main

import (
	"encoding/json"
	"fmt"
	"net"
)

// udp net package server

/*
*
* tcp: base layer
	connection based
	ensures there is a connection.
	1 conn to server, one response as an acknowledgement and then 1 final conn to send data
	slower than http actually
	meant for transferring data
udp: speed, no data integrity
	fires and forgets its data
	no checking, no connection checking
	just sends data
	good for when speed is more important than data integrity
	VOIP/games/real time applications
* http: webpages
*   sends html files
	meant for websites
*   more error checking
*   higher latency
* ftp: file transfer protocol
*   directly send files
*/

type BasicData struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
}

func main() { // we using tcp/udp
	//listen, accept, handle

	PORT := ":4000" // we pass in a :port to use

	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	if err != nil {
		fmt.Println(err)
		return
	}

	defer conn.Close()
	buffer := make([]byte, 1024)

	fmt.Printf("Listening on port: %s\n", PORT)

	for { // listen indefinitely
		n, addr, err := conn.ReadFromUDP(buffer) // returns length of read data and address
		if err != nil {
			fmt.Println(err)
			return
		}

		// handle em in a goroutine
		go func(buffer []byte) {

			// unmarshall the data into some format
			var data BasicData
			err = json.Unmarshal(buffer[:n], &data)
			if err != nil {
				fmt.Println(err)
				return
			}

			// do some work
			fmt.Printf("{name: '%s', age: %d}", data.Name, data.Age) // message can be accessed via indexes

			// marshall the data back up and send it back
			res, err := json.Marshal(data)
			if err != nil {
				fmt.Println(err)
				return
			}

			// responds and closes connection
			_, _ = conn.WriteToUDP(res, addr)
		}(buffer)
	}
}
