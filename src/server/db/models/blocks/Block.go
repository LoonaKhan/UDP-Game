package blocks

import (
	"gorm.io/gorm"
)

type Block struct {
	gorm.Model

	// these coords are relative to their block
	X int
	Y int

	ChunkID uint // the chunk they belong to

	// determined by perlin noise on the client
	Colour int
	Height int
}
