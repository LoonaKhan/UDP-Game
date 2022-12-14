package routes

import (
	"server/db/models/chunks"
	"server/db/models/players"
)

/* REQUESTED DATA STRUCTS */
type PlayerCoords struct { // player coords recieved to update pos, get chunks etc
	SessToken string `json:"sess_token"`
	Coords    []int  `json:"coords"`
	ID        uint   `json:"id"`
}

type ChunkCoords struct { //
	SessToken   string  `json:"sess_token"`
	ChunkCoords [][]int `json:"chunk_coords"`
}

/* RESPONSE DATA STRUCTS */

type ListPlayers struct { // list of players to send with used for listing all players online to a client
	Players []players.Player `json:"players"`
}

type ChunkSpan struct { // span of chunks either sent or recieved
	Chunks []chunks.Chunk `json:"chunks"`
	TL     [2]int         `json:"top-left"`
	BR     [2]int         `json:"bottom-right"`
}
