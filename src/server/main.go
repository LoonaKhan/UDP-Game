package main

import (
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
	"strings"
)

// keeps track of which chunks to load and updates a player's coordinates
/*
intakes a user's position
based on that position, determine which chunks to load
*/

func parseHeader(buffer []byte) (method []byte, idx int) { // error handle for no semi colons
	idx = strings.Index(string(buffer), ":") + 1 // dont use a colon as that is used in json.
	method = buffer[:idx]
	//fmt.Printf(string(method))
	return method, idx
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

		header, idx := parseHeader(buffer) // parses the header to find the header

		_, exists := routes.Methods[string(header)]
		if exists {
			go routes.Methods[string(header)](buffer[idx:n], conn, addr, string(header))
		}
	}

}
