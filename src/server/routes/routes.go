package routes

import (
	"encoding/json"
	"net"
	"server/db/models/chunks"
	"server/err_handling"
)

var Methods = map[string]func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr){
	"get_chunks:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},

	"post_chunks:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		/*
			when a player posts chunk updates,
			  update
			  also send those updates to all clients currently connected
			  via handshakes
				so no get chunks method
		*/
	},

	"get_chunk_updates:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// client sends all loaded chunks
		// server checks for differences and sends back the differences
		// will be very inefficient.
		// instead, the server does this when another player updates
	},

	"post_chunk_updates:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {},

	"update_pos:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// accepts a position formatted as an array
		// updates it on the server
	},

	"get_players:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// server queries all players connected and sends them back
	},

	"default:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// get the data
		var req PlayerCoords
		err := json.Unmarshal(buffer, &req)
		defer err_handling.Recover("Invalid request data")
		err_handling.Handle(err)

		// handle it
		chunkCoords := chunks.ChunksInRenderDist(chunks.ToChunkCoords(req.Coords))
		res_data := ChunkCoords{
			SessToken:   req.SessToken,
			ChunkCoords: chunkCoords,
		}

		// responds
		res, err := json.Marshal(res_data)
		defer err_handling.Recover("Unable to marshal json data")
		err_handling.Handle(err)
		conn.WriteToUDP(res, addr)
	},
}
