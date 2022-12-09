package routes

import (
	"encoding/json"
	"net"
	"server/error_handling"
	"server/models/chunks"
)

type PlayerCoords struct { // recieved
	SessToken string `json:"sess_token"`
	Coords    []int  `json:"coords"`
}

type ChunkCoords struct { // sent back
	SessToken   string  `json:"sess_token"`
	ChunkCoords [][]int `json:"chunk_coords"`
}

var Methods = map[string]func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr){
	"get_chunks:":         func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"post_chunks:":        func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"get_chunk_updates:":  func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"post_chunk_updates:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"update_pos:":         func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"get_players:":        func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},
	"default:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// get the data
		var req PlayerCoords
		err := json.Unmarshal(buffer, &req)
		error_handling.Handle(err)

		// handle it
		chunkCoords := chunks.ChunksInRenderDist(chunks.ToChunkCoords(req.Coords))
		res_data := ChunkCoords{
			SessToken:   req.SessToken,
			ChunkCoords: chunkCoords,
		}

		// responds
		res, err := json.Marshal(res_data)
		error_handling.Handle(err)
		_, _ = conn.WriteToUDP(res, addr)
	},
}
