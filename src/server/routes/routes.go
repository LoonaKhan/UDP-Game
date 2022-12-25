package routes

import (
	"encoding/json"
	"net"
	"server/addys"
	"server/conf"
	"server/db"
	"server/db/models/chunks"
	"server/db/models/players"
	"server/err_handling"
	"server/routes/route_structs"
	"time"
)

var Methods = map[string]func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr){
	"get_chunks:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		/*
			User submits their coordinates,
			server sends back all existing chunks as well as the top-left and bottom-right coords of the chunk span
		*/

		// accepts the user data
		var coords route_structs.PlayerCoords
		err := json.Unmarshal(buffer, &coords)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		// uses coords to find the chunk span to render
		curChunk := chunks.ToChunkCoords(coords.Coords)
		TL, BR, xspan, yspan := chunks.ChunkSpan(curChunk)

		// gets all chunks in the chunk span that already exist
		var chunks []chunks.Chunk
		db.Conn.Find(&chunks, "x IN ? AND y IN ?", xspan, yspan)

		// return the chunk span as well as the existing chunks
		span := route_structs.ChunkSpan{
			Chunks: chunks,
			TL:     TL,
			BR:     BR,
		}
		res, _ := json.Marshal(span)
		conn.WriteToUDP(res, addr)
	},

	"post_chunks:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		/*
			when a player posts chunk updates,
			  update
			  also send those updates to all clients currently connected
			  via handshakes
				so no get chunks method
		*/

		// accepts user data
		var span route_structs.ChunkSpan
		err := json.Unmarshal(buffer, &span)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		// adds all chunks into the database
		for c := range span.Chunks {
			db.Conn.Create(&span.Chunks[c])
		}

		// responds
		res_data := map[string]string{
			"msg": "Recieved",
		}
		res, _ := json.Marshal(res_data)
		conn.WriteToUDP(res, addr)
	},

	"get_chunk_updates:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// client sends all loaded chunks
		// server checks for differences and sends back the differences
		// will be very inefficient.
		// instead, the server does this when another player updates
	},

	"post_chunk_updates:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		/*
		* player sends in a chunk that has been updated.
		* server updates that chunk and sets it to all players within render distance of that chunk.
		* */
		var c = map[string]chunks.Chunk{}
		err := json.Unmarshal(buffer, &c)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		// update the database
		
		// finds all addys within render distance and updates them 
		// should fetch all players beforehand. find if they addys match
		// takes the current chunk and its TL and BR
		// for client.players in addy, convert to chunk coords and check if within TL/BR
		addys <- AddyChan 

	},

	"update_pos:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// todo: Does not allow the player to move faster than the max speed. if they do, only move them by max speed
		// accepts a position formatted as an array
		// updates it on the server

		var coords route_structs.PlayerCoords
		err := json.Unmarshal(buffer, &coords)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		defer err_handling.UDPRespond("Unable to update position", conn, addr)
		err_handling.Handle(db.Conn.Model(&players.Player{}).
			Where("id = ?", coords.ID).
			Updates(players.Player{X: coords.Coords[0], Y: coords.Coords[1]}).Error)

		res_data := map[string]string{
			"msg": "Updated",
		}
		res, _ := json.Marshal(res_data)
		conn.WriteToUDP(res, addr)

	},
	"post_player:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// takes in a player struct
		// todo: ensure only certain fields are filled? id needs to be null
		// 		maybe make a barebones player type they have to use and gets converted to regular player?
		//		ensure player name is unique
		var p players.Player
		err := json.Unmarshal(buffer, &p)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		defer err_handling.UDPRespond("Unable to create player", conn, addr)
		err_handling.Handle(db.Conn.Create(&p).Error)

		res_data := map[string]string{
			"msg": "Created",
		}
		res, _ := json.Marshal(res_data)
		conn.WriteToUDP(res, addr)
	},

	"login:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) { // todo: complete
		// client sends in player login credentials along with their request
		// server finds a player in the database with that info
		var req map[string]string
		err := json.Unmarshal(buffer, &req)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		var plr players.Player
		db.Conn.First(&plr, "name = ?", req["name"]) // todo: handle this.

		// checks if the player is mapped to any addy already
		// if so, deny the request
		// if not, check if that address is mapped to any player
		if addys.PlayerExists(plr) { // todo: make sure this gives the right errors
			res, _ := json.Marshal(route_structs.Response{Err: "Login refused. Specified player is logged in already"})
			conn.WriteToUDP(res, addr)
			return
		}

		// if the player and addy each are not mapped
		// map em together
		addys.Insert(plr, addr)
		res, _ := json.Marshal(route_structs.PlayerID{Id: plr.ID})
		conn.WriteToUDP(res, addr)
	},

	"syn:": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr) {
		// does the player do this unprompted every sec?
		/*
			decode the json data. requires a player
			verify if the client owns that player. match()
			if !time.Now().After(Addys[plr].Expiry) : expiry.add(time.second)

			we dont need to send data back tho
		*/

		// decode data
		var data map[string]uint
		err := json.Unmarshal(buffer, &data)
		defer err_handling.UDPRespond("Invalid request data", conn, addr)
		err_handling.Handle(err)

		// verify if the client owns that player
		var plr players.Player
		db.Conn.First(&plr, "id = ?", data["pid"])
		if !(addys.AddyMatch(plr, addr)) {
			return
		}

		// extend time
		//client := addys.Addys[plr]
		a := <-addys.AddyChan
		if !time.Now().After(a[plr.ID].Expiry) { // increase it to no more than 5 seconds from now
			a[plr.ID] = addys.Client{
				Addy:   a[plr.ID].Addy,
				Expiry: time.Now().Add(conf.TIMEOUT * time.Second),
			}
		}
		addys.AddyChan <- a

	},
}
