package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"net"
	a "server/addys"
	"server/conf"
	"server/db"
	b "server/db/models/blocks"
	c "server/db/models/chunks"
	p "server/db/models/players"
	"server/err_handling"
	"server/routes"
	rs "server/routes/route_structs"
	"strings"
)

// keeps track of which chunks to load and updates a player's coordinates
/*
intakes a user's position
based on that position, determine which chunks to load
*/

func parseReq(buffer []byte) (header rs.Header, idx int, err error) { // ensures the index and headers are valid
	idx = strings.Index(string(buffer), "|") // maybe dont use a colon as that is used in json.
	if idx == -1 {                           // colon not found
		return header, idx, errors.New("'|' not found")
	}

	// parses header
	header_buff := buffer[:idx]
	err = json.Unmarshal(header_buff, &header)
	if err != nil { // header invalid
		fmt.Println(err)
		return header, idx, err
	}

	return header, idx, nil
}

func main() {

	// we connect to the db and handle its error if any
	err_handling.Handle(db.Conn_err)
	err_handling.Handle(db.Conn.AutoMigrate(&p.Player{}))
	err_handling.Handle(db.Conn.AutoMigrate(&c.Chunk{}))
	err_handling.Handle(db.Conn.AutoMigrate(&b.Block{}))

	// fills up the address channel
	a.AddyChan <- map[uint]a.Client{}

	// sets up the port
	PORT := fmt.Sprintf(":%d", conf.PORT)

	// connection
	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	defer conn.Close()
	err_handling.Handle(err)
	fmt.Printf("Listening on Port: %s\n", PORT)

	go a.VerifyOnline(conn) // worker checks all addresses continuously

	for { // runs the server indefinitely
		buffer := make([]byte, 1024)
		n, addr, err := conn.ReadFromUDP(buffer)
		err_handling.Handle(err)

		if conf.DEBUG {
			fmt.Println(string(buffer))
		}

		// ensures the request is formatted properly
		header, idx, err := parseReq(buffer) // headers and body need to be seperated by a semicolon
		if err != nil {                      // if no semicolon is detected, ignore the request
			fmt.Println("bad header")
			continue
		}
		if _, exists := routes.Methods[header.Method]; exists { // ensures the header is valid
			go routes.Methods[header.Method](buffer[idx+1:n], conn, addr, header)
		}
	}

}
