package blocks

import (
	"github.com/aquilax/go-perlin"
	"gorm.io/gorm"
)

type Block struct {
	gorm.Model

	// these coords are relative to their chunk
	X byte `json:"x"`
	Y byte `json:"y"`

	// determined by perlin noise on the client
	Colour byte `json:"colour"`
	Height byte `json:"height"`

	Noise float64 // the perlin noise value of the block. we use it to determine other things

	ChunkID uint `json:"chunkID"` // the chunk they belong to todo: remove the json tag
}

func genColour(b *Block, p *perlin.Perlin, x, y float64) {
	_ := p.Noise2D(x, y)

	// convert noise to
}
