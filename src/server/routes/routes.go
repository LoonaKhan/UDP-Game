package routes

import (
	"encoding/json"
	"fmt"
	"net"
	a "server/addys"
	"server/conf"
	"server/db"
	c "server/db/models/chunks"
	p "server/db/models/players"
	"server/err_handling"
	rs "server/routes/route_structs"
	nu "server/utils/net_utils"
	"time"
)

var Methods = map[string]func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header){
	"get_chunks": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		/*
			User submits their coordinates,
			server sends back all existing chunks as well as the top-left and bottom-right coords of the chunk span
		*/
		if !(a.Matches(header.Cred, addr)) { // client credentials must match
			return
		}

		// accepts the user data
		var coords rs.PlayerCoords
		err := json.Unmarshal(buffer, &coords)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		// uses coords to find the chunk span to render
		curChunk := c.ToChunkCoords(coords.Coords)
		TL, BR, xspan, yspan := c.ChunkSpan(curChunk)

		// gets all chunks in the chunk span that already exist
		var chunks []c.Chunk
		db.Conn.Find(&chunks, "x IN ? AND y IN ?", xspan, yspan)

		// return the chunk span as well as the existing chunks
		span := rs.ChunkSpan{
			Chunks: chunks,
			TL:     TL,
			BR:     BR,
		}
		res := nu.FormatRes(span, header)
		conn.WriteToUDP(res, addr)
	},

	"post_chunk": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		/*
			Creates a chunk.
			Only creates the chunk if it does not already exist
		*/
		if !(a.Matches(header.Cred, addr)) { // client credentials must match
			return
		}

		// accepts user data
		var chunk c.Chunk
		err := json.Unmarshal(buffer, &chunk)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		if db.Conn.First(&c.Chunk{}, "x = ? AND y = ?", chunk.X, chunk.Y).Error == nil { // if no record is found
			res := nu.FormatRes(rs.Response{Err: "Chunk not created. Chunk already exists"}, header)
			conn.WriteToUDP(res, addr)
			return
		} else {
			db.Conn.Create(&chunk)
		}

		res := nu.FormatRes(rs.Response{Msg: "Chunk Created."}, header)
		conn.WriteToUDP(res, addr)
	},

	"post_chunk_updates": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		/*
		* player sends in a chunk that has been updated.
		* server updates that chunk and sets it to all players within render distance of that chunk.
		* */
		if !(a.Matches(header.Cred, addr)) { // client credentials must match
			fmt.Println("denied")
			return
		}

		var updated = rs.UpdatedChunk{}
		err := json.Unmarshal(buffer, &updated)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		// update the database
		defer UDPRespondErr("Unable to update chunk.", conn, addr, header)
		err_handling.Handle(db.Conn.Model(&c.Chunk{}).
			Where("x = ? AND y = ?", updated.Chunk.X, updated.Chunk.Y).
			Update("blocks", &updated.Chunk.Blocks).Error,
		)

		// finds all addys within render distance and updates them
		// should fetch all players beforehand. find if they addys match
		// takes the current chunk and its TL and BR
		// for client.players in addy, convert to chunk coords and check if within TL/BR
		var plrs []p.Player
		var plrIds []uint

		// gets all players from addys
		addys := <-a.AddyChan
		for plr := range addys {
			plrIds = append(plrIds, plr)
		}
		a.AddyChan <- addys

		// retrieve those players
		db.Conn.Find(&plrs, "id IN ?", plrIds)

		res_header := rs.Header{Method: header.Method}
		marshalled_head, _ := json.Marshal(res_header)
		res := []byte(fmt.Sprintf("%s|%s", string(marshalled_head), string(buffer)))
		// check if in render distance. if so, update them
		for plr := range plrs { // todo: ignores current player
			plrChunk := c.ToChunkCoords([]int{plrs[plr].X, plrs[plr].Y})
			if c.IsInRenderDist([]int{updated.Chunk.X, updated.Chunk.Y}, plrChunk) {
				conn.WriteToUDP(res, addys[plrs[plr].ID].Addy)
			}
		}
	},

	"update_pos": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		// todo: Does not allow the player to move faster than the max speed. if they do, only move them by max speed
		// accepts a position formatted as an array
		// updates it on the server

		if !(a.Matches(header.Cred, addr)) { // client credentials must match
			return
		}

		var coords rs.PlayerCoords
		err := json.Unmarshal(buffer, &coords)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		defer UDPRespondErr("Unable to update position", conn, addr, header)
		err_handling.Handle(db.Conn.Model(&p.Player{}).
			Where("id = ?", header.Cred).
			Updates(p.Player{X: coords.Coords[0], Y: coords.Coords[1]}).Error,
		)

		res_data := map[string]string{
			"msg": "Updated",
		}
		res := nu.FormatRes(res_data, header)
		conn.WriteToUDP(res, addr)

	},

	"post_player": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		// takes in a player name and creates the player if they dont already exist

		var plr map[string]string
		err := json.Unmarshal(buffer, &plr)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		defer UDPRespondErr("Unable to create player", conn, addr, header)
		err_handling.Handle(db.Conn.Create(&p.Player{Name: plr["name"]}).Error)

		res := nu.FormatRes(rs.Response{Msg: "Created"}, header)
		conn.WriteToUDP(res, addr)
	},

	"login": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		// client sends in player login credentials along with their request
		// server finds a player in the database with that info
		// does not require credentials

		var req map[string]string
		err := json.Unmarshal(buffer, &req)
		defer UDPRespondErr("Invalid request data", conn, addr, header)
		err_handling.Handle(err)

		var plr p.Player
		if db.Conn.First(&plr, "name = ?", req["name"]).Error != nil { // if no record is found
			res := nu.FormatRes(rs.Response{Err: "Login refused. Specified player does not exist"}, header)
			conn.WriteToUDP(res, addr)
			return
		}

		// checks if the player is already logged in
		if a.Mapped(plr.ID) {
			res := nu.FormatRes(rs.Response{Err: "Login refused. Specified player is logged in already"}, header)
			conn.WriteToUDP(res, addr)
			return
		}

		// if the player exists and isnt already logged in, map em together
		header.Cred = plr.ID // sets the credential to the player id
		a.Insert(plr.ID, addr)
		res := nu.FormatRes(rs.PlayerID{Id: plr.ID}, header)
		conn.WriteToUDP(res, addr)
	},

	"syn": func(buffer []byte, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) {
		// does the player do this unprompted every sec?
		/*
			decode the json data. requires a player
			verify if the client owns that player. match()
			if !time.Now().After(Addys[plr].Expiry) : expiry.add(time.second)

			we dont need to send data back tho
		*/

		// verify if the client owns that player
		if !(a.Matches(header.Cred, addr)) {
			return
		}

		// extend time
		addys := <-a.AddyChan
		if !time.Now().After(addys[header.Cred].Expiry) { // increase it to no more than 5 seconds from now
			addys[header.Cred] = a.Client{
				Addy:   addys[header.Cred].Addy,
				Expiry: time.Now().Add(conf.TIMEOUT * time.Second),
			}
		}
		a.AddyChan <- addys

	},
}

// another response function which is like recover, but it Writes to UDP the argument u send it
func UDPRespondErr(msg string, conn *net.UDPConn, addr *net.UDPAddr, header rs.Header) { // recovers a thread and sends a response to the client
	if r := recover(); r != nil {
		res := nu.FormatRes(rs.Response{Err: msg}, header)
		conn.WriteToUDP(res, addr)
	}
}
