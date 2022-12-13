package routes

import (
	"encoding/json"
	"net"
	"server/db"
	"server/db/models/chunks"
	"server/db/models/players"
	"server/err_handling"
)

// todo: make the error handling just respond with an error and call it a day?
//		err_handling.Respond, writes to UDP as it exits.
//		defer writeToUDP?
//		clients are given sess id's that let them modify specific players. what about logging in?

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
		// todo: Does not allow the player to move faster than the max speed. if they do, only move them by max speed
		// accepts a position formatted as an array
		// updates it on the server

		var coords PlayerCoords
		err := json.Unmarshal(buffer, &coords)
		defer err_handling.Recover("Invalid request data")
		err_handling.Handle(err)

		defer err_handling.Recover("Unable to update position")
		err_handling.Handle(db.Conn.Model(&players.Player{}).
			Where("id = ?", coords.ID).
			Updates(players.Player{X: coords.Coords[0], Y: coords.Coords[1]}).Error)

		res_data := map[string]string{
			"msg": "Updated",
		}
		res, err := json.Marshal(res_data)
		defer err_handling.Recover("Unable to marshal response")
		err_handling.Handle(err)

		conn.WriteToUDP(res, addr)

	},
	"post_player:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// takes in a player struct
		// todo: ensure only certain fields are filled? id needs to be null
		// 		maybe make a barebones player type they have to use and gets converted to regular player?
		var p players.Player
		err := json.Unmarshal(buffer, &p)
		defer err_handling.Recover("Invalid request data")
		err_handling.Handle(err)

		p.Online = true // not a required field so we set it.

		defer err_handling.Recover("Unable to create player")
		err_handling.Handle(db.Conn.Create(&p).Error)

		res_data := map[string]string{
			"msg": "Created",
		}
		res, err := json.Marshal(res_data)
		defer err_handling.Recover("Unable to marshall response")
		err_handling.Handle(err)
		conn.WriteToUDP(res, addr)
	},

	"get_players:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) { // server queries all players connected and sends them back

		// we dont require any relevant data. so dont check

		var players []players.Player
		db.Conn.Find(&players)

		var plist = ListPlayers{Players: players}
		res, err := json.Marshal(plist)
		defer err_handling.Recover("Unable to marshal players data")
		err_handling.Handle(err)
		conn.WriteToUDP(res, addr)

	},

	"default:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {

		/*
			gets all chunk coords given a player's coordinates
		*/

		// get the data
		var req PlayerCoords
		err := json.Unmarshal(buffer, &req)
		defer err_handling.Recover("Invalid request data")
		err_handling.Handle(err)

		// returns chunks
		chunkCoords := chunks.ChunksInRenderDist(chunks.ToChunkCoords(req.Coords))
		res_data := ChunkCoords{
			SessToken:   req.SessToken,
			ChunkCoords: chunkCoords,
		}

		// responds
		res, err := json.Marshal(res_data)
		defer err_handling.Recover("Unable to marshal chunk coord data")
		err_handling.Handle(err)
		conn.WriteToUDP(res, addr)
	},
}
