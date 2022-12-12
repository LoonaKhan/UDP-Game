package blocks

import "server/db/models/chunks"

type Block struct {
	// these coords are relative to their block
	X int
	Y int

	Chunk *chunks.Chunk // the chunk they belong to

	// determined by perlin noise on the client
	Colour int
	Height int
}
