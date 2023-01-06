package blocks

import (
	"gorm.io/gorm"
)

type Block struct {
	gorm.Model

	// these coords are relative to their chunk
	X int `json:"x"`
	Y int `json:"y"`

	ChunkID uint `json:"chunkID"` // the chunk they belong to

	// determined by perlin noise on the client
	Colour int `json:"colour"`
	Height int `json:"height"`
}
