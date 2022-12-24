package main

import (
	"fmt"
	"net"
	"server/addys"
	"server/conf"
	"server/db"
	"server/db/models/blocks"
	"server/db/models/chunks"
	"server/db/models/players"
	"server/err_handling"
	"server/routes"
	"strings"
)

// keeps track of which chunks to load and updates a player's coordinates
/*
intakes a user's position
based on that position, determine which chunks to load
*/

func parseHeader(buffer []byte) (method []byte, idx int) {
	idx = strings.Index(string(buffer), ":") + 1 // dont use a colon as that is used in json.
	method = buffer[:idx]
	//fmt.Printf(string(method))
	return method, idx
}

func main() {

	// we connect to the db and handle its error if any
	err_handling.Handle(db.Conn_err)
	err_handling.Handle(db.Conn.AutoMigrate(&players.Player{}))
	err_handling.Handle(db.Conn.AutoMigrate(&chunks.Chunk{}))
	err_handling.Handle(db.Conn.AutoMigrate(&blocks.Block{}))

	// fills up the address channel
	addys.AddyChan <- map[uint]addys.Client{}

	// sets up the port
	PORT := fmt.Sprintf(":%d", conf.PORT)

	// connection
	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	defer conn.Close()
	err_handling.Handle(err)
	fmt.Printf("Listening on Port: %s\n", PORT)

	go addys.VerifyOnline(conn) // worker checks all addresses continuously

	buffer := make([]byte, 1024)
	for { // runs the server indefinitely
		n, addr, err := conn.ReadFromUDP(buffer)
		err_handling.Handle(err)

		method, idx := parseHeader(buffer) // parses the header to find the method

		_, exists := routes.Methods[string(method)]
		if exists {
			go routes.Methods[string(method)](buffer[idx:n], conn, addr)
		}
	}

}
