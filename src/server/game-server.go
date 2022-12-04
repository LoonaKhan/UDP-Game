package main

import (
	"encoding/json"
	"fmt"
	"net"
	"server/config"
	"server/error_handling"
	"server/models/chunks"
	"server/sessions"
	"time"
)

// keeps track of which chunks to load and updates a player's coordinates
/*
intakes a user's position
based on that position, determine which chunks to load
*/

type PlayerCoords struct { // recieved
	SessToken string `json_utils:"sess_token"`
	Coords    []int  `json_utils:"coords"`
}

type ChunkCoords struct { // sent back
	SessToken   string  `json_utils:"sess_token"`
	ChunkCoords [][]int `json_utils:"chunk_coords"`
}

func main() {

	// a goroutine to keep track of all sessions and delete any
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
	error_handling.HandleErr(err)
	defer conn.Close()

	buffer := make([]byte, 1024)
	for { // runs the server indefinitely
		n, addr, err := conn.ReadFromUDP(buffer)
		error_handling.HandleErr(err)

		go func(buffer []byte) {

			// get the data
			var req PlayerCoords
			err := json.Unmarshal(buffer[:n], &req)
			error_handling.HandleErr(err)

			// handle it
			chunkCoords := chunks.ChunksInRenderDist(chunks.ToChunkCoords(req.Coords))
			res_data := ChunkCoords{
				SessToken:   req.SessToken,
				ChunkCoords: chunkCoords,
			}

			// responds
			res, err := json.Marshal(res_data)
			error_handling.HandleErr(err)
			_, _ = conn.WriteToUDP(res, addr)

		}(buffer)

	}

}
