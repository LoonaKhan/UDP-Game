package main

import (
	"fmt"
	"server/models/chunks"
)

var pos = []int{0, 0}

func main() {
	chunkCoords := chunks.ToChunkCoords(pos)
	fmt.Printf("Chunk coords: %d, %d\n", chunkCoords[0], chunkCoords[1])

	fmt.Println("Render distance: ")
	renderDist := chunks.ChunksInRenderDist(chunkCoords)
	for i := range renderDist {
		fmt.Printf("In render dist: %d, %d\n", renderDist[i][0], renderDist[i][1])
	}
}