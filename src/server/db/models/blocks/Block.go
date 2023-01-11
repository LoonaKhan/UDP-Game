package blocks

import (
	"gorm.io/gorm"
	gv "server/globvars"
)

type Block struct {
	gorm.Model

	// these coords are relative to their chunk
	X byte `json:"x"`
	Y byte `json:"y"`

	// determined by perlin noise on the client
	Colour byte `json:"colour"` //todo: this needs to be 3 bytes. unsigned
	Height byte `json:"height"`

	Noise float64 // the perlin noise value of the block. we use it to determine other things

	ChunkID uint `json:"chunkID"` // the chunk they belong to todo: remove the json tag
}

func Init(x byte, y byte, cx, cy float64) Block {
	/*
		Initializes a block.
		assigns the X and Y to the block's coordinates, and uses the chunk coordinates for the noise generation
	*/
	b := Block{X: x, Y: y}

	// generates the blocks noise and noise-related properties
	b.genNoise(cx, cy)
	b.genColour()
	b.genHeight()

	return b
}

func (b *Block) genNoise(x, y float64) {
	b.Noise = gv.P.Noise2D((x+float64(b.X))/10, (y+float64(b.Y))/10)
}

func (b *Block) genColour() {
	// generates a colour based on the block's noise and the seed
	// todo, implement the algo

	//_ = gv.P.Noise2D(b.Noise, gv.SEED)

	// convert noise to a colour
	b.Colour = 1
}

func (b *Block) genHeight() {
	// generates a height based on the block's noise and seed

	//_ = gv.P.Noise2D(b.Noise, gv.SEED)

	b.Height = 1
}
