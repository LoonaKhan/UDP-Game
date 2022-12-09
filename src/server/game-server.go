package main

import (
	"fmt"
	"net"
	"server/config"
	"server/error_handling"
	"server/routes"
	"server/sessions"
	"strings"
	"time"
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
	fmt.Printf(string(method))
	return method, idx
}

func main() {

	// a goroutine to keep track of all sessions and delete any
	// todo: this might not be needed and is stupid
	go func() {
		for {
			for sess := range sessions.Sessions {
				if sessions.Sessions[sess].ExpiresAt.Before(time.Now()) { // if the session has expired, delete
					sessions.Delete(sess)
				}
			}
		}
	}()

	// sets up the port
	PORT := fmt.Sprintf(":%d", config.GAME_SERVER_PORT)

	// connection
	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	error_handling.Handle(err)
	defer conn.Close()

	buffer := make([]byte, 1024)
	for { // runs the server indefinitely
		n, addr, err := conn.ReadFromUDP(buffer)
		error_handling.Handle(err)

		method, idx := parseHeader(buffer) // parses the header to find the method

		go routes.Methods[string(method)](buffer[idx:n], conn, addr) // can crash if given the wrong input
		// try a wrapper function to try and access the map with the given key, returns an error

	}

}
