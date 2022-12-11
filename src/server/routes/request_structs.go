package routes

type PlayerCoords struct { // recieved
	SessToken string `json:"sess_token"`
	Coords    []int  `json:"coords"`
}

type ChunkCoords struct { // sent back
	SessToken   string  `json:"sess_token"`
	ChunkCoords [][]int `json:"chunk_coords"`
}
