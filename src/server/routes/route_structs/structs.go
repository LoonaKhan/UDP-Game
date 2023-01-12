package route_structs

import (
	"server/db/models/chunks"
	"server/db/models/players"
)

type PlayerCoords struct { // player coords recieved to update pos, get chunks etc
	Coords []int `json:"coords"`
}

type ListPlayers struct { // lists all players online to a client
	Players []players.Player `json:"players"`
}

type ChunkSpan struct { // span of chunks sent back
	Chunks []chunks.Chunk `json:"chunks"`
	TL     [2]int         `json:"top-left"`
	BR     [2]int         `json:"bottom-right"`
}

type Response struct { // generic responses. error messages or messages
	Msg string `json:"msg"`
	Err string `json:"err"`
}

type PlayerID struct { // used for responding to login requests
	Id uint `json:"id"`
}

type UpdatedChunk struct { // used by chunk update requests
	Chunk chunks.Chunk `json:"chunk"`
}

type Header struct { // our header that is placed on every request and response
	Method string `json:"method"` // the method we are calling
	Cred   uint   `json:"cred"`   // the client's player they are logged into
	Code   bool   `json:"code"`   // pass/fail status code
}
