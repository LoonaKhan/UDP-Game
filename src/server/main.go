package main

import (
	"fmt"
	"net"
	"server/config"
	"server/err_handling"
	"server/routes"
	"strings"
)

// keeps track of which chunks to load and updates a player's coordinates
/*
intakes a user's position
based on that position, determine which chunks to load
*/

type PlayerCoords struct { // recieved
	SessToken string `json:"sess_token"`
	Coords    []int  `json:"coords"`
}

type ChunkCoords struct { // sent back
	SessToken   string  `json:"sess_token"`
	ChunkCoords [][]int `json:"chunk_coords"`
}

func parseHeader(buffer []byte) (method []byte, idx int) {
	idx = strings.Index(string(buffer), ":") + 1 // dont use a colon as that is used in json.
	method = buffer[:idx]
	//fmt.Printf(string(method))
	return method, idx
}

func main() {

	// a goroutine to keep track of all sessions and delete any
	// todo: this might not be needed and is stupid
	/*
		go func() {
				for {
					for sess := range sessions.Sessions {
						if sessions.Sessions[sess].ExpiresAt.Before(time.Now()) { // if the session has expired, delete
							sessions.Delete(sess)
						}
					}
				}
			}()
	*/

	// sets up the port
	PORT := fmt.Sprintf(":%d", config.PORT)

	// connection
	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	defer conn.Close()
	err_handling.Handle(err)
	fmt.Printf("Listening on Port: %s\n", PORT)

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
