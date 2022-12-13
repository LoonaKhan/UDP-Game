package routes

import "server/db/models/players"

/* REQUESTED DATA STRUCTS */
type PlayerCoords struct { // recieved data
	SessToken string `json:"sess_token"`
	Coords    []int  `json:"coords"`
	ID        uint   `json:"id"`
}

type ChunkCoords struct { // sent back
	SessToken   string  `json:"sess_token"`
	ChunkCoords [][]int `json:"chunk_coords"`
}

/* RESPONSE DATA STRUCTS */

type ListPlayers struct {
	Players []players.Player `json:"players"`
}
