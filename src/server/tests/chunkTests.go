package main

import (
	"fmt"
	b "server/db/models/blocks"
	c "server/db/models/chunks"
)

var pos = []int{0, 0}

func blockInitTest() {
	block := b.Init(1, 1, 1, 1)
	fmt.Printf("Block: [%d, %d],\n"+
		"Noise: %f\n"+
		"Colour: %d, Height: %d\n",
		block.X, block.Y, block.Noise, block.Colour, block.Height)
}

func chunkInitTest() {
	var avg, high, low float64 = 0, 0, 0
	var noises []float64

	chunk := c.Init(1, 1)
	fmt.Printf("Chunk: [%d, %d]\n", chunk.X, chunk.Y)
	for i := range chunk.Blocks {
		fmt.Printf("Block: [%d, %d],\n"+
			"Noise: %f\n"+
			"Colour: %d, Height: %d\n",
			chunk.Blocks[i].X, chunk.Blocks[i].Y, chunk.Blocks[i].Noise, chunk.Blocks[i].Colour, chunk.Blocks[i].Height)
		avg += chunk.Blocks[i].Noise
		noises = append(noises, chunk.Blocks[i].Noise)
		if chunk.Blocks[i].Noise > high {
			high = chunk.Blocks[i].Noise
		}
		if chunk.Blocks[i].Noise < low {
			low = chunk.Blocks[i].Noise
		}
	}

	avg /= float64(len(chunk.Blocks))
	fmt.Printf("high: %f, low: %f, avg: %f", high, low, avg)

}

func main() {
	/*chunkCoords := chunks.ToChunkCoords(pos)
	fmt.Printf("Chunk coords: %d, %d\n", chunkCoords[0], chunkCoords[1])

	fmt.Println("Render distance: ")
	renderDist := chunks.ChunksInRenderDist(chunkCoords)
	for i := range renderDist {
		fmt.Printf("In render dist: %d, %d\n", renderDist[i][0], renderDist[i][1])
	}*/

	chunkInitTest()

}
