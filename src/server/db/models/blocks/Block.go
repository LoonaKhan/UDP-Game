package blocks

import (
	"gorm.io/gorm"
	gv "server/globvars"
)

var biomeColours = map[string]byte{
	"Lake":     0,
	"Beach":    1,
	"Plains":   2,
	"Forest":   3,
	"Mountain": 4,
}

var biomeHeights = map[string]byte{
	"Lake":     0,
	"Beach":    0,
	"Plains":   1,
	"Forest":   1,
	"Mountain": 5,
}

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
	b.Noise = gv.P.Noise2D(
		((x*gv.CHUNK_SIZE)+float64(b.X))/10,
		((y*gv.CHUNK_SIZE)+float64(b.Y))/10,
	)
}

func (b *Block) genColour() {
	// generates a colour based on the block's noise and the seed
	// todo, implement the algo

	var colour byte

	noise := gv.P.Noise2D(b.Noise, gv.SEED) * 1000 // ranges from [-1000, 1000]

	// based on noise, assign a base value
	if noise >= -1000 && noise < -600 {
		colour = biomeColours["Lake"]
	} else if noise >= -600 && noise < -200 {
		colour = biomeColours["Beach"]
	} else if noise >= -200 && noise < 200 {
		colour = biomeColours["Plains"]
	} else if noise >= 200 && noise < 600 {
		colour = biomeColours["Forest"]
	} else if noise >= 600 && noise <= 1000 {
		colour = biomeColours["Mountain"]
	}

	// finetune the value with another noise value

	// convert noise to a colour
	b.Colour = colour
}

func (b *Block) genHeight() {
	// generates a height based on the block's noise and seed
	// todo: later, this just determines the texture?

	noise := gv.P.Noise2D(b.Noise, gv.SEED)
	if noise >= -1000 && noise < -600 {
		b.Height = biomeHeights["Lake"]
	} else if noise >= -600 && noise < -200 {
		b.Height = biomeHeights["Beach"]
	} else if noise >= -200 && noise < 200 {
		b.Height = biomeHeights["Plains"]
	} else if noise >= 200 && noise < 600 {
		b.Height = biomeHeights["Forest"]
	} else if noise >= 600 && noise <= 1000 {
		b.Height = biomeHeights["Mountain"]
	}

	// finetunes the value afterward
}
